/*
 * bc_collect.cpp
 *
 *  Created on: 2013-11-6
 *      Author: hyq
 */

#include "bc_collect.h"

void BcCollection::refreshReg()
{
	sc_uint<7> addr;
	sc_uint<6> data;
	addr = addrIn.read();
	data = dataIn.read();
	if(addr >= 40 && addr < 50)
	{
		regIn[addr - 40] = data.range(0, 0);
		regOut[addr - 40] = data.range(1, 1);
	}
	if(addr >= 50 && addr < 60)
	{
		dataLenInput[addr - 50]->write(data);
	}
	else
	{
		return;
	}
}

void BcCollection::refreshReadWrite()
{
	sc_biguint<20> temp;
	temp = startReadWrite.read();
	int i;
	for(i = 0; i < 10; i++)
	{
		startRead[i]->write(temp.range(i, i) == 1);
	}
	for(i = 0; i < 10; i++)
	{
		startWrite[i]->write(temp.range(i + 10, i + 10) == 1);
	}
}

void BcCollection::outFunc()
{
	int i;
	for(i = 0; i < 10; i++)
	{
		if (regOut[i] == 0)
		{
			(*dataOutLeft[i])->write(buffs[i]->outputData.read());
		}
		else
		{
			(*dataOutRight[i])->write(buffs[i]->outputData.read());
		}
	}
}

void BcCollection::inFunc()
{
	int i;
	for(i = 0; i < 10; i++)
	{
		if(regIn[i] == 0)
		{
			dataInput[i]->write((*dataInLeft[i])->read());
		}
		else
		{
			dataInput[i]->write((*dataInRight[i])->read());
		}
	}
}
