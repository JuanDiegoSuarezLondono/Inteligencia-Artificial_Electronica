//***********************************************************************
// Matlab .fis to arduino C converter v2.0.0.29032014                              
// - Karthik Nadig, USA                                                  
// Please report bugs to: karthiknadig@gmail.com                         
//***********************************************************************

#include "fis_header.h"

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

#define leftMotor1  2
#define leftMotor2  4

#define rightMotor1 8
#define rightMotor2 7


char path[30] = {};
int pathLength;
int readLength;

// Number of inputs to the fuzzy inference system
const int fis_gcI = 5;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 1;
// Number of rules to the fuzzy inference system
const int fis_gcR = 31;

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

// Setup routine runs once when you press reset:
void setup()
{
   Serial.begin(2000000);
    // initialize the Analog pins for input.
    // Pin mode for Input: Fotodiodo_Izquierdo
    pinMode(0 , INPUT);
    // Pin mode for Input: Fotodiodo_MIzquierdo
    pinMode(1 , INPUT);
    // Pin mode for Input: Fotodiodo_MDerecho
    pinMode(2 , INPUT);
    // Pin mode for Input: Fotodiodo_Derecho
    pinMode(3 , INPUT);
    // Pin mode for Input: Fotofiofo_Meta
    pinMode(4 , INPUT);   

    // initialize the Analog pins for output.
    // Pin mode for Output: Linea
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  delay(1000);

}

// Loop routine runs over and over again forever:
void loop()
{

    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
    straight();
  if(g_fisOutput[0]<=10)  
  {
    straight();                                                                                      
  }
  
  else{                                                                                              
    leftHandWall();                                                                    
  }
    // Set output vlaue: Linea
}

void done()
{
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  replaystage=1;
  path[pathLength]='D';
  pathLength++;
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
 while((g_fisOutput[0]>30 && g_fisOutput[0]<=55) || (g_fisOutput[0]>80 && g_fisOutput[0]<=125) || (g_fisOutput[0]>150 && g_fisOutput[0]<=170))
 {
   delay(300);
      // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
 }
 delay(500);
  replay();
}


void turnLeft()
{    
     // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
        
  while(g_fisOutput[0]<=10 || (g_fisOutput[0]>30 && g_fisOutput[0]<=125) || g_fisOutput[0]>150)
  {
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  }
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
    
  while((g_fisOutput[0]>10 && g_fisOutput[0]<=30) || (g_fisOutput[0]>195 && g_fisOutput[0]<=220))
  {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  }
 
  if(replaystage==0)
  {
    path[pathLength]='L';
    pathLength++;
      if(path[pathLength-2]=='B')
      {
        shortPath();
      }
  }
}


void leftHandWall()
{  
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  
  if( (g_fisOutput[0]>100 && g_fisOutput[0]<=125) || (g_fisOutput[0]>80 && g_fisOutput[0]<=100))
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
    
    if((g_fisOutput[0]>30 && g_fisOutput[0]<=125) || (g_fisOutput[0]>150 && g_fisOutput[0]<=195))
    {
      done();
    }
    
    if(g_fisOutput[0]<=30)
    { 
      turnLeft();
    }
    
  }

  if((g_fisOutput[0]>30 && g_fisOutput[0]<=55) || (g_fisOutput[0]>80 && g_fisOutput[0]<=125) || (g_fisOutput[0]>150 && g_fisOutput[0]<=170))
  { 
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();

    if(g_fisOutput[0]<=30 )
      {
      turnLeft();
      }

     else if((g_fisOutput[0]>30 && g_fisOutput[0]<=125) || (g_fisOutput[0]>150 && g_fisOutput[0]<=195))
     {
      done();
    }
  }

  if((g_fisOutput[0]>55 && g_fisOutput[0]<=125) || (g_fisOutput[0]>170 && g_fisOutput[0]<=195))
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(30);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();

    if((g_fisOutput[0]>30 && g_fisOutput[0]<=55) || (g_fisOutput[0]>80 && g_fisOutput[0]<=125) || (g_fisOutput[0]>150 && g_fisOutput[0]<=170)) //sensor izquierda
    {
      delay(leapTime-30);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
          
      if(g_fisOutput[0]>80 && g_fisOutput[0]<=125)
      {
        done();
      }
      
      else{
        turnLeft();
        return;
      }
    }
    delay(leapTime-30);
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
    if(g_fisOutput[0]>10 && g_fisOutput[0]<=30)
    {
      turnRight();
      return;
    }

    path[pathLength]='S';
    pathLength++;
    if(path[pathLength-2]=='B')
     {
     shortPath();
     }
    straight();
  }
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
    
  if(g_fisOutput[0]>10 && g_fisOutput[0]<=30)
  {
    turnAround();
  }

}

