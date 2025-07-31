#include "Gimbal.h"

Gimbal myGimbal;

void setup() {

  // delay(5000);

  pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);


  myGimbal.attach();


}

float count = 0.0;


void loop() {

  double bruh = sin(count)*5;

  myGimbal.write(bruh,-bruh);

  count = count + 0.1;

  if (count >= 2*PI) {
    count = 0.0;
  }

  delay(20);
  

}
