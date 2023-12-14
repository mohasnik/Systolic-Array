#ifndef __ARRAYSHIFTER_H__
#define __ARRAYSHIFTER_H__

#include <systemc.h>
#include <iostream>
#include <fstream>

#define ARRAY_FILE_ADDRESS "init/arr.txt"

template<int ROW, int COL, int WORD_SIZE>
SC_MODULE(ARRAYSHIFTER)
{
    sc_in<sc_logic> clk, rst, startTransfer;
    sc_out<sc_lv<WORD_SIZE>> arrOut[ROW];

    sc_uint<WORD_SIZE> arr[ROW][ROW + COL -1];
    

    SC_CTOR(ARRAYSHIFTER)
    {
        readArrFile();

        SC_THREAD(seqFunc);
            sensitive << clk.pos() << rst;
    }

    void readArrFile();
    void readArrFile(std::string addr);
    void seqFunc();
};


template<int ROW, int COL, int WORD_SIZE>
void ARRAYSHIFTER<ROW, COL, WORD_SIZE>::readArrFile(std::string addr)
{
    std::ifstream input(addr);
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < ROW + COL - 1; j++)
        {
            if(j >= i && j < i+ COL)
                input >> arr[i][j];
            else
                arr[i][j] = 0;
        }
    }
    input.close();

    std::cout << "arr recieved correctly : " << std::endl;

}

template<int ROW, int COL, int WORD_SIZE>
void ARRAYSHIFTER<ROW, COL, WORD_SIZE>::readArrFile()
{
    readArrFile(ARRAY_FILE_ADDRESS);
}

template<int ROW, int COL, int WORD_SIZE>
void ARRAYSHIFTER<ROW, COL, WORD_SIZE>::seqFunc()
{
    while (true)
    {
        if (rst == '1')
        {
            for (int i = 0; i < ROW; i++)
            {
                arrOut[i] = sc_lv<WORD_SIZE>(0);
                wait(0, SC_NS);
            }
        }
        else
        {
            if(startTransfer == '1')
            {
                std::cout << "i get here!" << std::endl;
                for (int i = 0; i < COL + ROW - 1; i++)
                {
                    for (int j = 0; j < ROW; j++)
                    {
                        arrOut[j] = sc_lv<WORD_SIZE>(arr[j][i]);
                    }
                    wait(clk->posedge_event());
                }
            }
            
        }

        wait();
    }
    
}



#endif