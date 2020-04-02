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
	string departure_time;//���ʱ��
	b_plus_tree *tree;
	flight_time_node(string time);
};
class flight_information
{
public:
	Sort* sort_manager;//���û���ѯ�����������
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
	void search_ticket_by_city(string departure,string destination);
	void search_ticket_by_flight_number(string flight_number);
	void show_ticket_info(flight_information_node *target);
	void sort_flight_info(vector<flight_information_node*>& flight_info);
	void forDebug_run();//���ڱ�����������������debug
};