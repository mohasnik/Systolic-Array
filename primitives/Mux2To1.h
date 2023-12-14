#ifndef __MUX_H__
#define __MUX_H__

#include <systemc.h>

template<int SIZE>
SC_MODULE(Mux2To1)
{
    sc_in<sc_lv<SIZE>> in0;
    sc_in<sc_lv<SIZE>> in1;
    sc_in<sc_logic> select;
    sc_out<sc_lv<SIZE>> out;

    SC_CTOR(Mux2To1)
    {
        SC_METHOD(MuxOP);
            sensitive << in0 << in1 << select;
    }

    void MuxOP();
};


template<int SIZE>
void Mux2To1<SIZE>::MuxOP()
{
    if(select == '1')
        out = in1;
    else
        out = in0;

}


#endif