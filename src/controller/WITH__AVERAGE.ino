//define Pins
#define buzzer 11
#include <Servo.h>

Servo servo;

int trigPin = 9;
int echoPin = 8;
int flag = 1;

// defines variables
long duration;
int distance;
int sound = 250;
int mult = 3;

void setup() 
{
  servo.attach(7);
  servo.write(0);
  
// Sets the trigPin as an Output
pinMode(trigPin, OUTPUT);
// Sets the echoPin as an Input 
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
// Starts the serial communication 
Serial.begin(9600); 
}

//Function that returns the Average of SampleSize N
int getAverageDistance()
{
  int aveEchoRead = 0;
  int sampSize = 20;
  for(int i = 0; i <= sampSize; i++)
    {
      aveEchoRead += distance;
      delay(5);
    }
  Serial.println("______________________");
  Serial.print("Number of Samples: ");
  Serial.println(sampSize);
  Serial.print("Raw Data: ");
  Serial.println(aveEchoRead);
  Serial.print("Average: ");
  Serial.println(aveEchoRead/sampSize);
  return aveEchoRead/sampSize;
}

void loop() 
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;

  if ( getAverageDistance() <= 80  ) // Change Distance according to Ultrasonic Sensor Placement
   {
    servo.write(100);
    Serial.println("Status: DOOR OPEN!");
    if (flag == 1)
    {
      sound = 250*mult;
      tone(buzzer, sound);
      delay(300);
      noTone(buzzer);
    }
    flag = 0;
    delay(1000);
   } 
  else 
  {
    delay(1000);
    noTone(buzzer);
    flag = 1;
    servo.write(0);
    Serial.println("Status: DOOR CLOSE!");  
  }
}
