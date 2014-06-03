/*
 * main.cpp
 *
 *  Created on: 2013-12-15
 *      Author: hyq
 */


#include "bc_collect.h"
#include "exec_ctrl.h"
#include "interconnect.h"
#include "prc_collect.h"
#include "strct_ctrl.h"

int sc_main(int argc, char* argv[])
{
	ExecCtrl execController("exec_controller");
	StrctCtrl strctController("strct_controller");
	BcCollection bufferCollection("buffer_collection0");
	PrcCollection prcCollection("prc_collection");
	IntCnnt interconnect("interconnect");

	// signal connection starts here
	// clock signal
	sc_clock clk("clock", 10, SC_NS);
	execController.clk(clk);
	strctController.clk(clk);
	interconnect.clk(clk);
	for(int i = 0; i < 10; i++)
	{
		bufferCollection.clk[i](clk);
		prcCollection.clk[i](clk);
	}

	// addr signals
	sc_signal<sc_uint<7> > regAddr;
	sc_signal<sc_uint<6> > regData;
	strctController.regAddr(regAddr);
	strctController.regData(regData);
	bufferCollection.addrIn(regAddr);
	bufferCollection.dataIn(regData);
	interconnect.addrIn(regAddr);
	interconnect.regIn(regData);
	prcCollection.regAddr(regAddr);
	prcCollection.regData(regData);

	// signals between 2 controller
	sc_signal<bool> ready, reconfig;
	sc_signal<sc_uint<3> > branchAddr;
	strctController.ready(ready);
	strctController.reconfig(reconfig);
	strctController.branchAddrIn(branchAddr);
	execController.ready(ready);
	execController.reconfig(reconfig);
	execController.branchAddrOut(branchAddr);

	// read_write signal
	sc_signal<sc_biguint<20> > readWrite;
	execController.startReadWrite(readWrite);
	bufferCollection.startReadWrite(readWrite);

	// signals between interconnect & prc collection
	sc_signal<sc_uint<8> > prcIn0Signals[10], prcIn1Signals[10], prcOut0Signals[10], prcOut1Signals[10];
	for(int i = 0; i < 10; i++)
	{
		(*prcCollection.dataIn0[i])(prcIn0Signals[i]);
		(*prcCollection.dataIn1[i])(prcIn1Signals[i]);
		(*prcCollection.dataOut0[i])(prcOut0Signals[i]);
		(*prcCollection.dataOut1[i])(prcOut1Signals[i]);
	}
	for(int i = 0; i < 5; i++)
	{
		(*interconnect.inputDataLeft[i * 2])(prcOut0Signals[i]);
		(*interconnect.inputDataLeft[i * 2 + 1])(prcOut1Signals[i]);
		(*interconnect.outputDataLeft[i * 2])(prcIn0Signals[i]);
		(*interconnect.outputDataLeft[i * 2 + 1])(prcIn1Signals[i]);
	}

	// signals between interconnect & bc collection
	sc_signal<sc_uint<8> > bcInLeftSignals[10], bcInRightSignals[10], bcOutLeftSignals[10], bcOutRightSignals[10];
	for(int i = 0; i < 10; i++)
	{
		(*bufferCollection.dataInLeft[i])(bcInLeftSignals[i]);
		(*bufferCollection.dataInRight[i])(bcInRightSignals[i]);
		(*bufferCollection.dataOutLeft[i])(bcOutLeftSignals[i]);
		(*bufferCollection.dataOutRight[i])(bcOutRightSignals[i]);
	}
	for(int i = 0; i < 10; i++)
	{
		(*interconnect.inputDataRight[i])(bcOutLeftSignals[i]);
		(*interconnect.outputDataRight[i])(bcInLeftSignals[i]);
	}

	// signal connection ends here

	// vcd file
	sc_trace_file *fp;
	fp = sc_create_vcd_trace_file("/home/hyq/workspace/501_proj_2/whole_system");
	sc_trace(fp, clk, "clock");
	sc_trace(fp, bcOutLeftSignals[0], "original_data");
	sc_trace(fp, ready, "reday");
	sc_trace(fp, reconfig, "reconfig");
	sc_trace(fp, bcInLeftSignals[6], "app1_output");
	sc_trace(fp, bcInLeftSignals[7], "app2_output");

	reconfig.write(0);
	branchAddr.write(0);
	sc_start(10, SC_NS);
	reconfig.write(1);
	branchAddr.write(1);
	sc_start(1990, SC_NS);
	sc_start(500, SC_NS);

	cout << "done!" << endl;
	sc_close_vcd_trace_file(fp);

	return 0;
}
