#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h> // for sleep()

// Simulation parameters
#define DT 1.0           // Time step (seconds)
#define TOTAL_TIME 300   // Total simulation time (seconds)

void morning_temp(double *temp){
    double min = -0.5, max = 1;
    double temp_change = min + ((double)arc4random() / UINT32_MAX) * (max - min); // choose random value between -0.5 to 1
 
    *temp = *temp + temp_change;
    
}

void even_temp(double *temp){
    double min = -1, max = 0.5;
    double temp_change = min + ((double)arc4random() / UINT32_MAX) * (max - min);
 
    *temp = *temp + temp_change;
    
}

void people_in_room(double *temp, int t) {
    if (t >= 60 && t <= 240) {
        int people = 5;
        double heat = people * 0.01;
        *temp += heat;
    }
}

void equipment_heat(double *temp) {
    *temp += 0.05;
}


void event_disturbances(double *temp, int t) {
    if (t % 100 == 0 && t != 0) {
        printf("🔁 Window opened\n");
        *temp -= 1.5;
    }
    if (t == 180) {
        printf("👥 Big meeting!\n");
        *temp += 2.0;
    }
}

void PID_pid(double previous_error, double error, double* error_sum, double* u, double Kp, double Ki, double Kd) {
    *error_sum += error * DT; // Integrate error over time
    
    //error = (target_temp - room_temp)
    //when error + , heater should turn on
    //when error - , AC should turn on
    
    double P = Kp * error;
    double I = Ki * (*error_sum);
    double D = Kd * (error - previous_error) / DT;

    *u = P + I + D;
}


int main(){
    
    FILE *fp = fopen("temperature_.csv", "w");
    if (fp == NULL) {
        printf("File open error\n");
        return 1;
    }
    
    fprintf(fp, "Time(s),Temperature(°C)\n"); // CSV header
    
    double ambient_temp = 25.0;

    
    double min = 0.0, max = 10.0; // morning
    
    double room_temp = min + ((double)arc4random() / UINT32_MAX) * (max - min);
    
    double low_temp = 25.0;   // low range (°C)

    double high_temp = 20.0;   // high range (°C)

    
    double target_temp = 22.0;   // Target temperature (°C)
    
    double error = 0;

    double Kp = 20;
    double u;
    
    double previous_error = 0;
    double Kd = 2; //0.6
    
    //I part
    double error_sum = 0.0; // Initialize once at the top
    double Ki = 0.5; //0.2
    
    double heater_power = 0.0;
    double AC_power = 0.0;

   
    for(int t=0;t<TOTAL_TIME;t+=DT){
        if(t<150){
            morning_temp(&room_temp);
        }
        else{
            even_temp(&room_temp);
        }
        
        // Realism features
        people_in_room(&room_temp, t);
        equipment_heat(&room_temp);
        event_disturbances(&room_temp, t);
        
        //PID
        error = target_temp - room_temp;
        
        PID_pid(previous_error, error, &error_sum, &u, Kp, Ki, Kd);
        previous_error = error;
        
        //Adjusting the AC/Heater
        //Heater adds 2 degree every 3 second
        double heater_rate = 2.0/3.0;
        
        //AC reduces 2 degree every 3 second
        double AC_rate = 2.0/3.0;
        
        if (u > 100) u = 100;
        if (u < -100) u = -100;
        
        printf("u = %.2f\n",u);
        
        if(u>=0){
            heater_power = (u/100.0)*heater_rate;
            AC_power = 0.0;
        }
        else{
            AC_power = (-u/100.0)*AC_rate;
            heater_power = 0.0;
        }

        room_temp = room_temp + (heater_power-AC_power)*DT;

        
        
        printf("After: Time: %03d sec, Temp: %.2f°C\n", t, room_temp);
        fprintf(fp, "%d,%.2f,%.2f,%.2f\n", t, room_temp, low_temp, high_temp); // ✅ correct CSV line
        
        usleep(1000); // Wait 0.1 second (100 ms)

    }

    fclose(fp); // ✅ Done only once

    
    return 0;
}
