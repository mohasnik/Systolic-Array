#include "systolicArr_CT.h"


void SYSARR_CT::setAllOutsToZero()
{
    busyLoading = SC_LOGIC_0;
    cen = SC_LOGIC_0;
    cntMode = SC_LOGIC_0;
    rstCounter = SC_LOGIC_0;
    startPE = SC_LOGIC_0;
    busyPE = SC_LOGIC_0;
}

void SYSARR_CT::setNextState()
{
    ns = STATE_IDLE;

    switch (ps)
    {
    case STATE_IDLE:
        if(loadStart == '1')
            ns = STATE_LOAD_CNT_PREP;
        else if(calcStart == '1')
            ns = STATE_CALC;
        else
            ns = STATE_IDLE;
        break;
    
    case STATE_LOAD_CNT_PREP:
        ns = STATE_LOADING;
        break;
    
    case STATE_LOADING:
        if(co == '1')
            ns = STATE_IDLE;
        else
            ns = STATE_LOADING;
        break;

    case STATE_CALC:
        if(co == '1')
            ns = STATE_IDLE;
        else
            ns = STATE_CALC;
        break;
    
    
    default:
        break;
    }
}

void SYSARR_CT::setPersentStateSignals()
{
    setAllOutsToZero();

    switch (ps)
    {
    case STATE_IDLE:
        rstCounter = SC_LOGIC_1;
        break;
    case STATE_LOAD_CNT_PREP:
        cntMode = SC_LOGIC_1;
        rstCounter = SC_LOGIC_1;
        busyLoading = SC_LOGIC_1;
        break;
    
    case STATE_LOADING:
        cen = SC_LOGIC_1;
        startPE = SC_LOGIC_1;
        break;
    
    case STATE_CALC:
        busyPE = SC_LOGIC_1;
        cen = SC_LOGIC_1;
        break;
    
    default:
        break;
    }



}

void SYSARR_CT::seqOP()
{
    if(rst == '1')
    {
        ps = STATE_IDLE;
    }
    else
    {
        ps = ns;
    }
}

void SYSARR_CT::psNsTrack()
{
    while (true)
    {
        p_state = sc_lv<2>((int)(ps.read()));
        n_state = sc_lv<2>((int)(ns.read()));
        

        std::cout << "--> time : " << std::endl;
        std::cout << "ps : " << ps << std::endl;
        std::cout << "ns : " << ns << std::endl;
        wait();
    }
}



