#include "stdafx.h"
#include "FUNCTIONS.h"


void InitialNode (treeNode* &a)//��ʼ�������
{
	a->parent=NULL; a->nwchild=NULL; a->nechild=NULL;a->confirm='0';
}


void InsertNode (treeNode* &root)//���뺢�ӽ��
{
	root->nwchild=new treeNode ; InitialNode (root->nwchild) ; root->nwchild->parent=root;
	root->nechild=new treeNode ; InitialNode (root->nechild) ; root->nechild->parent=root;
}

void LevelOrder(vector<char> &Q , treeNode* root)//��α���
{
	Q.push_back(root->confirm);
		if (root->nwchild!=NULL)
		{
			LevelOrder(Q , root->nwchild);
		}
		if (root->nechild!=NULL)
		{
			LevelOrder(Q , root->nechild);
		}
}