#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include "b_plus_tree.h"
#include "global.h"
#include "customer_info.h"
#include "file.h"
#include <vector>
#include "sort.h"
#include <conio.h>
using namespace std;
class flight_time_node
{
public:
	string departure_time;//起飞时间
	b_plus_tree *tree;
	flight_time_node(string time);
};
class flight_information
{
public:
	Sort* sort_manager;//对用户查询结果进行排序
	file_manage* file_manager;
	customer_info customers;//用户信息管理类
	list<flight_time_node*> flight_time_chain;
	list<flight_information_node*>delay_list;//延误航班信息列表
	void insert_flight_info();
	flight_time_node* find_node_by_data(string data);//寻找日期所在的节点
	void get_info_from_file();//从文件中获取已存航班信息，仅debug使用
	void buy_ticket();//购票
	void solve_buying_info(flight_information_node* flight_info,int position_type);//处理购票时的信息更新,type:1:普通购票,2:换票
	void cancel_ticket();//退票
	flight_information_node* check_whether_fly(string departure_start_time,string departure,string destination,string flight_number);//此函数也可用于返回航班信息节点
	//判断是否已经起飞，注：待改进！！改进方向：飞机可能延迟起飞导致起飞时间对不上
	void delay_flight(string departure_start_time,string departure,string destination,string flight_number,int delay_minute);//飞机延迟
	void notice_flight();//通知飞机延误/取消
	void solve_change_ticket(flight_information_node*flight_node);//更换机票更新信息
	void cancel_flight(string departure_start_time,string departure,string destination,string flight_number);//飞机取消
	void plane_fly(string departure_start_time,string departure,string destination,string flight_number);//飞机起飞信息更新
	void search_ticket_by_city(string departure,string destination);
	void search_ticket_by_flight_number(string flight_number);
	void show_ticket_info(flight_information_node *target);
	void sort_flight_info(vector<flight_information_node*>& flight_info);
	void forDebug_run();//用于遍历整个链，仅用于debug
};