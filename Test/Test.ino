#define sensorCnt 12
#include <Servo.h>
#include <math.h>

  int nextCmd = 90;
Servo srv1;
float lineState[sensorCnt];
float weight[sensorCnt]={-45,-40,-35,-25,-15,-5,5,15,25,35,40,45};

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
   pinMode(A8, INPUT);
   pinMode(A9, INPUT);
   pinMode(A10, INPUT);
   pinMode(A11, INPUT);
   // define baudrate
   Serial.begin(9600);
}

void loop() {

  // read sensor

   for(unsigned short i=0; i<sensorCnt; i++) {
      lineState[i] = (analogRead(i)>=500) ? 1 : 0;
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
  /*
  float total = 0;
  float count = 0;
  for(int i=0; i<sensorCnt; ++i) {
    if(analogRead(i)>450)
    {
    total = total + (analogRead(i)-450)*weight[i];
    count = count + analogRead(i)-450;
    }
  }
  if (count !=0 )
  {
    nextCmd = 90 + total/count;
  }
  */


  // write cmd
   srv1.write(nextCmd+offset);


   // for debug
   //Serial.print("\tDesired angle: ");
   Serial.println(nextCmd);
   //Serial.println(total);
  // unsigned long   time = millis();
   //Serial.println(time);
}






