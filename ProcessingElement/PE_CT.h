#ifndef __PE_CT_H__
#define __PE_CT_H__

#include <systemc.h>


SC_MODULE(PE_CT)
{
    sc_in<sc_logic> clk, rst, startPE, busyPE;
    sc_out<sc_logic> ldW, ldD, ldS;

    enum states {STATE_IDLE, STATE_LOAD_WEIGHT, STATE_MAC_OPERATION};

    sc_signal<states> ps, ns;
    sc_signal<sc_lv<2>> p_state, n_state;

    SC_CTOR(PE_CT)
    {
        SC_METHOD(setPersentStateSignals);
            sensitive << ps;
        SC_METHOD(setNextState);
            sensitive << ps << startPE << busyPE;
        SC_METHOD(syncOP);
            sensitive << clk.pos() << rst;
        SC_THREAD(psNsTrack);
            sensitive << ps << ns;
    }

    void setPersentStateSignals();
    void setNextState();
    void syncOP();
    void setAllOutsToZero();
    void psNsTrack();
};


#endif