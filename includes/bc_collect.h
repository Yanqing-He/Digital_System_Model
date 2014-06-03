/*
 * bc_collect.h
 *
 *  Created on: 2013-11-6
 *      Author: hyq
 */

#ifndef BC_COLLECT_H_
#define BC_COLLECT_H_

#include "basic_define.h"
#include "buff_control.h"
#include <vector>
#include <string>

SC_MODULE(BcCollection)
{
	BuffCtrl *buffs[10];
	bool regIn[10], regOut[10];

	sc_signal<bool> *startRead[10], *startWrite[10];
	sc_signal<sc_uint<8> > *dataInput[10], *dataOutput[10];
	sc_signal<sc_uint<6> > *dataLenInput[10];

	//sc_in<bool> clk;
	sc_in<bool> clk[10];
	sc_in<sc_uint<8> > *dataInLeft[10], *dataInRight[10];
	sc_out<sc_uint<8> > *dataOutLeft[10], *dataOutRight[10];
	sc_in<sc_uint<7> > addrIn;
	sc_in<sc_uint<6> > dataIn;
	sc_in<sc_biguint<20> > startReadWrite; // need correction

	void refreshReg();
	void refreshReadWrite();
	void inFunc();
	void outFunc();

	SC_CTOR(BcCollection)
	{
		//this->clk(clk_signal);
		int i;
		for(i = 0; i < 10; i++)
		{
			std::ostringstream insName;
			insName << "buffer_" << i << std::ends;
			buffs[i] = new BuffCtrl(insName.str().c_str());
			startRead[i] = new sc_signal<bool>;
			startWrite[i] = new sc_signal<bool>;
			dataLenInput[i] = new sc_signal<sc_uint<6> >;
			dataInLeft[i] = new sc_in<sc_uint<8> >;
			dataInRight[i] = new sc_in<sc_uint<8> >;
			dataOutLeft[i] = new sc_out<sc_uint<8> >;
			dataOutRight[i] = new sc_out<sc_uint<8> >;
			dataInput[i] = new sc_signal<sc_uint<8> >;
			dataOutput[i] = new sc_signal<sc_uint<8> >;
		}
		for(i = 0; i < 10; i++)
		{
			buffs[i]->startRead(*startRead[i]);
			buffs[i]->startWrite(*startWrite[i]);
			buffs[i]->dataLength(*dataLenInput[i]);
			//buffs[i]->clk(clk_signal);
			buffs[i]->clk(clk[i]);
			buffs[i]->inputData(*dataInput[i]);
			buffs[i]->outputData(*dataOutput[i]);
		}
		SC_METHOD(refreshReg);
		sensitive << clk[0].neg();
		SC_METHOD(refreshReadWrite);
		sensitive << startReadWrite;
		SC_METHOD(inFunc);
		sensitive << *dataInLeft[0] << *dataInLeft[1] << *dataInLeft[2]
		          << *dataInLeft[3] << *dataInLeft[4] << *dataInLeft[5]
		          << *dataInLeft[6] << *dataInLeft[7] << *dataInLeft[8]
		          << *dataInLeft[9]
		          << *dataInRight[0] << *dataInRight[1] << *dataInRight[2]
		          << *dataInRight[3] << *dataInRight[4] << *dataInRight[5]
		          << *dataInRight[6] << *dataInRight[7] << *dataInRight[8]
		          << *dataInRight[9];
		SC_METHOD(outFunc);
		sensitive << *dataOutput[0] << *dataOutput[1]
				<< *dataOutput[2] << *dataOutput[3]
				<< *dataOutput[4] << *dataOutput[5]
				<< *dataOutput[6] << *dataOutput[7]
				<< *dataOutput[8] << *dataOutput[9];
	}
};



#endif /* BC_COLLECT_H_ */
