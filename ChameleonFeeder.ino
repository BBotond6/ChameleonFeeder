#include <Servo.h>

#define True                        1
#define False                       2
#define SERVO_PIN                  12
#define SERVO_PERIOD_TIME       10000 // 10 second
#define SERVO_STARTING_POSITION     0 //  0 degree
#define SERVO_TARGET_POSITION      90 // 90 degree

Servo servo;
byte Servo_State;
unsigned long int Servo_Time;

unsigned long int Timestamp;
unsigned long int Prev_Timestamp;

void setup() {
  servo.attach(SERVO_PIN);
  servo.write(SERVO_STARTING_POSITION);

  Servo_State=False;

  Serial.begin(38400);    //Initializing the serial port with 38400 baud.
  while (!Serial);

  Timestamp=millis();
  Prev_Timestamp = 0;
}

void Servo_Event(){
  Timestamp=millis();
  if((Timestamp - Prev_Timestamp) >= SERVO_PERIOD_TIME && Servo_State == False){
    servo.write(SERVO_TARGET_POSITION);
    Servo_State = True;
    Prev_Timestamp = Timestamp;
  }else if((Timestamp - Prev_Timestamp) >= SERVO_PERIOD_TIME && Servo_State == True){
    servo.write(SERVO_STARTING_POSITION);
    Servo_State = False;
    Prev_Timestamp = Timestamp;
  }
}



void loop() {
  Servo_Event();
}
