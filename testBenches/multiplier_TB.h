#ifndef __MULTIPLIERTB_H__
#define __MULTIPLIERTB_H__

#include "multiplier.h"

SC_MODULE(Multiplier_TB)
{
	sc_signal<sc_lv<8>> inA, inB;
    sc_signal<sc_lv<16>> result;

	Multiplier<8>* DUT;

	SC_CTOR(Multiplier_TB)
	{
		DUT = new Multiplier<8>("myMult");
		DUT->inA(inA);
		DUT->inB(inB);
		DUT->result(result);
        
		SC_THREAD(inputHandler);
	}

	void inputHandler();
};



#endif
