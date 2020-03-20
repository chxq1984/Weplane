#pragma once

#include "customer_info.h"
#include "b_plus_tree_customer.h"
#include "global.h"
customer_info::customer_info()
{
	tree = new b_plus_tree_customer(level);
}
void customer_info::create_account()
{
	unsigned int account_number;
	account_number = account;
	code.add_information();
	customer_info_node *new_customer = new customer_info_node;
	new_customer->load_data(account_number);
	tree->insert_customer_info(new_customer);
}
customer_info_node* customer_info::search_customer_info(unsigned int account)
{
	node_customer *target = tree->find_position(account,tree->root,NULL)[0];
	if(!target)
	{
		//cout<<"无此用户信息"<<endl;
		return NULL;
	}
	int m;
	for(m=0;m<target->position;m++)
	{
		if(target->index[m] == account)
			break;
	}
	customer_info_node* customer_info = target->info_list[m];
	//cout<<"账号:"<<customer_info->account<<endl;
}
void customer_info::login()
{
	code.input_information();
	code.check_information();
	string account = code.ret_name();
	login_account = atoi(account.c_str());
}
void customer_info::get_info_from_file()
{
	ifstream customer_info;
    customer_info.open("customer_info.in", ios::in);
    while (!customer_info.eof())
	{
		unsigned int account_number;
		customer_info>>account_number;
		customer_info_node *new_customer = new customer_info_node;
		new_customer->load_data(account_number);
		tree->insert_customer_info(new_customer);
	}
	customer_info.close();
	login_account = 100000;//默认测试账号,模拟登录以跳过登录操作,方便调试
}