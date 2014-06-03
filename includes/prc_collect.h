/*
 * prc_collect.h
 *
 *  Created on: 2013-12-11
 *      Author: hyq
 */

#ifndef PRC_COLLECT_H_
#define PRC_COLLECT_H_

#include "prc_element.h"

SC_MODULE(PrcCollection)
{
	sc_in<bool> clk[10];
	sc_in<sc_uint<7> > regAddr;
	sc_in<sc_uint<6> > regData;
	bool ready[10];

	PrcElement *prcs[10];
	sc_signal<sc_uint<8> > *inSignal0[10], *inSignal1[10],*outSignal0[10], *outSignal1[10];
	sc_signal<sc_uint<6> > *latSignal[10];
	sc_in<sc_uint<8> > *dataIn0[10], *dataIn1[10];
	sc_out<sc_uint<8> > *dataOut0[10], *dataOut1[10];

	void refreshPrcs();
	void outputFunc();

	SC_CTOR(PrcCollection)
	{
		for(int i = 0; i < 10; i++)
		{
			std::ostringstream insName;
			insName << "prc_" << i << std::ends;
			prcs[i] = new PrcElement(insName.str().c_str(), 0, 3);
			dataIn0[i] = new sc_in<sc_uint<8> >;
			dataIn1[i] = new sc_in<sc_uint<8> >;
			dataOut0[i] = new sc_out<sc_uint<8> >;
			dataOut1[i] = new sc_out<sc_uint<8> >;
			inSignal0[i] = new sc_signal<sc_uint<8> >;
			inSignal1[i] = new sc_signal<sc_uint<8> >;
			outSignal0[i] = new sc_signal<sc_uint<8> >;
			outSignal1[i] = new sc_signal<sc_uint<8> >;
			latSignal[i] = new sc_signal<sc_uint<6> >;
			prcs[i]->clk(clk[i]);
			prcs[i]->inputData0(*inSignal0[i]);
			prcs[i]->inputData1(*inSignal1[i]);
			prcs[i]->outputData0(*outSignal0[i]);
			prcs[i]->outputData1(*outSignal1[i]);
			prcs[i]->latencyIn(*latSignal[i]);

		}
		SC_METHOD(refreshPrcs);
		sensitive << clk[0].neg();
		SC_METHOD(outputFunc);
		sensitive << clk[0].pos();
	}
};



#endif /* PRC_COLLECT_H_ */
