#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include "b_plus_tree.h"
#include "global.h"
#include "customer_info.h"
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
	customer_info customers;//用户信息管理类
	list<flight_time_node*> flight_time_chain;
	void insert_flight_info();
	flight_time_node* find_node_by_data(string data);//寻找日期所在的节点
	void get_info_from_file();//从文件中获取已存航班信息，仅debug使用
	void buy_ticket();//购票
	void solve_buying_info(flight_information_node* flight_info);//处理购票时的信息更新
};
int main()
{
	make_info_map();//初始化map
	flight_information test;
	test.get_info_from_file();
	test.customers.get_info_from_file();
	//test.customers.create_account();
	//test.customers.login();
	//test.customers.get_info_from_file();
	test.buy_ticket();
	//test.buy_ticket();
	/*
	//test.insert_flight_info();
	test.get_info_from_file();
	test.search_flight_info();*/
	//customer_info customers;
	//customers.login();
	/*customers.create_account();
	customers.search_customer_info(100000);*/
}
flight_time_node::flight_time_node(string time)
{
	tree = new b_plus_tree(level);
	departure_time = time;
}
void flight_information::insert_flight_info()
{
	string flight_number;
	string company_name;//航空公司名称
	string departure;//航班起飞地
	string destination;//航班降落地
	string stop = "";//航班经停地点
	string departure_start_time;//出发地起飞时间
	string stop_arrive_time = "";//到达经停地时间
	string stop_start_time = "";//由经停地起飞时间
	string destination_arrive_time;//目的地到达时间
	int remain_number_normal;//剩余票数
	int remain_number_vip;
	float price_normal;//普通票价
	float price_vip;//公务舱票价

	int has_stop = 0;
	cout<<"请输入航班号:";
	cin>>flight_number;
	cout<<"请输入航空公司名称:";
	cin>>company_name;
	cout<<"请输入航班起飞地:";
	cin>>departure;
	cout<<"请输入航班降落地:";
	cin>>destination;
	cout<<"请输入出发点起飞时间:";
	cin>>departure_start_time;
	cout<<"是否有经停地点(有：1，无：0):";
	cin>>has_stop;
	if(has_stop == 1)
	{
		cout<<"请输入经停地点:";
		cin>>stop;
		cout<<"请输入到达经停地时间:";
		cin>>stop_arrive_time;
		cout<<"请输入由经停地起飞时间:";
		cin>>stop_start_time;
	}
	cout << "请输入到达目的地时间:";
	cin>>destination_arrive_time;
	cout<<"请输入客舱总票数:";
	cin>>remain_number_normal;
	cout<<"请输入商务舱总票数:";
	cin>>remain_number_vip;
	cout<<"请输入普通票价:";
	cin>>price_normal;
	cout<<"请输入VIP票价:";
	cin>>price_vip;
	//时间格式：2020/03/18/13:28，存储格式：2020/03/18
	flight_time_node* target = find_node_by_data(departure_start_time.substr(0,10));
	if(!target)
	{
		target = new flight_time_node(departure_start_time.substr(0,10));
		flight_time_chain.push_back(target);
	}
	flight_information_node* information_node;
	if(has_stop == 1)
		information_node = new flight_information_node(flight_number,company_name,departure,destination,stop,departure_start_time,stop_arrive_time,stop_start_time,destination_arrive_time,remain_number_normal,remain_number_vip,price_normal,price_vip);
	else
		information_node = new flight_information_node(flight_number,company_name,departure,destination,departure_start_time,destination_arrive_time,remain_number_normal,remain_number_vip,price_normal,price_vip);
	target->tree->insert_flight_info(information_node);
}
flight_time_node* flight_information::find_node_by_data(string data)
{
	for(list<flight_time_node*>::iterator iter = flight_time_chain.begin();iter != flight_time_chain.end();iter++)  
  	{  
  		//cout<<(*iter)->departure_time;
    	if((*iter)->departure_time == data)
    		return *iter;
  	}  
	return NULL;
}
void flight_information::get_info_from_file()
{
	ifstream flight_info;
    flight_info.open("flight_info.in", ios::in);
    while (!flight_info.eof())
	{
	    string flight_number;
		string company_name;//航空公司名称
		string departure;//航班起飞地
		string destination;//航班降落地
		string stop = "";//航班经停地点
		string departure_start_time;//出发地起飞时间
		string stop_arrive_time = "";//到达经停地时间
		string stop_start_time = "";//由经停地起飞时间
		string destination_arrive_time;//目的地到达时间
		int remain_number_normal;//剩余票数
		int remain_number_vip;
		float price_normal;//普通票价
		float price_vip;//公务舱票价
		int has_stop = 0;

		flight_info>>flight_number;
		flight_info>>company_name;
		flight_info>>departure;
		flight_info>>destination;
		flight_info>>departure_start_time;
		flight_info>>has_stop;
		if(has_stop == 1)
		{
			flight_info>>stop;
			flight_info>>stop_arrive_time;
			flight_info>>stop_start_time;
		}
		flight_info>>destination_arrive_time;
		flight_info>>remain_number_normal;
		flight_info >> remain_number_vip;
		flight_info>>price_normal;
		flight_info>>price_vip;

		flight_time_node* target = find_node_by_data(departure_start_time.substr(0,10));
		if(!target)
		{
			target = new flight_time_node(departure_start_time.substr(0,10));
			flight_time_chain.push_back(target);
		}
		flight_information_node* information_node;
		if(has_stop == 1)
			information_node = new flight_information_node(flight_number,company_name,departure,destination,stop,departure_start_time,stop_arrive_time,stop_start_time,destination_arrive_time,remain_number_normal,remain_number_vip,price_normal,price_vip);
		else
			information_node = new flight_information_node(flight_number,company_name,departure,destination,departure_start_time,destination_arrive_time,remain_number_normal,remain_number_vip,price_normal,price_vip);
		target->tree->insert_flight_info(information_node);
	}
	flight_info.close();
}
void flight_information::buy_ticket()
{
	string departure_time;
	string departure;
	string destination;
	cout<<"请输入出发日期:";
	cin>>departure_time;
	cout<<"请输入出发地:";
	cin>>departure;
	cout<<"请输入目的地:";
	cin>>destination;
	flight_time_node* target_day = find_node_by_data(departure_time);
	if(!target_day)
	{
		cout<<"暂无"<<departure_time<<"航班相关信息";
		return;
	}
	int number = 1;
	string position = departure+"/"+destination;
	int data = info_map[position];
	list<flight_information_node*> info_list = target_day->tree->find_info_list(data);
	cout<<"航班信息:"<<endl;
	for(list<flight_information_node*>::iterator iter = info_list.begin();iter != info_list.end();iter++)  
  	{  
  		cout<<"第"<<number<<"条:"<<endl;
  		cout<<"航班号:"<<(*iter)->flight_number<<endl;
    	cout<<"航空公司:"<<(*iter)->company_name<<endl;
    	cout<<"起始地:"<<(*iter)->departure<<endl;
    	cout<<"目的地:"<<(*iter)->destination<<endl;
    	cout<<"起飞时间:"<<(*iter)->departure_start_time<<endl;
    	cout<<"到达时间:"<<(*iter)->destination_arrive_time<<endl;
    	cout<<endl;
    	number++;
  	}
	cout<<"请输入您想要购买的航班：";
	int target;
	cin>>target;
	int i = 1;
	list<flight_information_node*>::iterator iter;
	for(iter = info_list.begin();iter != info_list.end();iter++,i++)
	{
		if(i == target)
			break;
	}
	solve_buying_info(*iter);

}
void flight_information::solve_buying_info(flight_information_node* flight_info)
{
	customer_info_node* customer = customers.search_customer_info(login_account);
	cout<<"客舱剩余票数:"<<flight_info->remain_number_normal<<endl;
	cout<<"客舱票价:"<<flight_info->price_normal<<endl;
	cout<<"商务舱剩余票数:"<<flight_info->remain_number_vip<<endl;
	cout<<"商务舱票价:"<<flight_info->price_vip<<endl;
	cout<<"请输入您所想要购买的类型:\n客舱:1  商务舱:2"<<endl;
	int type;
	cin>>type;
	int have_buy = 0;//判断是否已经购票
	if(type == 1)//客舱
	{
		if(flight_info->remain_number_normal == 0)
		{
			flight_info->appointment.push(login_account);
			cout<<"已为您预约此票！"<<endl;
		}
		else
		{

			flight_info->remain_number_normal -= 1;
			flight_info->buying_customer.push_back(login_account);
			cout<<"购票成功！"<<endl;
			have_buy = 1;
		}
	}
	else if(type == 2)//商务舱
	{
		if(flight_info->remain_number_vip == 0)
		{
			flight_info->appointment.push(login_account);
			cout<<"已为您预约此票！"<<endl;
		}
		else
		{
			flight_info->remain_number_vip -= 1;
			flight_info->buying_customer.push_back(login_account);
			cout<<"购票成功！"<<endl;
			have_buy = 1;
		}
	}
	if(have_buy)
	{
		have_buy_info *ticket_info = new have_buy_info();
		ticket_info->set_info(flight_info->flight_number,flight_info->company_name,flight_info->departure,flight_info->destination,flight_info->stop,flight_info->departure_start_time,flight_info->stop_arrive_time,flight_info->stop_start_time,flight_info->destination_arrive_time,type);
		customer->ticket_info_list.push_back(ticket_info);
		cout<<"写入成功！";
	}
}