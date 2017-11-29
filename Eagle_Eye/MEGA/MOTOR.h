/**
 * MOTOR.h holds the code to operate the turbofans.
 */

 
#ifndef MOTOR_h
#define MOTOR_h

#include <Arduino.h>
#include <Servo.h>

class MOTOR
{
  public:
  
  //Constructor
  MOTOR();
  
  //Runs initialzation script for the TurboFans.
  void initialize();

  //Based on the input given to the craft. This function calulates the desired
  //   PDM pulse width to send to the motor.
  void manager();

  //Rotates the servos back the original positon of all facing forward.
  void rotateLevel();
  
  //Moves the servos in coordination to rotate the craft right.
  void rotateRight();

  //Moves the servos in coordination to rotate the craft left.
  void rotateLeft();

  //Compares the current throttle status to the "desired" throttle.
  //Increments the PDM signal if the craft needs to throttle up.
  void spinUp();

  //Compares the current throttle status to the "desired" throttle.
  //   Decrements the PDM signal if the craft needs to throttle down.
  void spinDown();

  //Writes a PDM Waveform that is below the cutoff. This takes the throttle to
  //   an instant 0%.
  void applyBreak();
  
  //Connection pins from Arduino MEGA to their respective ESC's.
  //   The craft has four motors, but we can get away with only 
  //   simulating one motor due to them otherwise being parallel
  //   tasks and taking up memory.
  #define MOTOR_PIN 36
  
  //Connection pins from the Arduino MEGA to the servos. 
  //   Like stated above for the turbofans, we have four 
  //   physical serovs on the craft, but only need to 
  //   simulate two due to their being two pairs acting
  //   together.
  #define SERVO_PIN1 42    
  #define SERVO_PIN2 44

  //Specific amount alter the PWM waveform between each pulse. 
  //   This ensures that each increment or decrement is suttle
  //   and therefore does not burn the motors out.
  #define INCREMENT_AMOUNT 10
  
  //Specific delay between increments in speed changes (pulses).
  #define INCREMENT_DELAY 320    

  //Creates a Servo object
  Servo motor;
  
  //Creates a Servo object
  Servo servoRight; 
  Servo servoLeft;  

  //Throttle value current being sent to the craft.
  int currentThrottle = 900;
  
  //Throttle value that has been calculated. This is the desired
  //   value that currentThrottle will compare itself to and 
  //   iterate toward.
  double throttle = 900;
  
  //This is a fraction.
  double fraction = 0;
  
  //This variables it the desired throttle percentage value that 
  //   takes takes in a "percentage (0-100)" and calculates the 
  //   appropriate PWM waveform. 
  int input = 0;
  
  //The initalization setting for the servos.
  int pos = 90; 
  
  //Used in rotating the servos. (designed to be exact opposite of pos)
  int opp = 90; 
  
  //If true, will trigger the motors to orient themselves to rotate the craft right.
  bool turnRight = true;
  
  //If true, will trigger the motors to orient themselves to rotate the craft left.
  bool turnLeft = false;

  enum Orientation {NONE,RIGHT,LEFT,FORWARD,UP,DOWN};
  enum Orientation state = NONE;
  
};

#endif

