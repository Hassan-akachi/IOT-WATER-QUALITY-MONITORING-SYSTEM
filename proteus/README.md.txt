IoT Water Quality Monitoring System (Proteus Simulation)
This repository contains the Proteus ISIS Professional simulation files for an IoT-based water quality monitoring system. This simulation focuses on the hardware implementation and sensor interfacing aspects, complementing a separate MATLAB simulation for data analysis and visualization. The system monitors key water quality parameters (pH, TDS, Conductivity, and Turbidity) and provides real-time readings and alerts via a virtual terminal.

Features
Simulation of an Arduino-based water quality monitoring circuit.

Integration of simulated pH, TDS, Conductivity, and Turbidity sensors.

Real-time display of water quality parameters on a virtual terminal.

Visual and audible alerting (buzzer) when parameters exceed predefined thresholds.

Demonstrates basic sensor-to-microcontroller interfacing.

Components (Simulated in Proteus)
Arduino UNO (or compatible board): The central microcontroller.

pH Sensor: Simulated to provide analog pH readings.

TDS Module: Simulated to provide Total Dissolved Solids readings.

Conductivity Sensor: Simulated to provide electrical conductivity readings.

Turbidity Sensor: Custom library used for simulating turbidity levels.

Virtual Terminal: For displaying sensor data and status messages.

Buzzer: To indicate alert conditions.

Resistors, Capacitors, LEDs: Supporting components for the circuit.

Setup Instructions
To run this simulation, you will need Proteus ISIS Professional and a custom library for the Turbidity Sensor.

Install Proteus ISIS Professional: Ensure you have Proteus 8 (or newer) installed on your system.

Add Turbidity Sensor Library:
The standard Proteus library might not include a dedicated Turbidity Sensor. We use a custom library for this.

Download the Library: Visit Electronics Tree - Turbidity Sensor Proteus 8 Library and download the provided library files.

Installation Steps:

Extract the downloaded .zip file. You should find files like TURBIDITY SENSOR.IDX and TURBIDITY SENSOR.LIB.

Copy these files into your Proteus library folder. The typical path is C:\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\LIBRARY (or similar, depending on your Proteus version and installation path).

Restart Proteus ISIS Professional. You should now be able to search for and place the "TURBIDITY SENSOR" component in your schematic.

Arduino IDE:

You need the Arduino IDE installed to compile the Arduino sketch (.ino file) into a .hex file, which is then loaded into the simulated Arduino in Proteus.

Download the Arduino IDE from arduino.cc.

Prepare Arduino Code (.hex file):

Navigate to the src/arduino directory in this repository (assuming your Arduino code will be placed there).

Open the .ino file (e.g., water_quality_monitor.ino) with the Arduino IDE.

Go to Sketch > Export compiled Binary. This will generate a .hex file in the same directory as your .ino file.

Load .hex into Proteus:

Open the Proteus project file (.pdsprj) located in the proteus directory of this repository.

Double-click on the simulated Arduino board in the Proteus schematic.

In the properties window, locate the "Program File" field. Click the folder icon and browse to select the .hex file you generated in the previous step.

Click "OK" to apply the changes.

Circuit Design
The Proteus schematic (.pdsprj file) illustrates the connections:

Sensors: Simulated pH, TDS, Conductivity, and Turbidity sensors are connected to the analog input pins of the Arduino.

Buzzer: Connected to a digital output pin on the Arduino.

Virtual Terminal: Connected to the Arduino's serial communication pins (RX/TX).

Arduino Code
The Arduino sketch (src/arduino/water_quality_monitor.ino) is responsible for:

Reading analog values from the simulated sensors.

Converting raw sensor data into meaningful water quality units.

Applying predefined water quality thresholds (e.g., WHO or FEPA standards).

Triggering the buzzer and sending alert messages to the virtual terminal if thresholds are exceeded.

Periodically sending sensor readings to the virtual terminal.

(Note: The actual Arduino code file should be placed in the src/arduino directory.)

Running the Simulation
Open the Proteus project file (.pdsprj).

Ensure the .hex file is loaded into the Arduino as per the setup instructions.

Click the "Play" button (usually a green triangle at the bottom left) in Proteus to start the simulation.

Observe the output on the Virtual Terminal window that appears.

Results and Observations
Upon running the simulation, the virtual terminal will display real-time (simulated) readings for pH, TDS, Conductivity, and Turbidity. It will also indicate whether these values are within acceptable limits ("OK" or "Normal") or if they have breached a threshold. If a breach occurs, the simulated buzzer will activate, and an alert message will be shown on the terminal. This provides a visual and audible indication of water quality status, mimicking a real-world monitoring system's behavior.

References
Turbidity Sensor Proteus Library:

Electronics Tree - Turbidity Sensor Proteus 8 Library

pH Sensor Arduino Tutorial (Reference for conceptual understanding):

YouTube - pH Sensor With Arduino | How to use a pH Sensor With Arduino

TDS Sensor Arduino Tutorial (Reference for conceptual understanding):

YouTube - TDS Sensor with Arduino - Total Dissolved Solids | How to use a TDS Sensor with Arduino