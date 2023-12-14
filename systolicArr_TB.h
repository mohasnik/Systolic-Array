#ifndef __SYSARR_TB_H__
#define __SYSARR_TB_H__

#include "systolicArray/systolicArr_DP.h"
#include "systolicArray/systolicArr_CT.h"
#include "matrixShifter/arrayShifter.h"
#include "matrixShifter/constShifter.h"

#define ROW  3
#define COL 3
#define COUNTER_SIZE 3



SC_MODULE(SYSARR_TB)
{
    sc_signal<sc_logic> clk, rst, startLoading, startCalc, cen, cntDone, rstCounter, cntMode, busyLoading, startPE, busyPE;
    sc_signal<sc_lv<SIZE>> Din[ROW];
    sc_signal<sc_lv<SIZE>> Win[COL];
    sc_signal<sc_lv<SIZE*3>> Sin[COL];
    sc_signal<sc_lv<SIZE*3>> Sout[COL];
    sc_signal<sc_lv<SIZE>> Wout[COL];

    SYSARR_DP<ROW, COL, COUNTER_SIZE>* Datapath;
    SYSARR_CT* Controller;

    ARRAYSHIFTER<ROW, COL, SIZE>* arrShifter;
    CONSTSHIFTER<COL, SIZE>* constShifter;
    

    SC_CTOR(SYSARR_TB)
    {

        Datapath = new SYSARR_DP<ROW, COL, COUNTER_SIZE>("Datapath", Din, Win, Sin, Sout, Wout);
        Datapath->clk(clk);
        Datapath->rst(rst);
        Datapath->startPE(startPE);
        Datapath->busyPE(busyPE);
        Datapath->cntMode(cntMode);
        Datapath->cen(cen);
        Datapath->cntDone(cntDone);
        Datapath->rstCounter(rstCounter);


        Controller = new SYSARR_CT("Controller");
        Controller->clk(clk);
        Controller->rst(rst);
        Controller->co(cntDone);
        Controller->loadStart(startLoading);
        Controller->calcStart(startCalc);
        Controller->busyLoading(busyLoading);
        Controller->cen(cen);
        Controller->cntMode(cntMode);
        Controller->rstCounter(rstCounter);
        Controller->startPE(startPE);
        Controller->busyPE(busyPE);


        arrShifter = new ARRAYSHIFTER<ROW, COL, SIZE>("arrShifter");
        (*arrShifter)(clk, rst, startCalc, Din[0], Din[1], Din[2]);

        std::cout << "im here!" << std::endl;

        constShifter = new CONSTSHIFTER<COL, SIZE>("constShifter");
        (*constShifter)(clk, rst, startLoading, Win[0], Win[1], Win[2]);

        SC_THREAD(clocking);

        SC_THREAD(resetting);

        SC_THREAD(signalAssignment);

        SC_THREAD(setSinToZero);


        
    }

    void clocking();
    void resetting();
    void signalAssignment();
    void setSinToZero();

};

void SYSARR_TB::clocking()
{
    while (true)
    {
        wait(5, SC_NS);
        clk = SC_LOGIC_0;
        wait(5, SC_NS);
        clk = SC_LOGIC_1;
    }
}


void SYSARR_TB::resetting()
{
    wait(10, SC_NS);
    rst = SC_LOGIC_1;
    wait(19, SC_NS);
    rst = SC_LOGIC_0;
}


void SYSARR_TB::setSinToZero()
{
    for (int i = 0; i < COL; i++)
    {
        Sin[i] = sc_lv<SIZE * 3>(0);
    }
}

void SYSARR_TB::signalAssignment()
{
    while (true)
    {
        wait(0, SC_NS);
        startLoading = SC_LOGIC_0;
        startCalc = SC_LOGIC_0;

        

        wait(95, SC_NS);

        startLoading = SC_LOGIC_1;

        wait(30, SC_NS);
        startLoading = SC_LOGIC_0;


        wait(100, SC_NS);
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                std::cout << "W of PE[" << i << "][" << j << "] : " << Datapath->PEs[i][j]->datapath->WRegOut.read().to_uint() << std::endl;
            }
        }

        std::cout << std::endl << std::endl;

        wait(200, SC_NS);
        startCalc = SC_LOGIC_1;
        
        wait(10, SC_NS);
        startCalc = SC_LOGIC_0;

        for (int i = 0; i < 2; i++)
        {
            wait(130, SC_NS);
            //std::cout << "hello!!!" << std::endl;
            arrShifter->readArrFile("init/arr_part" + std::to_string(i+1) + ".txt");

            wait(0, SC_NS);
            startCalc = SC_LOGIC_1;

            wait(10, SC_NS);
            startCalc = SC_LOGIC_0;
        }
        
        



        wait(100, SC_NS);

        wait();
    }
    
}



#endif