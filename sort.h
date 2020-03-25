#pragma once
#include <iostream>
#include <vector>
#include "b_plus_tree.h"
using namespace std;
class Sort
{
public:
	virtual int* tosort(vector<flight_information_node*>& sort_flight_info)=0;

	int number;
	int *data,*link;
	int entrance;//入口
	void merge(int pre,int bac,int &later);
	void merge_sort(int low,int high,int &p);
	void insertSort(int pre,int bac,int &ret);
	int get_flytime(string start,string end);//获取飞行时间,返回分钟
};
class sort_by_price:public Sort//根据normal_price进行排序
{
public:
	int* tosort(vector<flight_information_node*>& sort_flight_info);
};
class sort_by_time:public Sort//根据飞行时间排序
{
public:
	int* tosort(vector<flight_information_node*>& sort_flight_info);
};
class sort_by_remain_number:public Sort//根据剩余票数排序
{
public:
	int* tosort(vector<flight_information_node*>& sort_flight_info);
};