#include "multiplier_TB.h"
using namespace std;

void Multiplier_TB::inputHandler()
{
    while (true)
    {
        wait(0, SC_NS);
        inA = 0;
        inB = 0;

        wait(13, SC_NS);
        inA = 12;

        wait(15, SC_NS);
        inB = 17;

        wait(10, SC_NS);
        inA = 100;

        wait(5, SC_NS);
        inB = 100;

        wait(12, SC_NS);
        inA = 4;
        inB= -6;

        wait(17, SC_NS);
        inA = 44;

        wait(25, SC_NS);
        inB = 27;

        wait();
    }
    
}