#pragma once

#include "b_plus_tree_customer.h"
#include "global.h"
#include "code.h"
class customer_info
{
public:
	b_plus_tree_customer* tree;
	password code;//密码管理类
	customer_info();
	void create_account();//创建账号
	void login();//登录
	void search_customer_info(unsigned int account);//获取用户信息
};
