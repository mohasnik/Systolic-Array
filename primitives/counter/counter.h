#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <systemc.h>


template<int SIZE>
SC_MODULE(Counter)
{
    sc_in<sc_logic> clk, rst, cen;
    sc_in<sc_lv<SIZE>> parIn;
    sc_out<sc_lv<SIZE>> cntOut;
    sc_out<sc_logic> cOut;

    

    SC_CTOR(Counter)
    {
        SC_METHOD(counting);
        sensitive << clk.pos() << rst;
        
        SC_METHOD(carryOut);
        sensitive << cntOut << rst << cen;
    }

    void counting();
    void carryOut();
};


template<int SIZE>
void Counter<SIZE>::counting()
{
    if(rst == '1')
        cntOut = parIn.read();
    else
    {
        if(cen.read() == '1')
            cntOut = cntOut.read().to_uint() + 1;
    }
}

template<int SIZE>
void Counter<SIZE>::carryOut()
{
    sc_logic c = SC_LOGIC_1;
    sc_lv<SIZE> cValue = cntOut.read();

    for(int i =0; i < SIZE; i++)
    {
        c &= cValue[i];
    }
    cOut = c;
}

#endif