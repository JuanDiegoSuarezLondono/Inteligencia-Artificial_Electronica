#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 1,71,255,0);//49-71
  if(frequency<0)
  {
   frequency=0;
   }
  
  Serial.print(frequency);
  Serial.print("  ");
  delay(100);


  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 1,75,255,0);//55-75
    if(frequency<0)
  {
   frequency=0;
   }
  
  Serial.print(frequency);
  Serial.print("  ");
  delay(100);


  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  frequency = map(frequency, 2,50, 255,0);//32-50
    if(frequency<0)
  {
   frequency=0;
   }
 
  Serial.print(frequency);
  Serial.println("  ");
  delay(100);
}
