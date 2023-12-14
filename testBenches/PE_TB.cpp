#include "PE_TB.h"

void PE_TB::clocking()
{
    while (true)
    {
        wait(5, SC_NS);
        clk = SC_LOGIC_0;
        wait(5, SC_NS);
        clk = SC_LOGIC_1;
    }
    
}


void PE_TB::resetting()
{
    wait(10, SC_NS);
    rst = SC_LOGIC_1;
    wait(19, SC_NS);
    rst = SC_LOGIC_0;
}

void PE_TB::signalAssigning()
{
    while (true)
    {
        wait(0, SC_NS);
        startPE = SC_LOGIC_0;
        busyPE = SC_LOGIC_0;
        Win = sc_lv<8>(25);
        Din = sc_lv<8>(73);
        Sin = sc_lv<24>(10023);

        wait(53, SC_NS);
        startPE = SC_LOGIC_1;

        wait(95, SC_NS);
        startPE = SC_LOGIC_0;

        wait(25, SC_NS);
        busyPE = SC_LOGIC_1;
        
        wait(23, SC_NS);
        busyPE = SC_LOGIC_0;

        wait();
    }
    
}
