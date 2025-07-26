#include "Gimbal.h"

Gimbal myGimbal;

void setup() {

  // only run once Serial port has started for debugging purposes
  while (!Serial) ;

  pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);


  myGimbal.attach();


  Serial.println("Started");

}

float inc = PI/2.0;
float radius = 0.02;
float step = 0.001;
bool up = true;

void loop() {
  
  myGimbal.write(PI/2, 91*(PI/180));


  // if ( up ) {
  //   inc = inc + step;
  //   if (inc >= PI/2.0 + radius) {
  //     up = false;
  //     inc = PI/2.0 + radius;
  //   }
  // } else {
  //   inc = inc - step;
  //   if (inc <= PI/2.0 - radius) {
  //     up = true;
  //     inc = PI/2.0 - radius;
  //   }
  // }

  // Serial.print("(");
  // Serial.print(inc);
  // Serial.print("\t");
  // Serial.print(inc);
  // Serial.println(")");

  delay(20);

}
