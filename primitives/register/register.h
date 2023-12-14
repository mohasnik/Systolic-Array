#ifndef __REGISTER_H__
#define __REGISTER_H__

#include <systemc.h>

template<int SIZE>
SC_MODULE(Register)
{
    sc_in<sc_logic> clk, rst, load;
    sc_in<sc_lv<SIZE> > input;
    sc_out<sc_lv<SIZE> > output;

    // SC_CTOR(Register)
    // {
    //     SC_METHOD(registerOP);
    //     sensitive << clk << rst;
    // }
    SC_HAS_PROCESS(Register);
    Register(sc_module_name);

    void registerOP();
};

template<int SIZE>
Register<SIZE>::Register(sc_module_name)
{
    SC_METHOD(registerOP);
        sensitive << clk << rst;
}

template<int SIZE>
void Register<SIZE>::registerOP()
{
    if (rst == '1')
        output = sc_lv<SIZE>(sc_logic_0);
    else if (clk.posedge())
    {
        if (load == '1')
            output = input;
    }
}


#endif