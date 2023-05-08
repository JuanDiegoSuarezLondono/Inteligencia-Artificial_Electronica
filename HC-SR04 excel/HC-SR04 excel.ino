#define trigPin 13
#define echoPin 12
int ROW=0;
int LABEL=1;

void setup() {
  Serial.begin (9600);
  Serial.print("CLEARDATA");
  Serial.print("LABEL,Time,val,ROM");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, val;  
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  val = pulseIn(echoPin, HIGH);
  val = val*0.017;
if(ROW<=120)
{
Serial.print("DATA,TIME,");
Serial.print(val);
Serial.print(",");
Serial.println(ROW);
  delay(200);
  ROW++;
}

}

