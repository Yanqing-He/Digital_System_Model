/*
 * buff_control.cpp
 *
 *  Created on: 2013-11-3
 *      Author: hyq
 */

#include "buff_control.h"

void BuffCtrl::setFlags()
{
	if(startWrite.read() == 1)
	{
		writing = 1;
	}
	if(startRead.read() == 1)
	{
		reading = 1;
	}
}

void BuffCtrl::readWrite()
{
	if(writing == 1)
	{
		if(writeCounter < (int)dataLength.read())
		{
			buffer[writeCounter] = inputData.read();
			writeCounter++;
		}
		else
		{
			writing = 0;
			writeCounter = 0;
		}
	}
	if(reading == 1)
	{
		if(readCounter < (int)dataLength.read())
		{
			int temp = dataLength.read();
			outputData.write(buffer.at(readCounter));
			readCounter++;
		}
		else
		{
			reading = 0;
			readCounter = 0;
		}
	}
}
