/*
 * prc_element.cpp
 *
 *  Created on: 2013-11-3
 *      Author: hyq
 */

#include "prc_element.h"
void PrcElement::refreshLatency()
{
	ready = 0;
	latency = latencyIn.read().range(3, 0);
	reg.clear();
	for(int count = 0; count < latency + 1; count++)
	{
		reg.push_back(0);
	}
	function = latencyIn.read().range(5, 4);
	ready = 1;
}

void PrcElement::processFunc()
{
	if(ready == 0)
	{
		return;
	}
	if(function == 0)
	{
		#include "/home/hyq/workspace/501_proj_2/files/func0"
	}
	else if(function == 1)
	{
		#include "/home/hyq/workspace/501_proj_2/files/func1"
	}
	else if(function == 2)
	{
		#include "/home/hyq/workspace/501_proj_2/files/func2"
	}
	else
	{
		exit(-1);
	}
}
