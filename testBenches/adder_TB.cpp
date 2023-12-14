#include "adder_TB.h"
using namespace std;

void Adder_TB::inputHandler()
{
	while (true)
	{
		wait(0, SC_NS);
		inA = 0;
		inB = 0;
		cIn = SC_LOGIC_0;

		wait(10, SC_NS);
		inA = 24;
		inB = -21;

		wait(10, SC_NS);
		inA = 95;
		inB = 41;

		wait(17, SC_NS);
		inA = 200;

		wait();
	}
}