#include <iostream>
#include <cstdlib>
#include "BPlusTree.h"

using namespace std;

//! first() is the function that initializes an empty tree
/*!
* A void function that creates a block of size 5 and child pointers for
* each “side” of each cell in the block. All cells NULL.
* returns root Node.
* This function not to be confused with the constructor.
*/
BPlusTree::Node* BPlusTree::first()
{
	long i;
	nodePtr = new Node;
	nodePtr->data = new long[15];
	nodePtr->childPtr = new Node*[6];
	nodePtr->leaf_Node = true;
	nodePtr->n = 0;
	for (i = 0; i < 6; i++)
	{
		nodePtr->childPtr[i] = NULL;
	}
	return nodePtr;
}
//! display is used to output the contents of the tree to a given stream
/*!
	\param const BPlusTree &tree is the B plus tree passed to function.
	\param ostream& display is the C++ stream to which we write.
*/
void BPlusTree::Display(const BPlusTree& tree, ostream& display)
{
	help_display(tree.root, display);
}

//! help_display is a function that visits all nodes and writes their contents out
/*!
	\param Node *a is the “root” or where to begin traversing the tree.
	\param ostream& output is the stream to which we write the data.
*/

void BPlusTree::help_display(Node *a, ostream& output)
{
	for (long i = 0; i < a->n; i++)
	{
		if (a->leaf_Node == false)
		{
			help_display(a->childPtr[i], output);
		}
		output << " " << a->data[i];
	}
	if (a->leaf_Node == false)
		help_display(a->childPtr[i], output);
}

//! Sort is used by insert() to re-sort list after insertion
/*!
	\param long *a is a swap value.
	\param long b is a limit value.
*/
void BPlusTree::Sort(long *a, long b)
{
	long i, j, temp;
	for (i = 0; i < b; i++)
	{
		for (j = i; j <= b; j++)
		{
			if (a[i] > a[j])
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

//! split_child functions to split a block when it contains too many elements
/*!
	\param Node *x is a pointer to a block to be split.
	\param long i
*/
long BPlusTree::Split_Child(Node *a, long i)
{
	long j, mid_Node;
	Node *nodePtr1, *nodePtr3, *x;
	nodePtr3 = first();
	nodePtr3->leaf_Node = true;
	if (i == -1)
	{
		mid_Node = a->data[2];
		a->data[2] = 0;
		a->n--;
		nodePtr1 = first();
		nodePtr1->leaf_Node = false;
		a->leaf_Node = true;
		for (j = 3; j < 5; j++)
		{
			nodePtr3->data[j - 3] = a->data[j];
			nodePtr3->childPtr[j - 3] = a->childPtr[j];
			nodePtr3->n++;
			a->data[j] = 0;
			a->n--;
		}
		for(j = 0; j < 6; j++)
		{
			a->childPtr[j] = NULL;
		}
		nodePtr1->data[0] = mid_Node;
		nodePtr1->childPtr[nodePtr1->n] = a;
		nodePtr1->childPtr[nodePtr1->n + 1] = nodePtr3;
		nodePtr1->n++;
		root = nodePtr1;
	}
	else
	{
		x = a->childPtr[i];
		mid_Node = x->data[2];
		x->data[2] = 0;
		x->n--;
		for (j = 3; j < 5; j++)
		{
			nodePtr3->data[j - 3] = x->data[j];
			nodePtr3->n++;
			x->data[j] = 0;
			x->n--;
		}
		a->childPtr[i + 1] = x;
		a->childPtr[i + 1] = nodePtr3;
	}
	return mid_Node;
}

/! Insert creates a space for a new piece of data in the tree.
/*!
	\param long a is the data to be inserted longo the tree.
*/
void BPlusTree::Insert(long a)
{
	long i, temp;
	Node* x = root;
	if (x == NULL)
	{
		root = first();
		x = root;
	}
	else
	{
		if (x->leaf_Node == true && x->n == 5)
		{
			temp = Split_Child(x, -1);
			x = root;
			for (i = 0; i < (x->n); i++)
			{
				if ((a > x->data[i]) && (a < x->data[i + 1]))
				{
					i++;
					break;
				}
				else if (a < x->data[0])
				{
					break;
				}
				else
				{
					continue;
				}
			}
			x = x->childPtr[i];
		}
		else
		{
			while (x->leaf_Node == false)
			{
				for (i = 0; i < (x->n); i++)
				{
					if ((a > x->data[i]) && (a < x->data[i + 1]))
					{
						i++;
						break;
					}
					else if (a < x->data[0])
					{
						break;
					}
					else
					{
						continue;
					}
				}
				if ((x->childPtr[i])->n == 5)
				{
					temp = Split_Child(x, i);
					x->data[x->n] = temp;
					x->n++;
				}
				else
				{
					x = x->childPtr[i];
				}
			}//end while
		}//end else
	}
	x->data[x->n] = a;
	Sort(x->data, x->n);
	x->n++;
}

//! help_remove is a function that performs the "dirty work" of removing an entry
/*!
	\param Node *a is a node pointer for traversal
	\param long i is the data to be removed
*/
void BPlusTree::help_remove(Node *a, long i)
{
	//if node data = data in param
	Node * temp = root;

	for (long j = 0; j < a->n; j++)
	{
		if (a->leaf_Node == false)
			help_remove(a->childPtr[j], i);

		if (a->data[j] == i) //delete
			a->data[j] = NULL;
	}
}

//! Delete calls help_remove to remove passed value
void BPlusTree::Delete(long i)
{
	help_remove(root, i);
}
