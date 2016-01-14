#define sensorCnt 8
#include <Servo.h>
#include <math.h>

Servo srv1;
boolean lineState[sensorCnt];
float weight[sensorCnt]={-30,-22.5,-14,-5,5,14,22.5,30};

int nextCmd = 90;
int currentCmd = 90;
const int increase = 20;

// the original position of the servo is not perfectly 90 degree
int offset = -5;

void setup() {
   // define servo
   srv1.attach(9);
   srv1.write(90);

   // define input pins from line sensor
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(A2, INPUT);
   pinMode(A3, INPUT);
   pinMode(A4, INPUT);
   pinMode(A5, INPUT);
   pinMode(A6, INPUT);
   pinMode(A7, INPUT);

   // define baudrate
   Serial.begin(9600);
}

void loop() {

  // read sensor
   for(unsigned short i=0; i<sensorCnt; i++) {
      lineState[i] = (analogRead(i)<=550) ? 1 : 0;
   }
   
   // calculate the position of white line
  int total = 0;
  int count = 0;
  for(int i=0; i<sensorCnt; ++i) {
    total = total + lineState[i]*weight[i];
    count = count + lineState[i];
  }
  if (count != 0)
  {
    nextCmd = 90 + total/count;
  }

  //Change step by step
  if (nextCmd > currentCmd + increase)
  {
    currentCmd = currentCmd + increase;
  }
  if ((nextCmd <= currentCmd + increase) && (nextCmd >= currentCmd - increase))
  {
    currentCmd = nextCmd;
  }
  if (nextCmd < currentCmd - increase)
  {
    currentCmd = currentCmd - increase;
  }

  // write cmd
   srv1.write(currentCmd+offset);

   // for debug
   Serial.print("\tDesired angle: ");
   Serial.println(currentCmd+offset);
   unsigned long   time = millis();
   Serial.println(time);
}






