#ifndef __STEPS
#define __STEPS

#include <iostream>
using namespace std;

const int MAXPWM = 256;

class Steps{
	private:
		int _n;
		int _paso;
		int _getPaso(int m, int j);
	public:
		Steps(int n);
		int getCurrent(int m);
		void add(int incr);
};

#endif
