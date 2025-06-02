
// Constant
#define ENA D7
#define IN1 D6
#define IN2 D5
#define IN3 D3
#define IN4 D4
#define ENB D2

#define BLYNK_TEMPLATE_ID "Thy template ID"
#define BLYNK_TEMPLATE_NAME "Thy template name"
#define BLYNK_AUTH_TOKEN "Thy auth token"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer; //This function prevent fundamental process inside esp8266 from outside interupting 

//WiFi name and password
char ssid[] = "Thy WiFi name"; 
char pass[] = "Thy password";
//Initial setup 
int motor_speed = 100;
bool forward = false;
bool backward = false;
bool turnleft = false;
bool turnright = false;

void setup() 
{
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(100L, movement);
}

void loop() 
{
  Blynk.run();
  timer.run();
}

//This function recieve input from Blynk app
BLYNK_WRITE(V0)
{
  forward = param.asInt(); 
}
BLYNK_WRITE(V1)
{
  backward = param.asInt(); 
}
BLYNK_WRITE(V2)
{
  turnright = param.asInt();

}
BLYNK_WRITE(V3)
{
  turnleft = param.asInt();
}
BLYNK_WRITE(V4)
{
  motor_speed = param.asInt(); 
}

//This function control motors
void movement()
{
  if (forward)
  {
    Serial.println("FORWARD");
    analogWrite(ENA, motor_speed);
    analogWrite(ENB, motor_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if (backward)
  {
    Serial.println("BACKWARD");
    analogWrite(ENA, motor_speed);
    analogWrite(ENB, motor_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (turnleft)
  {
    Serial.println("TURN LEFT");
    analogWrite(ENA, motor_speed);
    analogWrite(ENB, motor_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if (turnright)
  {
    Serial.println("TURN RIGHT");
    analogWrite(ENA, motor_speed);
    analogWrite(ENB, motor_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else
  {
    Serial.println("STOP");
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}
