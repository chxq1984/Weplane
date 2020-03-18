#pragma once

#include "customer_info.h"
#include "b_plus_tree_customer.h"
customer_info::customer_info()
{
	tree = new b_plus_tree_customer(level);
}
void customer_info::create_account()
{
	unsigned int account_number;
	account_number = account;
	code.add_information();
	/*cout<<"您的账号为:"<<account_number;
	cout<<"请设置密码:";
	cin>>password;*/
	customer_info_node *new_customer = new customer_info_node;
	new_customer->load_data(account_number);
	tree->insert_customer_info(new_customer);
}
void customer_info::search_customer_info(unsigned int account)
{
	node_customer *target = tree->find_position(account,tree->root,NULL)[0];
	if(!target)
	{
		cout<<"无此用户信息"<<endl;
		return;
	}
	int m;
	for(m=0;m<target->position;m++)
	{
		if(target->index[m] == account)
			break;
	}
	customer_info_node* customer_info = target->info_list[m];
	cout<<"账号:"<<customer_info->account<<endl;
}
void customer_info::login()
{
	code.input_information();
	code.check_information();
}