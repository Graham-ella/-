#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

typedef char datatype;

//二叉树的左右链表示，也叫做二叉链表表示
typedef struct node {
	datatype data;
	struct node* lchild;
	struct node* rchild;
}Node;

typedef Node* Btree;

//创建新的结构体list，包含Btree和int，来帮助实现后序非递归算法
typedef struct list {
	Btree ptr;
	int flag;
}List;



Btree preCreateBT() {
	Btree T;
	char ch;
	cin >> ch;
	if (ch == '#') {
		T = NULL;
	}
	else {
		T = new node;
		T->data = ch;
		T->lchild = preCreateBT();
		T->rchild = preCreateBT();
	}
	return T;
}

//先序遍历
void PreOrder(Btree BT) {
	
	if (BT != NULL) {
		cout << BT->data;
		PreOrder(BT->lchild);
		PreOrder(BT->rchild);
	}
}

//中序遍历
void InOrder(Btree BT) {
	
	if (BT != NULL) {
		InOrder(BT->lchild);
		cout << BT->data;
		InOrder(BT->rchild);
	}
}

//后序遍历
void PostOrder(Btree BT) {
	if (BT != NULL) {
		PostOrder(BT->lchild);
		PostOrder(BT->rchild);
		cout << BT->data;
	}
}

//求树的高度，递归算法
int Height(Btree T) {
	if (T == NULL) {
		return 0;
	}
	else {
		int m = Height(T->lchild);
		int n = Height(T->rchild);
		return (m > n) ? (m + 1) : (n + 1);
	}
}


//按先序次序打印二叉树中的叶子结点的算法
void preOrderPrint(Btree T) {
	if (T) {
		if (!T->lchild && !T->rchild) {
			cout << T->data;//T没有所有孩子，即T为结点时，打印出来
		}
		preOrderPrint(T->lchild);//先序的顺序
		preOrderPrint(T->rchild);
	}
}

//先序遍历非递归算法
void PreOrderNoRecur(Btree root) {
	stack<Btree> S;
	while (root != NULL || !S.empty()) {
		while (root != NULL) {
			cout << root->data;
			S.push(root);
			root = root->lchild;
		}

		if (!S.empty()) {
			root = S.top();
			S.pop();
			root = root->rchild;
		}
	}
}

//中序遍历非递归算法
void InOrderNoRecur(Btree root) {
	stack<Btree> S;
	while (root != NULL || !S.empty()) {
		while (root != NULL) {
			S.push(root);
			root = root->lchild;
		}

		if (!S.empty()) {
			root = S.top();
			cout << root->data;
			S.pop();
			root = root->rchild;
		}
	}
}

//后序遍历非递归算法
void PostOrderNoRecur(Btree root) {
	stack<List> newS;
	while (root != NULL || !newS.empty()) {
		while (root != NULL) {
			List element;
			element.ptr = root;
			element.flag = 1;
			newS.push(element);
			root = root->lchild;
		}
		while (!newS.empty() && newS.top().flag == 2) {
			cout << newS.top().ptr->data;
			newS.pop();
		}
		if (!newS.empty()) {
			newS.top().flag = 2;
			root = newS.top().ptr->rchild;
		}
	}
}

//二叉树的层序遍历算法
void LevelOrder(Btree root) {
	queue<Btree> Q;
	Btree q;
	if (root == NULL) {
		return;
	}
	Q.push(root);
	while (!Q.empty()) {
		q = Q.front();
		cout << q->data;
		Q.pop();
		if (q->lchild != NULL) {
			Q.push(q->lchild);
		}
		if (q->rchild != NULL) {
			Q.push(q->rchild);
		}
	}
}

