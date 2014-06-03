/*
 * exec_ctrl.cpp
 *
 *  Created on: 2013-11-25
 *      Author: hyq
 */

#include "exec_ctrl.h"
#include <string>
#include <iostream>

void ExecCtrl::readFile()
{
	std::ifstream file;
	file.open("/home/hyq/workspace/501_proj_2/files/read_write");
	std::string readWriteData, BJAddrData;
	while(file.eof() != 1)
	{
		file >> readWriteData >> BJAddrData;
		if(file.eof() == 1)
		{
			break;
		}
		sc_bv<20> data;
		data = readWriteData.c_str();
		sc_bv<5> BJ;
		BJ = BJAddrData.c_str();
		readWrite.push_back(data);
		BJAddr.push_back(BJ);
		readWriteData.clear();
		BJAddrData.clear();
	}
	file.close();
	file.open("/home/hyq/workspace/501_proj_2/files/jump_branch_table");
	std::string data;
	while(file.eof() != 1)
	{
		file >> data;
		if(file.eof() == 1)
		{
			break;
		}
		sc_bv<13> jump;
		jump = data.c_str();
		jumpBranchTable.push_back(jump);
		data.clear();
	}
	file.close();

}

void ExecCtrl::sendData()
{
	if(selfReady == 0)
	{
		return;
	}
	else
	{
		reconfig.write(0);
		if(counter > (int)readWrite.size())
		{
			cout << "program ends" << endl;
			return;
		}
		if(BJAddr[counter].range(1, 0) == "00") //output addr
		{
			sc_biguint<20> readWriteData;
			readWriteData = readWrite[counter];
			startReadWrite.write(readWriteData);
			counter++;
		}
		else if(BJAddr[counter].range(1, 0) == "01") //jump
		{
			sc_uint<3> addr;
			addr = BJAddr[counter].range(4, 2).to_uint();
			sc_uint<10> jumpAddr = jumpBranchTable[addr].range(9, 0).to_uint();
			counter = jumpAddr;
		}
		else if(BJAddr[counter].range(1, 0) == "10") // branch
		{
			selfReady = 0;
			sc_uint<3> addr;
			addr = BJAddr[counter].range(4, 2).to_uint();
			sc_uint<10> jumpAddr = jumpBranchTable[addr].range(9, 0).to_uint();
			counter = jumpAddr;
			sc_uint<3> branchAddr = jumpBranchTable[addr].range(12, 10).to_uint();
			branchAddrOut.write(branchAddr);
			reconfig.write(1);
		}
		else // error
		{
			std::cout << "error in branch/jump" << std::endl;
			exit(-1);
		}
	}
}

void ExecCtrl::setSelfReady()
{
	if(ready.read() == 1)
	{
		selfReady = 1;
		//reconfig.write(0);
	}
}
