#pragma once
#include "global.h"
#include <fstream>
#include <iostream>
map<string,int> info_map;
void make_info_map()
{
	info_map["����/����"] = 1;
	info_map["�Ͼ�/����"] = 2;
	info_map["�ɶ�/����"] = 3;
	info_map["̨��/����"] = 4;
	info_map["�ɶ�/����"] = 5;
	info_map["����/����"] = 6;
	info_map["�ɶ�/����"] = 7;
	info_map["����/����"] = 8;
	info_map["����/����"] = 9;
	info_map["����/֣��"] = 10;
	info_map["����/����"] = 11;
	info_map["����/����"] = 12;
	info_map["����/����"] = 13;
	info_map["����/����"] = 14;
	info_map["����/����"] = 15;
	info_map["����/����"] = 16;
	info_map["�żҽ�/����"] = 17;
	info_map["����/����"] = 18;
	info_map["����/����"] = 19;
	info_map["�żҽ�/����"] = 20;
	info_map["�Ϸ�/�Ϻ�"] = 21;
	info_map["�żҽ�/����"] = 22;
	info_map["�żҽ�/����"] = 23;
	info_map["֣��/����"] = 24;
	info_map["̨��/�żҽ�"] = 25;
	info_map["����/�Ϸ�"] = 26;
	info_map["֣��/����"] = 27;
	info_map["����/����"] = 28;
	info_map["����/����"] = 29;
	info_map["����/̨��"] = 30;
	info_map["����/����"] = 31;
	info_map["�Ͼ�/�ɶ�"] = 32;
	info_map["֣��/����"] = 33;
	info_map["����/����"] = 34;
	info_map["����/�żҽ�"] = 35;
	info_map["�ɶ�/�Ϸ�"] = 36;
	info_map["����/�żҽ�"] = 37;
	info_map["�Ͼ�/֣��"] = 38;
	info_map["�Ͼ�/����"] = 39;
	info_map["����/�Ϸ�"] = 40;
	info_map["����/֣��"] = 41;
	info_map["����/����"] = 42;
	info_map["����/����"] = 43;
	info_map["����/����"] = 44;
	info_map["����/�Ͼ�"] = 45;
	info_map["�żҽ�/����"] = 46;
	info_map["����/����"] = 47;
	info_map["����/����"] = 48;
	info_map["�Ϻ�/����"] = 49;
	info_map["����/�Ͼ�"] = 50;
	info_map["����/֣��"] = 51;
	info_map["̨��/�Ϸ�"] = 52;
	info_map["����/�ɶ�"] = 53;
	info_map["�Ϸ�/����"] = 54;
	info_map["����/����"] = 55;
	info_map["����/�Ͼ�"] = 56;
	info_map["����/�Ϻ�"] = 57;
	info_map["����/����"] = 58;
	info_map["����/����"] = 59;
	info_map["�Ͼ�/����"] = 60;
	info_map["����/̨��"] = 61;
	info_map["����/����"] = 62;
	info_map["̨��/����"] = 63;
	info_map["����/�ɶ�"] = 64;
	info_map["����/����"] = 65;
	info_map["�Ͼ�/����"] = 66;
	info_map["����/����"] = 67;
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