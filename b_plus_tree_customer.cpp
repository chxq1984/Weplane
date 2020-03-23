#pragma once

#include "b_plus_tree_customer.h"
#include <queue>
void have_buy_info::set_info(string flight_number,string company_name,string departure,string destination,string stop,string departure_start_time,string stop_arrive_time,string stop_start_time,string destination_arrive_time,int ticket_type,float price)
{
	this->flight_number = flight_number;
	this->company_name = company_name;
	this->departure = departure;
	this->destination = destination;
	this->stop = stop;
	this->departure_start_time = departure_start_time;
	this->stop_arrive_time = stop_arrive_time;
	this->stop_start_time = stop_start_time;
	this->destination_arrive_time = destination_arrive_time;
	this->ticket_type = ticket_type;
	this->price = price;
}
void customer_info_node::load_data(unsigned int account)
{
	this->account = account;
}
node_customer::node_customer(int n)
{
	level = n;
	index = new int[level-1]();
	point = new node_customer*[level];
	for(int m=0;m<n;m++)
		point[m] = NULL;
	position = 0;
	right = NULL;
	info_list = new customer_info_node*[level-1];
}
b_plus_tree_customer::b_plus_tree_customer(int n)
{
	level = n;
	root = NULL;
}
node_customer **b_plus_tree_customer::find_position(int data,node_customer *target,node_customer *father)
{
	node_customer **target_father = new node_customer*[2];
	target_father[0] = target;
	target_father[1] = father;
	int m;
	for(m=0;m<target->position;m++)
	{
		if(data<target->index[m])
			break;
	}
	if(target->point[m] != NULL)
	{
		delete target_father;
		return find_position(data,target->point[m],target);
	}
	else
	{
		return target_father;
	}
}
void b_plus_tree_customer::split_node(node_customer*& target,node_customer*&father,int data)
{
	int last_data = data;//多出的那个数
	node_customer *up=father,*right;
	if(target->index[target->position-1] > data)//进行排序，将最大值提出至last_data
	{
		last_data = target->index[target->position-1];
		insert_sort(data,target->index,level-2);
	}
	right = new node_customer(level);
	right->right = target->right;//横向连入结点
	target->right = right;
	if(!up)
		up = new node_customer(level);//说明为根结点分裂
	
	int mid = level/2;
	if(up->position == level-1)//处理非叶结点分裂
	{
		split_up_node(up,target->index[mid]);
		node_customer *up_right = up->right;
		node_customer *temp = up->point[0];
		for(int m=0;m<=level/2;m++)//处理叶子节点指针
		{
			up->point[m] = temp;
			temp = temp->right;
		}
		for(int m=0;m<=level/2;m++)
		{
			up_right->point[m] = temp;
			temp = temp->right;
		}

	}
	else
	{
		insert_sort(target->index[mid],up->index,up->position++);//向up中插入数据并排序
		if(up->position == 1)//树长高
		{
			up->point[0] = target;
			up->point[1] = right;
			root = up;
		}
		else
		{
			int i=0;
			node_customer *temp=up->point[0];
			for(int m=0;m<=up->position;m++)
			{
				up->point[i] = temp;
				i++;
				temp = temp->right;
			}

		}//上述代码功能：将父结点指向子结点的指针重置
	}
	for(int m=0;m<level-mid-1;m++)//将target后半部分转至right
	{
		right->index[right->position++] = target->index[mid+m];
		target->index[mid+m] = 0;//还原为默认值0
	}
	right->index[right->position++] = last_data;
	target->position = level/2;//维护position
}
void b_plus_tree_customer::insert(int data)
{
	if(!root)
	{
		root = new node_customer(level);
		int position = root->position;
		root->index[position] = data;
		root->position++;
		return;
	}
	node_customer **target_father = find_position(data,root,NULL);
	node_customer *target = target_father[0];
	node_customer *father = target_father[1];
	int exist = is_exist(data,target->index,target->position);
	if(exist != -1)
	{
		//插入值相同，若要操作在此处进行即可
		return;
	}
	if(target -> position != level-1)//未满,直接插入即可
	{
		insert_sort(data,target->index,target->position);
		target->position++;
		return;
	}
	else//已满，需要分裂
	{
		split_node(target,father,data);
	}
}
void b_plus_tree_customer::insert_sort(int data,int *&index,int number)
{
	int m;
	for(m=number-1;m>=0;m--)
	{
		if(data < index[m])
		{
			index[m+1] = index[m];
		}
		else
			break;
	}
	index[m+1] = data;
}
int b_plus_tree_customer::is_exist(int data,int *&index,int number)
{
	for(int m=0;m<number;m++)
	{
		if(index[m] == data)
			return m;
	}
	return -1;
}
void b_plus_tree_customer::run_down()
{
	if(!root)
		return;
	node_customer *temp = root;
	for(;temp->point[0];temp=temp->point[0]);//寻找叶结点始端
	for(;temp;temp=temp->right)
	{
		for(int m=0;m<temp->position;m++)
		{
			cout<<temp->index[m]<<" ";
		}
	}
}
node_customer *b_plus_tree_customer::find_father(int data,node_customer *target,node_customer *father)
{
	int m;
	for(m=0;m<target->position;m++)
	{
		if(data<=target->index[m])
			break;
	}
	if(data == target->index[m])
		return father;
	else
	{
		return find_father(data,target->point[m],target);
	}
	
}
void b_plus_tree_customer::split_up_node(node_customer *target,int data)
{
	int last_data = data;//多出的那个数
	node_customer *father = find_father(target->index[0],root,NULL);
	node_customer *up=father,*right;
	if(target->index[target->position-1] > data)//进行排序，将最大值提出至last_data
	{
		last_data = target->index[target->position-1];
		insert_sort(data,target->index,level-2);
	}
	right = new node_customer(level);
	right->right = target->right;
	target->right = right;
	if(!up)
		up = new node_customer(level);//说明为根结点分裂

	int mid = level/2;
	if(up->position == level-1)
	{
		split_up_node(up,target->index[mid]);
		node_customer *up_right = up->right;
		int i = 0;
		node_customer *temp = up->point[0];
		for(int m=0;m<=level/2;m++)//处理叶子节点指针
		{
			up->point[m] = temp;
			temp = temp->right;
		}
		for(int m=0;m<=level/2;m++)
		{
			up_right->point[m] = temp;
			temp = temp->right;
		}
	}
	else
	{
	insert_sort(target->index[mid],up->index,up->position++);//向up中插入数据并排序
	if(up->position == 1)//树长高
	{
		up->point[0] = target;
		up->point[1] = right;
		root = up;
	}
	else
	{
		int i=0;
		node_customer *temp=up->point[0];
		for(int m=0;m<=up->position;m++)
		{
			up->point[i] = temp;
			i++;
			temp = temp->right;
		}
	}
	}
	target->index[mid] = 0;
	for(int m=mid+1;m<level-1;m++)
	{
		right->index[right->position++] = target->index[m];
		target->index[m] = 0;
	}
	right->index[right->position++] = last_data;
	target->position = level/2;
}
void b_plus_tree_customer::overTree()
{
	node_customer *temp;
	queue<node_customer*> store_node;
	store_node.push(root);
	while(store_node.size())
	{
		temp = store_node.front();
		int m;
		for(m=0;m<temp->position;m++)
		{
			cout<<temp->index[m]<<" ";
			if(temp->point[m])
			{
				store_node.push(temp->point[m]);
			}
		}
		if(temp->point[m])
		{
			store_node.push(temp->point[m]);
		}
		cout<<endl;
		store_node.pop();
	}
}
void b_plus_tree_customer::delete_data(int data)
{
	node_customer **target_father = find_position(data,root,NULL);
	node_customer *target = target_father[0];
	node_customer *father = target_father[1];
	int m;
	for(m=0;m<target->position;m++)
	{
		if(target->index[m] == data)
			break;
	}
	if(target == root && father == NULL)
	{
		delete_index(target->index,m,target->position);
		return;
	}
	int limit = level/2;
	if(target->position > limit)
	{
		delete_index(target->index,m,target->position);
		return;
	}
	node_customer *pre = get_pre_node(target,father);
	node_customer *brother = pre;
	if(pre && pre->position>limit || !pre && target->right->position>limit)
	{//兄弟节点数目足够
		if(!pre)
		{
			//无前置节点
			brother = target->right;//以下一节点为目标
			int borrow = brother->index[0];
			delete_index(brother->index,0,brother->position);
			target->index[m] = borrow;
			sort_index(target->index,target->position,m);
			int father_position = find_father_position(target,brother,father);
			father->index[father_position] = brother->index[0];
		}
		else
		{
			int borrow = pre->index[pre->position-1];
			pre->index[pre->position-1] = 0;
			pre->position--;
			target->index[m] = borrow;
			sort_index(target->index,target->position,m);
			int father_position = find_father_position(pre,target,father);
			father->index[father_position] = borrow;
		}
	}
	else
	{
		//合并兄弟节点
		delete_index(target->index,m,target->position);
		if(!pre)
		{
			together_index(target->index,target->right->index,target->position,target->right->position);
			node_customer *temp = target->right;
			target->right = temp->right;
			delete temp;
		}
		else
		{
			together_index(pre->index,target->index,pre->position,target->position);
			pre->right = target->right;
			delete target;
		}
		int delete_father_position = 0;
		if(pre)
		{
			for(delete_father_position=0;delete_father_position<father->position;delete_father_position++)
			{
				if(father->point[delete_father_position]==pre && father->point[delete_father_position+1]==target)
					break;
			}
		}
		delete_father_node(father,delete_father_position);
	}

}
void b_plus_tree_customer::delete_index(int*& index,int position,int &number)
{
	int m;
	for(m=position;m<number-1;m++)
	{
		index[m] = index[m+1];
	}
	index[m] = 0;
	number--;
}
node_customer* b_plus_tree_customer::get_pre_node(node_customer*target,node_customer *father)
{
	node_customer *temp = father->point[0];
	node_customer *pre = NULL;
	for(;temp;temp=temp->right)
	{
		if(temp == target)
			return pre;
		pre = temp;
	}
}
void b_plus_tree_customer::sort_index(int *&index,int number,int position)
{
	int data = index[position];
	if(position-1>=0 && data<index[position-1])
	{
		int m;
		for(m=position-1;m>=0;m--)
		{
			if(index[m]<=data)
				break;
			else
			{
				index[m+1] = index[m];
			}
		}
		index[m+1] = data;
	}
	else
	{
		int m;
		for(m=position+1;m<number;m++)
		{
			if(index[m]>=data)
				break;
			else
			{
				index[m-1] = index[m];
			}
		}
		index[m-1] = data;
	}
}
void b_plus_tree_customer::together_index(int*& pre,int *&bac,int &number_pre,int &number_bac)
{
	for(int m=0;m<number_bac;m++)
	{
		pre[number_pre+m] = bac[m];
	}
	number_pre += number_bac;
	number_bac = 0;
}
void b_plus_tree_customer::delete_father_node(node_customer *&target,int position)
{
	if(target == root && target->position==1)
	{
		root = target->point[0];
		delete target;
		target = NULL;
		return;
	}
	else if(target == root)
	{
		delete_index(target->index,position,target->position);
		move_point(target,position);
		return;
	}
	if(target->position>level/2)
	{
		//元素数足够，删除元素后不需要合并
		delete_index(target->index,position,target->position);//删除元素
		move_point(target,position);
	}
	else
	{
		node_customer *father = find_father(target->index[0],root,NULL);
		node_customer *pre = get_pre_node(target,father);
		node_customer *right = target->right;
		if(pre)
		{
			int father_position = find_father_position(pre,target,father);
			//存在pre节点
			if(pre->position>level/2)
			{
				//pre节点富裕,转移兄弟节点
				target->index[position] = father->index[father_position];
				sort_index(target->index,target->position,position);
				father->index[father_position] = pre->index[pre->position-1];
				pre->index[pre->position-1] = 0;
				pre->position--;
				/*node *temp = pre->point[pre->position+1];//处理target的指针
				for(int m=0;m<=target->position;m++)
				{
					target->point[m] = temp;
					temp = temp->right;
				}*/
				//position+1=position ... 1=0
				for(int m=position;m>=0;m--)
					target->point[m+1] = target->point[m];
				target->point[0] = pre->point[pre->position+1];
				pre->point[pre->position+1] = NULL;
			}
			else
			{
				//pre节点不富裕，需要合并
				delete_index(target->index,position,target->position);
				int father_index = father->index[father_position];
				delete_father_node(father,father_position);
				pre->right = target->right;
				//move_point(father,father_position);//移动father的指针
				move_point(target,position);
				for(int m=0;m<=target->position;m++)//移动pre指针
				{
					pre->point[pre->position+1+m] = target->point[m];
				}
				pre->index[pre->position++] = father_index;
				for(int m=0;m<target->position;m++)//将target的值复制到pre中
				{
					pre->index[pre->position++] = target->index[m];
					target->index[m] = 0;
				}
				target->position = 0;
				delete target;
			}
		}
		else
		{
			//不存在pre节点，需要用right节点代替
			int father_position = find_father_position(target,right,father);
			if(right->position>level/2)
			{
				//right节点富裕,转移兄弟节点
				target->index[position] = father->index[father_position];
				sort_index(target->index,target->position,position);
				father->index[father_position] = right->index[0];
				for(int m=position+1;m<target->position;m++)
				{
					target->point[m] = target->point[m+1];
				}
				target->point[target->position] = right->point[0];
				delete_index(right->index,0,right->position);
				/*move_point(target,position);*/
				move_point(right,-1);//right指针前移
			}
			else
			{
				//right节点不富裕，需要合并
				delete_index(target->index,position,target->position);
				int father_index = father->index[father_position];
				delete_father_node(father,father_position);
				target->right = right->right;
				//move_point(father,father_position);//移动father的指针
				move_point(target,position);
				for(int m=0;m<=right->position;m++)//移动target的指针
				{
					target->point[target->position+1+m] = right->point[m];
				}
				target->index[target->position++] = father_index;
				for(int m=0;m<right->position;m++)//将target的值复制到pre中
				{
					target->index[target->position++] = right->index[m];
					right->index[m] = 0;
				}
				right->position = 0;
				delete right;
			}
		}
	}
}
int b_plus_tree_customer::find_father_position(node_customer *pre,node_customer *target,node_customer *father)
{
	int position;
	for(position=0;position<father->position;position++)
	{
		if(father->point[position]==pre && father->point[position+1]==target)
			break;
	}
	return position;
}	
void b_plus_tree_customer::move_point(node_customer *target,int position)
{
	if(!target)
		return;
	int m;
	for(m=position+1;m<=target->position;m++)
	{
		target->point[m] = target->point[m+1];
	}
	target->point[m] = NULL;
}
void b_plus_tree_customer::insert_customer_info(customer_info_node *new_customer)
{
	unsigned int account = new_customer->account;
	insert(account);
	node_customer *target = find_position(account,root,NULL)[0];
	int m;
	for(m=0;m<target->position;m++)
	{
		if(target->index[m] == account)
			break;
	}
	target->info_list[m] = new_customer;
}
customer_info_node* b_plus_tree_customer:: search_customer_info(unsigned int account)
{
	node_customer* customers_node = find_position(account,root,NULL)[0];
	for(int m=0;m<level-1;m++)
	{
		if(customers_node->info_list[m]->account == account)
			return (customers_node->info_list[m]);
	}
	return NULL;
}