#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__

#include <systemc.h>

template<int SIZE>
SC_MODULE(Multiplier)
{
    sc_in<sc_lv<SIZE>> inA, inB;
    sc_out<sc_lv<2*SIZE>> result;


    SC_CTOR(Multiplier)
    {
        SC_METHOD(multiplicationOP);
            sensitive << inA << inB;
    }

    void multiplicationOP();
};


template<int SIZE>
void Multiplier<SIZE>::multiplicationOP()
{
    result = inA->read().to_uint() * inB->read().to_uint();
}


#endif