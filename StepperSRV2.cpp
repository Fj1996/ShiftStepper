#include "StepperSRV2.h"
#include "Arduino.h"
#define SHIFTPWM_USE_TIMER2
#define SHIFTPWM_NOSPI
const int ShiftPWM_dataPin = 8;
const int ShiftPWM_clockPin = 9;
const int ShiftPWM_latchPin=10;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>

const int _numMotores = 2;
int _motores[_numMotores];
const int _maxpasos = 128;
int _pasosA[_maxpasos];
int _pasosB[_maxpasos];
int _pasosC[_maxpasos];
int _pasosD[_maxpasos];

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 1;

StepperSRV2::StepperSRV2(int numpasos){
  if(numpasos > _maxpasos) numpasos = _maxpasos;
  _pasos = numpasos;
  _inicializaPasos(); 
}

void StepperSRV2::init(){
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
}

void StepperSRV2::off(){
  int pin = 0;
  for( int m : _motores){
    ShiftPWM.SetOne(pin++, 0);
    ShiftPWM.SetOne(pin++, 0);
    ShiftPWM.SetOne(pin++, 0);
    ShiftPWM.SetOne(pin++, 0);
  }
}

void StepperSRV2::step(int dir, int motor){
  if((dir == 1 || dir == -1) && motor <= _numMotores && motor >= 1){
    int state = _motores[motor-1];
    state = state + dir;
    if(state < 0) state = _pasos-1;
    if(state == _pasos) state = 0;
    _motores[motor-1] = state;
    _writePaso();
  }
}

// Escribe los registros de los pasos
void StepperSRV2::_writePaso(){
  int pin = 0;
  for( int m : _motores){
    ShiftPWM.SetOne(pin++, _pasosA[m]);
    ShiftPWM.SetOne(pin++, _pasosB[m]);
    ShiftPWM.SetOne(pin++, _pasosC[m]);
    ShiftPWM.SetOne(pin++, _pasosD[m]);
  }
}
// Inicializa los vectores con la combinacion de pasos
void  StepperSRV2::_inicializaPasos(){
  int auxlength = _pasos / 2;
  int aux[auxlength];
  int m = 0;
    for(int i = 1; i < auxlength/(auxlength/4); i++){
      aux[i*(auxlength/4)] = 255;
      m = i*(auxlength/4);
    }
    int n = 0;
    for(int i = 0; i < auxlength/4; i++){
      aux[i] = i * (256/(auxlength/4));
      n = i;
    }
    for(int i = n+1; i < m+1; i++) aux[i] = 255;
    for(int i = m+1; i < auxlength; i++) aux[i] = aux[n--];
    int a = (_pasos / 4) * 3;
    int b = 0;
    int c = _pasos / 4;
    int d = _pasos / 2;
    for (int i : aux) {
      _pasosA[a++] = i;
      _pasosB[b++] = i;
      _pasosC[c++] = i;
      _pasosD[d++] = i;
      if(a == _pasos) a = 0;
    }
}
