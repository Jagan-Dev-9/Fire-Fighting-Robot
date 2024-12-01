#include <Servo.h>  // Include the Servo library

// Pin definitions
#define enA 5    // Motor driver pin for enabling left motor
#define in1 6    // Motor driver pin for left motor direction 1
#define in2 7    // Motor driver pin for left motor direction 2
#define in3 8    // Motor driver pin for right motor direction 1
#define in4 9    // Motor driver pin for right motor direction 2
#define enB 10   // Motor driver pin for enabling right motor
#define ir_L A2  // Left sensor connected to A2
#define ir_F A1  // Front (middle) sensor connected to A1
#define ir_R A0  // Right sensor connected to A0
#define pump A5  // Water pump connected to A5

int Speed = 160; // Motor speed
int s1, s2, s3;  // Sensor values

// Create a Servo object
Servo fireServo;

// Flame detection thresholds
int closeThreshold = 400; // Adjusted to stop further from the flame
int flameDetectedThreshold = 350; // Detection value for flame

void setup() {
    Serial.begin(9600); // Start serial communication at 9600bps

    // Pin setup for fire sensors
    pinMode(ir_L, INPUT); // Left sensor
    pinMode(ir_F, INPUT); // Front (middle) sensor
    pinMode(ir_R, INPUT); // Right sensor

    // Pin setup for motor driver
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);

    // Pin setup for pump
    pinMode(pump, OUTPUT);

    // Attach the servo to pin A4
    fireServo.attach(A4);

    // Move servo to default position
    fireServo.write(90);

    // Set initial motor speed
    analogWrite(enA, Speed);
    analogWrite(enB, Speed);
    delay(500);
}

void loop() {
    // Read sensor values
    s1 = analogRead(ir_L);  // Left sensor
    s2 = analogRead(ir_F);  // Front sensor
    s3 = analogRead(ir_R);  // Right sensor

    // Debugging: Print sensor values to check detection
    Serial.print("Left Sensor: ");
    Serial.print(s1);
    Serial.print("\tMiddle Sensor: ");
    Serial.print(s2);
    Serial.print("\tRight Sensor: ");
    Serial.println(s3);
    delay(50);

    // Flame detection and response
    if (s2 < flameDetectedThreshold) {
        Serial.println("Flame detected in the MIDDLE.");
        if (s2 > closeThreshold) {
            Serial.println("Approaching the flame - Moving FORWARD.");
            forword();
        } else {
            Serial.println("Close to the flame - Stopping.");
            Stop();
            operatePumpAndServo();
        }
    } 
    else if (s1 < flameDetectedThreshold) {
        Serial.println("Flame detected on the LEFT - Adjusting.");
        Stop();
        turnLeft();
        delay(500);  // Adjust this delay for better turning
    } 
    else if (s3 < flameDetectedThreshold) {
        Serial.println("Flame detected on the RIGHT - Adjusting.");
        Stop();
        turnRight();
        delay(500);  // Adjust this delay for better turning
    } 
    else {
        Serial.println("No flame detected - Stopping.");
        Stop();
    }

    delay(10);
}

// Movement functions with debugging
void forword() {
    Serial.println("Moving FORWARD.");
    digitalWrite(in1, HIGH); // Right Motor forward
    digitalWrite(in2, LOW);  // Right Motor backward
    digitalWrite(in3, LOW);  // Left Motor backward
    digitalWrite(in4, HIGH); // Left Motor forward
}

void backword() {
    Serial.println("Moving BACKWARD.");
    digitalWrite(in1, LOW);  // Right Motor forward
    digitalWrite(in2, HIGH); // Right Motor backward
    digitalWrite(in3, HIGH); // Left Motor backward
    digitalWrite(in4, LOW);  // Left Motor forward
}

void turnRight() {
    Serial.println("Turning RIGHT.");
    digitalWrite(in1, LOW);  // Right Motor forward
    digitalWrite(in2, HIGH); // Right Motor backward
    digitalWrite(in3, LOW);  // Left Motor backward
    digitalWrite(in4, HIGH); // Left Motor forward
}

void turnLeft() {
    Serial.println("Turning LEFT.");
    digitalWrite(in1, HIGH); // Right Motor forward
    digitalWrite(in2, LOW);  // Right Motor backward
    digitalWrite(in3, HIGH); // Left Motor backward
    digitalWrite(in4, LOW);  // Left Motor forward
}

void Stop() {
    Serial.println("Stopping.");
    digitalWrite(in1, LOW);  // Right Motor forward
    digitalWrite(in2, LOW);  // Right Motor backward
    digitalWrite(in3, LOW);  // Left Motor backward
    digitalWrite(in4, LOW);  // Left Motor forward
}

void operatePumpAndServo() {
    Serial.println("Activating water pump and moving servo...");
    
    // Turn on the water pump
    digitalWrite(pump, HIGH);

    // Move servo to the 3 positions
    fireServo.write(40);  // Move to 40 degrees
    delay(500);           // Wait for the servo to move
    fireServo.write(90);  // Move to 90 degrees
    delay(500);           // Wait for the servo to move
    fireServo.write(120); // Move to 120 degrees
    delay(500);           // Wait for the servo to move
    fireServo.write(90);  // Return to 90 degrees (default position)
    delay(500);

    // Keep the pump running while checking the fire status
    while (analogRead(ir_F) < flameDetectedThreshold) {
        delay(50);
    }

    // Turn off the water pump
    digitalWrite(pump, LOW);
    Serial.println("Water pump deactivated, servo reset to 90 degrees.");
}
