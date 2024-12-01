# Fire Fighting Robot

An autonomous fire-fighting robot that uses sensors to detect fire and a water pump to extinguish it.

## Features
- Fire detection using multiple sensors
- Servo motor-controlled movement
- Water pump to extinguish the fire

## Hardware Requirements:
- Arduino Board (or compatible microcontroller)
- Servo Motor
- Fire Sensors (left, middle, right)
- Water Pump
- Motor Driver
- Power Supply for the motors and pump

## Software Requirements:
- Arduino IDE
- Libraries for servo motors and fire sensors

## Setup Instructions:

1. **Connect the hardware**:
   - Connect the fire sensors to pins A0, A1, and A2 on the Arduino.
   - Connect the servo motor to pin A4.
   - Connect the water pump to pin A5.
   - Connect the motor driver and other components according to the schematic.

2. **Install the software**:
   - Install the Arduino IDE and necessary libraries.
   - Upload the code to the Arduino using the Arduino IDE.

3. **Power on the system**:
   - Once powered on, the robot will detect fire and take action to extinguish it using the water pump.

## How to Use:

1. After the system is powered on and the code is uploaded, the robot will start moving and detecting fire.
2. It will activate the water pump when it detects fire and stop once the fire is extinguished.

## Contributing:

If you’d like to contribute to the project:
1. Fork the repository
2. Create a new branch for your feature or fix
3. Submit a pull request for review

## License:
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
