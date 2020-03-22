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
	string temp_file_name;//��ʱ�ļ���
	file_manage();
	queue<string> split(string position,string parameter);
	void delete_file(int file_type,string target);//ɾ������
	virtual void write_file(flight_information_node*flight_info,int file_type)=0;
	queue<string> search(string key_word,int position);//���ҷ�����������Ϣ������,positionΪkey_word���ڵ�����
	//virtual void revise_file();//�޸Ĳ���
};
class notice_file:public file_manage
{
public:
	void write_file(flight_information_node*flight_info,int file_type);
	notice_file();
};