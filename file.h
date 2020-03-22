#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <cstdio>
#include "b_plus_tree.h"
using namespace std;
class file_manage
{
public:
	string file_name;
	string temp_file_name;//临时文件名
	file_manage();
	queue<string> split(string position,string parameter);
	void delete_file(int file_type,string target);//删除操作
	virtual void write_file(flight_information_node*flight_info,int file_type)=0;
	queue<string> search(string key_word,int position);//查找符合条件的信息并返回,position为key_word所在的条数
	//virtual void revise_file();//修改操作
};
class notice_file:public file_manage
{
public:
	void write_file(flight_information_node*flight_info,int file_type);
	notice_file();
};