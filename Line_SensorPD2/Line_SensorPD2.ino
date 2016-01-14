#define sensorCnt 8
#include <Servo.h>
#include <math.h>

Servo srv1;
boolean lineState[sensorCnt];
float weight[sensorCnt]={-35,-25,-15,-5,5,15,25,35};
int offset = -5;
int nextCmd = 90;
int currentCmd = 90;
int dcount = 0;
const int dloop = 5;
int d = 0;
const int LEFTCOUNT = 6;
int isleftcount = LEFTCOUNT;


const int MODE_START = 0;
const int MODE_SEARCH_90_DEGREE = 1;
const int MODE_TURN = 2;
const int MODE_ZIGZAG = 3;
int current_mode = MODE_START;
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
   pinMode(A11, INPUT);
   Serial.begin(9600);
   //for(int i=0; i<sensorCnt; ++i)lineSensorMean[i] = 0;
}

void loop() {

  //declares
  float total = 0;
  int count = 0;
  
  currentCmd = nextCmd;
  
//read sensor
  for(unsigned short i=0; i<sensorCnt; i++) {
      lineState[i] = (analogRead(i)<=550) ? 1 : 0;
   }
  int isleft = (analogRead(11)<=550) ? 1 : 0;


  switch(current_mode)
  {
    // at the begining, the sensor is close to the ground.
    // once the sensor could not detect the ground, we can change to next mode
    case MODE_START:
    {       
        if (isleft == 0)
        {
          isleftcount--;
        }
        else
        {
          isleftcount = LEFTCOUNT;
        }
        if(isleftcount == 0 )
        {
          isleftcount = LEFTCOUNT;
          current_mode = MODE_SEARCH_90_DEGREE;
        }
        for(int i=0; i<sensorCnt; ++i) {
          total = total + lineState[i]*weight[i];
          count = count + lineState[i];
        }
       
      break;
    }

    //Now we are searching for the bridge, so that we can turn.
    case MODE_SEARCH_90_DEGREE:
    {
        if (isleft == 1)
        {
          isleftcount--;
        }
        else
        {
          isleftcount = LEFTCOUNT;
        }
        if(isleftcount == 0 )
        {
          isleftcount = LEFTCOUNT;
          current_mode = MODE_TURN;
        }
        for(int i=0; i<sensorCnt; ++i) {
          total = total + lineState[i]*weight[i];
          count = count + lineState[i];
        }
        break;
    }

    // Once we have found the bridge, we disable the sensors in the right part.
    case MODE_TURN:
    {
        if (isleft == 0)
        {
          isleftcount--;
        }
        else
        {
          isleftcount = LEFTCOUNT;
        }
        if(isleftcount == 0 )
        {
          isleftcount = LEFTCOUNT;
          current_mode = MODE_ZIGZAG;
        }
        for(int i=0; i<sensorCnt/2; ++i) {
          total = total + lineState[i]*weight[i];
          count = count + lineState[i];
        }
        break;
    }
    // after that we back to normal mode again.
    case MODE_ZIGZAG:
    default:
    {
         for(int i=0; i<sensorCnt; ++i) {
          total = total + lineState[i]*weight[i];
          count = count + lineState[i];
        }
        break;
    }
  }

  if (count != 0)
  {
    nextCmd = 90 + total/count;
  }

  if (nextCmd > currentCmd)
  {
    dcount = dloop;
    d = 5;
  }
  if (nextCmd < currentCmd)
  {
    dcount = dloop;
    d = -5;
  }
  if (nextCmd == currentCmd)
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

 srv1.write(nextCmd + d + offset);
 
 Serial.print("\tDesired angle: ");
 Serial.println(nextCmd + d);
 unsigned long time = millis();
 Serial.println(time);
 Serial.println(isleft);
 
}






