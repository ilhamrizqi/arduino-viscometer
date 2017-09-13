#include <TimerOne.h>

byte startPin = 2;
byte stopPin  = 3;
byte buttonPin = 4;
byte ledPin = 14;
byte laserPin = 13;
byte button = 0;
byte laserOn = 0;

//  shared variable
volatile unsigned long mscounter = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(laserPin, OUTPUT);

  //  turn off led & laser
  digitalWrite(ledPin, LOW);
  digitalWrite(laserPin, LOW);

  //   Timer set to 1ms
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerCounter);

  attachInterrupt(digitalPinToInterrupt(startPin), start, FALLING);
  attachInterrupt(digitalPinToInterrupt(stopPin), stop, FALLING);

  Serial.begin(9600);
  Serial.writeln("Tekan button untuk menyalakan/mematikan laser");

  //  turn on led & laser
  digitalWrite(ledPin, HIGH);  
}

void loop() {
  // put your main code here, to run repeatedly:  
  button = digitalRead(buttonPin);
  if(button = 1)
  {
    //  toggle laser
    digitalWrite(laserPin, !digitalRead(laserPin));
    laserOn = digitalRead(laserPin);    
  }
}

void start()
{
  ms = 0;
  Timer1.start();
}

void stop()
{  
  unsigned long ms;    

  Timer1.stop();
  noInterrupts();
  ms = mscounter;
  interrupts();

  Serial.println(ms);
}

void timerCounter()
{
  mscounter++;
}

