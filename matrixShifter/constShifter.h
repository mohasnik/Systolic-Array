#ifndef __CONSTSHIFTER_H__
#define __CONSTSHIFTER_H__

#include <systemc.h>
#include <iostream>
#include <fstream>

#define CONST_MATRIX_FILE_ADDRESS "init/consts.txt"


template<int ARR_SIZE, int WORD_SIZE>
SC_MODULE(CONSTSHIFTER)
{
    sc_in<sc_logic> clk, rst, startLoading;
    sc_out<sc_lv<WORD_SIZE>> coefsOut[ARR_SIZE];
    
    sc_uint<WORD_SIZE> constArr[ARR_SIZE][ARR_SIZE];

    uint8_t cycle;

    SC_CTOR(CONSTSHIFTER)
    {
        cycle = 0;
        readArrFile();

        SC_THREAD(seqFunc);
        sensitive << clk.pos() << rst;

    }

    void readArrFile();
    void seqFunc();

};

template<int ARR_SIZE, int WORD_SIZE>
void CONSTSHIFTER<ARR_SIZE, WORD_SIZE>::readArrFile()
{
    std::ifstream input(CONST_MATRIX_FILE_ADDRESS);
    for(int i = 0; i < ARR_SIZE; i++)
    {
        for(int j = 0; j < ARR_SIZE; j++)
        {
            input >> constArr[i][j];
        }
    }


    input.close();

    std::cout << "constArr recieved correctly : " << std::endl;
    std::cout << "constArr[0][0] : " << constArr[0][0] << std::endl;
    std::cout << "constArr[2][2] : " << constArr[2][2] << std::endl;

}

template<int ARR_SIZE, int WORD_SIZE>
void CONSTSHIFTER<ARR_SIZE, WORD_SIZE>::seqFunc()
{
    while (true)
    {
        if (rst == '1')
        {
            for (int i = 0; i < ARR_SIZE; i++)
            {
                coefsOut[i] = sc_lv<WORD_SIZE>(0);
                wait(0, SC_NS);
            }
        }
        else
        {
            if(startLoading.read() == SC_LOGIC_1)
            {
                wait(clk->posedge_event());
                wait(clk->posedge_event());
                for (int i = 0; i < ARR_SIZE+1; i++)
                {
                    for (int j = 0; j < ARR_SIZE; j++)
                    {
                        if(i == ARR_SIZE)
                            coefsOut[j] = sc_lv<WORD_SIZE>(0);
                        else
                            coefsOut[j] = sc_lv<WORD_SIZE>(constArr[ARR_SIZE - i -1][j]);

                    }
                    wait(clk->posedge_event());
                }
                
            }
        
        }

        wait();
    }
    
}






#endif