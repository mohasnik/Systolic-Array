#include "systolicArr_TB.h"


using namespace std;

const char* vcdOutputAddress = "output/systolicArray_trace";

int sc_main(int argc, char** argv)
{

		
	SYSARR_TB* tb = new SYSARR_TB("tb");
	sc_trace_file* f = sc_create_vcd_trace_file(vcdOutputAddress);

	sc_trace(f, tb->clk, "clk");
	sc_trace(f, tb->rst, "rst");
	sc_trace(f, tb->Datapath->counter->cen, "sysDp_count_en");
	sc_trace(f, tb->Datapath->cntInit, "sysDp_count_init");

	sc_trace(f, tb->Datapath->cntOut, "sysDp_count_val");

	sc_trace(f, tb->startPE, "startPE");
	sc_trace(f, tb->busyPE, "busyPE");

	sc_trace(f, tb->startLoading, "startLoading");
	sc_trace(f, tb->startCalc, "startCalc");

	sc_trace(f, tb->Controller->p_state, "sysCT_present_state");
	

	sc_trace(f, tb->Din[0], "Din(0)");
	sc_trace(f, tb->Din[1], "Din(1)");
	sc_trace(f, tb->Din[2], "Din(2)");

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j  < COL; j++)
        {
            sc_trace(f, tb->Datapath->PEs[i][j]->datapath->DRegOut, "DReg_PE(" + std::to_string(i) + ")(" + std::to_string(j) + ")");
			sc_trace(f, tb->Datapath->PEs[i][j]->datapath->Sout, "Sout_PE(" + std::to_string(i) + ")(" + std::to_string(j) + ")");
        }
    }


	sc_trace(f, tb->Sout[0], "Sout_final(0)");
	sc_trace(f, tb->Sout[1], "Sout_final(1)");
	sc_trace(f, tb->Sout[2], "Sout_final(2)");


	
	

	sc_start(1000, SC_NS);

	return 0;
}