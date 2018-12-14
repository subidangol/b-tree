#include<iostream>
#include<cstdlib>

using namespace std;

class BPlusTree
{
	public:
		//! BPlusTree() is the constructor of the class. It sets root pointer to NULL
		BPlusTree() { root = NULL; nodePtr = NULL; }
		void Display(const BPlusTree& tree, ostream& display);
		void Insert(long a);
		void Delete(long i);
		void Sort(long *a, long b);

	private:
		//! struct Node is representative of a block of records.
		struct Node 
		{
			long *data; /**< The long value of a key or data. */
			Node **childPtr; /** Pointer to child block. */
			bool leaf_Node; /** If a node is a child.*/
			long n;
		};

		Node* root; /**< Pointer to root of tree. */
		Node* nodePtr;  /**< Generic node pointer for traversal. */
		Node* first();
		void Traverse(Node *a, ostream& output);
		long Split_Child(Node *a, long i);
		void HelpRemove(Node *a, long i);
};
