#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <queue>
#include "global.h"
using namespace std;
class flight_information_node
{
public:
	flight_information_node(string flight_number,string company_name,string departure,string destination,string stop,string departure_start_time,string stop_arrive_time,string stop_start_time,string destination_arrive_time,int remain_number_normal,int remain_numer_vip,float price_normal,float price_vip);
	flight_information_node(string flight_number,string company_name,string departure,string destination,string departure_start_time,string destination_arrive_time,int remain_number_normal,int remain_numer_vip,float price_normal,float price_vip);
	string flight_number;//�����
	string company_name;//���չ�˾����
	string departure;//������ɵ�
	string destination;//���ཱུ���
	string stop;//���ྭͣ�ص�
	string departure_start_time;//���������ʱ��
	string stop_arrive_time;//���ﾭͣ��ʱ��
	string stop_start_time;//�ɾ�ͣ�����ʱ��
	string destination_arrive_time;//Ŀ�ĵص���ʱ��
	int remain_number_normal;//ʣ����ͨƱ��
	int remain_number_vip;//ʣ�������Ʊ��
	int islater;//�Ƿ�����
	float price_normal;//��ͨƱ��
	float price_vip;//�����Ʊ��
	list<unsigned int> buying_customer;//�洢��Ʊ�ߵ��˺�
	queue<unsigned int> appointment;//�洢ԤԼ��Ʊ�ߵ��˺�
};
class node
{
public:
	node(int n);
	int level;//����
	node **point;//ָ�룬��ʼΪ��
	int *index;//������ֵ(����),��ʼΪ0
	int position;//��ǰ��������,��ʼΪ0
	node *right;//b+�����ص㣬����ָ��
	list<flight_information_node*>* info_list;//�洢�б�
};
class b_plus_tree
{
public:
	b_plus_tree(int n);
	int level;//����b+���Ľ���
	node *root;
	void insert_flight_info(flight_information_node*info);//���뺽����Ϣ
	list<flight_information_node*>& find_info_list(int data);//����data���Ҷ�Ӧ��list
	void insert(int data);
	node **find_position(int data,node *target,node *father);//Ѱ��Ҫ�����λ�ã����ر�dataС����һ��node��λ�ã�����ֵ[0]:target,[1]:father
	void split_node(node*& target,node*&father,int data);//��target������
	void insert_sort(int data,int *&index,int number);//��data���в�������
	int is_exist(int data,int *&index,int number);//�ж��Ƿ��Ѿ�����
	node *find_father(int data,node *target,node *father);//��data�ҵ����ĸ��׽��
	void run_down();//�������
	void split_up_node(node *target,int data);//���ѳ�Ҷ�����Ľ��
	void overTree();//��α���������������debug
	void delete_data(int data);//ɾ����Ӧkey������
	void delete_index(int*& index,int position,int &number);//ɾ�������е�position�±��Ԫ��
	node *get_pre_node(node *target,node *father);//����targetҶ�ӽڵ��ǰ��ڵ�
	void sort_index(int *&index,int number,int position);//�Գ�position�±������������������в�������
	void together_index(int*& pre,int *&bac,int &number_pre,int &number_bac);//��bac�ϵ����ݺϲ���pre
	void delete_father_node(node *&target,int position);//ɾ�������ڵ������
	int find_father_position(node *pre,node *target,node *father);//�ҵ�father�ڵ�����pre��target��index�±�
	void move_point(node *target,int position);//��target��position�±���ָ��ǰ��,positionΪindexҪɾ����Ԫ���±�
};