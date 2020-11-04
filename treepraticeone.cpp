#include <iostream>
#include "operation.h"
using namespace std;

int main() {
	//前序遍历创建树
	Btree TreeOne = preCreateBT();

	/*
	int rs = Height(TreeOne);
	cout<<"二叉树的高度为："<<rs << endl;

	cout << "该树的所有叶子结点为：";
	preOrderPrint(TreeOne);
	cout << endl;

	
	cout << "该树的前序遍历（递归）为：";
	PreOrder(TreeOne);
	cout << endl;
	cout << "该树的中序遍历（递归）为：";
	InOrder(TreeOne);
	cout << endl;
	cout << "该树的后序遍历（递归）为：";
	PostOrder(TreeOne);
	cout << endl;

	cout << "该树的前序遍历（非递归）为：";
	PreOrderNoRecur(TreeOne);
	cout << endl;

	cout << "该树的中序遍历（非递归）为：";
	InOrderNoRecur(TreeOne);
	cout << endl;

	cout << "该树的后序遍历（非递归）为：";
	PostOrderNoRecur(TreeOne);
	cout << endl;

	cout << "该树的层序遍历为：";
	LevelOrder(TreeOne);
	cout << endl;
	

	bool result = ifCompleteTree(TreeOne);
	cout << result;

	*/

	vector<datatype> v1;
	Btree tempone = findNodeByData(TreeOne, 'H');
	bool rsone = findPath(TreeOne, tempone, v1);
	cout << rsone << endl;

	vector<datatype> v2;
	Btree temptwo = findNodeByData(TreeOne, 'J');
	bool rstwo = findPath(TreeOne, temptwo, v2);
	cout << rstwo << endl;
	
	if (rsone && rstwo) {
		findComAncestor(v1, v2);

	}
	
}
