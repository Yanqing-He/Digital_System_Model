/*
 * top_controller.h
 *
 *  Created on: 2013-11-12
 *      Author: hyq
 */

#ifndef TOP_CONTROLLER_H_
#define TOP_CONTROLLER_H_

#include "basic_define.h"
#include <string>
#include <iostream>

SC_MODULE(StrctCtrl)
{
	sc_in<bool> clk;
	sc_in<bool> reconfig;
	sc_in<sc_uint<3> > branchAddrIn;
	sc_out<bool> ready;
	sc_out<sc_uint<7> > regAddr;
	sc_out<sc_uint<6> > regData;

	std::vector<sc_uint<10> > startTable;
	std::vector<sc_uint<10> > stopTable;
	std::vector<std::string> addrTable;

	unsigned regAddrCnt;
	bool readyToSend, selfReconfig;
	int counter;

	void readAddrFile();
	void sendAddrData();
	void setSelfReconfig();

	SC_CTOR(StrctCtrl)
	{
		counter = 0;
		regAddrCnt = 0;
		readyToSend = 0;
		selfReconfig = 0;

		regAddr.initialize(255);
		regData.initialize(127);

		SC_THREAD(readAddrFile);
		SC_METHOD(sendAddrData);
		sensitive << clk.neg();
		SC_METHOD(setSelfReconfig);
		sensitive << reconfig.pos();
	}
};


#endif /* TOP_CONTROLLER_H_ */
