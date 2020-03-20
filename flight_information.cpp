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
	string departure_time;//���ʱ��
	b_plus_tree *tree;
	flight_time_node(string time);
};
class flight_information
{
public:
	customer_info customers;//�û���Ϣ������
	list<flight_time_node*> flight_time_chain;
	void insert_flight_info();
	flight_time_node* find_node_by_data(string data);//Ѱ���������ڵĽڵ�
	void get_info_from_file();//���ļ��л�ȡ�Ѵ溽����Ϣ����debugʹ��
	void buy_ticket();//��Ʊ
	void solve_buying_info(flight_information_node* flight_info);//����Ʊʱ����Ϣ����
};
int main()
{
	make_info_map();//��ʼ��map
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
	string company_name;//���չ�˾����
	string departure;//������ɵ�
	string destination;//���ཱུ���
	string stop = "";//���ྭͣ�ص�
	string departure_start_time;//���������ʱ��
	string stop_arrive_time = "";//���ﾭͣ��ʱ��
	string stop_start_time = "";//�ɾ�ͣ�����ʱ��
	string destination_arrive_time;//Ŀ�ĵص���ʱ��
	int remain_number_normal;//ʣ��Ʊ��
	int remain_number_vip;
	float price_normal;//��ͨƱ��
	float price_vip;//�����Ʊ��

	int has_stop = 0;
	cout<<"�����뺽���:";
	cin>>flight_number;
	cout<<"�����뺽�չ�˾����:";
	cin>>company_name;
	cout<<"�����뺽����ɵ�:";
	cin>>departure;
	cout<<"�����뺽�ཱུ���:";
	cin>>destination;
	cout<<"��������������ʱ��:";
	cin>>departure_start_time;
	cout<<"�Ƿ��о�ͣ�ص�(�У�1���ޣ�0):";
	cin>>has_stop;
	if(has_stop == 1)
	{
		cout<<"�����뾭ͣ�ص�:";
		cin>>stop;
		cout<<"�����뵽�ﾭͣ��ʱ��:";
		cin>>stop_arrive_time;
		cout<<"�������ɾ�ͣ�����ʱ��:";
		cin>>stop_start_time;
	}
	cout << "�����뵽��Ŀ�ĵ�ʱ��:";
	cin>>destination_arrive_time;
	cout<<"������Ͳ���Ʊ��:";
	cin>>remain_number_normal;
	cout<<"�������������Ʊ��:";
	cin>>remain_number_vip;
	cout<<"��������ͨƱ��:";
	cin>>price_normal;
	cout<<"������VIPƱ��:";
	cin>>price_vip;
	//ʱ���ʽ��2020/03/18/13:28���洢��ʽ��2020/03/18
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
		string company_name;//���չ�˾����
		string departure;//������ɵ�
		string destination;//���ཱུ���
		string stop = "";//���ྭͣ�ص�
		string departure_start_time;//���������ʱ��
		string stop_arrive_time = "";//���ﾭͣ��ʱ��
		string stop_start_time = "";//�ɾ�ͣ�����ʱ��
		string destination_arrive_time;//Ŀ�ĵص���ʱ��
		int remain_number_normal;//ʣ��Ʊ��
		int remain_number_vip;
		float price_normal;//��ͨƱ��
		float price_vip;//�����Ʊ��
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
	cout<<"�������������:";
	cin>>departure_time;
	cout<<"�����������:";
	cin>>departure;
	cout<<"������Ŀ�ĵ�:";
	cin>>destination;
	flight_time_node* target_day = find_node_by_data(departure_time);
	if(!target_day)
	{
		cout<<"����"<<departure_time<<"���������Ϣ";
		return;
	}
	int number = 1;
	string position = departure+"/"+destination;
	int data = info_map[position];
	list<flight_information_node*> info_list = target_day->tree->find_info_list(data);
	cout<<"������Ϣ:"<<endl;
	for(list<flight_information_node*>::iterator iter = info_list.begin();iter != info_list.end();iter++)  
  	{  
  		cout<<"��"<<number<<"��:"<<endl;
  		cout<<"�����:"<<(*iter)->flight_number<<endl;
    	cout<<"���չ�˾:"<<(*iter)->company_name<<endl;
    	cout<<"��ʼ��:"<<(*iter)->departure<<endl;
    	cout<<"Ŀ�ĵ�:"<<(*iter)->destination<<endl;
    	cout<<"���ʱ��:"<<(*iter)->departure_start_time<<endl;
    	cout<<"����ʱ��:"<<(*iter)->destination_arrive_time<<endl;
    	cout<<endl;
    	number++;
  	}
	cout<<"����������Ҫ����ĺ��ࣺ";
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
	cout<<"�Ͳ�ʣ��Ʊ��:"<<flight_info->remain_number_normal<<endl;
	cout<<"�Ͳ�Ʊ��:"<<flight_info->price_normal<<endl;
	cout<<"�����ʣ��Ʊ��:"<<flight_info->remain_number_vip<<endl;
	cout<<"�����Ʊ��:"<<flight_info->price_vip<<endl;
	cout<<"������������Ҫ���������:\n�Ͳ�:1  �����:2"<<endl;
	int type;
	cin>>type;
	int have_buy = 0;//�ж��Ƿ��Ѿ���Ʊ
	if(type == 1)//�Ͳ�
	{
		if(flight_info->remain_number_normal == 0)
		{
			flight_info->appointment.push(login_account);
			cout<<"��Ϊ��ԤԼ��Ʊ��"<<endl;
		}
		else
		{

			flight_info->remain_number_normal -= 1;
			flight_info->buying_customer.push_back(login_account);
			cout<<"��Ʊ�ɹ���"<<endl;
			have_buy = 1;
		}
	}
	else if(type == 2)//�����
	{
		if(flight_info->remain_number_vip == 0)
		{
			flight_info->appointment.push(login_account);
			cout<<"��Ϊ��ԤԼ��Ʊ��"<<endl;
		}
		else
		{
			flight_info->remain_number_vip -= 1;
			flight_info->buying_customer.push_back(login_account);
			cout<<"��Ʊ�ɹ���"<<endl;
			have_buy = 1;
		}
	}
	if(have_buy)
	{
		have_buy_info *ticket_info = new have_buy_info();
		ticket_info->set_info(flight_info->flight_number,flight_info->company_name,flight_info->departure,flight_info->destination,flight_info->stop,flight_info->departure_start_time,flight_info->stop_arrive_time,flight_info->stop_start_time,flight_info->destination_arrive_time,type);
		customer->ticket_info_list.push_back(ticket_info);
		cout<<"д��ɹ���";
	}
}