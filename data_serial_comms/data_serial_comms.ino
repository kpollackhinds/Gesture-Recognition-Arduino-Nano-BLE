// Much Credit to Miguelcmaramara on Github for this code!

/**
 * Libraries and outside files
 */
#include <Arduino_LSM9DS1.h>


#define GREEN 23  
#define RED 22
unsigned int numData = 0;
const unsigned int BUTTON_PIN = 2;
unsigned long t = 0;
unsigned long curr_t = 0;

float ax; float ay; float az;
float gx; float gy; float gz;
int delayTime = 0;

int counter = 0;
bool elapsed = false;
/*****************************************
 * SETUP
 ****************************************/
void setup() {
  // don't miss serial output
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(13, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  // Begin IMU
  if(!IMU.begin()){
    Serial.print("IMU failed to initialize");
  }

}

void loop() {
  if(digitalRead(BUTTON_PIN) == HIGH && IMU.accelerationAvailable() && IMU.gyroscopeAvailable()){
    // Serial1.println("b");
    t = millis();
    // numData = 0;
    while(digitalRead(BUTTON_PIN) == HIGH){

      //digitalWrite(13, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);

      //read sensors
      IMU.readAcceleration(ax,ay,az);
      IMU.readGyroscope(gx, gy, gz);
      
      //send data
      sendData(ax); sendData(ay); sendData(az);
      sendData(gx); sendData(gy); sendData(gz);

      curr_t = millis() -t;
      delay(delayTime);
      
    }
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);


  }
  delay(delayTime);

}


void sendData(float data) {
  byte *dataPtr = (byte*)&data; //creating byte array from data (using mem address)
  
  for (size_t i =0; i < sizeof(float); i++){
    Serial1.write(dataPtr[i]);
  }
}