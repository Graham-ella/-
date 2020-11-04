#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

typedef char datatype;

//����������������ʾ��Ҳ�������������ʾ
typedef struct node {
	datatype data;
	struct node* lchild;
	struct node* rchild;
}Node;

typedef Node* Btree;

//�����µĽṹ��list������Btree��int��������ʵ�ֺ���ǵݹ��㷨
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

//�������
void PreOrder(Btree BT) {
	
	if (BT != NULL) {
		cout << BT->data;
		PreOrder(BT->lchild);
		PreOrder(BT->rchild);
	}
}

//�������
void InOrder(Btree BT) {
	
	if (BT != NULL) {
		InOrder(BT->lchild);
		cout << BT->data;
		InOrder(BT->rchild);
	}
}

//�������
void PostOrder(Btree BT) {
	if (BT != NULL) {
		PostOrder(BT->lchild);
		PostOrder(BT->rchild);
		cout << BT->data;
	}
}

//�����ĸ߶ȣ��ݹ��㷨
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


//����������ӡ�������е�Ҷ�ӽ����㷨
void preOrderPrint(Btree T) {
	if (T) {
		if (!T->lchild && !T->rchild) {
			cout << T->data;//Tû�����к��ӣ���TΪ���ʱ����ӡ����
		}
		preOrderPrint(T->lchild);//�����˳��
		preOrderPrint(T->rchild);
	}
}

//��������ǵݹ��㷨
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

//��������ǵݹ��㷨
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

//��������ǵݹ��㷨
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

//�������Ĳ�������㷨
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

//�ж϶������Ƿ�Ϊ��ȫ�����������������
/*�ж��Ƿ�����ȫ������˼·��
  ���ղ���������ж�ȡ
  �����Ϊ�գ�ֱ�ӷ���false
  �����Ϊ�գ������ĸ���ӿ�ʼ����
  ��ȡ���е�ͷԪ��
  �������Ҷ�ӽ�㣬���־λΪ1
  ����������ҽڵ㣬û����ڵ㣬��Ȼ����������ȫ������
  �������ڵ�û���ҽڵ㣬��ô֮ǰ�����ܶ�����Ҷ�ӽ�㣬������ȫ��û�����ͽ��������
  ������ҽڵ㶼���գ���ǰӦ��û��������Ҷ�ӽڣ��������������
*/
bool ifCompleteTree(Btree T) {
	queue<Btree> Q;
	Btree q;
	int flag = 0;//��Ǳ��������flag=0��֤��֮ǰû��������Ҷ�ӽڵ㣬flag=1��֮ǰ�Ѿ�������Ҷ�ӽڵ�
	int flagtwo = 0;//������ֻ�����ӵ����
	if (T == NULL) {
		return false;
	}
	Q.push(T);
	
	while (!Q.empty()) {
		//�������
		q = Q.front();
		Q.pop();

		if (q->lchild == NULL && q->rchild == NULL) {//���ҽڵ㶼û��
			flag = 1;//���������Ҷ�ӽڵ�,flag = 1
		}
		else if (q->lchild == NULL && q->rchild != NULL) {//���ҽڵ㣬û����ڵ�
			return false;//������ҽڵ㣬û����ڵ㣬��Ȼ����
		}
		else if(q->lchild != NULL && q->rchild == NULL){//����ڵ㣬û���ҽڵ�
			if (flag == 1||flagtwo==1) {//��ǰ������Ҷ�ӽڵ�
				return false;
			}
			else {
				Q.push(q->lchild);
				flagtwo = 1;
			}
		}
		else if (q->lchild != NULL && q->rchild != NULL) {//���ҽڵ㶼����

			if (flag == 1||flagtwo==1) {//������Ҷ�ӽڵ�
				return false;
			}
			else {//û��������
				Q.push(q->lchild);
				Q.push(q->rchild);
			}

		}
		

	}

	return true;
 }






//��������������������Ĺ�������

//��һ��findNodeByData ǰ�����������Ԫ���������ҵ���Ӧ�Ľ��
//������
Btree findNodeByData(Btree root, datatype target) {
	//������������ǵݹ��㷨
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

//���õݹ�Ѱ��·��
bool findPath(Btree T, Btree target,vector<datatype>&v) {//TΪ���ڵ㣬targetΪĿ���㣬v�����洢·��
	if (T == NULL) {
		return false;
	}//������ڵ�Ϊ�գ�ֱ�ӷ���false
	v.push_back(T->data);//���ڵ㲻�գ������ڵ����v��
	bool found = false;//��Ǳ���

	if (T == target) {
		return true;
	}//����ҵ���Ŀ���㣬��ӡ����
	
	if (!found && T->lchild) {//����ʱ��T����Ŀ��ڵ㣬��T������
		found = findPath(T->lchild, target, v);//�ݹ飬��T��������
	}
	if (!found && T->rchild) {//����û�ҵ���T�����Һ���
		found = findPath(T->rchild, target, v);//���Һ�����һ��
	}

	if (!found) {//T��T�����Һ��Ӷ��Ҳ���Ŀ���㣬˵��Ŀ���㲻��T��ߣ���T��v��ɾ��
		v.pop_back();
	}

	return found;
}

void findComAncestor(vector<datatype> v1, vector<datatype> v2) {
	string s1 = "";
	string s2 = "";
	string rs = "";
	int flag = 0;//�ж����޹�������
	for (unsigned int i = 0; i < v1.size(); i++) {
		s1 = s1 + v1[i];
	}
	for (unsigned int i = 0; i < v2.size(); i++) {
		s2 = s2 + v2[i];
	}
	string::size_type idxone=s1.find(s2);
	string::size_type idxtwo=s2.find(s1);

	if (idxone != string::npos) {//s1�а�����s2
		flag = 1;
		rs = s2;
	}
	else if (idxtwo != string::npos) {//s2�а�����s1
		flag = 1;
		rs = s1;
	}
	else {//�����ַ������಻����
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
		cout << "��������Ϊ��" << rs << endl;
	}
	else {
		cout << "�޹�������"<< endl;
	}
	
	
}












//Ѱ�����������Ĺ�������
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
