#include "PE_CT.h"


void PE_CT::setAllOutsToZero()
{
    ldW = SC_LOGIC_0;
    ldD = SC_LOGIC_0;
    ldS = SC_LOGIC_0;
}

void PE_CT::setPersentStateSignals()
{
    setAllOutsToZero();

    ldD = SC_LOGIC_1;

    switch (ps)
    {
    case STATE_IDLE:
        break;
    
    case STATE_LOAD_WEIGHT:
        ldW = SC_LOGIC_1;
        break;
    
    case STATE_MAC_OPERATION:
        ldS = SC_LOGIC_1;
        break;
    }
}


void PE_CT::setNextState()
{
    ns = STATE_IDLE;

    switch (ps)
    {
    case STATE_IDLE:
        if (startPE == '1')
            ns = STATE_LOAD_WEIGHT;
        else if(busyPE == '1')
            ns = STATE_MAC_OPERATION;
        else
            ns = ps;
        break;
    
    case STATE_LOAD_WEIGHT:
        if(startPE == '1')
            ns = STATE_LOAD_WEIGHT;
        else if(busyPE == '1')
            ns = STATE_MAC_OPERATION;
        else if(startPE == '0')
            ns = STATE_IDLE;
        else
            ns = ps;
        break;
    
    case STATE_MAC_OPERATION:
        if(startPE == '1')
            ns = STATE_LOAD_WEIGHT;
        else if(startPE == '0' && busyPE == '1')
            ns = STATE_MAC_OPERATION;
        else if(busyPE == '0')
            ns = STATE_IDLE;
        else
            ns = ps;
        break;
    }
}


void PE_CT::syncOP()
{
    if(rst == '1')
        ps = STATE_IDLE;
    else
    {
        ps = ns;

    }
}


void PE_CT::psNsTrack()
{
    while (true)
    {
        p_state = sc_lv<2>((int)(ps));
        n_state = sc_lv<2>((int)(ns));
        
        wait(0, SC_NS);
        //std::cout << "--> time : " << sc_time_stamp() << std::endl;
        //std::cout << "ps : " << ps << std::endl;
        //std::cout << "p_state : " << p_state.read().to_uint() << std::endl;
        //std::cout << "ns : " << ns << std::endl;
        //std::cout << "n_state : " << n_state.read().to_uint() << std::endl;
        wait();
    }
}