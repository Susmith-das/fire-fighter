#include <Servo.h>
Servo myservo;
 
int pos = 0;    
boolean fire = false;

#define Left_S 9      // left sensor
#define Right_S 10      // right sensor
#define Forward_S 8 //forward sensor
#define LMB 2       // left motor Bw-C2A
#define LMF 3       // left motor FW-C2B
#define RMF 4       // right motor FW-C1A
#define RMB 5       // right motor BW-C1B
#define pump 6

void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LMF, OUTPUT);
  pinMode(LMB, OUTPUT);
  pinMode(RMF, OUTPUT);
  pinMode(RMB, OUTPUT);
  pinMode(pump, OUTPUT);
 
  myservo.attach(11);
  
 Serial.begin(9600);
}

void put_off_fire()
{
    delay (500);
 
    digitalWrite(LMF,LOW);
    digitalWrite(LMB,LOW);
    digitalWrite(RMF,LOW);
    digitalWrite(RMB, LOW);
    digitalWrite(pump, HIGH); 
    
    delay(500);
    
    for (pos = 50; pos <= 130; pos++)
    { 
    myservo.write(pos); 
    delay(10);  
    } 
   for (pos = 130; pos >= 50; pos--) 
    { 
    myservo.write(pos); 
    delay(10);
    }
  
  digitalWrite(pump,LOW);
  myservo.write(90);
  
  fire=false;
}

void loop()
{
   if (digitalRead(Left_S) ==1 && digitalRead(Right_S)==1 && digitalRead(Forward_S) ==1) //If Fire not detected all sensors are zero
    {
    //Do not move the robot
    digitalWrite(LMF,LOW);
    digitalWrite(LMB,LOW);
    digitalWrite(RMF,LOW);
    digitalWrite(RMB,LOW);
    }
    
    else if (digitalRead(Forward_S) ==0) //If Fire is straight ahead
    {
    //Move the robot forward
    digitalWrite(LMF,HIGH);
    digitalWrite(LMB,LOW);
    digitalWrite(RMF,HIGH);
    digitalWrite(RMB,LOW); 
    fire = true;
    
    }
    
    else if (digitalRead(Left_S) ==0) //If Fire is to the left
    {
    //Move the robot left
    digitalWrite(LMF,LOW);
    digitalWrite(LMB,LOW);
    digitalWrite(RMF,HIGH);
    digitalWrite(RMB,LOW);
    }
    
    else if (digitalRead(Right_S) ==0) //If Fire is to the right
    {
    //Move the robot right
    digitalWrite(LMF,HIGH);
    digitalWrite(LMB,LOW);
    digitalWrite(RMF,LOW);
    digitalWrite(RMB,LOW);
    }

    delay(300); //Slow down the speed of robot
 
     while (fire == true)
     {
      put_off_fire();
     }

}
