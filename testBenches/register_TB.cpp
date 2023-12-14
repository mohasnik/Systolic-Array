#include "register_TB.h"

using namespace std;

void Register_TB::clockGeneration()
{
    while (true)
    {
        wait(5, SC_NS);
        clk = SC_LOGIC_0;
        wait(5, SC_NS);
        clk = SC_LOGIC_1;
    }
    
}

void Register_TB::signalHandler()
{
    while (true)
    {
        wait(0, SC_NS);
        rst = SC_LOGIC_1;
        in = "10101010";
        load = SC_LOGIC_0;

        wait(37, SC_NS);
        rst = SC_LOGIC_0;

        wait(27, SC_NS);
        load = SC_LOGIC_1;

        for(int i = 0; i < 5; i++)
        {
            wait(13, SC_NS);
            in = in.read().to_int() + 1;
        }

        wait(27, SC_NS);
        load = SC_LOGIC_0;

        for(int i = 0; i < 5; i++)
        {
            wait(13, SC_NS);
            in = in.read().to_int() + 1;
        }
        

        wait();
    }
    
}