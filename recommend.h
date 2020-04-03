#pragma once

#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#define MAX 100000
struct map_find_short
{
	int code;
	int weight;
	map_find_short *next;
};
class node_for_queue
{
public:
	int id;
	int distance;
	friend bool operator <(node_for_queue a,node_for_queue b)
	{
		return a.distance>b.distance;
	}
};
class input_data
{
public:
	int from;
	int to;
	int wei;
};
struct find_shortest
{
	priority_queue<node_for_queue> q;//���ȶ���
	map_find_short*head;
	int sum;
	int *distance;
	int *path;
	int *s;
	find_shortest();
	void build(int sum_place_number,vector<input_data*> route);//�ص��������ߵ�������Ϣ
	stack<int>* Dijkstra(int x,int y);//x:��ʼ�� y:�յ�
};