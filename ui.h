#pragma once
#include <iostream>
#include <conio.h>
#include "flight_information.h"
#include "code.h"
using namespace std;

class UI
{
public:
	flight_information manager;
	int main_width,main_height;
	UI();
	void main_window();
	void default_setting();//��ʼ��
	void header();
	void footer();
	void login_customer();//�û���¼
	void register_customer();//�û�ע��
	char customer_login_choose();//��¼������
	char choose_login();//�жϵ�¼����
	char choose_buy_cancel();//�ж�����Ʊ������Ʊ
	void buying_ticket();//��Ʊ
	void cancel_ticket();//��Ʊ
	void login_administor();//����Ա��¼
	char administor_operator();//����Ա����
	void add_flight();//���Ӻ���
	void deny_flight();//��������
	void cancel_flight();//����ȡ��
	void fly_flight();//�������
	void search_flight_info();
	void search_flight_info_by_city();
	void search_flight_info_by_flight_number();
};