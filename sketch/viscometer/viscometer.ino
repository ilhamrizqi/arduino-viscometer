#include <TimerOne.h>

byte startPin = 2;
byte stopPin  = 3;
byte buttonPin = 4;
byte buzzerPin = 5;
byte ledPin = 12;
byte laserPin = 13;
byte button = 0;
bool laserOn = true;

//  shared variable
volatile unsigned long mscounter = 0;
volatile bool detected = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(laserPin, OUTPUT);

  //  turn off led & laser
  digitalWrite(ledPin, LOW);
  digitalWrite(laserPin, LOW);

  //   Timer set to 1ms
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerInterrupt);

  attachInterrupt(digitalPinToInterrupt(startPin), start, FALLING);
  attachInterrupt(digitalPinToInterrupt(stopPin), stop, FALLING);

  Serial.begin(9600);
  Serial.println("Tekan button untuk menyalakan/mematikan laser");

  //  turn on led & laser
  digitalWrite(laserPin, HIGH);
  digitalWrite(ledPin, LOW);
  beep(200);
}

void loop() {
  bool ballDetected;
  // put your main code here, to run repeatedly:  
  button = digitalRead(buttonPin);  
  if(button == 1)
  {
    laserOn = !laserOn;
    // toggle laser
    digitalWrite(laserPin, laserOn);    
    delay(200);        
  }
  
  ballDetected = detected;
  if(ballDetected)
  {
    digitalWrite(ledPin, HIGH);
    beepDetected(200);
    delay(200);    
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

void beep(int duration)
{
  tone(buzzerPin, 1000);
  delay(duration);
  noTone(buzzerPin);
}

void beepDetected(int duration)
{
  tone(buzzerPin, 3000);
  delay(duration);
  noTone(buzzerPin);  
}

void start()
{
  if(detected || !laserOn)
  {
    return;
  }
  noInterrupts();
  mscounter = 0;
  detected = true;  
  interrupts();
    
  Timer1.start();
}

void stop()
{  
  unsigned long ms;    
  if(!detected)
  {
    return;
  }
  Timer1.stop();
  noInterrupts();
  ms = mscounter;
  detected = false;
  interrupts();

  Serial.println(ms);
}

void timerInterrupt()
{
  mscounter++;
}


