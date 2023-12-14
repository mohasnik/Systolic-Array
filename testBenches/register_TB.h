#include "../register.h"

SC_MODULE(Register_TB)
{
    sc_signal<sc_logic> clk, rst, load;
	sc_signal<sc_lv<8>> in, out;

    Register<8>* DUT;

    SC_CTOR(Register_TB)
    {
        DUT = new Register<8>("myReg");
            DUT->clk(clk);
            DUT->rst(rst);
            DUT->load(load);
            DUT->input(in);
            DUT->output(out);

        SC_THREAD(clockGeneration);
        SC_THREAD(signalHandler);
            sensitive << clk.posedge_event();
        
    }

    void clockGeneration();
    void signalHandler();
};
