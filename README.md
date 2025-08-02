# # 🌡️ Temperature Sensor PID Simulation

> “Control is just this question: *How do I change something so that it behaves the way I want?”*

This project simulates the behaviour of a temperature control system using a **PID controller**. It models how a physical system — in this case, a temperature sensing heater — reacts to changes and adjusts itself to meet the desired temperature.

---

## 🧠 Project Concept

In real-world systems, change doesn’t happen instantly. Energy is stored and dissipated gradually, which means:

- Giving an input does **not result in immediate output change**
- The system has **inertia and lag**
- You need a **feedback mechanism** to steer the system toward your goal

This project models that lag using a simplified temperature simulation and a PID control loop to manage the heater power.

---

## 📈 System Behaviour

- **Current Temperature**: 5-10°C (Temperature of the office in the morning)
- **Heater Power**: +2°C every 3 seconds
- **AC Power **: -2°C every 3 seconds
- **Temperature Change**: From morning to evening temperature increases, however from evening to night, temperature starts dropping. Temperature varies
throughout the day, depending on the amount of people, windows left open and other situations that will vary the temperature.
- **Temperature Update Rule**:
Temp = Temp + (Heater Power - AC Power) * dt

## ⚙️ What the Controller Does

- The controller runs in a loop (e.g., a `for` loop).
- At each step:
- It calculates the **error** between the desired and current temperature.
- It uses a **PID algorithm** (Proportional, Integral, Derivative) to adjust the heater power.
- It updates the system using the equation above to simulate time passing.

---

## 🎯 Objectives / Requirements

- ✅ Investigate how the controller uses the **PID concept** to simulate temperature behavior.
- ✅ Write code to simulate model changes using `+= something * dt`.
- ✅ Monitor the error and adjust input accordingly.
- ✅ Learn how you can control **any physical system** using the same logic.

> **Note**: Coding this system is essentially like stepping through time, one moment at a time, updating the system as you go — just like nature.

---

## 📁 Files

- `main.c` – Contains the simulation logic and PID controller
- `README.md` – Project overview and instructions

---

## 📌 Final Thought

This simulation is a foundational step in understanding **control systems**. Whether you’re building a thermostat, a motor controller, or a drone stabilizer — it all starts with understanding feedback and the power of PID.

---


