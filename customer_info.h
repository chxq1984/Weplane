#pragma once

#include "b_plus_tree_customer.h"
#include "global.h"
#include "code.h"
class customer_info
{
public:
	b_plus_tree_customer* tree;
	password code;//密码管理类
	void get_info_from_file();//从文件读入用户信息，暂时仅用于debug
	customer_info();
	void create_account();//创建账号
	void login();//登录
	customer_info_node* search_customer_info(unsigned int account);//返回用户信息节点
};
