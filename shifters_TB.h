#ifndef __SHIFTER_TB_H__
#define __SHIFTER_TB_H__

#include "arrayShifter.h"
#include "constShifter.h"

SC_MODULE(SHIFTER_TB)
{
    sc_signal<sc_logic> clk, rst, startLoading;
    sc_signal<sc_lv<8>> outs[3];

    // ARRAYSHIFTER<3, 8>* DUT;
    CONSTSHIFTER<3,8>* DUT;

    SC_CTOR(SHIFTER_TB)
    {
        // DUT = new ARRAYSHIFTER<3, 8>("DUT");
        // (*DUT)(clk, rst, startLoading, outs[0], outs[1], outs[2]);
        
        DUT = new CONSTSHIFTER<3, 8>("DUT");
        (*DUT)(clk, rst, startLoading, outs[0], outs[1], outs[2]);


        SC_THREAD(clocking);

        SC_THREAD(resetting);

        SC_THREAD(signalAssignment);

    }

    void clocking();
    void resetting();
    void signalAssignment();
};


void SHIFTER_TB::clocking()
{
    while (true)
    {
        wait(5, SC_NS);
        clk = SC_LOGIC_0;
        wait(5, SC_NS);
        clk = SC_LOGIC_1;
    }
}


void SHIFTER_TB::resetting()
{
    wait(10, SC_NS);
    rst = SC_LOGIC_1;
    wait(19, SC_NS);
    rst = SC_LOGIC_0;
}


void SHIFTER_TB::signalAssignment()
{
    while (true)
    {
        wait(0, SC_NS);
        startLoading = SC_LOGIC_0;

        wait(95, SC_NS);
        startLoading = SC_LOGIC_1;

        wait(10, SC_NS);
        startLoading = SC_LOGIC_0;

        wait();
    }
    
    
}




#endif