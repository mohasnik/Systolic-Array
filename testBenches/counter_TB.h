#ifndef __COUNTER_TB_H__
#define __COUNTER_TB_H__

#include "counter.h"


SC_MODULE(COUNTER_TB)
{
    sc_signal<sc_logic> clk, rst, cen, cOut;
    sc_signal<sc_lv<4>> parIn, cntOut;

    Counter<4>* counter;


    SC_CTOR(COUNTER_TB)
    {
        counter = new Counter<4>("DUT");
        (*counter)(clk, rst, cen, parIn, cntOut, cOut);

        SC_THREAD(clocking);
        
        SC_THREAD(resetting);;

        SC_THREAD(signaling);
    }

    void clocking();
    void resetting();
    void signaling();
};


void COUNTER_TB::clocking()
{
    while (true)
    {
        wait(5, SC_NS);
        clk = SC_LOGIC_0;
        wait(5, SC_NS);
        clk = SC_LOGIC_1;
    }
}

void COUNTER_TB::resetting()
{
    wait(10, SC_NS);
    rst = SC_LOGIC_1;
    wait(19, SC_NS);
    rst = SC_LOGIC_0;
}

void COUNTER_TB::signaling()
{
    while (true)
    {
        wait(0, SC_NS);
        cen = SC_LOGIC_0;
        parIn = sc_lv<4>(10);

        wait(70, SC_NS);
        cen = SC_LOGIC_1;

        wait(100, SC_NS);

        wait();
    }
    
}

#endif