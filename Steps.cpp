#include "Steps.h"

Steps::Steps(int n){
	_n = n;
	_paso = 0;
}

int Steps::_getPaso(int m, int j){
	int sec = _n / 4;
	int pcent = m * sec;
	int incPWM = MAXPWM/sec;
	if(j == pcent) return 255;
	else if(j<(pcent+sec) && j > (pcent-sec) || (m == 0 && j > sec*3 )){
		if(m == 0 && j > sec*3 )pcent = sec * 4;
		int dist = pcent - j;
		if(dist < 0) dist = -dist;
		return (sec-dist)*incPWM;
	}else return 0;
}

int Steps::getCurrent(int m){
	return _getPaso(m, _paso);
}

void Steps::add(int incr){
	_paso += incr;
	if(_paso >= _n){
		int dif = _paso - _n;
		_paso = 0 + dif;
	}else if (_paso < 0){
		int dif = _paso + _n;
		_paso = (_n-1) + dif;
	}
}
