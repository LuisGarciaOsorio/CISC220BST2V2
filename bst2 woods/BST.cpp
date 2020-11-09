/*
 * BST.cpp
 *
 *  Created on: Oct 21, 2020
 *      Author: LuisGarciaOsorio
 */


#include <iostream>
#include <string>
#include "BST.hpp"

BST::BST() {
	root = NULL;
}
BST::BST(string sarr[]) {
	root = new TNode(sarr);
}
void BST::clearTree() {
if (root == NULL) {
	cout << "Tree already empty" << endl;
	}
else {
	cout << endl << "Clearing Tree:" << endl;
	clearTree(root);
	root = NULL;
	}
}
void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
else { clearTree(tmp->left);
	clearTree(tmp->right);
	tmp->printNode();
	delete(tmp);
	}
}
/*Note: the following three functionsÃ­ sole job is to call printTreeIO(TNode *t),printTreePre(TNode *t), and printTreePost(TNode *t) while printint out which
Function is being called.
YOU MUST STILL WRITE THE RECURSIVE VERSION OF THESE FUNCTIONS!!!*/
void BST::printTreeIO() { // Just the start Ã± you must write the recursive version
	//TNode *tmp = root;
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}
void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}
void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}
bool BST::insert(string sarr[]){
	TNode *tracker = root;
	if(root==NULL){
		root = new TNode(sarr);
		return true;
	}
	return insert(sarr,tracker);
}

bool BST::insert(string sarr[],TNode *tracker){  //updated
	//iterate recursively.
	if (tracker->student->last == sarr[0]) {
		return true;
	}
	else{
		if(sarr[0]<tracker->student->last){
			if(tracker->left!=NULL){
				insert(sarr,tracker->left);
			}
			else{
				tracker->left = new TNode(sarr);
				tracker->left->parent = tracker;

			}

		}
		else{
			if(tracker->right!=NULL){
				insert(sarr,tracker->right);
			}
			else{
				tracker->right = new TNode(sarr);
				tracker->right->parent = tracker;
			}
		}
	}
	setHeight(tracker);
	return false;
}
TNode *BST::find(string l, string f,TNode *tracker){ //updated
	if (tracker->student->last == l && tracker->student->first == f){
		return tracker;
	}
	else{
		if (tracker->right == NULL && tracker->left ==NULL){
			return NULL;
		}
		else if(tracker->right==NULL&&tracker->left!=NULL){
			return find(l,f,tracker->left);
		}
		else if(tracker->left==NULL&&tracker->right!=NULL){
			return find(l,f, tracker->right);
		}
		else{
			if(l<tracker->student->last){
				return find(l,f,tracker->left);

			}
			else{
				return find(l,f, tracker->right);
			}
		}
	}
}
TNode *BST::find(string l, string f){
	TNode *tracker = root;
	return find(l,f, tracker);
}
void BST::printTreeIO(TNode *n){ //add stopping condition
	if(n!=NULL){
	printTreeIO(n->left);
	cout<<n->student->last<<","<<n->height<<endl;
	printTreeIO(n->right);
	}
	else{
	return;
	}
}

void BST::printTreePre(TNode *n){
	if(n!=NULL){
	cout<<n->student->last<<endl;
	printTreePre(n->left);
	printTreePre(n->right);
	}
	else{
	return;
	}
}

void BST::printTreePost(TNode *n){
	if(n!=NULL){
	printTreePost(n->left);
	printTreePost(n->right);
	cout<<n->student->last<<endl;
	}
	else{
	return;
	}
}


 //how to structure function
TNode *BST::remove(string f, string l){
	TNode *tmp = root;
	tmp = find(l,f, tmp);
	TNode *tmp2 = tmp->left;
		if(tmp->left == NULL && tmp->right==NULL){ //no kids
			return removeNoKids(tmp);
		}
		else if(tmp->left!=NULL && tmp->right==NULL){
			bool leftFlag = true;
			return removeOneKid(tmp, leftFlag);
		}
		else if(tmp->left == NULL && tmp->right!=NULL){
			bool leftFlag = false;
			return removeOneKid(tmp, leftFlag);
		}
		else {
			cout<<"Test else"<<endl;
			while(tmp2->right!=NULL){
				cout<<"Test while loop"<<endl;
				tmp2 = tmp2->right;
			}
			 //once we get to the farthest right node
			tmp->student = tmp2->student;
				if (tmp2->left == NULL){
					removeNoKids(tmp2);
				}

				else {
					removeOneKid(tmp2, true);
				}
		}
		return tmp;
	}

TNode *BST::removeNoKids(TNode *tmp){
	if(tmp->parent->left == tmp){
		tmp->parent->left = NULL;
	}
	else if(tmp->parent->right == tmp){
		tmp->parent->right = NULL;

	}
	setHeight(tmp->parent);
	return tmp;
}
TNode *BST::removeOneKid(TNode *tmp, bool leftFlag){
	if(leftFlag){
		tmp->left->parent = tmp->parent;
		tmp->parent->left = tmp->left;
		setHeight(tmp->left);
		return tmp;
	}
	else{
		tmp->right->parent = tmp->parent;
		if(tmp->parent->left == tmp){
			tmp->parent->left = tmp->right;
		}
		else{
		tmp->parent->right = tmp->right;
		}
		setHeight(tmp->right);
		return tmp;
	}
}
void BST::setHeight(TNode *n){

	int left_height = n->left != NULL ? n->left->height : 0;
	int right_height = n->right != NULL ? n->right->height : 0;
	int bal = getBalance(n);
	//cout<<bal<<endl; //balance works
	//if (balance > 1){
		//rotateRight(n);
		//}
//	if (bal < -1 ){
//		rotateLeft(n);
//		}
	n->height = left_height > right_height ? left_height+1 : right_height+1;
	if (n->parent){
		setHeight(n->parent);
	}


}

int BST::getBalance(TNode *n){
	int balance;
	int left_height = n->left != NULL ? n->left->height : 0;
	int right_height = n->right != NULL ? n->right->height : 0;
	balance = left_height - right_height;
	return balance;

}


TNode *BST::rotateLeft(TNode *tmp){
	TNode *tmp2 = new TNode();
	if(getBalance(tmp) < -1){
		tmp2= tmp->right;

		tmp->right = tmp2->left;
		tmp2->left->parent = tmp;

		if(tmp->parent->right == tmp){
			tmp->parent->right = tmp2;
			tmp2->parent = tmp->parent; // if there is a parent
		}
		else if (tmp->parent->left == tmp){
			tmp->parent->left = tmp2;
			tmp2->parent = tmp->parent; // if there is a parent
		}
		else {
			root = tmp2;
		}

		tmp->parent = tmp2;
		tmp2->left = tmp;


	}
	return tmp;
}
TNode *BST::rotateRight(TNode *tmp){
	TNode *tmp2 = new TNode();
	if(getBalance(tmp) > 1){
		tmp2= tmp->left;

		tmp->left = tmp2->right;
		tmp2->right->parent = tmp;

		if(tmp->parent->right == tmp){
			tmp->parent->right = tmp2;
			tmp2->parent = tmp->parent; // if there is a parent
		}
		else if (tmp->parent->left == tmp){
			tmp->parent->left = tmp2;
			tmp2->parent = tmp->parent; // if there is a parent
		}
		else {
			root = tmp2;
		}

		tmp->parent = tmp2;
		tmp2->right = tmp;


	}
	return tmp;
}




























