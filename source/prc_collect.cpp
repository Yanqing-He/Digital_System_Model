/*
 * prc_collect.cpp
 *
 *  Created on: 2013-12-11
 *      Author: hyq
 */


#include "prc_collect.h"

void PrcCollection::refreshPrcs()
{
	if(regAddr.read() >= 60 && regAddr.read() < 70)
	{
		int i = regAddr.read() - 60;
		latSignal[i]->write(regData.read());
//		int latency, function;
//		latency = regData.read().range(0, 3);
//		function = regData.read().range(4, 5);
//		delete prcs[regAddr.read() - 50];
//		delete inSignal0[regAddr.read() - 50];
//		delete inSignal1[regAddr.read() - 50];
//		std::ostringstream insName;
//		insName << "prc_" << regAddr.read() << std::ends;
//		prcs[regAddr.read() - 50] = new PrcElement(insName.str().c_str(), latency, function);
//		prcs[regAddr.read() - 50]->clk(clk[regAddr.read() - 50]);
//		prcs[regAddr.read() - 50]->inputData0(*inSignal0[regAddr.read() - 50]);
//		prcs[regAddr.read() - 50]->inputData1(*inSignal1[regAddr.read() - 50]);
//		prcs[regAddr.read() - 50]->outputData0(*outSignal0[regAddr.read() - 50]);
//		prcs[regAddr.read() - 50]->outputData1(*outSignal1[regAddr.read() - 50]);
	}
}

void PrcCollection::outputFunc()
{
	for(int i = 0; i < 10; i++)
	{
		inSignal0[i]->write(dataIn0[i]->read());
		inSignal1[i]->write(dataIn1[i]->read());
		dataOut0[i]->write(outSignal0[i]->read());
		dataOut1[i]->write(outSignal1[i]->read());
	}
}
