#include "stdafx.h"
#include "FUNCTIONS.h"


void InitialNode (treeNode* &a)//初始化树结点
{
	a->parent=NULL; a->nwchild=NULL; a->nechild=NULL;a->confirm='0';
}


void InsertNode (treeNode* &root)//插入孩子结点
{
	root->nwchild=new treeNode ; InitialNode (root->nwchild) ; root->nwchild->parent=root;
	root->nechild=new treeNode ; InitialNode (root->nechild) ; root->nechild->parent=root;
}

void LevelOrder(vector<char> &Q , treeNode* root)//层次遍历
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