#include "sort.h"
void Sort::merge(int pre,int bac,int &later)
{
	int prePoint = pre;
	int bacPoint = bac;
	int linkPoint = 0;
	while(prePoint && bacPoint)
	{
		if(data[prePoint] < data[bacPoint])
		{
			link[linkPoint] = prePoint;
			linkPoint = prePoint;
			prePoint = link[prePoint];
		}
		else
		{
			link[linkPoint] = bacPoint;
			linkPoint = bacPoint;
			bacPoint = link[bacPoint];

		}
	}
	if(!prePoint)
	{
		link[linkPoint] = bacPoint;
	}
	else
	{
		link[linkPoint] = prePoint;
	}
	later = link[0];
}
void Sort::insertSort(int pre,int bac,int &ret)
{
	//功能：将data数组中的pre至bac使用link进行插入排序，并返回入口ret
	ret = pre;
	for(int m=pre+1;m<=bac;m++)
	{
		int n = ret;
		int h = 0;
		do{
			if(data[m] < data[n])
				break;
			h = n;
			n = link[n];
		}while(n != 0);
		if(n == ret)
		{
			int temp = ret;
			ret = m;
			link[m] = temp;
		}
		else
		{
			link[h] = m;
			link[m] = n;
		}
	}
	
}
void Sort::merge_sort(int low,int high,int &p)
{
	if(high-low+1<5)
		insertSort(low,high,p);
	else
	{
		int pre,bac;
		int mid = (low+high)/2;
		merge_sort(low,mid,pre);
		merge_sort(mid+1,high,bac);
		merge(pre,bac,p);
	}
}
int* sort_by_price::tosort(vector<flight_information_node*>& sort_flight_info)
{
	number = sort_flight_info.size();
	data = new int[number+1];
	for(int m=1;m<=number;m++)
	{
		data[m] = sort_flight_info[m-1]->price_normal;
	}
	link = new int[number+1]();
	merge_sort(1,number,entrance);
	return link;
}
int Sort::get_flytime(string start,string end)
{
	//start格式:2021/03/18/23:44   以2020/01/01/00:00为基准
	int minute_year = 60*24*365;//一年几分钟
	int minute_month = 60*24*31;
	int s_year = stoi(start.substr(2,2));
	int s_month = stoi(start.substr(5,2));
	int s_day = stoi(start.substr(8,2));
	int s_hour = stoi(start.substr(11,2));
	int s_minute = stoi(start.substr(15,2));
	unsigned int s_time = (s_year-20)*minute_year+(s_month-1)*minute_month+(s_day-1)*60*24+s_hour*60+s_minute;

	int e_year = stoi(end.substr(0,4));
	int e_month = stoi(end.substr(5,2));
	int e_day = stoi(end.substr(8,2));
	int e_hour = stoi(end.substr(11,2));
	int e_minute = stoi(end.substr(15,2));
	unsigned int e_time = (e_year-20)*minute_year+(e_month-1)*minute_month+(e_day-1)*60*24+e_hour*60+e_minute;

	int minute = e_time-s_time;
	return minute;
}
int* sort_by_time::tosort(vector<flight_information_node*>& sort_flight_info)
{
	number = sort_flight_info.size();
	data = new int[number+1];
	for(int m=1;m<=number;m++)
	{
		int time = get_flytime(sort_flight_info[m-1]->departure_start_time,sort_flight_info[m-1]->destination_arrive_time);
		data[m] = time;
	}
	link = new int[number+1]();
	merge_sort(1,number,entrance);
	return link;
}
int* sort_by_remain_number::tosort(vector<flight_information_node*>& sort_flight_info)
{
	number = sort_flight_info.size();
	data = new int[number+1];
	for(int m=1;m<=number;m++)
	{
		data[m] = sort_flight_info[m-1]->remain_number_normal;
	}
	link = new int[number+1]();
	merge_sort(1,number,entrance);
	return link;
}