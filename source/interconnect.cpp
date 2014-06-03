/*
 * interconnect.cpp
 *
 *  Created on: 2013-11-3
 *      Author: hyq
 */

#include "interconnect.h"

void IntCnnt::refreshReg()
{
	int addr;
	int data;
	addr = addrIn.read();
	data = regIn.read();
	if (addr == 0)
	{
		reg.clear();
		regCount = 0;
	}
	if (addr < 40 && addr >= 0)
	{
		reg.push_back(data);
		regCount++;
		if(addr == 39)
		{
			for(int i = 0; i < 40; i++)
			{
				cout << reg[i] << endl;
			}
			cout << "end config" << endl;
		}
	}
	else
	{
		return;
	}
}

void IntCnnt::inOut()
{
	if(regCount < 40)
		return;
	int i;
	for(i = 0; i < 10; i++)
	{
		int tempIn, tempOut;
		tempOut = reg.at(i);
		if(tempOut < 10)
		{
			tempIn = reg.at(tempOut + 20);
			if(tempIn == i)
			{
				(*(this->outputDataLeft[tempOut])).write((*(this->inputDataLeft[i])).read());
			}
		}
		else
		{
			tempIn = reg.at(tempOut + 20);
			if(tempIn == i)
			{
				(*outputDataRight[tempOut - 10]).write((*inputDataLeft[i]).read());
			}
		}
	}

	for(i = 0; i < 10; i++)
	{
		int tempIn, tempOut;
		tempOut = reg.at(i + 10);
		if(tempOut < 10)
		{
			tempIn = reg.at(tempOut + 20);
			if(tempIn == i)
			{
				(*outputDataLeft[tempOut]).write((*inputDataRight[i]).read());
			}
		}
		else
		{
			tempIn = reg.at(tempOut + 20);
			if(tempIn == i)
			{
				(*outputDataRight[tempOut - 10]).write((*inputDataRight[i]).read());
			}
		}
	}
}
