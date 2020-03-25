#pragma once
#include "global.h"
#include <fstream>
map<string,int> info_map;
void make_info_map()
{
	info_map["北京/广州"] = 1;
	info_map["上海/福州"] = 2;
}
int global_transform(string departure,string destination)
{
	string data = departure+"/"+destination;
	return info_map[data];
}
int isfile_empty(string file_name)
{
	ifstream fin(file_name.c_str());
	char c;
	fin>>c;
	if(fin.eof())
	{
		fin.close();
		return 1;
	}
	else
	{
		fin.close();
		return 0;
	}
}
unsigned int account = 100000;
unsigned int login_account;