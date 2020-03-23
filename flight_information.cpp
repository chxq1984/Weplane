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
	string departure_time;//���ʱ��
	b_plus_tree *tree;
	flight_time_node(string time);
};
class flight_information
{
public:
	file_manage* file_manager;
	customer_info customers;//�û���Ϣ������
	list<flight_time_node*> flight_time_chain;
	list<flight_information_node*>delay_list;//���󺽰���Ϣ�б�
	void insert_flight_info();
	flight_time_node* find_node_by_data(string data);//Ѱ���������ڵĽڵ�
	void get_info_from_file();//���ļ��л�ȡ�Ѵ溽����Ϣ����debugʹ��
	void buy_ticket();//��Ʊ
	void solve_buying_info(flight_information_node* flight_info,int position_type);//����Ʊʱ����Ϣ����,type:1:��ͨ��Ʊ,2:��Ʊ
	void cancel_ticket();//��Ʊ
	flight_information_node* check_whether_fly(string departure_start_time,string departure,string destination,string flight_number);//�˺���Ҳ�����ڷ��غ�����Ϣ�ڵ�
	//�ж��Ƿ��Ѿ���ɣ�ע�����Ľ������Ľ����򣺷ɻ������ӳ���ɵ������ʱ��Բ���
	void delay_flight(string departure_start_time,string departure,string destination,string flight_number,int delay_minute);//�ɻ��ӳ�
	void notice_flight();//֪ͨ�ɻ�����/ȡ��
	void solve_change_ticket(flight_information_node*flight_node);//������Ʊ������Ϣ
	void cancel_flight(string departure_start_time,string departure,string destination,string flight_number);//�ɻ�ȡ��
	void plane_fly(string departure_start_time,string departure,string destination,string flight_number);//�ɻ������Ϣ����
};
int main()
{
	make_info_map();//��ʼ��map
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
	string departure="����";
	string destination="����";
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
	solve_buying_info(*iter,1);

}
void flight_information::solve_buying_info(flight_information_node* flight_info,int position_type)
{
	customer_info_node* customer = customers.search_customer_info(login_account);
	cout<<"�Ͳ�ʣ��Ʊ��:"<<flight_info->remain_number_normal<<endl;
	cout<<"�Ͳ�Ʊ��:"<<flight_info->price_normal<<endl;
	cout<<"�����ʣ��Ʊ��:"<<flight_info->remain_number_vip<<endl;
	cout<<"�����Ʊ��:"<<flight_info->price_vip<<endl;
	if(position_type == 1)
		cout<<"������������Ҫ���������:\n�Ͳ�:1  �����:2"<<endl;
	else if(position_type == 2)
		cout<<"������������Ҫ���˵�����:\n�Ͳ�:1  �����:2"<<endl;
	int type;
	cin>>type;
	int have_buy = 0;//�ж��Ƿ��Ѿ���Ʊ
	float price;
	if(type == 1)//�Ͳ�
	{
		price = flight_info->price_normal;
		if(flight_info->remain_number_normal == 0)
		{
			flight_info->appointment_normal.push(login_account);
			cout<<"��Ϊ��ԤԼ��Ʊ��"<<endl;
		}
		else
		{

			flight_info->remain_number_normal -= 1;
			flight_info->buying_customer.push_back(login_account);
			if(position_type == 1)
				cout<<"��Ʊ�ɹ���"<<endl;
			else if(position_type == 2)
				cout<<"��Ʊ�ɹ���"<<endl;
			have_buy = 1;
		}
	}
	else if(type == 2)//�����
	{
		price = flight_info->price_vip;
		if(flight_info->remain_number_vip == 0)
		{
			flight_info->appointment_vip.push(login_account);
			cout<<"��Ϊ��ԤԼ��Ʊ��"<<endl;
		}
		else
		{
			flight_info->remain_number_vip -= 1;
			flight_info->buying_customer.push_back(login_account);
			if(position_type == 1)
				cout<<"��Ʊ�ɹ���"<<endl;
			else if(position_type == 2)
				cout<<"��Ʊ�ɹ���"<<endl;
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
	cout<<"��������ĺ�����Ϣ����:"<<endl;
	for(iter=customer->ticket_info_list.begin();iter!=customer->ticket_info_list.end();iter++,number++)
	{
		cout<<"��"<<number<<"��:"<<endl;
		if((*iter)->ticket_type==1)
			cout<<"�Ͳ�:"<<(*iter)->price<<"Ԫ�����"<<endl;
		else
			cout<<"�����:"<<(*iter)->price<<"Ԫ�����"<<endl;
  		cout<<"�����:"<<(*iter)->flight_number<<endl;
    	cout<<"���չ�˾:"<<(*iter)->company_name<<endl;
    	cout<<"��ʼ��:"<<(*iter)->departure<<endl;
    	cout<<"Ŀ�ĵ�:"<<(*iter)->destination<<endl;
    	cout<<"���ʱ��:"<<(*iter)->departure_start_time<<endl;
    	cout<<"����ʱ��:"<<(*iter)->destination_arrive_time<<endl;
    	cout<<endl;
	}
	cout<<"����������Ҫ�˵�Ʊ:"<<endl;
	cin>>target;
	int i=1;
	for(iter=customer->ticket_info_list.begin();iter!=customer->ticket_info_list.end();iter++,i++)
	{
		if(i==target)
			break;
	}
	flight_information_node* target_flight = check_whether_fly((*iter)->departure_start_time,(*iter)->departure,(*iter)->destination,(*iter)->flight_number);
	if(!target_flight)//�Ѿ����
	{
		cout<<"�ɻ��Ѿ����,�޷���Ʊ!"<<endl;
	}
	else
	{//δ��ɣ�ִ����Ʊ����
		int type = (*iter)->ticket_type;
		target_flight->buying_customer.remove(login_account);//ɾ���ѹ�Ʊ��Ϣ
		if(type == 1 && target_flight->appointment_normal.size())//�Ͳ�,��ԤԼ
		{
			unsigned int account = target_flight->appointment_normal.front();
			target_flight->appointment_normal.pop();//�õ�ԤԼ�˺�

			have_buy_info *ticket_info = new have_buy_info();
			ticket_info->set_info(target_flight->flight_number,target_flight->company_name,target_flight->departure,target_flight->destination,target_flight->stop,target_flight->departure_start_time,target_flight->stop_arrive_time,target_flight->stop_start_time,target_flight->destination_arrive_time,type,target_flight->price_normal);
			//customer->ticket_info_list.push_back(ticket_info);
			customer_info_node* appoint_customer = customers.search_customer_info(account);
			appoint_customer->ticket_info_list.push_back(ticket_info);//�û�д���ѹ�Ʊ��Ϣ
			target_flight->buying_customer.push_back(account);//��Ʊд�빺Ʊ�û���Ϣ
		}
		else if(type==2 && target_flight->appointment_vip.size())//����գ���ԤԼ
		{
			unsigned int account = target_flight->appointment_vip.front();
			target_flight->appointment_vip.pop();//�õ�ԤԼ�˺�

			have_buy_info *ticket_info = new have_buy_info();
			ticket_info->set_info(target_flight->flight_number,target_flight->company_name,target_flight->departure,target_flight->destination,target_flight->stop,target_flight->departure_start_time,target_flight->stop_arrive_time,target_flight->stop_start_time,target_flight->destination_arrive_time,type,target_flight->price_vip);
			customer_info_node* appoint_customer = customers.search_customer_info(account);
			appoint_customer->ticket_info_list.push_back(ticket_info);//�û�д���ѹ�Ʊ��Ϣ
			target_flight->buying_customer.push_back(account);//��Ʊд�빺Ʊ�û���Ϣ
		}
		else
		{
			//��ԤԼ,����Ʊ������
			if(type == 1)
				target_flight->remain_number_normal++;
			else if(type == 2)
				target_flight->remain_number_vip++;
		}
		cout<<"��Ʊ�ɹ�!"<<endl;
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
	delay_list.push_back(target);//�����б�
	file_manager = new notice_file();
	file_manager->write_file(target,1);//д���ļ�
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
		string type = notice.front();//1������  2��ȡ��
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
		if(type=="1")//����
		{
			file_manager->delete_file(1,to_string(login_account));
			cout<<"����������"<<flight_number<<"�κ���Ԥ������"<<later_time<<"����"<<endl;
		}
		else if(type=="2")
		{
			file_manager->delete_file(2,to_string(login_account));
			cout<<"����������"<<flight_number<<"�κ�����ȡ��"<<endl;
		}
		int key = global_transform(departure,destination);
		flight_time_node* target_time_node = find_node_by_data(departure_start_time.substr(0,10));
		if(!target_time_node)
		{
			cout<<"���޵����Ƽ�����,������Ʊ����ϵ���湤����Ա"<<endl;
			return;
		}
		list<flight_information_node*> flight_info_list = target_time_node->tree->find_info_list(key);
		if(!flight_info_list.size())
		{
			cout<<"���޵����Ƽ�����,������Ʊ����ϵ���湤����Ա"<<endl;
			return;
		}
		cout<<"�Ƽ����˺���:"<<endl;
		list<flight_information_node*>::iterator iter;
		int number = 1;
		for(iter=flight_info_list.begin();iter!=flight_info_list.end();iter++)
		{
			if(!(*iter)->islater)
			{
				//û������
				cout<<number++<<":"<<endl;
				cout<<(*iter)->company_name<<" "<<(*iter)->flight_number<<"�κ���"<<endl;
				cout<<"���ʱ��:"<<(*iter)->departure_start_time<<endl;
				cout<<"����ʱ��:"<<(*iter)->destination_arrive_time<<endl;
				cout<<endl;
			}
		}
		cout<<"����������ѡ�еĻ��˺���(��ѡ�񲻻���������0):"<<endl;
		int target_number;
		cin>>target_number;
		if(!target_number)
			return;
		for(number=1,iter=flight_info_list.begin();iter!=flight_info_list.end();iter++,number++)
		{
			if(number == target_number)
			{
				solve_buying_info((*iter),2);//��Ʊѡ��
				for(iter=flight_info_list.begin();iter!=flight_info_list.end();iter++)
				{
					if((*iter)->flight_number == flight_number && (*iter)->departure_start_time == departure_start_time)
					{
						//cout<<"��Ʊ��Ϣ������..."<<endl;
						solve_change_ticket((*iter));//����Ʊ��Ϣ����
						break;
					}
				}
				break;
			}
		}
	}
}
//����ɾ���ɻ�����ڵ��еĳ˿���Ϣ����ɾ���˿͹����˴�Ʊ����Ϣ���������Ʊ����Ϣ��ԭƱ��������
void flight_information::solve_change_ticket(flight_information_node*flight_node)
{
	int ticket_type;
	customer_info_node*customer_info = customers.tree->search_customer_info(login_account);
	if(!customer_info)
	{
		cout<<"��ѯ�����˿���Ϣ!"<<endl;
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
	customer_info->ticket_info_list.remove((*iter));//ɾ���û������Ʊ�ļ�¼
	//cout<<"��ɾ��ԭ��Ʊ��¼"<<endl;
	if(ticket_type == 1)//����Ʊ��
	{
		flight_node->remain_number_normal++;
	}
	else if(ticket_type == 2)
	{
		flight_node->remain_number_vip++;
	}
	//cout<<"������"<<ticket_type<<"Ʊ��"<<endl;
	flight_node->buying_customer.remove(login_account);//ɾ���û���Ϣ
	//cout<<"��ɾ���û���Ϣ"<<endl;
}
void flight_information::cancel_flight(string departure_start_time,string departure,string destination,string flight_number)
{
	flight_information_node *target = check_whether_fly(departure_start_time,departure,destination,flight_number);
	file_manager = new notice_file();
	file_manager->write_file(target,2);//д���ļ�
	delete file_manager;
	flight_time_node* target_day = find_node_by_data(departure_start_time.substr(0,10));
	int data = global_transform(departure,destination);
	list<flight_information_node*>flight_info_list = target_day->tree->find_info_list(data);
	flight_info_list.remove(target);//ɾ���˺�����Ϣ
}
void flight_information::plane_fly(string departure_start_time,string departure,string destination,string flight_number)
{
	flight_information_node *target = check_whether_fly(departure_start_time,departure,destination,flight_number);
	flight_time_node* target_day = find_node_by_data(departure_start_time.substr(0,10));
	int data = global_transform(departure,destination);
	list<flight_information_node*>flight_info_list = target_day->tree->find_info_list(data);
	flight_info_list.remove(target);//ɾ���˺�����Ϣ
	if(target->islater)
	{
		delay_list.remove(target);//ɾ�����󺽰��ڵ���Ϣ
	}
	cout<<"��"<<departure<<"����"<<destination<<"��"<<flight_number<<"�κ����Ѿ����"<<endl;
}