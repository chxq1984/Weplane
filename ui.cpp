#include "ui.h"
UI::UI()
{
	main_width = 30;
	main_height = 20;
}
void UI::default_setting()
{
	make_info_map();
	manager.get_info_from_file();
	manager.customers.get_info_from_file();
}
void UI::header()
{
	for(int m=0;m<main_width/2-1;m++)
		cout<<" ";
	cout<<"��ӭʹ��WePlane�ɻ���Ϣ����ϵͳ"<<endl;
	for (int m = 0;m < main_width;m++)
	{
		cout<<"��";
	}
	cout<<endl<<endl;
}
void UI::footer()
{
	cout<<endl;
	for(int m=0;m<main_width;m++)
	{
		cout<<"��";
	}
}
char UI::choose_login()
{
	header();
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"1.�˿͵�¼"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"2.����Ա��¼"<<endl;
	footer();
	char choose;
	choose = _getch();
	cout << choose;
	return choose;
}
void UI::main_window()
{
	default_setting();
	while(1)
	{
		system("cls");
		char juge_object = choose_login();
		int is_exit_inner,is_exit_outer;
		is_exit_inner=is_exit_outer=0;
		if(juge_object == '1')//�˿�
		{
			char is_out = customer_login_choose();
			if(is_out == 'q')
				continue;
			while(1)
			{
				char juge_buy_cancel = choose_buy_cancel();
				switch(juge_buy_cancel)
				{
					case '1':
						buying_ticket();//��Ʊ
						break;
					case '2':
						cancel_ticket();//��Ʊ
						break;
					case '3':
						search_flight_info();//Ʊ���ѯ
						break;
					case '4':
						flight_recommend();//�����Ƽ�
					case 'q':
						is_exit_inner = 1;
						break;
				}
				if(is_exit_inner)
					break;
			}
		}
		else if(juge_object == '2')
		{
			login_administor();
			while(1)
			{
				char juge_operator = administor_operator();
				switch(juge_operator)
				{
					case '1':
						add_flight();
						break;
					case '2':
						deny_flight();
						break;
					case '3':
						cancel_flight();
						break;
					case '4':
						fly_flight();
						break;
					case 'q':
						is_exit_inner = 1;
						break;
				}
				if(is_exit_inner)
					break;
			}
		}
		else if(juge_object == 'q')
			is_exit_outer = 1;
		if(is_exit_outer)
			break;
	}
}
void UI::login_customer()
{
	system("cls");
	manager.customers.login();
	system("cls");
	manager.notice_flight();
}
char UI::customer_login_choose()
{
	system("cls");
	header();
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"1.��¼�˺�"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"2.ע���˺�"<<endl;
	footer();
	char choose = _getch();
	cin.sync();
	switch(choose)
	{
		case '1':
			login_customer();
			break;
		case '2':
			register_customer();
			break;
	}
	return choose;
}
void UI::register_customer()
{
	system("cls");
	manager.customers.create_account();
}
char UI::choose_buy_cancel()
{
	system("cls");
	header();
	for(int m=0;m<main_width/2+7;m++)
		cout<<" ";
	cout<<"1.��Ʊ"<<endl<<endl;
	for(int m=0;m<main_width/2+7;m++)
		cout<<" ";
	cout<<"2.��Ʊ"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"3.Ʊ���ѯ"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"4.�����Ƽ�"<<endl<<endl;
	footer();
	char choose;
	choose = _getch();
	return choose;
}
void UI::buying_ticket()
{
	system("cls");
	manager.buy_ticket();
}
void UI::cancel_ticket()
{
	system("cls");
	manager.cancel_ticket();
}
void UI::login_administor()
{
	/*password code_ad;
	account = 453480049;
	code_ad.add_information();//���ع���Աע�����*/
	system("cls");
	manager.customers.login();
}
char UI::administor_operator()
{
	system("cls");
	header();
	for(int m=0;m<main_width/2+4;m++)
		cout<<" ";
	cout<<"1.���Ӻ�����Ϣ"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"2.��������"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"3.ȡ������"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"4.�������"<<endl<<endl;
	footer();
	char choose = _getch();
	return choose;
}
void UI::add_flight()
{
	system("cls");
	manager.insert_flight_info();
}
void UI::deny_flight()
{
	system("cls");
	string departure_start_time;
	string departure;
	string destination;
	string flight_number;
	int delay_minute;
	cout<<"�����뺽�����ʱ��:";
	cin>>departure_start_time;
	cout<<"�����뺽����ɵ�:";
	cin>>departure;
	cout<<"�����뺽��Ŀ�ĵ�:";
	cin>>destination;
	cout<<"�����뺽���:";
	cin>>flight_number;
	cout<<"������Ԥ������ʱ��:";
	cin>>delay_minute;
	manager.delay_flight(departure_start_time,departure,destination,flight_number,delay_minute);

}
void UI::cancel_flight()
{
	system("cls");
	string departure_start_time;
	string departure;
	string destination;
	string flight_number;
	cout<<"�����뺽�����ʱ��:";
	cin>>departure_start_time;
	cout<<"�����뺽����ɵ�:";
	cin>>departure;
	cout<<"�����뺽��Ŀ�ĵ�:";
	cin>>destination;
	cout<<"�����뺽���:";
	cin>>flight_number;
	manager.cancel_flight(departure_start_time,departure,destination,flight_number);
}
void UI::fly_flight()
{
	system("cls");
	string departure_start_time;
	string departure;
	string destination;
	string flight_number;
	cout<<"�����뺽�����ʱ��:";
	cin>>departure_start_time;
	cout<<"�����뺽����ɵ�:";
	cin>>departure;
	cout<<"�����뺽��Ŀ�ĵ�:";
	cin>>destination;
	cout<<"�����뺽���:";
	cin>>flight_number;
	manager.cancel_flight(departure_start_time,departure,destination,flight_number);
}
void UI::search_flight_info()
{
	system("cls");
	header();
	for(int m=0;m<main_width/2-4;m++)
		cout<<" ";
	cout<<"1.������ʼ��/Ŀ�ĵز�ѯ"<<endl<<endl;
	for(int m=0;m<main_width/2-2;m++)
		cout<<" ";
	cout<<"2.���ݺ���Ų�ѯ"<<endl<<endl;
	footer();
	char choose;
	choose = _getch();
	switch(choose)
	{
		case '1':
			search_flight_info_by_city();
			break;
		case '2':
			search_flight_info_by_flight_number();
			break;
		case 'q':
			break;
	}
}
void UI::search_flight_info_by_city()
{
	string departure,destination;
	system("cls");
	cout<<"�����������:"<<endl;
	cin>>departure;
	cout<<"������Ŀ�ĵ�:"<<endl;
	cin>>destination;
	system("cls");
	manager.search_ticket_by_city(departure,destination);
	_getch();
}
void UI::search_flight_info_by_flight_number()
{
	string flight_number;
	system("cls");
	cout<<"�����뺽���:"<<endl;
	cin>>flight_number;
	system("cls");
	manager.search_ticket_by_flight_number(flight_number);
	_getch();
}
void UI::flight_recommend()
{
	system("cls");
	string departure,destination;
	cout<<"�����������:"<<endl;
	cin>>departure;
	cout<<"������Ŀ�ĵ�:"<<endl;
	cin>>destination;
	system("cls");
	manager.recommend_ticket(departure,destination);
	_getch();
}