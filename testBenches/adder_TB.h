#ifndef __ADDERTB_H__
#define __ADDERTB_H__

#include "adder.h"

SC_MODULE(Adder_TB)
{
	sc_signal<sc_lv<8>> inA, inB, result;
	sc_signal<sc_logic> cIn, cOut;

	Adder<8>* DUT;

	SC_CTOR(Adder_TB)
	{
		DUT = new Adder<8>("myAdder");
		DUT->inA(inA);
		DUT->inB(inB);
		DUT->result(result);
		DUT->carryIn(cIn);
		DUT->carryOut(cOut);

		SC_THREAD(inputHandler);
	}

	void inputHandler();
};



#endif
