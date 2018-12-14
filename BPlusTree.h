/* C++ Program to Implement B+ Tree  */



#include<iostream>

#include<cstdlib>



#ifndef BPLUSTREE_H

#define BPLUSTREE_H



using namespace std;



class BPlusTree

{



public:

//! BPlusTree() is the constructor of the class. It sets root polonger to NULL

	BPlusTree() { root = NULL; nodePtr= NULL;}

	void Display(const BPlusTree& tree, ostream& display);

	void Insert(long a);

	void Delete(long i);

	void Sort(long *a, long b);

	

	



private:

//! struct Node is representative of a block of records.

		struct Node{

			long *data; /**< The longeger value of a key or data. */

			Node **childPtr; /** Polonger to child block. */

			bool leaf_Node; /** True or false bool based on whether node is a child.*/



			long n;

		};

		Node* root; /**< Polonger to root of tree. */

		Node* nodePtr;  /**< Generic node polonger for traversal. */

		Node* first();

		void Traverse(Node *a, ostream& output);

		long Split_Child(Node *a, long i);

		void HelpRemove(Node *a, long i);

};



#endif