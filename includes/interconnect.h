/*
 * interconnect.h
 *
 *  Created on: 2013-11-3
 *      Author: hyq
 */

#ifndef INTERCONNECT_H_
#define INTERCONNECT_H_

#include "systemc.h"
#include <vector>

SC_MODULE(IntCnnt)
{
	sc_in<bool> clk;
	sc_in<sc_uint<7> > addrIn;
	sc_in<sc_uint<6> > regIn;
	sc_in<sc_uint<8> > *inputDataLeft[10], *inputDataRight[10];
	sc_out<sc_uint<8> > *outputDataLeft[10], *outputDataRight[10];

	std::vector<sc_uint<6> > reg;

	int regCount;

	void refreshReg();
	void inOut();

	SC_CTOR(IntCnnt)
	{
		regCount = 0;
		int i;
		for(i = 0; i < 10; i++)
		{
			inputDataLeft[i] = new sc_in<sc_uint<8> >;
			inputDataRight[i] = new sc_in<sc_uint<8> >;
			outputDataLeft[i] = new sc_out<sc_uint<8> >;
			outputDataRight[i] = new sc_out<sc_uint<8> >;
		}
		SC_METHOD(refreshReg);
		sensitive << clk.neg();
		SC_METHOD(inOut);
		sensitive << *inputDataLeft[0] << *inputDataLeft[1] << *inputDataLeft[2]
		          << *inputDataLeft[3] << *inputDataLeft[4] << *inputDataLeft[5]
		          << *inputDataLeft[6] << *inputDataLeft[7] << *inputDataLeft[8]
		          << *inputDataLeft[9]
		          << *inputDataRight[0] << *inputDataRight[1] << *inputDataRight[2]
		          << *inputDataRight[3] << *inputDataRight[4] << *inputDataRight[5]
		          << *inputDataRight[6] << *inputDataRight[7] << *inputDataRight[8]
		          << *inputDataRight[9];
	}
};



#endif /* INTERCONNECT_H_ */
