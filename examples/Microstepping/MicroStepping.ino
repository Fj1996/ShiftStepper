#include "StepperSRV2.h"

StepperSRV2 motor(24);

double contador = 0;
int dire = 1;
double pasosTotal = 51000;

void setup() {
  motor.init();
}

void loop() {
  motor.step(dire,1);
  contador++;
  if(contador >= pasosTotal){
    contador = 0;
    dire = dire * -1;
    delay(3000);
  }
  delayMicroseconds(225);
}



