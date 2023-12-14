#ifndef __SYSTOLICARRAY_H__
#define __SYSTOLICARRAY_H__

#include <cmath>
#include "../ProcessingElement/PE.h"
#include "../primitives/counter/counter.h"



#define SIZE 8



template<int ROW, int COL, int COUNTER_SIZE>
SC_MODULE(SYSARR_DP)
{
    sc_in<sc_logic> clk, rst, startPE, busyPE, cntMode, cen, rstCounter;
    sc_in<sc_lv<SIZE>> Din[ROW];
    sc_in<sc_lv<SIZE>> Win[COL];
    sc_in<sc_lv<SIZE*3>> Sin[COL];
    sc_out<sc_lv<SIZE*3>> Sout[COL];
    sc_out<sc_lv<SIZE>> Wout[COL];
    sc_out<sc_logic> cntDone;

    PE<SIZE>* PEs[ROW][COL];
    Counter<COUNTER_SIZE>* counter;

    sc_signal<sc_lv<SIZE>> Dout[ROW][COL];
    sc_signal<sc_lv<SIZE>> W_internal[ROW-1][COL];
    sc_signal<sc_lv<SIZE*3>> S_internal[ROW-1][COL];
    sc_signal<sc_lv<COUNTER_SIZE>> cntInit, cntOut;

    SC_HAS_PROCESS(SYSARR_DP);
    SYSARR_DP(sc_module_name, sc_signal<sc_lv<SIZE>> _Din[], sc_signal<sc_lv<SIZE>> _Win[], sc_signal<sc_lv<SIZE*3>> _Sin[], sc_signal<sc_lv<SIZE*3>> _Sout[] , sc_signal<sc_lv<SIZE>> _Wout[]);
    

    void configureInputs(sc_in<sc_lv<SIZE>> inputs[], sc_signal<sc_lv<SIZE>> outSignals[], int size);
    void configureInputs(sc_in<sc_lv<SIZE*3>> inputs[], sc_signal<sc_lv<SIZE*3>> outSignals[], int size);
    void configureOutputs(sc_out<sc_lv<SIZE>> outputs[], sc_signal<sc_lv<SIZE>> outSignals[], int size);
    void configureOutputs(sc_out<sc_lv<SIZE*3>> outputs[], sc_signal<sc_lv<SIZE*3>> outSignals[], int size);
    void internalPEWiring();

    void cntInitSet();

};


template<int ROW, int COL, int COUNTER_SIZE>
SYSARR_DP<ROW, COL, COUNTER_SIZE>::SYSARR_DP(sc_module_name, sc_signal<sc_lv<SIZE>> _Din[], sc_signal<sc_lv<SIZE>> _Win[], sc_signal<sc_lv<SIZE*3>> _Sin[], sc_signal<sc_lv<SIZE*3>> _Sout[], sc_signal<sc_lv<SIZE>> _Wout[])
{
    configureInputs(Din, _Din, ROW);
    configureInputs(Win, _Win, COL);
    configureInputs(Sin, _Sin, COL);
    configureOutputs(Sout, _Sout, COL);
    configureOutputs(Wout, _Wout, COL);
    internalPEWiring();



    SC_METHOD(cntInitSet);
    sensitive << cntMode;
    
    counter = new Counter<COUNTER_SIZE>("counter");
    counter->clk(clk);
    counter->rst(rstCounter);
    counter->cen(cen);
    counter->cOut(cntDone);
    counter->parIn(cntInit);
    counter->cntOut(cntOut);


}

template<int ROW, int COL, int COUNTER_SIZE>
void SYSARR_DP<ROW, COL, COUNTER_SIZE>::internalPEWiring()
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            PEs[i][j] = new PE<SIZE>("name");
            (PEs[i][j])->clk(clk);
            (PEs[i][j])->rst(rst);
            (PEs[i][j])->startPE(startPE);
            (PEs[i][j])->busyPE(busyPE);
            (PEs[i][j])->Dout(Dout[i][j]);

            //setting Sin and Win :
            if(i==0)
            {
                (PEs[i][j])->Sin(Sin[j]);
                (PEs[i][j])->Win(Win[j]);
            }
            else
            {
                (PEs[i][j])->Sin(S_internal[i-1][j]);
                (PEs[i][j])->Win(W_internal[i-1][j]);
            }

            //setting Sout and Wout:
            if(i == ROW-1)
            {
                (PEs[i][j])->Sout(Sout[j]);
                (PEs[i][j])->Wout(Wout[j]);
            }
            else
            {
                (PEs[i][j])->Sout(S_internal[i][j]);
                (PEs[i][j])->Wout(W_internal[i][j]);
            }

            //setting Din :
            if(j==0)
            {
                (PEs[i][j])->Din(Din[i]);
            }
            else
            {
                (PEs[i][j])->Din(Dout[i][j-1]);
            }
        }
    }
}

//input port assignments for with input signals with the width of SIZE
template<int ROW, int COL, int COUNTER_SIZE>
void SYSARR_DP<ROW, COL, COUNTER_SIZE>::configureInputs(sc_in<sc_lv<SIZE>> inputs[], sc_signal<sc_lv<SIZE>> outSignals[], int size)
{
    for(int i = 0; i < size; i++)
    {
        inputs[i](outSignals[i]);
    }
}

//input port assignments for with input signals with the width of SIZE
template<int ROW, int COL, int COUNTER_SIZE>
void SYSARR_DP<ROW, COL, COUNTER_SIZE>::configureInputs(sc_in<sc_lv<SIZE*3>> inputs[], sc_signal<sc_lv<SIZE*3>> outSignals[], int size)
{
    for(int i = 0; i < size; i++)
    {
        inputs[i](outSignals[i]);
    }
}

template<int ROW, int COL, int COUNTER_SIZE>
void SYSARR_DP<ROW, COL, COUNTER_SIZE>::configureOutputs(sc_out<sc_lv<SIZE>> outputs[], sc_signal<sc_lv<SIZE>> outSignals[], int size)
{
    for(int i = 0; i < size; i++)
    {
        outputs[i](outSignals[i]);
    }
}

template<int ROW, int COL, int COUNTER_SIZE>
void SYSARR_DP<ROW, COL, COUNTER_SIZE>::configureOutputs(sc_out<sc_lv<SIZE*3>> outputs[], sc_signal<sc_lv<SIZE*3>> outSignals[], int size)
{
    for(int i = 0; i < size; i++)
    {
        outputs[i](outSignals[i]);
    }
}

template<int ROW, int COL, int COUNTER_SIZE>
void SYSARR_DP<ROW, COL, COUNTER_SIZE>::cntInitSet()
{
    if(cntMode == '0')
        cntInit = sc_lv<COUNTER_SIZE>(((1 << COUNTER_SIZE) - 1) - (2*COL + ROW - 2));
    else
        cntInit = sc_lv<COUNTER_SIZE>(((1 << COUNTER_SIZE) - 1) - ROW);
}


#endif