//判断二叉树是否为完全二叉树（层序遍历）
/*判断是否是完全二叉树思路：
  按照层序遍历进行读取
  如果树为空，直接返回false
  如果不为空，将树的根入队开始遍历
  读取队列的头元素
  如果读到叶子结点，设标志位为1
  如果读到有右节点，没有左节点，必然不可能是完全二叉树
  如果有左节点没有右节点，那么之前不可能读到过叶子结点，否则不完全，没读到就将左孩子入队
  如果左右节点都不空，先前应该没有遇到过叶子节，将两个孩子入队
*/
bool ifCompleteTree(Btree T) {
	queue<Btree> Q;
	Btree q;
	int flag = 0;//标记变量，如果flag=0，证明之前没有遇到过叶子节点，flag=1，之前已经遇到过叶子节点
	int flagtwo = 0;//遇到先只有左孩子的情况
	if (T == NULL) {
		return false;
	}
	Q.push(T);
	
	while (!Q.empty()) {
		//层序遍历
		q = Q.front();
		Q.pop();

		if (q->lchild == NULL && q->rchild == NULL) {//左右节点都没有
			flag = 1;//如果碰到了叶子节点,flag = 1
		}
		else if (q->lchild == NULL && q->rchild != NULL) {//有右节点，没有左节点
			return false;//如果有右节点，没有左节点，必然不是
		}
		else if(q->lchild != NULL && q->rchild == NULL){//有左节点，没有右节点
			if (flag == 1||flagtwo==1) {//先前遇到过叶子节点
				return false;
			}
			else {
				Q.push(q->lchild);
				flagtwo = 1;
			}
		}
		else if (q->lchild != NULL && q->rchild != NULL) {//左右节点都不空

			if (flag == 1||flagtwo==1) {//遇到过叶子节点
				return false;
			}
			else {//没有遇到过
				Q.push(q->lchild);
				Q.push(q->rchild);
			}

		}
		

	}

	return true;
 }






//求二叉树中任意两个结点的公共祖先

//（一）findNodeByData 前序遍历，根据元素在树中找到对应的结点
//（二）
Btree findNodeByData(Btree root, datatype target) {
	//利用先序遍历非递归算法
	stack<Btree> S;
	while (root != NULL || !S.empty()) {
		while (root != NULL) {
			if (root->data == target) {
				return root;
			}
			S.push(root);
			root = root->lchild;
		}

		if (!S.empty()) {
			root = S.top();
			S.pop();
			root = root->rchild;
		}
	}
	return NULL;
}

//利用递归寻找路径
bool findPath(Btree T, Btree target,vector<datatype>&v) {//T为根节点，target为目标结点，v用来存储路径
	if (T == NULL) {
		return false;
	}//如果根节点为空，直接返回false
	v.push_back(T->data);//根节点不空，将根节点存入v中
	bool found = false;//标记变量

	if (T == target) {
		return true;
	}//如果找到了目标结点，打印出来
	
	if (!found && T->lchild) {//若此时的T不是目标节点，且T有左孩子
		found = findPath(T->lchild, target, v);//递归，用T的左孩子找
	}
	if (!found && T->rchild) {//左孩子没找到，T还有右孩子
		found = findPath(T->rchild, target, v);//用右孩子找一遍
	}

	if (!found) {//T和T的左右孩子都找不到目标结点，说明目标结点不在T这边，将T从v中删除
		v.pop_back();
	}

	return found;
}

void findComAncestor(vector<datatype> v1, vector<datatype> v2) {
	string s1 = "";
	string s2 = "";
	string rs = "";
	int flag = 0;//判断有无公共祖先
	for (unsigned int i = 0; i < v1.size(); i++) {
		s1 = s1 + v1[i];
	}
	for (unsigned int i = 0; i < v2.size(); i++) {
		s2 = s2 + v2[i];
	}
	string::size_type idxone=s1.find(s2);
	string::size_type idxtwo=s2.find(s1);

	if (idxone != string::npos) {//s1中包含了s2
		flag = 1;
		rs = s2;
	}
	else if (idxtwo != string::npos) {//s2中包含了s1
		flag = 1;
		rs = s1;
	}
	else {//两个字符串互相不包含
		for (int i = 0; i < s1.size(); i++) {
			for (int j = 0; j < s2.size(); j++) {
				if (s1[i] == s2[j]) {
					flag = 1;
					rs = rs + s1[i];
				}
			}
		}
	}
	if (flag == 1) {
		cout << "公共祖先为：" << rs << endl;
	}
	else {
		cout << "无公共祖先"<< endl;
	}
	
	
}












//寻找两结点最近的公共祖先
Btree nearComAncestor(Btree root, Btree p, Btree q) {
	if (root == q || root == p || root == NULL) {
		return root;
	}
	Btree left = nearComAncestor(root->lchild, p, q);
	Btree right = nearComAncestor(root->rchild, p, q);

	if (left != NULL && right != NULL) {
		return root;
	}
	else if (left == NULL) {
		return right;
	}
	else if (right == NULL) {
		return left;
	}
}
