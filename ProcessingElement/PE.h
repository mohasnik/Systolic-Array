// MODULE : PE
// The complete description of Processing Element (PE) 
// after connecting datapath (PE_DP) and controller (PE_CT) together
// This module is the base of element of the whole Systolic array
// the value SIZE shows the bit-width of PE module
//
// -------------------------------------------------------------------------

#ifndef __PE_H__
#define __PE_H__

#include <systemc.h>
#include "PE_DP.h"
#include "PE_CT.h"

template<int SIZE>
SC_MODULE(PE)
{
    // input output ports
    sc_in<sc_logic> clk, rst, startPE, busyPE;
    sc_in<sc_lv<SIZE*3>> Sin;
    sc_in<sc_lv<SIZE>> Din, Win;
    sc_out<sc_lv<SIZE*3>> Sout;
    sc_out<sc_lv<SIZE>> Dout, Wout;

    // instances
    PE_DP<SIZE>* datapath;
    PE_CT* controller;

    // internal wirings :
    sc_signal<sc_logic> ldW, ldD, ldS;

    SC_CTOR(PE)
    {
        //datapath port connections
        datapath = new PE_DP<SIZE>("PE_datapath");
        datapath->clk(clk);
        datapath->rst(rst);
        datapath->ldW(ldW);
        datapath->ldD(ldD);
        datapath->ldS(ldS);
        datapath->Sin(Sin);
        datapath->Din(Din);
        datapath->Win(Win);
        datapath->Sout(Sout);
        datapath->Dout(Dout);
        datapath->Wout(Wout);

        // controller port connections
        controller = new PE_CT("PE_controller");
        controller->clk(clk);
        controller->rst(rst);
        controller->startPE(startPE);
        controller->busyPE(busyPE);
        controller->ldW(ldW);
        controller->ldD(ldD);
        controller->ldS(ldS);



    }

    
    
};


#endif

