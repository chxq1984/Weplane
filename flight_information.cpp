#pragma once

#include <iostream>
#include <list>
#include <fstream>
#include "b_plus_tree.h"
#include "global.h"
#include "customer_info.h"
#include "file.h"
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
};
int main()
{
	make_info_map();//初始化map
	flight_information test;
	test.get_info_from_file();
	test.customers.get_info_from_file();
	
	/*string data="100000";
	test.file_manager = new notice_file();
	test.file_manager->delete_file(1,data);*/
	//test.buy_ticket();
	//test.customers.login();
	//test.buy_ticket();
	string departure_start_time="2020/03/18/20:00";
	string departure="北京";
	string destination="广州";
	string flight_number="1111";
	test.plane_fly(departure_start_time,departure,destination,flight_number);
	//test.notice_flight();
	//test.cancel_ticket();
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
	solve_buying_info(*iter,1);

}
void flight_information::solve_buying_info(flight_information_node* flight_info,int position_type)
{
	customer_info_node* customer = customers.search_customer_info(login_account);
	cout<<"客舱剩余票数:"<<flight_info->remain_number_normal<<endl;
	cout<<"客舱票价:"<<flight_info->price_normal<<endl;
	cout<<"商务舱剩余票数:"<<flight_info->remain_number_vip<<endl;
	cout<<"商务舱票价:"<<flight_info->price_vip<<endl;
	if(position_type == 1)
		cout<<"请输入您所想要购买的类型:\n客舱:1  商务舱:2"<<endl;
	else if(position_type == 2)
		cout<<"请输入您所想要换乘的类型:\n客舱:1  商务舱:2"<<endl;
	int type;
	cin>>type;
	int have_buy = 0;//判断是否已经购票
	float price;
	if(type == 1)//客舱
	{
		price = flight_info->price_normal;
		if(flight_info->remain_number_normal == 0)
		{
			flight_info->appointment_normal.push(login_account);
			cout<<"已为您预约此票！"<<endl;
		}
		else
		{

			flight_info->remain_number_normal -= 1;
			flight_info->buying_customer.push_back(login_account);
			if(position_type == 1)
				cout<<"购票成功！"<<endl;
			else if(position_type == 2)
				cout<<"换票成功！"<<endl;
			have_buy = 1;
		}
	}
	else if(type == 2)//商务舱
	{
		price = flight_info->price_vip;
		if(flight_info->remain_number_vip == 0)
		{
			flight_info->appointment_vip.push(login_account);
			cout<<"已为您预约此票！"<<endl;
		}
		else
		{
			flight_info->remain_number_vip -= 1;
			flight_info->buying_customer.push_back(login_account);
			if(position_type == 1)
				cout<<"购票成功！"<<endl;
			else if(position_type == 2)
				cout<<"换票成功！"<<endl;
			have_buy = 1;
		}
	}
	if(have_buy)
	{
		have_buy_info *ticket_info = new have_buy_info();
		ticket_info->set_info(flight_info->flight_number,flight_info->company_name,flight_info->departure,flight_info->destination,flight_info->stop,flight_info->departure_start_time,flight_info->stop_arrive_time,flight_info->stop_start_time,flight_info->destination_arrive_time,type,price);
		customer->ticket_info_list.push_back(ticket_info);
	}
}
void flight_information::cancel_ticket()
{
	customer_info_node* customer = customers.search_customer_info(login_account);
	list<have_buy_info*>::iterator iter;
	int number = 1;
	int target;
	cout<<"您所购买的航班信息如下:"<<endl;
	for(iter=customer->ticket_info_list.begin();iter!=customer->ticket_info_list.end();iter++,number++)
	{
		cout<<"第"<<number<<"条:"<<endl;
		if((*iter)->ticket_type==1)
			cout<<"客舱:"<<(*iter)->price<<"元人民币"<<endl;
		else
			cout<<"商务舱:"<<(*iter)->price<<"元人民币"<<endl;
  		cout<<"航班号:"<<(*iter)->flight_number<<endl;
    	cout<<"航空公司:"<<(*iter)->company_name<<endl;
    	cout<<"起始地:"<<(*iter)->departure<<endl;
    	cout<<"目的地:"<<(*iter)->destination<<endl;
    	cout<<"起飞时间:"<<(*iter)->departure_start_time<<endl;
    	cout<<"到达时间:"<<(*iter)->destination_arrive_time<<endl;
    	cout<<endl;
	}
	cout<<"请输入您想要退的票:"<<endl;
	cin>>target;
	int i=1;
	for(iter=customer->ticket_info_list.begin();iter!=customer->ticket_info_list.end();iter++,i++)
	{
		if(i==target)
			break;
	}
	flight_information_node* target_flight = check_whether_fly((*iter)->departure_start_time,(*iter)->departure,(*iter)->destination,(*iter)->flight_number);
	if(!target_flight)//已经起飞
	{
		cout<<"飞机已经起飞,无法退票!"<<endl;
	}
	else
	{//未起飞，执行退票操作
		int type = (*iter)->ticket_type;
		target_flight->buying_customer.remove(login_account);//删除已购票信息
		if(type == 1 && target_flight->appointment_normal.size())//客舱,有预约
		{
			unsigned int account = target_flight->appointment_normal.front();
			target_flight->appointment_normal.pop();//得到预约账号

			have_buy_info *ticket_info = new have_buy_info();
			ticket_info->set_info(target_flight->flight_number,target_flight->company_name,target_flight->departure,target_flight->destination,target_flight->stop,target_flight->departure_start_time,target_flight->stop_arrive_time,target_flight->stop_start_time,target_flight->destination_arrive_time,type,target_flight->price_normal);
			//customer->ticket_info_list.push_back(ticket_info);
			customer_info_node* appoint_customer = customers.search_customer_info(account);
			appoint_customer->ticket_info_list.push_back(ticket_info);//用户写入已购票信息
			target_flight->buying_customer.push_back(account);//机票写入购票用户信息
		}
		else if(type==2 && target_flight->appointment_vip.size())//商务舱，有预约
		{
			unsigned int account = target_flight->appointment_vip.front();
			target_flight->appointment_vip.pop();//得到预约账号

			have_buy_info *ticket_info = new have_buy_info();
			ticket_info->set_info(target_flight->flight_number,target_flight->company_name,target_flight->departure,target_flight->destination,target_flight->stop,target_flight->departure_start_time,target_flight->stop_arrive_time,target_flight->stop_start_time,target_flight->destination_arrive_time,type,target_flight->price_vip);
			customer_info_node* appoint_customer = customers.search_customer_info(account);
			appoint_customer->ticket_info_list.push_back(ticket_info);//用户写入已购票信息
			target_flight->buying_customer.push_back(account);//机票写入购票用户信息
		}
		else
		{
			//无预约,增加票的数量
			if(type == 1)
				target_flight->remain_number_normal++;
			else if(type == 2)
				target_flight->remain_number_vip++;
		}
		cout<<"退票成功!"<<endl;
	}

}
flight_information_node* flight_information::check_whether_fly(string departure_start_time,string departure,string destination,string flight_number)
{
	flight_time_node*target = find_node_by_data(departure_start_time.substr(0,10));
	if(!target)
		return NULL;
	int data = global_transform(departure,destination);
	list<flight_information_node*>info_list = target->tree->find_info_list(data);
	list<flight_information_node*>::iterator iter;
	for(iter=info_list.begin();iter!=info_list.end();iter++)
	{
		if((*iter)->departure_start_time==departure_start_time && (*iter)->flight_number==flight_number)
			return (*iter);
	}
	return NULL;
}
void flight_information::delay_flight(string departure_start_time,string departure,string destination,string flight_number,int delay_minute)
{
	flight_information_node *target = check_whether_fly(departure_start_time,departure,destination,flight_number);
	target->islater = delay_minute;
	delay_list.push_back(target);//加入列表
	file_manager = new notice_file();
	file_manager->write_file(target,1);//写入文件
	delete file_manager;
}
void flight_information::notice_flight()
{
	file_manager = new notice_file();
	queue<string> notice_list = file_manager->search(to_string(login_account),2);
	while(notice_list.size())
	{
		string data = notice_list.front();
		notice_list.pop();
		queue<string> notice = file_manager->split(data," ");
		string type = notice.front();//1：延误  2：取消
		notice.pop();
		notice.pop();
		string flight_number = notice.front();
		notice.pop();
		string departure_start_time = notice.front();
		notice.pop();
		string departure = notice.front();
		notice.pop();
		string destination = notice.front();
		notice.pop();
		string later_time = notice.front();
		if(type=="1")//延误
		{
			file_manager->delete_file(1,to_string(login_account));
			cout<<"您所乘坐的"<<flight_number<<"次航班预计延误"<<later_time<<"分钟"<<endl;
		}
		else if(type=="2")
		{
			file_manager->delete_file(2,to_string(login_account));
			cout<<"您所乘坐的"<<flight_number<<"次航班已取消"<<endl;
		}
		int key = global_transform(departure,destination);
		flight_time_node* target_time_node = find_node_by_data(departure_start_time.substr(0,10));
		if(!target_time_node)
		{
			cout<<"暂无当日推荐航班,如需退票请联系地面工作人员"<<endl;
			return;
		}
		list<flight_information_node*> flight_info_list = target_time_node->tree->find_info_list(key);
		if(!flight_info_list.size())
		{
			cout<<"暂无当日推荐航班,如需退票请联系地面工作人员"<<endl;
			return;
		}
		cout<<"推荐换乘航班:"<<endl;
		list<flight_information_node*>::iterator iter;
		int number = 1;
		for(iter=flight_info_list.begin();iter!=flight_info_list.end();iter++)
		{
			if(!(*iter)->islater)
			{
				//没有延误
				cout<<number++<<":"<<endl;
				cout<<(*iter)->company_name<<" "<<(*iter)->flight_number<<"次航班"<<endl;
				cout<<"起飞时间:"<<(*iter)->departure_start_time<<endl;
				cout<<"到达时间:"<<(*iter)->destination_arrive_time<<endl;
				cout<<endl;
			}
		}
		cout<<"请输入您所选中的换乘航班(若选择不换乘则输入0):"<<endl;
		int target_number;
		cin>>target_number;
		if(!target_number)
			return;
		for(number=1,iter=flight_info_list.begin();iter!=flight_info_list.end();iter++,number++)
		{
			if(number == target_number)
			{
				solve_buying_info((*iter),2);//换票选择
				for(iter=flight_info_list.begin();iter!=flight_info_list.end();iter++)
				{
					if((*iter)->flight_number == flight_number && (*iter)->departure_start_time == departure_start_time)
					{
						//cout<<"换票信息更新中..."<<endl;
						solve_change_ticket((*iter));//处理换票信息更新
						break;
					}
				}
				break;
			}
		}
	}
}
//首先删除飞机航班节点中的乘客信息，再删除乘客购买了此票的信息，再添加新票的信息，原票数量增加
void flight_information::solve_change_ticket(flight_information_node*flight_node)
{
	int ticket_type;
	customer_info_node*customer_info = customers.tree->search_customer_info(login_account);
	if(!customer_info)
	{
		cout<<"查询不到乘客信息!"<<endl;
		return;
	}
	list<have_buy_info*>& have_buy_list = customer_info->ticket_info_list;
	list<have_buy_info*>::iterator iter;
	for(iter=have_buy_list.begin();iter!=have_buy_list.end();iter++)
	{
		if((*iter)->flight_number==flight_node->flight_number&&(*iter)->departure_start_time==flight_node->departure_start_time)
		{
			ticket_type = (*iter)->ticket_type;
			break;
		}
	}
	customer_info->ticket_info_list.remove((*iter));//删除用户购买此票的记录
	//cout<<"已删除原购票记录"<<endl;
	if(ticket_type == 1)//增加票数
	{
		flight_node->remain_number_normal++;
	}
	else if(ticket_type == 2)
	{
		flight_node->remain_number_vip++;
	}
	//cout<<"已增加"<<ticket_type<<"票数"<<endl;
	flight_node->buying_customer.remove(login_account);//删除用户信息
	//cout<<"已删除用户信息"<<endl;
}
void flight_information::cancel_flight(string departure_start_time,string departure,string destination,string flight_number)
{
	flight_information_node *target = check_whether_fly(departure_start_time,departure,destination,flight_number);
	file_manager = new notice_file();
	file_manager->write_file(target,2);//写入文件
	delete file_manager;
	flight_time_node* target_day = find_node_by_data(departure_start_time.substr(0,10));
	int data = global_transform(departure,destination);
	list<flight_information_node*>flight_info_list = target_day->tree->find_info_list(data);
	flight_info_list.remove(target);//删除此航班信息
}
void flight_information::plane_fly(string departure_start_time,string departure,string destination,string flight_number)
{
	flight_information_node *target = check_whether_fly(departure_start_time,departure,destination,flight_number);
	flight_time_node* target_day = find_node_by_data(departure_start_time.substr(0,10));
	int data = global_transform(departure,destination);
	list<flight_information_node*>flight_info_list = target_day->tree->find_info_list(data);
	flight_info_list.remove(target);//删除此航班信息
	if(target->islater)
	{
		delay_list.remove(target);//删除延误航班内的信息
	}
	cout<<"由"<<departure<<"飞往"<<destination<<"的"<<flight_number<<"次航班已经起飞"<<endl;
}