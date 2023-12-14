#ifndef __SYSARR_CT_H__
#define __SYSARR_CT_H__

#include <systemc.h>

SC_MODULE(SYSARR_CT)
{
    sc_in<sc_logic> clk, rst, co, loadStart, calcStart;
    sc_out<sc_logic> busyLoading, cen, cntMode, rstCounter, startPE, busyPE;

    enum states {STATE_IDLE, STATE_LOAD_CNT_PREP, STATE_LOADING, STATE_CALC};
    
    sc_signal<states> ps, ns;
    sc_signal<sc_lv<2>> p_state, n_state;

    SC_CTOR(SYSARR_CT)
    {
        SC_METHOD(setPersentStateSignals);
            sensitive << ps;
        
        SC_METHOD(setNextState);
            sensitive << ps << co << loadStart << calcStart;

        SC_METHOD(seqOP);
            sensitive << clk.pos() << rst;

        SC_THREAD(psNsTrack);
        sensitive << ps << ns;
    }

    void setAllOutsToZero();
    void setPersentStateSignals();
    void setNextState();
    void seqOP();
    void psNsTrack();

};



#endif