# AIM 
The aim of this project is to develop an IoT-enabled, automated flood monitoring and dam safety system using an ESP32 microcontroller, simulated via Wokwi and managed through the Blynk IoT platform. It aims to continuously measure water levels, provide local alert feedback using Blynk cloud and immediately send real-time alerts to prevent flooding disasters.

# PROBLEM STATEMENT
Simulate a flood monitoring system that

(a)continuously measures water flow levels at a dam.

(b) provides real-time alerts to authorities via the cloud when flow levels exceed a predefined threshold, indicating potential flooding risks.

# SCOPE OF THE SOLUTION 
1.Automated Sensing & Control: Continuous water level measurement using an ultrasonic sensor to automatically drive a dam gate (servo motor) and sound local buzzer alarms.
2.Local Monitoring: Visual output of live distance data and threat levels on a $16 \times 2$ I2C LCD screen.
3.Cloud Telemetry & Alerting: Real-time data logging to a Blynk IoT dashboard and immediate push notification alerts delivered to authorities during flood emergencies.
4.Virtual Prototype: A fully simulated, risk-free hardware environment running on an ESP32 via Wokwi.
5.Fail-Safe Mechanism: Automatic execution of emergency safety routines (gate opens, buzzer sounds) if a sensor failure occurs.

# REQUIRED COMPONENTS
#Simulation Components (Wokwi Hardware)
1 ESP32 Board: Microcontroller that processes data, manages Wi-Fi, and runs the control logic.
2 HC-SR04 Ultrasonic Sensor: Measures water level by tracking sound wave echoes.
3 Servo Motor: Simulates the physical opening and closing of the dam gate.
4 16x2 I2C LCD: Displays real-time water levels and system status on-site.
5 Piezo Buzzer: Sounds audible alarms (short beeps for warning, continuous for critical flood).
6 Virtual Wi-Fi (Wokwi-GUEST): Provides the internet gateway for the ESP32 inside the simulator.
#Cloud Components (Blynk IoT) 
1 Blynk Cloud Server: Securely manages the connection using your unique Template ID and Auth Token.
2 Virtual Pins ($V_0, V_1, V_2$): Data streams that send live water levels and status updates to the cloud.
3 Blynk Dashboard: The visual web/mobile interface used by authorities to monitor the dam remotely.
4 Blynk Webhook/Event Engine (logEvent): Triggers and sends instant mobile push notifications during critical flood emergencies.

# FLOW CHART OF CODDE 
(provided)

 
