#include <ezButton.h>
#include <AccelStepper.h>

ezButton button1(9);
ezButton button2(11);
ezButton button3(13);
ezButton button4(1);

#define DEG_PER_STEP 1.8
#define STEP_PER_REVOLUTION (360 / DEG_PER_STEP)
AccelStepper stepper(AccelStepper::FULL4WIRE, 7, 6, 5, 4);
const int steps_per_rev = 200;

int oldb1,newb1,oldb2,newb2,oldb3,newb3,oldb4,newb4;
int mode;
bool on = false;
bool b1toggled,b2toggled,b3toggled,b4toggled;
bool interrupt;
bool strobe = false;

void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(50);
  button2.setDebounceTime(50);
  button3.setDebounceTime(50);
  button4.setDebounceTime(50);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(0,OUTPUT);
  stepper.setCurrentPosition(0);
}
void togglesensing(){
  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  oldb1 = newb1, oldb2 = newb2, oldb3 = newb3, oldb4 = newb4;
  newb1 = button1.isPressed(), newb2 = button2.isPressed(), newb3 = button3.isPressed(), newb4 = button4.isPressed();
  b1toggled = (oldb1 == true && newb1 == false); 
  b2toggled = (oldb2 == true && newb2 == false);
  b3toggled = (oldb3 == true && newb3 == false);
  b4toggled = (oldb4 == true && newb4 == false);
  interrupt = (on && b4toggled);
  if (interrupt){
    digitalWrite(0,LOW);
  }
}
void moveThe17HS19_2004S1StepperMotorAxleBackAndForthInAZigZagMotionPeriodicallyAndContinuouslySoThatWavesMayBeGeneratedFromThisMotionForTheWaveTankToFunctionHopefullyInTheWorkshop(int speed,int distance){
  while (interrupt == false){
   stepper.setMaxSpeed(speed);
   stepper.setAcceleration(speed);

   stepper.moveTo(distance);
   while (stepper.currentPosition() != distance && interrupt == false){
     togglesensing();
     stepper.run();
   }
   stepper.stop(); // Stop as fast as possible: sets new target
   stepper.runToPosition(); 
   stepper.moveTo(0);
   while (stepper.currentPosition() != 0 && interrupt == false){ 
     togglesensing();
     stepper.run();
   }
   stepper.stop(); // Stop as fast as possible: sets new target
   stepper.runToPosition();
  }
}
void loop() {
  togglesensing();
  if (!on){
    digitalWrite(0,LOW);
  }
  if (b1toggled){
    mode = 1;
    digitalWrite(8,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(12,LOW);
  }
  if (b2toggled){
    mode = 2;
    digitalWrite(8,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(12,LOW);
  }
  if (b3toggled){
    mode = 3;
    digitalWrite(8,LOW);
    digitalWrite(10,LOW);
    digitalWrite(12,HIGH);
  }
  if (b4toggled){
    on = !on;
    digitalWrite(1,on);
    if (on){
      b4toggled == false;
      if (mode == 1){
        moveThe17HS19_2004S1StepperMotorAxleBackAndForthInAZigZagMotionPeriodicallyAndContinuouslySoThatWavesMayBeGeneratedFromThisMotionForTheWaveTankToFunctionHopefullyInTheWorkshop(100,150);
      }
      if (mode == 2){
        moveThe17HS19_2004S1StepperMotorAxleBackAndForthInAZigZagMotionPeriodicallyAndContinuouslySoThatWavesMayBeGeneratedFromThisMotionForTheWaveTankToFunctionHopefullyInTheWorkshop(500,150);
      }
      if (mode == 3){
        moveThe17HS19_2004S1StepperMotorAxleBackAndForthInAZigZagMotionPeriodicallyAndContinuouslySoThatWavesMayBeGeneratedFromThisMotionForTheWaveTankToFunctionHopefullyInTheWorkshop(1000,150);
      }
    }
  }
}
