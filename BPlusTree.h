/* C++ Program to Implement B+ Tree  */

#include<iostream>
#include<cstdlib>

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

using namespace std;

class BPlusTree
{

public:
//! BPlusTree() is the constructor of the class. It sets root pointer to NULL
	BPlusTree() { root = NULL; nodePtr= NULL;}
	void Display(const BPlusTree& tree, ostream& display);
	void Insert(int a);
	void Delete(int i);
	void Sort(int *a, int b);
	
	

private:
//! struct Node is representative of a block of records.
		struct Node{
			int *data; /**< The integer value of a key or data. */
			Node **childPtr; /** Pointer to child block. */
			bool leaf_Node; /** True or false bool based on whether node is a child.*/

			int n;
		};
		Node* root; /**< Pointer to root of tree. */
		Node* nodePtr;  /**< Generic node pointer for traversal. */
		Node* first();
		void Traverse(Node *a, ostream& output);
		int Split_Child(Node *a, int i);
		void HelpRemove(Node *a, int i);
};

#endif
