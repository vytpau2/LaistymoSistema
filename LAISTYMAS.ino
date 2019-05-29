int dregmPin = A0;     // Dregmes PIN
int tempPin = A1;      // Temperatura PIN 
int trigPin = 11;      // Trigger Atstumo PIN1
int echoPin = 12;      // Echo Atstumo PIN2
int sklendePin = 7;    // Sklendes PIN1
int sklendePin2 = 8;   // Sklendes papildomas PIN
int riba=300;

unsigned long laikas=0;
unsigned long StartTime = millis();


long duration, cm;
int dregme;
float temp;
 
void setup() {
  //Serial Port ijungimas
  Serial.begin (9600);
  //Inputai/Outputai
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sklendePin, OUTPUT);
  pinMode(sklendePin2,OUTPUT);
}
 
void loop() {
  // Skaiciavimai vykdomi 10 mikrosekundziu intervalu
  // 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH); //signalo trukme
  dregme = analogRead(dregmPin);     //dregme
  int tempRod = analogRead(tempPin); //temperaturos sensoriaus rodmenys
  float voltage = tempRod * 3.3;     //temperaturos gavimas pagal sensoriaus rodmenis
  voltage /= 1024.0;
  temp = (voltage - 0.5) * 10;
  // Atstumo apskaiciavimas pagal signalo trukme
  cm = (duration/2) / 29.1;     // Dalinti is 29.1 arba padauginti is 0.0343
  Serial.print(round(temp));
  Serial.print(";");
  Serial.print(dregme);
  Serial.print(";");
  Serial.print(cm);
  Serial.println();
  unsigned long CurrentTime = millis();
unsigned long ElapsedTime = (CurrentTime - StartTime)/1000;
laikas = laikas+ ElapsedTime;
// tikrinama dregmes riba, ir ar praejo pakankamai laiko nuo paskutinio palaistymo
  if(dregme>riba && laikas>10)
  {
   
  laistymas();
  laikas=0;
  StartTime=millis();
  }
    StartTime=millis();
  delay(2000);
}
//Laistymo mechanizmas
void laistymas()
{
  Serial.println("Palaistyta");
  digitalWrite(sklendePin,HIGH);
  delay(2000);
  digitalWrite(sklendePin,LOW);
}
