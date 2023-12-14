// MODULE : PE_DP
// The complete description of Processing Element (PE) 
// after connecting datapath (PE_DP) and controller (PE_CT) together
// This module is the base of element of the whole Systolic array
// the value SIZE shows the bit-width of PE module
//
// -------------------------------------------------------------------------


#ifndef __PE_DP_H__
#define __PE_DP_H__

#include <systemc.h>
#include "../primitives/Mux2To1.h"
#include "../primitives/register/register.h"
#include "../primitives/operators/multiplier.h"
#include "../primitives/operators/adder.h"


template<int SIZE>
SC_MODULE(PE_DP)
{

    sc_in<sc_logic> clk, rst, ldW, ldD, ldS;
    sc_in<sc_lv<SIZE*3>> Sin;
    sc_in<sc_lv<SIZE>> Din, Win;
    sc_out<sc_lv<SIZE*3>> Sout;
    sc_out<sc_lv<SIZE>> Dout, Wout;


    
    Register<SIZE>* DReg;
    Register<SIZE>* WReg;
    Register<SIZE*3>* SReg;

    Multiplier<SIZE>* multiplier;
    Adder<SIZE*3>* adder;

    sc_signal<sc_logic> carryIn, carryOut;
    sc_signal<sc_lv<SIZE>> DRegOut, WRegOut;
    sc_signal<sc_lv<SIZE*2>> multOut;
    sc_signal<sc_lv<SIZE*3>> adderOut, multOutExt;

    SC_CTOR(PE_DP)
    {
        DReg = new Register<SIZE>("DReg");
        DReg->clk(clk);
        DReg->rst(rst);
        DReg->load(ldD);
        DReg->input(Din);
        DReg->output(DRegOut);

        WReg = new Register<SIZE>("WReg");
        WReg->clk(clk);
        WReg->rst(rst);
        WReg->load(ldW);
        WReg->input(Win);
        WReg->output(WRegOut);

        SReg = new Register<SIZE*3>("SReg");
        SReg->clk(clk);
        SReg->rst(rst);
        SReg->load(ldS);
        SReg->input(adderOut);
        SReg->output(Sout);

        adder = new Adder<SIZE*3>("adder");
        adder->inA(multOutExt);
        adder->inB(Sin);
        adder->carryIn(carryIn);
        adder->result(adderOut);
        adder->carryOut(carryOut);

        multiplier = new Multiplier<SIZE>("Mult");
        multiplier->inA(WRegOut);
        multiplier->inB(DRegOut);
        multiplier->result(multOut);

        SC_THREAD(constSignals);

        SC_METHOD(signExtension);
            sensitive << multOut;
        
        SC_METHOD(outValues);
            sensitive << DRegOut << WRegOut;
    }

    void constSignals();
    void signExtension();
    void outValues();
    

};

template<int SIZE>
void PE_DP<SIZE>::constSignals()
{
    carryIn.write(SC_LOGIC_0); // adder has no carry in -> carryin = 0

}

template<int SIZE>
void PE_DP<SIZE>::signExtension()
{
    sc_lv<3 * SIZE> extended = multOut.read().to_uint();
    multOutExt.write(extended);
}

template<int SIZE>
void PE_DP<SIZE>::outValues()
{
    Dout = DRegOut.read();
    Wout = WRegOut.read();
}

#endif