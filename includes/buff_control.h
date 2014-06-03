/*
 * buff_control.h
 *
 *  Created on: 2013-11-3
 *      Author: hyq
 */

#ifndef BUFF_CONTROL_H_
#define BUFF_CONTROL_H_

#include "systemc.h"
#include <vector>

SC_MODULE(BuffCtrl)
{
	sc_in<bool> clk;
	sc_in<bool> startRead, startWrite;
	sc_in<sc_uint<6> > dataLength;
	sc_in<sc_uint<8> > inputData;
	sc_out<sc_uint<8> > outputData;
	bool reading, writing;
	int readCounter, writeCounter;
	std::vector<sc_uint<8> > buffer;

	void setFlags();
	void readWrite();

	//BuffCtrl& operator=(BuffCtrl &B);

	SC_CTOR(BuffCtrl)
	{
		reading = 0;
		writing = 0;
		readCounter = 0;
		writeCounter = 0;
		for(int i = 0; i < 3; i++)
		{
			buffer.push_back(i + 1);
		}
		SC_METHOD(setFlags);
		sensitive << startRead.pos() << startWrite.pos();
		SC_METHOD(readWrite);
		sensitive << clk.pos();
	}
};


#endif /* BUFF_CONTROL_H_ */
