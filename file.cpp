#include "file.h"
file_manage::file_manage()
{
	temp_file_name = "database/temp.in";
}
notice_file::notice_file()
{
	file_name = "database/notice.in";
}
void file_manage::delete_file(int file_type,string target)
{
	ifstream in(file_name);
	ofstream out(temp_file_name);
	string line;
	while(getline(in,line))
	{
		if(line.length()<=3)//过滤作用
			continue;
		queue<string> data_list = split(line," ");
		string type = data_list.front();
		data_list.pop();
		string flag = data_list.front();
		if(type==to_string(file_type)&&target==flag)//找到删除记录直接跳过
			continue;
		out<<line<<endl;
	}
	out.close();
	in.close();
	if(!remove(file_name.c_str()))
	{
		rename(temp_file_name.c_str(),file_name.c_str());
	}
}
queue<string> file_manage::split(string position,string parameter)
{
	queue<string> store;
	position += parameter;
	int lenPara = parameter.length();
	int end = position.length() - lenPara;
	int pre = position.find(parameter);
	while(pre != end)
	{
		string cat = position.substr(0,pre);
		store.push(cat);
		int length = position.length() - lenPara - pre;
		position = position.substr(pre + lenPara,length);
		pre = position.find(parameter);
		end = position.length() - lenPara;
	}
	store.push(position.substr(0,pre));
	return store;
}
void notice_file::write_file(flight_information_node*flight_info,int file_type)
{//写入延误航班/取消航班时所需通知的乘客信息
	ofstream out(file_name,ios::app);
	list<unsigned int>::iterator iter;
	for(iter=flight_info->buying_customer.begin();iter!=flight_info->buying_customer.end();iter++)
	{
		out<<file_type<<" ";
		out<<(*iter)<<" ";
		out<<flight_info->flight_number<<" ";
		out<<flight_info->departure_start_time<<" ";
		//cout<<flight_info->departure<<" "<<flight_info->destination;
		out<<flight_info->departure<<" ";
		out<<flight_info->destination<<" ";
		out<<flight_info->islater<<endl;
	}
	out.close();
}
queue<string> file_manage::search(string key_word,int position)
{
	queue<string> search_list;
	ifstream in(file_name);
	string line;
	while(getline(in,line))
	{
		if(line.length()<=3)
			continue;
		queue<string> data_list = split(line," ");
		for(int m=0;m<position-1;m++)
			data_list.pop();
		if(data_list.front() == key_word)
		{
			search_list.push(line);
		}
	}
	return search_list;
}