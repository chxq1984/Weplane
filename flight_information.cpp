#include <iostream>
#include <list>
#include "b_plus_tree.h"
#include "global.h"
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
	list<flight_time_node*> flight_time_chain;
	void insert_flight_info();
	flight_time_node* find_node_by_data(string data);//Ѱ���������ڵĽڵ�
	void search_flight_info();//��Ʊʱ�鿴������Ϣ
};
int main()
{
	make_info_map();//��ʼ��map
	flight_information test;
	test.insert_flight_info();
	test.search_flight_info();
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
	int remain_number;//ʣ��Ʊ��
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
	cout<<"��������Ʊ��:";
	cin>>remain_number;
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
		information_node = new flight_information_node(flight_number,company_name,departure,destination,stop,departure_start_time,stop_arrive_time,stop_start_time,destination_arrive_time,remain_number,price_normal,price_vip);
	else
		information_node = new flight_information_node(flight_number,company_name,departure,destination,departure_start_time,destination_arrive_time,remain_number,price_normal,price_vip);
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
void flight_information::search_flight_info()
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
	string position = departure+"/"+destination;
	int data = info_map[position];
	list<flight_information_node*> info_list = target_day->tree->find_info_list(data);
	cout<<"������Ϣ:"<<endl;
	for(list<flight_information_node*>::iterator iter = info_list.begin();iter != info_list.end();iter++)  
  	{  
  		cout<<"�����:"<<(*iter)->flight_number<<endl;
    	cout<<"���չ�˾:"<<(*iter)->company_name<<endl;
    	cout<<"��ʼ��:"<<(*iter)->departure<<endl;
    	cout<<"Ŀ�ĵ�:"<<(*iter)->destination<<endl;
    	cout<<"���ʱ��:"<<(*iter)->departure_start_time<<endl;
    	cout<<"����ʱ��:"<<(*iter)->destination_arrive_time<<endl;
    	cout<<endl;
  	}

}