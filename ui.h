#pragma once
#include <iostream>
#include <conio.h>
#include "flight_information.h"
#include "code.h"
using namespace std;

class UI
{
public:
	flight_information manager;
	int main_width,main_height;
	UI();
	void main_window();
	void default_setting();//初始化
	void header();
	void footer();
	void login_customer();//用户登录
	void register_customer();//用户注册
	char customer_login_choose();//登录主界面
	char choose_login();//判断登录对象
	char choose_buy_cancel();//判断是买票还是退票
	void buying_ticket();//买票
	void cancel_ticket();//退票
	void login_administor();//管理员登录
	char administor_operator();//管理员操作
	void add_flight();//增加航班
	void deny_flight();//航班延误
	void cancel_flight();//航班取消
	void fly_flight();//航班起飞
};