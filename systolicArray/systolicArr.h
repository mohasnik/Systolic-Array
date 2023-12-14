#ifndef __SYSARR_H__
#define __SYSARR_H__

#include "systolicArr_CT.h"
#include "systolicArr_DP.h"

template<int ROW, int COL, int COUNTER_SIZE>
SC_MODULE(SYSTOLIC_ARRAY)
{
    sc_in<sc_logic> clk, rst, startLoading, startCalc;
    sc_in<sc_lv<SIZE>> Din[ROW];
    sc_in<sc_lv<SIZE>> Win[COL];
    sc_out<sc_lv<SIZE*3>> Sout[COL];
    sc_out<sc_logic> busyLoading;

    SYSARR_CT* controller;
    SYSARR_DP<ROW, COL, COUNTER_SIZE>* datapath;

    sc_signal<sc_logic> cen, cntMode, rstCounter, startPE, busyPE, co;
    sc_signal<sc_lv<SIZE*3>> Sin[COL];
    sc_signal<sc_lv<SIZE*3>> _Sout[COL];
    sc_signal<sc_lv<SIZE>> Wout[COL];
    sc_signal<sc_lv<SIZE>> _Win[COL];
    sc_signal<sc_lv<SIZE>> _Din[ROW];

    SC_HAS_PROCESS(SYSTOLIC_ARRAY);
    SYSTOLIC_ARRAY(sc_module_name, sc_signal<sc_lv<SIZE>> _Din[], sc_signal<sc_lv<SIZE>> _Win[], sc_signal<sc_lv<SIZE*3>> _Sout[]);

    
    void sinSetToZero();
    void ioSyncronizing();
};


template<int ROW, int COL, int COUNTER_SIZE>
SYSTOLIC_ARRAY<ROW, COL, COUNTER_SIZE>::SYSTOLIC_ARRAY(sc_module_name, sc_signal<sc_lv<SIZE>> __Din[], sc_signal<sc_lv<SIZE>> __Win[], sc_signal<sc_lv<SIZE*3>> __Sout[])
{
    

    controller = new SYSARR_CT("sysArr_controller");
    (*controller)(clk, rst, co, startLoading, startCalc, busyLoading, cen, cntMode, rstCounter, startPE, busyPE);

    datapath = new SYSARR_DP<ROW, COL, COUNTER_SIZE>("sysArr_datapth", __Din, __Win, Sin, __Sout, Wout);
    datapath->clk(clk);
    datapath->rst(rst);
    datapath->startPE(startPE);
    datapath->busyPE(busyPE);
    datapath->cntMode(cntMode);
    datapath->cen(cen);
    datapath->rstCounter(rstCounter);
    datapath->cntDone(co);
    datapath->rstCounter(rstCounter);

    SC_THREAD(sinSetToZero);

    SC_METHOD(ioSyncronizing);
    for (int i = 0; i < COL; i++)
    {
        sensitive << datapath->Win[i] << datapath->Sout[i];
    }
    for (int i = 0; i < ROW; i++)
    {
        sensitive << Din[i];
    }
}

template<int ROW, int COL, int COUNTER_SIZE>
void SYSTOLIC_ARRAY<ROW, COL, COUNTER_SIZE>::sinSetToZero()
{
    for(int i = 0; i < COL; i++)
    {
        Sin[i] = sc_lv<SIZE*3>(0);
    }
}

template<int ROW, int COL, int COUNTER_SIZE>
void SYSTOLIC_ARRAY<ROW, COL, COUNTER_SIZE>::ioSyncronizing()
{
    for (int i = 0; i < COL; i++)
    {
        _Win[i] = Win[i].read();
        Sout[i] = _Sout[i].read();
    }
    for (int i = 0; i < ROW; i++)
    {
        _Din[i] = Din[i].read();
    }
}


#endif