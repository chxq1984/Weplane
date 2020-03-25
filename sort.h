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
	int entrance;//���
	void merge(int pre,int bac,int &later);
	void merge_sort(int low,int high,int &p);
	void insertSort(int pre,int bac,int &ret);
	int get_flytime(string start,string end);//��ȡ����ʱ��,���ط���
};
class sort_by_price:public Sort//����normal_price��������
{
public:
	int* tosort(vector<flight_information_node*>& sort_flight_info);
};
class sort_by_time:public Sort//���ݷ���ʱ������
{
public:
	int* tosort(vector<flight_information_node*>& sort_flight_info);
};
class sort_by_remain_number:public Sort//����ʣ��Ʊ������
{
public:
	int* tosort(vector<flight_information_node*>& sort_flight_info);
};