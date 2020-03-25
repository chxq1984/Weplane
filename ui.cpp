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
	cout<<"»¶Ó­Ê¹ÓÃWePlane·É»úĞÅÏ¢¹ÜÀíÏµÍ³"<<endl;
	for (int m = 0;m < main_width;m++)
	{
		cout<<"¨€";
	}
	cout<<endl<<endl;
}
void UI::footer()
{
	cout<<endl;
	for(int m=0;m<main_width;m++)
	{
		cout<<"¨€";
	}
}
char UI::choose_login()
{
	header();
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"1.³Ë¿ÍµÇÂ¼"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"2.¹ÜÀíÔ±µÇÂ¼"<<endl;
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
		is_exit_outer=is_exit_outer=0;
		if(juge_object == '1')//³Ë¿Í
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
						buying_ticket();//ÂòÆ±
						break;
					case '2':
						cancel_ticket();//ÍËÆ±
						break;
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
}
char UI::customer_login_choose()
{
	system("cls");
	header();
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"1.µÇÂ¼ÕËºÅ"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"2.×¢²áÕËºÅ"<<endl;
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
	cout<<"1.ÂòÆ±"<<endl<<endl;
	for(int m=0;m<main_width/2+7;m++)
		cout<<" ";
	cout<<"2.ÍËÆ±"<<endl;
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
	code_ad.add_information();//Òş²Ø¹ÜÀíÔ±×¢²áÈë¿Ú*/
	system("cls");
	manager.customers.login();
}
char UI::administor_operator()
{
	system("cls");
	header();
	for(int m=0;m<main_width/2+4;m++)
		cout<<" ";
	cout<<"1.Ôö¼Óº½°àĞÅÏ¢"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"2.º½°àÑÓÎó"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"3.È¡Ïûº½°à"<<endl<<endl;
	for(int m=0;m<main_width/2+5;m++)
		cout<<" ";
	cout<<"4.º½°àÆğ·É"<<endl<<endl;
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
	cout<<"ÇëÊäÈëº½°àÆğ·ÉÊ±¼ä:";
	cin>>departure_start_time;
	cout<<"ÇëÊäÈëº½°àÆğ·ÉµØ:";
	cin>>departure;
	cout<<"ÇëÊäÈëº½°àÄ¿µÄµØ:";
	cin>>destination;
	cout<<"ÇëÊäÈëº½°àºÅ:";
	cin>>flight_number;
	cout<<"ÇëÊäÈëÔ¤¼ÆÑÓÎóÊ±³¤:";
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
	cout<<"ÇëÊäÈëº½°àÆğ·ÉÊ±¼ä:";
	cin>>departure_start_time;
	cout<<"ÇëÊäÈëº½°àÆğ·ÉµØ:";
	cin>>departure;
	cout<<"ÇëÊäÈëº½°àÄ¿µÄµØ:";
	cin>>destination;
	cout<<"ÇëÊäÈëº½°àºÅ:";
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
	cout<<"ÇëÊäÈëº½°àÆğ·ÉÊ±¼ä:";
	cin>>departure_start_time;
	cout<<"ÇëÊäÈëº½°àÆğ·ÉµØ:";
	cin>>departure;
	cout<<"ÇëÊäÈëº½°àÄ¿µÄµØ:";
	cin>>destination;
	cout<<"ÇëÊäÈëº½°àºÅ:";
	cin>>flight_number;
	manager.cancel_flight(departure_start_time,departure,destination,flight_number);
}