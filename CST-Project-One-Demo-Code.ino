#include <Servo.h>
#include <Stepper.h>

#define STEPS 180
int pos = 0;
int buttonState = 0;
bool runMotors = false;
Servo servo_7;
Stepper stepper(STEPS, 8, 10, 9, 11);

//stuff for button pressing
//these are arbitrary values, used for demonstration
int servoSettings [] = {0, 15, 55, 35, 10, 50};
int stepperSettings [] = {0, 300, 150, 450, 0, 0};
int iterator = 0;
bool isReset = false;

void setup()
{
  stepper.setSpeed(50);
  servo_7.attach(7, 500, 2500);
}

void loop()
{
  buttonState= digitalRead(2);
  if(buttonState == HIGH){
      runMotors = true;
  }
  delay(30);
  if (runMotors){

    if (isReset) {
      //servo control
      for (pos = servoSettings[iterator]; pos >= 0; pos =pos - 1){
        servo_7.write(pos);
        delay(15);
      }

      //stepper control
      for (int i = stepperSettings[iterator]; i >= 0; i = i - 1){
        stepper.step(-1);
        delay(15);
      }

      //move to next step
      iterator++;
      isReset = false;
    } else {
      //servo control
      for (pos = 0; pos <= servoSettings[iterator]; pos += 1){
        servo_7.write(pos);
        delay(15);
      }

      //stepper control
      for (int i = 0; i < stepperSettings[iterator]; i++){
        stepper.step(1);
        delay(15);
      }

      //move to next step
      isReset = true;
    }
    if(iterator > 5){
      iterator = 0;
    }
    
    delay(150);
  }
  runMotors = false;
}