void turnRight(){

    
  while(g_fisOutput[0]<=10 || (g_fisOutput[0]>30 && g_fisOutput[0]<=125) || (g_fisOutput[0]>150 && g_fisOutput[0]<=195) || g_fisOutput[0]>220)
  {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
        // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  }
   while((g_fisOutput[0]>10 && g_fisOutput[0]<=30) || (g_fisOutput[0]>195 && g_fisOutput[0]<=220) )
   {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
            // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  }
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();  
   while(g_fisOutput[0]>220 || (g_fisOutput[0]>10 && g_fisOutput[0]<=30))
   {
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
                // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  }
  
  if(replaystage==0)
  {
  path[pathLength]='R';
  pathLength++;
    if(path[pathLength-2]=='B')
    {
      shortPath();
    }
  }
 
}

void straight(){
  
    // Read Input: Fotodiodo_Izquierdo
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  if(g_fisOutput[0]>220)
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  if(g_fisOutput[0]>195 && g_fisOutput[0]<=220)
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(4);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  
}

void turnAround()
{
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime-50);
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
   while((g_fisOutput[0]>10 && g_fisOutput[0]<=30) || g_fisOutput[0]>220)
   {
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
  path[pathLength]='B';
  pathLength++;
  straight();
}


void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
}


void replay(){
    g_fisInput[0] = analogRead(0);
    // Read Input: Fotodiodo_MIzquierdo
    g_fisInput[1] = analogRead(1);
    // Read Input: Fotodiodo_MDerecho
    g_fisInput[2] = analogRead(2);
    // Read Input: Fotodiodo_Derecho
    g_fisInput[3] = analogRead(3);
    // Read Input: Fotofiofo_Meta
    g_fisInput[4] = analogRead(4);
    g_fisOutput[0] = 0;
    fis_evaluate();
  if((g_fisOutput[0]<=10) || (g_fisOutput[0]>10 && g_fisOutput[0]<=30)){
    straight();
  }
  else{
    if(path[readLength]=='D'){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
      replay();  
}

void endMotion(){
    delay(1400);
  endMotion();
}

  
//***********************************************************************
// Support functions for Fuzzy Inference System                          
//***********************************************************************
// Z-shaped Member Function
FIS_TYPE fis_zmf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1];
    FIS_TYPE m = ((a + b) / 2.0);
    FIS_TYPE t = (b - a);
    if (x <= a) return (FIS_TYPE) 1;
    if (x <= m)
    {
        t = (x - a) / t;
        return (FIS_TYPE) (1.0 - (2.0 * t * t));
    }
    if (x <= b)
    {
        t = (b - x) / t;
        return (FIS_TYPE) (1.0 - (2.0 * t * t));
    }
    return (FIS_TYPE) 0;
}


// S-Shaped membership function
FIS_TYPE fis_smf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1];
    FIS_TYPE m = ((a + b) / 2.0);
    FIS_TYPE t = (b - a);
    if (a >= b) return (FIS_TYPE) (x >= m);
    if (x <= a) return (FIS_TYPE) 0;
    if (x <= m)
    {
        t = (x - a) / t;
        return (FIS_TYPE) (2.0 * t * t);
    }
    if (x <= b)
    {
        t = (b - x) / t;
        return (FIS_TYPE) (1.0 - (2.0 * t * t));
    }
    return (FIS_TYPE) 1;
}

// Triangular Member Function
FIS_TYPE fis_trimf(FIS_TYPE x, FIS_TYPE* p)
{
    FIS_TYPE a = p[0], b = p[1], c = p[2];
    FIS_TYPE t1 = (x - a) / (b - a);
    FIS_TYPE t2 = (c - x) / (c - b);
    if ((a == b) && (b == c)) return (FIS_TYPE) (x == a);
    if (a == b) return (FIS_TYPE) (t2*(b <= x)*(x <= c));
    if (b == c) return (FIS_TYPE) (t1*(a <= x)*(x <= b));
    t1 = min(t1, t2);
    return (FIS_TYPE) max(t1, 0);
}

FIS_TYPE fis_min(FIS_TYPE a, FIS_TYPE b)
{
    return min(a, b);
}

FIS_TYPE fis_max(FIS_TYPE a, FIS_TYPE b)
{
    return max(a, b);
}

FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp)
{
    int i;
    FIS_TYPE ret = 0;

    if (size == 0) return ret;
    if (size == 1) return array[0];

    ret = array[0];
    for (i = 1; i < size; i++)
    {
        ret = (*pfnOp)(ret, array[i]);
    }

    return ret;
}


//***********************************************************************
// Data for Fuzzy Inference System                                       
//***********************************************************************
// Pointers to the implementations of member functions
_FIS_MF fis_gMF[] =
{
    fis_zmf, fis_smf, fis_trimf
};

// Count of member function for each Input
int fis_gIMFCount[] = { 2, 2, 2, 2, 2 };

// Count of member function for each Output 
int fis_gOMFCount[] = { 11 };

// Coefficients for the Input Member Functions
FIS_TYPE fis_gMFI0Coeff1[] = { 100, 400 };
FIS_TYPE fis_gMFI0Coeff2[] = { 300, 800 };
FIS_TYPE* fis_gMFI0Coeff[] = { fis_gMFI0Coeff1, fis_gMFI0Coeff2 };
FIS_TYPE fis_gMFI1Coeff1[] = { 100, 400 };
FIS_TYPE fis_gMFI1Coeff2[] = { 300, 800 };
FIS_TYPE* fis_gMFI1Coeff[] = { fis_gMFI1Coeff1, fis_gMFI1Coeff2 };
FIS_TYPE fis_gMFI2Coeff1[] = { 100, 400 };
FIS_TYPE fis_gMFI2Coeff2[] = { 300, 800 };
FIS_TYPE* fis_gMFI2Coeff[] = { fis_gMFI2Coeff1, fis_gMFI2Coeff2 };
FIS_TYPE fis_gMFI3Coeff1[] = { 100, 400 };
FIS_TYPE fis_gMFI3Coeff2[] = { 300, 800 };
FIS_TYPE* fis_gMFI3Coeff[] = { fis_gMFI3Coeff1, fis_gMFI3Coeff2 };
FIS_TYPE fis_gMFI4Coeff1[] = { 100, 400 };
FIS_TYPE fis_gMFI4Coeff2[] = { 300, 800 };
FIS_TYPE* fis_gMFI4Coeff[] = { fis_gMFI4Coeff1, fis_gMFI4Coeff2 };
FIS_TYPE** fis_gMFICoeff[] = { fis_gMFI0Coeff, fis_gMFI1Coeff, fis_gMFI2Coeff, fis_gMFI3Coeff, fis_gMFI4Coeff };

// Coefficients for the Input Member Functions
FIS_TYPE fis_gMFO0Coeff1[] = { -31.6, 0, 25 };
FIS_TYPE fis_gMFO0Coeff2[] = { 0, 23, 46 };
FIS_TYPE fis_gMFO0Coeff3[] = { 23, 46, 69 };
FIS_TYPE fis_gMFO0Coeff4[] = { 46, 69, 92 };
FIS_TYPE fis_gMFO0Coeff5[] = { 69, 92, 115 };
FIS_TYPE fis_gMFO0Coeff6[] = { 92, 115, 138 };
FIS_TYPE fis_gMFO0Coeff7[] = { 115, 138, 161 };
FIS_TYPE fis_gMFO0Coeff8[] = { 138, 161, 184 };
FIS_TYPE fis_gMFO0Coeff9[] = { 161, 184, 207 };
FIS_TYPE fis_gMFO0Coeff10[] = { 184, 207, 230 };
FIS_TYPE fis_gMFO0Coeff11[] = { 207, 230, 255 };
FIS_TYPE* fis_gMFO0Coeff[] = { fis_gMFO0Coeff1, fis_gMFO0Coeff2, fis_gMFO0Coeff3, fis_gMFO0Coeff4, fis_gMFO0Coeff5, fis_gMFO0Coeff6, fis_gMFO0Coeff7, fis_gMFO0Coeff8, fis_gMFO0Coeff9, fis_gMFO0Coeff10, fis_gMFO0Coeff11 };
FIS_TYPE** fis_gMFOCoeff[] = { fis_gMFO0Coeff };

// Input membership function set
int fis_gMFI0[] = { 0, 1 };
int fis_gMFI1[] = { 0, 1 };
int fis_gMFI2[] = { 0, 1 };
int fis_gMFI3[] = { 0, 1 };
int fis_gMFI4[] = { 0, 1 };
int* fis_gMFI[] = { fis_gMFI0, fis_gMFI1, fis_gMFI2, fis_gMFI3, fis_gMFI4};

