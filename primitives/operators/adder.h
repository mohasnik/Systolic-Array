#ifndef __ADDER_H__
#define __ADDER_H__

#include <systemc.h>

template<int SIZE>
SC_MODULE(Adder)
{
    sc_in<sc_lv<SIZE>> inA, inB;
    sc_in<sc_logic> carryIn;
    sc_out<sc_lv<SIZE>> result;
    sc_out<sc_logic> carryOut;

    SC_CTOR(Adder)
    {
        SC_METHOD(addOP);
            sensitive << inA << inB << carryIn;
    }

    void addOP();

};


template<int SIZE>
void Adder<SIZE>::addOP()
{
    sc_lv<SIZE+1> sum = inA->read().to_uint() + inB->read().to_uint() + carryIn->read().value();
    result = sum.range(SIZE-1, 0);
    carryOut = sum[SIZE];
}

#endif