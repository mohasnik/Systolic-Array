#ifndef __SYSARR_BFM_H__
#define __SYSARR_BFM_H__

#include <systemc.h>
#include <vector>


#define WORD_SIZE 8

template<int ROW, int COL>
SC_MODULE(SYSARR_BFM)
{
    sc_in<sc_logic> clk, rst, startLoading, startCalc;
    sc_in<sc_lv<WORD_SIZE*3>> Sin[COL];
    sc_in<sc_lv<WORD_SIZE>> Din[ROW];
    sc_in<sc_lv<WORD_SIZE>> Win[COL];
    sc_out<sc_lv<WORD_SIZE*3>> Sout[COL];


    sc_uint<SIZE> W_Arr[COL][ROW];
    // sc_uint<SIZE*3> D_Arr[ROW][ROW + COL - 1];
    std::vector<sc_uint<SIZE*3>> D_Arr;


    SC_CTOR(SYSARR_BFM)
    {
        SC_THREAD(getCoefs);
        sensitive << clk.pos() << rst;

        SC_THREAD(calc);
        sensitive << clk.pos() << rst;
        
    }

    void getCoefs();
    void getDValues();
    void calc();




};


template<int ROW, int COL>
void SYSARR_BFM<ROW, COL>::getCoefs()
{
    while (true)
    {
        if(rst != '1' && startLoading == '1')
        {
            wait(clk.posedge_event());

            for(int i = 0; i < ROW; i++)
            {
                for(int j = 0; j < COL; j++)
                {
                    W_Arr[j][ROW - i -1] = Win[j]->read().to_uint();
                }
                wait(clk.posedge_event());
            }
            std::cout << "w matrix recieved" << std::endl;
        }

            wait();
    }
    
}



template<int ROW, int COL>
void SYSARR_BFM<ROW, COL>::calc()
{
    while (true)
    {
        if(rst == '1')
        {
            for(int i = 0; i < COL; i++)
            {
                Sout[i] = sc_lv<SIZE*3>(0);
            }
            wait(clk.posedge_event());
        }
        else if(startCalc == '1')
        {
            for(int i = 0; i < COL + ROW - 1; i++)
            {
                
            }
        }

        wait();
    }
    
}

template<int ROW, int COL>
void SYSARR_BFM<ROW, COL>::getDValues()
{
    
    
}


#endif