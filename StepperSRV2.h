#ifndef StepperSRV2_h
#define StepperSRV2_h
#include "StepperSRV2.h"
#include "Arduino.h"
/**
* Define una libreria para controlar motores paso a paso mediante un registro de desplazamiento
* Cada instancia puede controlar 2 motores: motor 1 -> 4 LSB bits, motor 2 -> 4 MSB bits
*/
class StepperSRV2{
  public:
    StepperSRV2(int numPasos);
    void step(int dir, int motor);
    void init();
    void off();
  private:
    int _pasos;
    void _addPaso(int dir, int motor, boolean full);
    void _writePaso();
    void _inicializaPasos();  
};

#endif
