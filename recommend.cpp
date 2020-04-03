#include "recommend.h"

find_shortest::find_shortest()
{
	head = NULL;sum = 0;
}
void find_shortest::build(int sum_place_number,vector<input_data*> route)
{
	sum = sum_place_number;
	head=new map_find_short[sum+1];
	distance=new int [sum+1];
	s=new int [sum+1]();
	path=new int [sum+1];
	int temp = route.size();
	for(int m=1;m<=sum;m++)
	{
		head[m].code=m;
		head[m].next=NULL;
		distance[m]=MAX;
		head[m].weight=0;
		path[m]=m;
	}
	for(int m=1;m<=temp;m++)
	{
		int from,to,wei;
		from = route[m-1]->from;
		to = route[m-1]->to;
		wei = route[m-1]->wei;
		map_find_short *temp=new map_find_short;
		temp->code=to;
		temp->weight=wei;
		map_find_short*hj=head[from].next;
		if(hj==NULL)
			head[from].next=temp;
		else
		{
			while(hj->next)
			{
				hj=hj->next;
			}
			hj->next=temp;
		}
		temp->next=NULL;
	}
}
stack<int>* find_shortest::Dijkstra(int x,int y)
{
	stack<int> *route_store;
	//int sum_number = sum + 1;
	node_for_queue * mid = new node_for_queue[sum+1];//用于优先队列的操作
	for(int m=1;m<=sum;m++)
	{
		mid[m].id=m;
		mid[m].distance=MAX;
	}
	mid[x].distance=0;
	distance[x]=0;
	path[x]=-1;
	q.push(mid[x]);
	while(!q.empty())
	{
		node_for_queue i=q.top();
		map_find_short*temp=&head[i.id];
		q.pop();
		if(s[i.id])
			continue;
		s[i.id]=1;
		for(temp=head[i.id].next;temp;temp=temp->next)
		{
			if(!s[temp->code]&&distance[i.id]+temp->weight<distance[temp->code])
			{
				distance[temp->code]=distance[i.id]+temp->weight;
				path[temp->code]=i.id;
				mid[temp->code].distance=distance[temp->code];
				q.push(mid[temp->code]);
			}
		}
	}
		int type,k;
		type = y;
		k=type;
		if(path[type]==type)//无法到达
		{
			return NULL;
		}
		route_store = new stack<int>;
		while(path[type]!=-1)
		{
			//cout<<type;
			route_store->push(type);
			type=path[type];
		}
		return route_store;
		//cout<<"    "<<distance[k];
	
}