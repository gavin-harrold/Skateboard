//pins for motor
#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define relayPin 10
#define offPin 11
#define pinIn 8
#define pinOut 9

int incomingByte = 0;
int randNumber;

void setup() {
  // put your setup code here, to run once:
  //RELAY PIN
  pinMode(relayPin, OUTPUT);
  pinMode(offPin, OUTPUT);
  pinMode(pinIn, OUTPUT);
  pinMode(pinOut, OUTPUT);
  //LED pin modes
  //pinMode(13, OUTPUT);
  //motor pin modes
 /* pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT); */
  //setting to proper start values
  digitalWrite(relayPin, LOW);
  digitalWrite(offPin, HIGH);
  digitalWrite(offPin, LOW);
  calibrate();
  Serial.begin(9600);
}

//current issue is with Arduino reading of Serial, figure it out later
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    if(incomingByte == 'f') {
      //digitalWrite(13, HIGH); //used for LED
      /* digitalWrite(ENABLE, HIGH); //motor
      digitalWrite(DIRA, HIGH); //motor direction A
      digitalWrite(DIRB, LOW); //motor direction B */
      //digitalWrite(DIRA, LOW);
      //digitalWrite(DIRB, HIGH);
      digitalWrite(offPin, LOW);
      digitalWrite(pinIn, LOW);
      digitalWrite(pinOut, LOW);
      
      digitalWrite(relayPin, HIGH);
      
      delay(2000);
    }
    else if(incomingByte == 'l') {
      digitalWrite(relayPin, LOW);
      digitalWrite(pinIn, LOW);
      digitalWrite(pinOut, HIGH);
      delay(2000);
      //digitalWrite(pinOut, LOW);
    }
    else if(incomingByte == 'r') {
      digitalWrite(relayPin, LOW);
      digitalWrite(pinOut, LOW);
      digitalWrite(pinIn, HIGH);
      delay(2000);
      //digitalWrite(pinIn, LOW);
    }
//    else {
//     //digitalWrite(13, LOW); //used for LED
//     /* digitalWrite(ENABLE, LOW);
//     digitalWrite(DIRA, LOW);
//     digitalWrite(DIRB, LOW); */
//     digitalWrite(relayPin, LOW);
//     digitalWrite(offPin, HIGH);
//     randNumber = random(0, 2);
//     Serial.println(randNumber);
//     if(randNumber == 0) {
//      digitalWrite(pinOut, HIGH);
//      delay(2000);
//      digitalWrite(pinOut, LOW);
//     }
//     else if(randNumber == 1) {
//      digitalWrite(pinIn, HIGH);
//      delay(2000);
//      digitalWrite(pinIn, LOW);
//     }
//    }
    while(Serial.available() > 0) {
      Serial.read();
    }
   }

}

void calibrate() {
  //first decrease length to 0, to ensure this, provide power for 11s
  
  //testing for max length to ensure it reaches 0 in allotted time
  digitalWrite(pinOut, HIGH);
  delay(12000);

  //performing zeroing process
  digitalWrite(pinOut, LOW);
  digitalWrite(pinIn, HIGH);
  delay(12000);

  digitalWrite(pinIn, LOW);
  digitalWrite(pinOut, HIGH);
  delay(5080);

  digitalWrite(pinOut, LOW);
  digitalWrite(pinIn, LOW);
}
