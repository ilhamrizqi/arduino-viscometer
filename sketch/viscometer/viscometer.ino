
int startPin = 2;
int stopPin  = 3;
int buttonPin = 4;
int laserPin = 13;
int button = 0;
int laserOn = 0;
int ms = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(laserPin, OUTPUT);
  
  digitalWrite(laserPin, LOW);

  attachInterrupt(digitalPinToInterrupt(startPin), start, FALLING);
  attachInterrupt(digitalPinToInterrupt(stopPin), stop, FALLING);

  Serial.begin(115200);
  Serial.writeln("Tekan button untuk menyalakan/mematikan laser");
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
}

void stop()
{
  
}

void timerISR()
{
  ms++;
}

