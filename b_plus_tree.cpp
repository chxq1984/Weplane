#pragma once

#include "b_plus_tree.h"
#include <queue>
flight_information_node::flight_information_node(string flight_number,string company_name,string departure,string destination,string stop,string departure_start_time,string stop_arrive_time,string stop_start_time,string destination_arrive_time,int remain_number_normal,int remain_number_vip,float price_normal,float price_vip)
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
	this->remain_number_normal = remain_number_normal;
	this->remain_number_vip = remain_number_vip;
	this->price_normal = price_normal;
	this->price_vip = price_vip;
	islater = 0;
}
flight_information_node::flight_information_node(string flight_number,string company_name,string departure,string destination,string departure_start_time,string destination_arrive_time,int remain_number_normal,int remain_number_vip,float price_normal,float price_vip)
{
	this->flight_number = flight_number;
	this->company_name = company_name;
	this->departure = departure;
	this->destination = destination;
	this->departure_start_time = departure_start_time;
	this->destination_arrive_time = destination_arrive_time;
	this->remain_number_normal = remain_number_normal;
	this->remain_number_vip = remain_number_vip;
	this->price_normal = price_normal;
	this->price_vip = price_vip;

	stop = "";
	stop_arrive_time = "";
	stop_start_time = "";
	islater = 0;
}
node::node(int n)
{
	level = n;
	index = new int[level-1]();
	point = new node*[level];
	for(int m=0;m<n;m++)
		point[m] = NULL;
	position = 0;
	right = NULL;
	info_list = new list<flight_information_node*>[level-1];
}
b_plus_tree::b_plus_tree(int n)
{
	level = n;
	root = NULL;
}
node **b_plus_tree::find_position(int data,node *target,node *father)
{
	node **target_father = new node*[2];
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
void b_plus_tree::split_node(node*& target,node*&father,int data)
{
	int last_data = data;//������Ǹ���
	node *up=father,*right;
	if(target->index[target->position-1] > data)//�������򣬽����ֵ�����last_data
	{
		last_data = target->index[target->position-1];
		insert_sort(data,target->index,level-2);
	}
	right = new node(level);
	right->right = target->right;//����������
	target->right = right;
	if(!up)
		up = new node(level);//˵��Ϊ��������
	
	int mid = level/2;
	if(up->position == level-1)//�����Ҷ������
	{
		split_up_node(up,target->index[mid]);
		node *up_right = up->right;
		node *temp = up->point[0];
		for(int m=0;m<=level/2;m++)//����Ҷ�ӽڵ�ָ��
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
		insert_sort(target->index[mid],up->index,up->position++);//��up�в������ݲ�����
		if(up->position == 1)//������
		{
			up->point[0] = target;
			up->point[1] = right;
			root = up;
		}
		else
		{
			int i=0;
			node *temp=up->point[0];
			for(int m=0;m<=up->position;m++)
			{
				up->point[i] = temp;
				i++;
				temp = temp->right;
			}

		}//�������빦�ܣ��������ָ���ӽ���ָ������
	}
	for(int m=0;m<level-mid-1;m++)//��target��벿��ת��right
	{
		right->index[right->position++] = target->index[mid+m];
		target->index[mid+m] = 0;//��ԭΪĬ��ֵ0
	}
	right->index[right->position++] = last_data;
	target->position = level/2;//ά��position
}
void b_plus_tree::insert(int data)
{
	if(!root)
	{
		root = new node(level);
		int position = root->position;
		root->index[position] = data;
		root->position++;
		return;
	}
	node **target_father = find_position(data,root,NULL);
	node *target = target_father[0];
	node *father = target_father[1];
	int exist = is_exist(data,target->index,target->position);
	if(exist != -1)
	{
		//����ֵ��ͬ����Ҫ�����ڴ˴����м���
		return;
	}
	if(target -> position != level-1)//δ��,ֱ�Ӳ��뼴��
	{
		insert_sort(data,target->index,target->position);
		target->position++;
		return;
	}
	else//��������Ҫ����
	{
		split_node(target,father,data);
	}
}
void b_plus_tree::insert_sort(int data,int *&index,int number)
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
int b_plus_tree::is_exist(int data,int *&index,int number)
{
	for(int m=0;m<number;m++)
	{
		if(index[m] == data)
			return m;
	}
	return -1;
}
void b_plus_tree::run_down()
{
	if(!root)
		return;
	node *temp = root;
	for(;temp->point[0];temp=temp->point[0]);//Ѱ��Ҷ���ʼ��
	for(;temp;temp=temp->right)
	{
		for(int m=0;m<temp->position;m++)
		{
			cout<<temp->index[m]<<" ";
		}
	}
}
node *b_plus_tree::find_father(int data,node *target,node *father)
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
void b_plus_tree::split_up_node(node *target,int data)
{
	int last_data = data;//������Ǹ���
	node *father = find_father(target->index[0],root,NULL);
	node *up=father,*right;
	if(target->index[target->position-1] > data)//�������򣬽����ֵ�����last_data
	{
		last_data = target->index[target->position-1];
		insert_sort(data,target->index,level-2);
	}
	right = new node(level);
	right->right = target->right;
	target->right = right;
	if(!up)
		up = new node(level);//˵��Ϊ��������

	int mid = level/2;
	if(up->position == level-1)
	{
		split_up_node(up,target->index[mid]);
		node *up_right = up->right;
		int i = 0;
		node *temp = up->point[0];
		for(int m=0;m<=level/2;m++)//����Ҷ�ӽڵ�ָ��
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
	insert_sort(target->index[mid],up->index,up->position++);//��up�в������ݲ�����
	if(up->position == 1)//������
	{
		up->point[0] = target;
		up->point[1] = right;
		root = up;
	}
	else
	{
		int i=0;
		node *temp=up->point[0];
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
void b_plus_tree::overTree()
{
	node *temp;
	queue<node*> store_node;
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
void b_plus_tree::delete_data(int data)
{
	node **target_father = find_position(data,root,NULL);
	node *target = target_father[0];
	node *father = target_father[1];
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
	node *pre = get_pre_node(target,father);
	node *brother = pre;
	if(pre && pre->position>limit || !pre && target->right->position>limit)
	{//�ֵܽڵ���Ŀ�㹻
		if(!pre)
		{
			//��ǰ�ýڵ�
			brother = target->right;//����һ�ڵ�ΪĿ��
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
		//�ϲ��ֵܽڵ�
		delete_index(target->index,m,target->position);
		if(!pre)
		{
			together_index(target->index,target->right->index,target->position,target->right->position);
			node *temp = target->right;
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
void b_plus_tree::delete_index(int*& index,int position,int &number)
{
	int m;
	for(m=position;m<number-1;m++)
	{
		index[m] = index[m+1];
	}
	index[m] = 0;
	number--;
}
node* b_plus_tree::get_pre_node(node*target,node *father)
{
	node *temp = father->point[0];
	node *pre = NULL;
	for(;temp;temp=temp->right)
	{
		if(temp == target)
			return pre;
		pre = temp;
	}
}
void b_plus_tree::sort_index(int *&index,int number,int position)
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
void b_plus_tree::together_index(int*& pre,int *&bac,int &number_pre,int &number_bac)
{
	for(int m=0;m<number_bac;m++)
	{
		pre[number_pre+m] = bac[m];
	}
	number_pre += number_bac;
	number_bac = 0;
}
void b_plus_tree::delete_father_node(node *&target,int position)
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
		//Ԫ�����㹻��ɾ��Ԫ�غ���Ҫ�ϲ�
		delete_index(target->index,position,target->position);//ɾ��Ԫ��
		move_point(target,position);
	}
	else
	{
		node *father = find_father(target->index[0],root,NULL);
		node *pre = get_pre_node(target,father);
		node *right = target->right;
		if(pre)
		{
			int father_position = find_father_position(pre,target,father);
			//����pre�ڵ�
			if(pre->position>level/2)
			{
				//pre�ڵ㸻ԣ,ת���ֵܽڵ�
				target->index[position] = father->index[father_position];
				sort_index(target->index,target->position,position);
				father->index[father_position] = pre->index[pre->position-1];
				pre->index[pre->position-1] = 0;
				pre->position--;
				/*node *temp = pre->point[pre->position+1];//����target��ָ��
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
				//pre�ڵ㲻��ԣ����Ҫ�ϲ�
				delete_index(target->index,position,target->position);
				int father_index = father->index[father_position];
				delete_father_node(father,father_position);
				pre->right = target->right;
				//move_point(father,father_position);//�ƶ�father��ָ��
				move_point(target,position);
				for(int m=0;m<=target->position;m++)//�ƶ�preָ��
				{
					pre->point[pre->position+1+m] = target->point[m];
				}
				pre->index[pre->position++] = father_index;
				for(int m=0;m<target->position;m++)//��target��ֵ���Ƶ�pre��
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
			//������pre�ڵ㣬��Ҫ��right�ڵ����
			int father_position = find_father_position(target,right,father);
			if(right->position>level/2)
			{
				//right�ڵ㸻ԣ,ת���ֵܽڵ�
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
				move_point(right,-1);//rightָ��ǰ��
			}
			else
			{
				//right�ڵ㲻��ԣ����Ҫ�ϲ�
				delete_index(target->index,position,target->position);
				int father_index = father->index[father_position];
				delete_father_node(father,father_position);
				target->right = right->right;
				//move_point(father,father_position);//�ƶ�father��ָ��
				move_point(target,position);
				for(int m=0;m<=right->position;m++)//�ƶ�target��ָ��
				{
					target->point[target->position+1+m] = right->point[m];
				}
				target->index[target->position++] = father_index;
				for(int m=0;m<right->position;m++)//��target��ֵ���Ƶ�pre��
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
int b_plus_tree::find_father_position(node *pre,node *target,node *father)
{
	int position;
	for(position=0;position<father->position;position++)
	{
		if(father->point[position]==pre && father->point[position+1]==target)
			break;
	}
	return position;
}	
void b_plus_tree::move_point(node *target,int position)
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
void b_plus_tree::insert_flight_info(flight_information_node*info)
{
	string index = info->departure+"/"+info->destination;
	int data = info_map[index];
	insert(data);
	node **target_father = find_position(data,root,NULL);
	node *target = target_father[0];
	int m;
	for(m=0;m<target->position;m++)
	{
		if(target->index[m] == data)
			break;
	}
	target->info_list[m].push_back(info);
}
list<flight_information_node*>& b_plus_tree:: find_info_list(int data)
{
	node *target = find_position(data,root,NULL)[0];
	int m;
	for(m=0;m<target->position;m++)
	{
		if(target->index[m] == data)
			break;
	}
	return target->info_list[m];
}