#pragma once
#include "global.h"
#include <fstream>
#include <iostream>
map<string,int> info_map;
void make_info_map()
{
	info_map["重庆/福州"] = 1;
	info_map["南京/重庆"] = 2;
	info_map["成都/丽江"] = 3;
	info_map["台州/大理"] = 4;
	info_map["成都/北京"] = 5;
	info_map["三亚/西安"] = 6;
	info_map["成都/福州"] = 7;
	info_map["长春/西安"] = 8;
	info_map["杭州/福州"] = 9;
	info_map["昆明/郑州"] = 10;
	info_map["昆明/三亚"] = 11;
	info_map["长春/三亚"] = 12;
	info_map["重庆/西安"] = 13;
	info_map["三亚/昆明"] = 14;
	info_map["大连/西安"] = 15;
	info_map["大连/昆明"] = 16;
	info_map["张家界/杭州"] = 17;
	info_map["海口/银川"] = 18;
	info_map["西安/北京"] = 19;
	info_map["张家界/重庆"] = 20;
	info_map["合肥/上海"] = 21;
	info_map["张家界/长春"] = 22;
	info_map["张家界/三亚"] = 23;
	info_map["郑州/大理"] = 24;
	info_map["台州/张家界"] = 25;
	info_map["海口/合肥"] = 26;
	info_map["郑州/大连"] = 27;
	info_map["杭州/大连"] = 28;
	info_map["长春/北京"] = 29;
	info_map["三亚/台州"] = 30;
	info_map["海口/大连"] = 31;
	info_map["南京/成都"] = 32;
	info_map["郑州/长春"] = 33;
	info_map["三亚/杭州"] = 34;
	info_map["海口/张家界"] = 35;
	info_map["成都/合肥"] = 36;
	info_map["大理/张家界"] = 37;
	info_map["南京/郑州"] = 38;
	info_map["南京/福州"] = 39;
	info_map["长春/合肥"] = 40;
	info_map["银川/郑州"] = 41;
	info_map["杭州/大理"] = 42;
	info_map["三亚/长春"] = 43;
	info_map["昆明/福州"] = 44;
	info_map["丽江/南京"] = 45;
	info_map["张家界/银川"] = 46;
	info_map["长春/大连"] = 47;
	info_map["北京/重庆"] = 48;
	info_map["上海/福州"] = 49;
	info_map["昆明/南京"] = 50;
	info_map["三亚/郑州"] = 51;
	info_map["台州/合肥"] = 52;
	info_map["大理/成都"] = 53;
	info_map["合肥/昆明"] = 54;
	info_map["大连/杭州"] = 55;
	info_map["北京/南京"] = 56;
	info_map["西安/上海"] = 57;
	info_map["银川/北京"] = 58;
	info_map["重庆/丽江"] = 59;
	info_map["南京/海口"] = 60;
	info_map["长春/台州"] = 61;
	info_map["大理/福州"] = 62;
	info_map["台州/昆明"] = 63;
	info_map["昆明/成都"] = 64;
	info_map["大连/北京"] = 65;
	info_map["南京/长春"] = 66;
	info_map["杭州/三亚"] = 67;
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