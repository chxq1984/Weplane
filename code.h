#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include "global.h"
using std::vector;
using namespace std;
class type_code
{
	string name,code;
public:
	string& retname(){return name;}
	string& retcode(){return code;}
};
class type_message
{
public:
	string name;
	int time,pretime;
};
class password
{
	string code,name;
	vector<type_code> store;
	vector<type_message> store_message;
public:
	int flag;//密码是否符合标准
	int times;//密码错误次数
	password(){code="";flag=0;}
	void input_information();
	void check_information();
	void add_information();
	void solve_code(string &code);//处理退格
	string add_dele_code(string temcode);//加密
	void change_code();//修改密码
	void dele_code();//注销账号
	void load_log_in();//读取登录信息
	void refresh_log_in();//刷新登录信息
	void add_log_in(const string &temname);//增加登录信息
	void dele_log_in();//删除登录信息
	string ret_name();//返回用户名
};