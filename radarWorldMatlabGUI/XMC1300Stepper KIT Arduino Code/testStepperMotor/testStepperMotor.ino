#include <IFX9201_XMC1300_StepperMotor.h>

#define DIR_PIN IFX9201_STEPPERMOTOR_STD_DIR		// Pin 9 is standard DIR Pin
#define STP_PIN IFX9201_STEPPERMOTOR_STD_STP		// Pin 10 is standard STP Pin
#define DIS_PIN IFX9201_STEPPERMOTOR_STD_DIS		// Pin 11 is standard DIS Pin

const int StepsPerRevolution = 200;  // change this to fit the total number of steps per revolution for your motor

//*** HALL Sensor Configuration *** 
const byte zeroPosPin = 2;         // hall sensor is connected to pin2 (IT0)
const byte zeroPosLedPin = 13;       // LED to indicate 0 position
char val=0;

//*** motor positioning variables ***
char motPos=1;   //used to set home position after homing
bool homed = LOW;
bool state = LOW;

int serCommand = 0;
byte incomingCmd;
// Stepper motor object
Stepper_motor MyStepperMotor = Stepper_motor(StepsPerRevolution, DIR_PIN, STP_PIN, DIS_PIN);

void setup() {

	// set pins' mode as OUTPUT, set default speed and enable the stepper motor
	MyStepperMotor.begin();

	// set the speed at 10 rpm:
	MyStepperMotor.setSpeed(100);

	// initialize the serial port:
	Serial.begin(9600);
  pinMode(zeroPosLedPin, OUTPUT); // zero pos indicator led
  pinMode(zeroPosPin, INPUT); //setup the INT0 interrupt on D2

  Serial.println('a');
  char a=0;
  while(a !='a'){
    a=Serial.read();
  }
}

void loop() {

  handleSerial2();
  }

void handleSerial2(){
  while (Serial.available()==0)
  {}

  if (Serial.available() >0){
    val = Serial.read();
    if (val == 'R'){
      stepMotorClockWise(); 
      Serial.print('R');
      digitalWrite(zeroPosLedPin, HIGH);     
    }
    if (val == 'L'){
      stepMotorCounterClockWise();
      Serial.print('L');
    }

    if (val == 'H'){
      homeMotor();
      Serial.print('H');
    }
  
  }
}


void handleSerial(){
  if (Serial.available() >0) {
    digitalWrite(zeroPosLedPin, HIGH);
    incomingCmd= Serial.read();
    Serial.print(incomingCmd, HEX);
    switch (incomingCmd){
      case 'a':
      homed=LOW;
      homeMotor();
      Serial.print(motPos, HEX);
      break;

      case 'b':
      stepMotorClockWise();
      Serial.print(motPos, HEX);
      break;

      case 'c':
      stepMotorCounterClockWise();
      Serial.print(motPos, HEX);
      break;

      default:
      Serial.print(incomingCmd, HEX);      
    }
  }
}

void homeMotor(){
  attachInterrupt(digitalPinToInterrupt(zeroPosPin), zeroPosInterrupt, RISING); //enable the interrupt only for this function
  while (homed==LOW) { //rotate motor until the hall sensor is activated
  motPos++;
  MyStepperMotor.step(motPos);
  }
}

void stepMotorClockWise(){
  MyStepperMotor.step(1);
  motPos++;  
}

void stepMotorCounterClockWise(){
  MyStepperMotor.step(-1);
  motPos--;  
}


void zeroPosInterrupt() {
  homed=HIGH;
  motPos=0;
  state = HIGH;
  detachInterrupt(digitalPinToInterrupt(zeroPosPin));
  
}
  
