/*
 * prc_element.h
 *
 *  Created on: 2013-11-3
 *      Author: hyq
 */

#ifndef PRC_ELEMENT_H_
#define PRC_ELEMENT_H_


#include "basic_define.h"
#include <vector>

class PrcElement : sc_module
{
public:
	sc_in<bool> clk;
	sc_in<sc_uint<8> > inputData0, inputData1;
	sc_out<sc_uint<8> > outputData0, outputData1;
	sc_in<sc_uint<6> > latencyIn;
	std::vector<sc_uint<8> > reg;

	int latency, function;
	bool ready;

	SC_HAS_PROCESS(PrcElement);
	void refreshLatency();
	void processFunc();

	PrcElement(sc_module_name name, int lat, int func)
		: sc_module(name), latency(lat), function(func)
	{
		ready = 0;
		SC_METHOD(refreshLatency);
		sensitive << latencyIn;
		SC_METHOD(processFunc);
		sensitive << clk.pos();

		for(int count = 0; count < latency + 1; count++)
		{
			reg.push_back(0);
		}
	}
};


#endif /* PRC_ELEMENT_H_ */
