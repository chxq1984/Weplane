#pragma once
#include "global.h"
map<string,int> info_map;
void make_info_map()
{
	info_map["北京/广州"] = 1;
	info_map["上海/福州"] = 2;
}
unsigned int account = 100000;