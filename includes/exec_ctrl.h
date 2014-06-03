/*
 * exec_ctrl.h
 *
 *  Created on: 2013-11-25
 *      Author: hyq
 */

#ifndef EXEC_CTRL_H_
#define EXEC_CTRL_H_

#include "systemc.h"
#include <vector>

SC_MODULE(ExecCtrl)
{
	sc_in<bool> clk;
	sc_in<bool> ready;
	sc_out<bool> reconfig;
	sc_out<sc_uint<3> > branchAddrOut;
	sc_out<sc_biguint<20> > startReadWrite;

	std::vector<sc_bv<5> > BJAddr;
	std::vector<sc_bv<20> > readWrite;
	std::vector<sc_bv<13> > jumpBranchTable;

	int counter;
	bool selfReady;

	void readFile();
	void sendData();
	void setSelfReady();

	SC_CTOR(ExecCtrl)
	{
		counter = 0;
		selfReady = 0;
		SC_THREAD(readFile);
		SC_METHOD(sendData);
		sensitive << clk.pos();
		SC_METHOD(setSelfReady);
		sensitive << ready.pos();
	}


};


#endif /* EXEC_CTRL_H_ */
