#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include "global.h"
using std::vector;
using namespace std;
class type_code
{
	string name,code;
public:
	string& retname(){return name;}
	string& retcode(){return code;}
};
class type_message
{
public:
	string name;
	int time,pretime;
};
class password
{
	string code,name;
	vector<type_code> store;
	vector<type_message> store_message;
public:
	int flag;//�����Ƿ���ϱ�׼
	int times;//����������
	password(){code="";flag=0;}
	void input_information();
	void check_information();
	void add_information();
	void solve_code(string &code);//�����˸�
	string add_dele_code(string temcode);//����
	void change_code();//�޸�����
	void dele_code();//ע���˺�
	void load_log_in();//��ȡ��¼��Ϣ
	void refresh_log_in();//ˢ�µ�¼��Ϣ
	void add_log_in(const string &temname);//���ӵ�¼��Ϣ
	void dele_log_in();//ɾ����¼��Ϣ
	string ret_name();//�����û���
};