// Output membership function set
int fis_gMFO0[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
int* fis_gMFO[] = { fis_gMFO0};

// Rule Weights
FIS_TYPE fis_gRWeight[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Type
int fis_gRType[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// Rule Inputs
int fis_gRI0[] = { 1, 1, 1, 1, 1 };
int fis_gRI1[] = { 1, 1, 1, 1, 2 };
int fis_gRI2[] = { 1, 1, 1, 2, 1 };
int fis_gRI3[] = { 1, 1, 1, 2, 2 };
int fis_gRI4[] = { 1, 1, 2, 1, 1 };
int fis_gRI5[] = { 1, 1, 2, 1, 2 };
int fis_gRI6[] = { 1, 1, 2, 2, 2 };
int fis_gRI7[] = { 1, 2, 1, 1, 1 };
int fis_gRI8[] = { 1, 2, 1, 1, 2 };
int fis_gRI9[] = { 1, 2, 1, 2, 1 };
int fis_gRI10[] = { 1, 2, 1, 2, 2 };
int fis_gRI11[] = { 1, 2, 2, 1, 1 };
int fis_gRI12[] = { 1, 2, 2, 1, 2 };
int fis_gRI13[] = { 1, 2, 2, 2, 1 };
int fis_gRI14[] = { 1, 2, 2, 2, 2 };
int fis_gRI15[] = { 2, 1, 1, 1, 1 };
int fis_gRI16[] = { 2, 1, 1, 1, 2 };
int fis_gRI17[] = { 2, 1, 1, 2, 1 };
int fis_gRI18[] = { 2, 1, 1, 2, 2 };
int fis_gRI19[] = { 2, 1, 2, 1, 1 };
int fis_gRI20[] = { 2, 1, 2, 1, 2 };
int fis_gRI21[] = { 2, 1, 2, 2, 1 };
int fis_gRI22[] = { 2, 1, 2, 2, 2 };
int fis_gRI23[] = { 2, 2, 1, 1, 1 };
int fis_gRI24[] = { 2, 2, 1, 1, 2 };
int fis_gRI25[] = { 2, 2, 1, 2, 1 };
int fis_gRI26[] = { 2, 2, 1, 2, 2 };
int fis_gRI27[] = { 2, 2, 2, 1, 1 };
int fis_gRI28[] = { 2, 2, 2, 1, 2 };
int fis_gRI29[] = { 2, 2, 2, 2, 1 };
int fis_gRI30[] = { 2, 2, 2, 2, 2 };
int* fis_gRI[] = { fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5, fis_gRI6, fis_gRI7, fis_gRI8, fis_gRI9, fis_gRI10, fis_gRI11, fis_gRI12, fis_gRI13, fis_gRI14, fis_gRI15, fis_gRI16, fis_gRI17, fis_gRI18, fis_gRI19, fis_gRI20, fis_gRI21, fis_gRI22, fis_gRI23, fis_gRI24, fis_gRI25, fis_gRI26, fis_gRI27, fis_gRI28, fis_gRI29, fis_gRI30 };

// Rule Outputs
int fis_gRO0[] = { 7 };
int fis_gRO1[] = { 5 };
int fis_gRO2[] = { 8 };
int fis_gRO3[] = { 8 };
int fis_gRO4[] = { 10 };
int fis_gRO5[] = { 10 };
int fis_gRO6[] = { 10 };
int fis_gRO7[] = { 9 };
int fis_gRO8[] = { 9 };
int fis_gRO9[] = { 9 };
int fis_gRO10[] = { 9 };
int fis_gRO11[] = { 6 };
int fis_gRO12[] = { 6 };
int fis_gRO13[] = { 3 };
int fis_gRO14[] = { 3 };
int fis_gRO15[] = { 9 };
int fis_gRO16[] = { 9 };
int fis_gRO17[] = { 1 };
int fis_gRO18[] = { 1 };
int fis_gRO19[] = { 10 };
int fis_gRO20[] = { 10 };
int fis_gRO21[] = { 10 };
int fis_gRO22[] = { 10 };
int fis_gRO23[] = { 11 };
int fis_gRO24[] = { 11 };
int fis_gRO25[] = { 11 };
int fis_gRO26[] = { 11 };
int fis_gRO27[] = { 4 };
int fis_gRO28[] = { 4 };
int fis_gRO29[] = { 2 };
int fis_gRO30[] = { 2 };
int* fis_gRO[] = { fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5, fis_gRO6, fis_gRO7, fis_gRO8, fis_gRO9, fis_gRO10, fis_gRO11, fis_gRO12, fis_gRO13, fis_gRO14, fis_gRO15, fis_gRO16, fis_gRO17, fis_gRO18, fis_gRO19, fis_gRO20, fis_gRO21, fis_gRO22, fis_gRO23, fis_gRO24, fis_gRO25, fis_gRO26, fis_gRO27, fis_gRO28, fis_gRO29, fis_gRO30 };

// Input range Min
FIS_TYPE fis_gIMin[] = { 0, 0, 0, 0, 0 };

// Input range Max
FIS_TYPE fis_gIMax[] = { 1023, 1023, 1023, 1023, 1023 };

// Output range Min
FIS_TYPE fis_gOMin[] = { 0 };

// Output range Max
FIS_TYPE fis_gOMax[] = { 255 };

//***********************************************************************
// Data dependent support functions for Fuzzy Inference System                          
//***********************************************************************
FIS_TYPE fis_MF_out(FIS_TYPE** fuzzyRuleSet, FIS_TYPE x, int o)
{
    FIS_TYPE mfOut;
    int r;

    for (r = 0; r < fis_gcR; ++r)
    {
        int index = fis_gRO[r][o];
        if (index > 0)
        {
            index = index - 1;
            mfOut = (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else if (index < 0)
        {
            index = -index - 1;
            mfOut = 1 - (fis_gMF[fis_gMFO[o][index]])(x, fis_gMFOCoeff[o][index]);
        }
        else
        {
            mfOut = 0;
        }

        fuzzyRuleSet[0][r] = fis_min(mfOut, fuzzyRuleSet[1][r]);
    }
    return fis_array_operation(fuzzyRuleSet[0], fis_gcR, fis_max);
}

FIS_TYPE fis_defuzz_centroid(FIS_TYPE** fuzzyRuleSet, int o)
{
    FIS_TYPE step = (fis_gOMax[o] - fis_gOMin[o]) / (FIS_RESOLUSION - 1);
    FIS_TYPE area = 0;
    FIS_TYPE momentum = 0;
    FIS_TYPE dist, slice;
    int i;

    // calculate the area under the curve formed by the MF outputs
    for (i = 0; i < FIS_RESOLUSION; ++i){
        dist = fis_gOMin[o] + (step * i);
        slice = step * fis_MF_out(fuzzyRuleSet, dist, o);
        area += slice;
        momentum += slice*dist;
    }

    return ((area == 0) ? ((fis_gOMax[o] + fis_gOMin[o]) / 2) : (momentum / area));
}

//***********************************************************************
// Fuzzy Inference System                                                
//***********************************************************************
void fis_evaluate()
{
    FIS_TYPE fuzzyInput0[] = { 0, 0 };
    FIS_TYPE fuzzyInput1[] = { 0, 0 };
    FIS_TYPE fuzzyInput2[] = { 0, 0 };
    FIS_TYPE fuzzyInput3[] = { 0, 0 };
    FIS_TYPE fuzzyInput4[] = { 0, 0 };
    FIS_TYPE* fuzzyInput[fis_gcI] = { fuzzyInput0, fuzzyInput1, fuzzyInput2, fuzzyInput3, fuzzyInput4, };
    FIS_TYPE fuzzyOutput0[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    FIS_TYPE* fuzzyOutput[fis_gcO] = { fuzzyOutput0, };
    FIS_TYPE fuzzyRules[fis_gcR] = { 0 };
    FIS_TYPE fuzzyFires[fis_gcR] = { 0 };
    FIS_TYPE* fuzzyRuleSet[] = { fuzzyRules, fuzzyFires };
    FIS_TYPE sW = 0;

    // Transforming input to fuzzy Input
    int i, j, r, o;
    for (i = 0; i < fis_gcI; ++i)
    {
        for (j = 0; j < fis_gIMFCount[i]; ++j)
        {
            fuzzyInput[i][j] =
                (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
        }
    }

    int index = 0;
    for (r = 0; r < fis_gcR; ++r)
    {
        if (fis_gRType[r] == 1)
        {
            fuzzyFires[r] = FIS_MAX;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_min(fuzzyFires[r], 1);
            }
        }
        else
        {
            fuzzyFires[r] = FIS_MIN;
            for (i = 0; i < fis_gcI; ++i)
            {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_max(fuzzyFires[r], 0);
            }
        }

        fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
        sW += fuzzyFires[r];
    }

    if (sW == 0)
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
        }
    }
    else
    {
        for (o = 0; o < fis_gcO; ++o)
        {
            g_fisOutput[o] = fis_defuzz_centroid(fuzzyRuleSet, o);
        }
    }
}
