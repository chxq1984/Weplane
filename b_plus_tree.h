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
	string flight_number;//航班号
	string company_name;//航空公司名称
	string departure;//航班起飞地
	string destination;//航班降落地
	string stop;//航班经停地点
	string departure_start_time;//出发地起飞时间
	string stop_arrive_time;//到达经停地时间
	string stop_start_time;//由经停地起飞时间
	string destination_arrive_time;//目的地到达时间
	int remain_number_normal;//剩余普通票数
	int remain_number_vip;//剩余商务舱票数
	int islater;//是否延误
	float price_normal;//普通票价
	float price_vip;//公务舱票价
	list<unsigned int> buying_customer;//存储购票者的账号
	queue<unsigned int> appointment;//存储预约购票者的账号
};
class node
{
public:
	node(int n);
	int level;//阶数
	node **point;//指针，初始为空
	int *index;//索引数值(数据),初始为0
	int position;//当前索引个数,初始为0
	node *right;//b+树的特点，向右指针
	list<flight_information_node*>* info_list;//存储列表
};
class b_plus_tree
{
public:
	b_plus_tree(int n);
	int level;//定义b+树的阶数
	node *root;
	void insert_flight_info(flight_information_node*info);//插入航班信息
	list<flight_information_node*>& find_info_list(int data);//根据data查找对应的list
	void insert(int data);
	node **find_position(int data,node *target,node *father);//寻找要插入的位置，返回比data小的上一个node的位置，返回值[0]:target,[1]:father
	void split_node(node*& target,node*&father,int data);//将target结点分裂
	void insert_sort(int data,int *&index,int number);//对data进行插入排序
	int is_exist(int data,int *&index,int number);//判断是否已经存在
	node *find_father(int data,node *target,node *father);//用data找到结点的父亲结点
	void run_down();//横向遍历
	void split_up_node(node *target,int data);//分裂除叶结点外的结点
	void overTree();//层次遍历整棵树，用于debug
	void delete_data(int data);//删除对应key的数据
	void delete_index(int*& index,int position,int &number);//删除数组中的position下标的元素
	node *get_pre_node(node *target,node *father);//返回target叶子节点的前向节点
	void sort_index(int *&index,int number,int position);//对除position下标外的其余有序数组进行插入排序
	void together_index(int*& pre,int *&bac,int &number_pre,int &number_bac);//将bac上的数据合并至pre
	void delete_father_node(node *&target,int position);//删除索引节点的数据
	int find_father_position(node *pre,node *target,node *father);//找到father节点中左pre右target的index下标
	void move_point(node *target,int position);//将target的position下标后的指针前移,position为index要删除的元素下标
};