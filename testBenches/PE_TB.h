#ifndef __PE_TB_H__
#define __PE_TB_H__

#include "PE.h"

SC_MODULE(PE_TB)
{
    sc_signal<sc_logic> clk, rst, startPE, busyPE;
    sc_signal<sc_lv<24>> Sin, Sout;
    sc_signal<sc_lv<8>> Din, Dout, Win, Wout;

    PE<8>* DUT;
    


    SC_CTOR(PE_TB)
    {
        DUT = new PE<8>("DUT");
        DUT->clk(clk);
        DUT->rst(rst);
        DUT->startPE(startPE);
        DUT->busyPE(busyPE);
        DUT->Sin(Sin);
        DUT->Din(Din);
        DUT->Win(Win);
        DUT->Sout(Sout);
        DUT->Dout(Dout);
        DUT->Wout(Wout);

        SC_THREAD(clocking);

        SC_THREAD(resetting);

        SC_THREAD(signalAssigning);

    }


    void clocking();
    void resetting();
    void signalAssigning();

};


#endif