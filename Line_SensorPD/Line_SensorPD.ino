#define sensorCnt 8
#include <Servo.h>
#include <math.h>

Servo srv1;

boolean lineState[sensorCnt];
float weight[sensorCnt]={-35,-25,-15,-5,5,15,25,35};

// the original position of the servo is not perfectly 90 degree
int offset = -5;

// record the last cmd so that we can calculate the derivative term
int nextCmd = 90;
int previousCmd = 90;

// As we only have 8 sensor, the information we get is too little.
// we have to let the influence of the derivative term last for several loops.
int dcount = 0;
const int dloop = 3;

// change of the derivative term.
int d = 0;

void setup() {
  srv1.attach(9);
   srv1.write(90);
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(A2, INPUT);
   pinMode(A3, INPUT);
   pinMode(A4, INPUT);
   pinMode(A5, INPUT);
   pinMode(A6, INPUT);
   pinMode(A7, INPUT);
   Serial.begin(9600);
}

void loop() {

  // change last Cmd
  previousCmd = nextCmd;

  // calculate new cmd
  //read sensor
   for(unsigned short i=0; i<sensorCnt; i++) {
      lineState[i] = (analogRead(i)<=550) ? 1 : 0;
   }
  float total = 0;
  int count = 0;
  for(int i=0; i<sensorCnt; ++i) {
    total = total + lineState[i]*weight[i];
    count = count + lineState[i];
  }
  if (count != 0)
  {
    nextCmd = 90 + total/count;
  }

  //calculate the derevitive 
  if (nextCmd > previousCmd)
  {
    dcount = dloop;
    d = 5;
  }
  if (nextCmd < previousCmd)
  {
    dcount = dloop;
    d = -5;
  }
  if (nextCmd == previousCmd)
  {
    if (dcount > 0)
    {
      dcount--;
    }
    else
    {
      d = 0;
    }
  }

  // write cmd
   srv1.write(nextCmd + d + offset);
   
   // for debug
   Serial.print("\tDesired angle: ");
   Serial.print(nextCmd + d);
   unsigned long time = millis();
   Serial.println(time);
   Serial.println();
   
}






