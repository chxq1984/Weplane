#pragma once
#include <map>
#include <string>
using namespace std;
extern map<string,int> info_map;//������ʼ��������ش�����map
extern map<string,int> name_map;//���ݵص����õ�id
void make_info_map();//����map
int global_transform(string departure,string destination);//ת���ֵ�
const int level=5;//b+����level
extern unsigned int account;//�˺�ֵ
extern unsigned int login_account;//��ǰ��¼���û��˺�
int isfile_empty(string file_name);//�ж��ļ��Ƿ�Ϊ��