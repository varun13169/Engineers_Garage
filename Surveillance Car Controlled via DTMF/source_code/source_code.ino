/*

m11 and m12 are for Left Motor and m21 and m22 are for Right Motor when viewing your car from the back.
To have forward motion set m11=m21=HIGH and m12=m22=LOW.

a,s,d,f defines four digits of Security PIN.
One can change it by changing their values in "Loop for Security PIN" section
Default PIN -> 1234

*/


#include <Servo.h> 

Servo myservo;
int servo=5;
int angle=180; // 180 is the initial angle and mobile phone should be placed with camera facing front

int d1=12;
int d2=11;
int d3=10;
int d4=9;
int st=8;
int vccdtmf=13;

int a=0,s=0,d=0,f=0,flag=0;

int m11=19;
int m12=18;
int m21=17;
int m22=16;

int p1=15;
int p2=14;



void setup()
{
  myservo.attach(5);     // Defines Pin 5 for Servo
  myservo.write(angle);
  
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);
  pinMode(d4,INPUT);
  pinMode(st,INPUT);
  pinMode(vccdtmf,OUTPUT);
  
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);
  
  pinMode(p1,OUTPUT);
  pinMode(p2,OUTPUT);
  
  pinMode(servo,OUTPUT);
}

void loop()
{
  digitalWrite(vccdtmf,HIGH); // +5V for DTMF Module
  digitalWrite(p1,HIGH);      // For Max. speed
  digitalWrite(p2,HIGH);      // For Max. speed
  
  
/////////////////////////////////////////////// Loop for Security PIN ///
  
  while(flag==0)
  {
    if(a!=1 && digitalRead(d1)==1 && digitalRead(d2)==0 && digitalRead(d3)==0 && digitalRead(d4)==0 && digitalRead(st)==1)
    {
      a=1;
    }
    if(a==1 && s!=2 && digitalRead(d1)==0 && digitalRead(d2)==1 && digitalRead(d3)==0 && digitalRead(d4)==0 && digitalRead(st)==1)
    {
      s=2;
    }
    if(s==2 && d!=3 && digitalRead(d1)==1 && digitalRead(d2)==1 && digitalRead(d3)==0 && digitalRead(d4)==0 && digitalRead(st)==1)
    {
      d=3;
    }
    if(d==3 && f!=4 && digitalRead(d1)==0 && digitalRead(d2)==0 && digitalRead(d3)==1 && digitalRead(d4)==0 && digitalRead(st)==1)
    {
      f=4;
    }
    if(a==1 && s==2 && d==3 && f==4)
    {
      flag=1;
    }
  }
  
/////////////////////////////////////////////////////////////////////////
  
  
///////////////////////////////////////// Movement of Car ///////////////
  
  while(digitalRead(st)==0)  // RESET the value when no valid tone is given
  {
    digitalWrite(m11,LOW);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,LOW);    
  }
  
  while(digitalRead(d1)==0 && digitalRead(d2)==1 && digitalRead(d3)==0 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 2 for Forward Direction
  {
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
  }
  
    
  while(digitalRead(d1)==1 && digitalRead(d2)==0 && digitalRead(d3)==0 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 1 for Right Forward Direction
  {
    digitalWrite(m11,HIGH);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,LOW);
  }
  
  while(digitalRead(d1)==1 && digitalRead(d2)==1 && digitalRead(d3)==0 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 3 for Left Forward Direction
  {
    digitalWrite(m11,LOW);
    digitalWrite(m12,LOW);
    digitalWrite(m21,HIGH);
    digitalWrite(m22,LOW);
  }
 
  while(digitalRead(d1)==1 && digitalRead(d2)==0 && digitalRead(d3)==1 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 5 for Backward Direction
  {
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
  }
 
  while(digitalRead(d1)==0 && digitalRead(d2)==0 && digitalRead(d3)==1 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 4 for Right Backward Direction
  {
    digitalWrite(m11,LOW);
    digitalWrite(m12,HIGH);
    digitalWrite(m21,LOW);
    digitalWrite(m22,LOW);
  }
 
  while(digitalRead(d1)==0 && digitalRead(d2)==1 && digitalRead(d3)==1 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 5 for Left Backward Direction
  {
    digitalWrite(m11,LOW);
    digitalWrite(m12,LOW);
    digitalWrite(m21,LOW);
    digitalWrite(m22,HIGH);
  }
 
/////////////////////////////////////////////////////////////////////////

 
////////////////////////////////////// Movement of Servo ////////////////

  if(digitalRead(d1)==1 && digitalRead(d2)==1 && digitalRead(d3)==1 && digitalRead(d4)==0 && digitalRead(st)==1) // Press 7 to turn servo in anti-clockwise direction
  {
    if(angle>0)
    {
      angle=angle-45;
      myservo.write(angle);
      delay(500);
    }
  }
  
  
  if(digitalRead(d1)==0 && digitalRead(d2)==0 && digitalRead(d3)==0 && digitalRead(d4)==1 && digitalRead(st)==1) // Press 8 to turn servo in clockwise direction
  {
    if(angle<180)
    {
      angle=angle+45;
      myservo.write(angle);
      delay(500);
    } 
  }
  
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////// You Have to Enter Password again ////

  while(digitalRead(d1)==1 && digitalRead(d2)==0 && digitalRead(d3)==1 && digitalRead(d4)==1 && digitalRead(st)==1) //Press A to reset the PIN
  {
    flag=1;
  }

/////////////////////////////////////////////////////////////////////////

}
/************ END *************/
