#pragma once
#include <map>
#include <string>
using namespace std;
extern map<string,int> info_map;//根据起始地与出发地创建的map
void make_info_map();//创建map

const int level=5;//b+树的level
extern unsigned int account;//账号值
extern unsigned int login_account;//当前登录的用户账号