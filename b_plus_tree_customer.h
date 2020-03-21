#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
#include "global.h"
#include <list>
using namespace std;
class have_buy_info//存储乘客所买的票的信息
{
public:
	string flight_number;//航班号
	string company_name;//航空公司名称
	string departure;//航班起飞地
	string destination;//航班降落地
	string stop;//航班经停地点
	string departure_start_time;//出发地起飞时间
	string stop_arrive_time;//到达经停地时间
	string stop_start_time;//由经停地起飞时间
	string destination_arrive_time;//目的地到达时间
	int ticket_type;//1:客舱  2:商务舱
	float price;//票价
	void set_info(string flight_number,string company_name,string departure,string destination,string stop,string departure_start_time,string stop_arrive_time,string stop_start_time,string destination_arrive_time,int ticket_type,float price);
};
class customer_info_node
{
public:
	unsigned int account;//账号，用unsigned int 保存更容易查找
	list<have_buy_info*> ticket_info_list;//已购票信息
	void load_data(unsigned int account);
};

class node_customer
{
public:
	node_customer(int n);
	int level;//阶数
	node_customer **point;//指针，初始为空
	int *index;//索引数值(数据),初始为0
	int position;//当前索引个数,初始为0
	node_customer *right;//b+树的特点，向右指针
	customer_info_node** info_list;//存储列表
};
class b_plus_tree_customer
{
public:
	b_plus_tree_customer(int n);
	int level;//定义b+树的阶数
	node_customer *root;
	void insert_customer_info(customer_info_node *new_customer);
	void insert(int data);
	node_customer **find_position(int data,node_customer *target,node_customer *father);//寻找要插入的位置，返回比data小的上一个node的位置，返回值[0]:target,[1]:father
	void split_node(node_customer*& target,node_customer*&father,int data);//将target结点分裂
	void insert_sort(int data,int *&index,int number);//对data进行插入排序
	int is_exist(int data,int *&index,int number);//判断是否已经存在
	node_customer *find_father(int data,node_customer *target,node_customer *father);//用data找到结点的父亲结点
	void run_down();//横向遍历
	void split_up_node(node_customer *target,int data);//分裂除叶结点外的结点
	void overTree();//层次遍历整棵树，用于debug
	void delete_data(int data);//删除对应key的数据
	void delete_index(int*& index,int position,int &number);//删除数组中的position下标的元素
	node_customer *get_pre_node(node_customer *target,node_customer *father);//返回target叶子节点的前向节点
	void sort_index(int *&index,int number,int position);//对除position下标外的其余有序数组进行插入排序
	void together_index(int*& pre,int *&bac,int &number_pre,int &number_bac);//将bac上的数据合并至pre
	void delete_father_node(node_customer *&target,int position);//删除索引节点的数据
	int find_father_position(node_customer *pre,node_customer *target,node_customer *father);//找到father节点中左pre右target的index下标
	void move_point(node_customer *target,int position);//将target的position下标后的指针前移,position为index要删除的元素下标
};