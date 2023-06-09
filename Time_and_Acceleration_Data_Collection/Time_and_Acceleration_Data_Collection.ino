// Much Credit to Miguelcmaramara on Github for this code!

/**
 * Libraries and outside files
 */
#include <Arduino_LSM9DS1.h>


#define GREEN 23  
#define RED 22
unsigned int numData = 0;
const unsigned int INPUT_LENGTH = 5000;
const unsigned int INPUT_TIME = 50000;
const unsigned int BUTTON_PIN = 2;
unsigned long t = 0;
unsigned long curr_t = 0;

float ax; float ay; float az;
float gx; float gy; float gz;

// float xIn [INPUT_LENGTH]; //Takes from IMU assigns to array
// float yIn [INPUT_LENGTH];
// float zIn [INPUT_LENGTH];
// float tIn [INPUT_LENGTH];
// float gx [INPUT_LENGTH]; //gyroscope data from IMU assigns to array
// float gy [INPUT_LENGTH];
// float gz [INPUT_LENGTH];
int delayTime = 1;

int counter = 0;
bool elapsed = false;
/*****************************************
 * SETUP
 ****************************************/
void setup() {
  // don't miss serial output
  Serial.begin(9600);

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
  if(digitalRead(BUTTON_PIN) == HIGH && IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && curr_t < INPUT_TIME){
    //Serial.println("in switch loop");
    Serial.print("Time");
    Serial.print(", ");
    Serial.print("Ax");
    Serial.print(", ");
    Serial.print("Ay");
    Serial.print(", ");
    Serial.print("Az");
    Serial.print(", ");
    Serial.print("Gx");
    Serial.print(", ");
    Serial.print("Gy");
    Serial.print(", ");
    Serial.println("Gz");
    t = millis();
    // numData = 0;
    while(digitalRead(BUTTON_PIN) == HIGH && curr_t < INPUT_TIME){

      //digitalWrite(13, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);

      //Data collection
      // IMU.readAcceleration(xIn[numData],yIn[numData],zIn[numData]);
      // IMU.readGyroscope(gx[numData], gy[numData], gz[numData]);
      // counter +=1;

      IMU.readAcceleration(ax,ay,az);
      IMU.readGyroscope(gx, gy, gz);
      
      curr_t = millis() -t;
      Serial.print(curr_t);
      Serial.print(", ");
      Serial.print(ax, 5);
      Serial.print(", ");
      Serial.print(ay, 5);
      Serial.print(", ");
      Serial.print(az, 5);
      Serial.print(", ");
      Serial.print(gx, 5);
      Serial.print(", ");
      Serial.print(gy, 5);
      Serial.print(", ");
      Serial.println(gz, 5);
      
      //prints out x, y, z, values in each row due to Serial.print() function constraints
      // Serial.print(millis() - t);
      // Serial.print(", ");
      // Serial.print(xIn[numData], 5);
      // Serial.print(", ");
      // Serial.print(yIn[numData], 5);
      // Serial.print(", ");
      // Serial.print(zIn[numData], 5);
      // Serial.print(", ");
      // Serial.print(gx[numData], 5);
      // Serial.print(", ");
      // Serial.print(gy[numData], 5);
      // Serial.print(", ");
      // Serial.println(gz[numData], 5);
      
      // tIn[numData] = (float) (millis()-t);

      //check if desired time of recording has passed
      // if (tIn[numData] >= INPUT_TIME){elapsed = true; break;}

      // numData++;
      delay(delayTime);
      
    }
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);

  //   for(int i = 0; i < counter; i++ ){
  //     Serial.print(tIn[i]);
  //     Serial.print(", ");
  //     Serial.print(xIn[i], 4);
  //     Serial.print(", ");
  //     Serial.print(yIn[i], 4);
  //     Serial.print(", ");
  //     Serial.print(zIn[i], 4);
  //     Serial.print(", ");
  //     Serial.print(gx[i], 4);
  //     Serial.print(", ");
  //     Serial.print(gy[i], 4);
  //     Serial.print(", ");
  //     Serial.println(gz[i], 4);
  // }

  }
  
  
  delay(delayTime);

}

