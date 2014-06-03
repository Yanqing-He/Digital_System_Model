/*
 * top_controller.cpp
 *
 *  Created on: 2013-11-12
 *      Author: hyq
 */

#include "strct_ctrl.h"

void StrctCtrl::readAddrFile()
{
		std::ifstream addrFile;
		addrFile.open("/home/hyq/workspace/501_proj_2/files/addr_file");
		std::string data;
		while (addrFile.eof() != 1)
		{
			getline(addrFile, data);
			addrTable.push_back(data);
		}
		addrFile.close();
		addrFile.open("/home/hyq/workspace/501_proj_2/files/start_end_file");
		std::string start, end;
		while (addrFile.eof() != 1)
		{
			addrFile >> start >> end;
			startTable.push_back(atoi(start.c_str()));
			stopTable.push_back(atoi(end.c_str()));
		}
}

void StrctCtrl::sendAddrData()
{
	if(selfReconfig == 1)
	{
		ready.write(0);
		if(regAddrCnt < stopTable[branchAddrIn.read()])
		{
			sc_bv<6> data;
			data = addrTable[regAddrCnt].c_str();
//			sc_uint<6> data;
//			data = atoi(addrTable[regAddrCnt].c_str());
			regAddr.write(counter);
			regData.write(data.to_uint());
			counter++;
			regAddrCnt++;
		}
		else if(regAddrCnt == stopTable[branchAddrIn.read()])
		{
			sc_uint<6> data;
			data = atoi(addrTable[regAddrCnt].c_str());
			regAddr.write(counter);
			regData.write(data);
			selfReconfig = 0;
			ready.write(1);
		}
	}
	else
	{
		regAddr.write(255);
		regData.write(127);
	}
}

void StrctCtrl::setSelfReconfig()
{
	if(reconfig.read() == 1)
	{
		selfReconfig = 1;
		regAddrCnt = startTable[branchAddrIn.read()];
		counter = 0;
	}
}

