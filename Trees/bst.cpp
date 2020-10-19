#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct bstnode
{
	int data;
	bstnode* lchild;
	bstnode* rchild;
};


bstnode* new_bstnode(int key)
{
	bstnode* node = new bstnode;
	node->data = key;
	node->lchild = NULL;
	node->rchild = NULL;

	return node;
}


void inorder_visualization(bstnode* rootptr)
{
	if (rootptr == NULL)
		return;

	inorder_visualization(rootptr -> lchild);
	cout<< rootptr->data <<" ";
	inorder_visualization(rootptr -> rchild);
}

void bst_insertion(bstnode** rootptr, int key)
{
	if(*rootptr == NULL)	// empty tree
		*rootptr = new_bstnode(key);
	
	else if(key > (*rootptr)->data)
		bst_insertion(&((*rootptr)->rchild), key);

	else
		bst_insertion(&((*rootptr)->lchild), key);
}


bstnode* bst_search(bstnode* rootptr, int key, int height)
{
	if (rootptr == NULL)
	{
		cout<< "\n Key not found in the BST !";
		return NULL;
	}

	if (rootptr -> data == key)
	{
		// assuming starting height = 0
		cout<< "\nKey found at height "<<height;
		return rootptr; 
	}

	else if (key < rootptr -> data)
	{
		bstnode* result = NULL;
		result = bst_search(rootptr -> lchild, key, height + 1);
		return result;
	}
	else
	{
		bstnode* result = NULL;
		result = bst_search(rootptr -> rchild, key, height + 1);
		return result;
	}

}


bstnode* findMin(bstnode* rootptr)
{
	if(rootptr -> lchild == NULL)
		return rootptr;
	rootptr = findMin(rootptr -> lchild);
}

bstnode* bst_deletion(bstnode* rootptr, int key)
{
	// if we want to use the search() to find the key first and then delete it, it would not be a 
	// recursive process completely. In that case, we would have to remember the parent of the node
	// we are deleting (write code for this in search()). Hence, here a complete recursive process
	// is being shown

	if (rootptr == NULL)
	{
		cout<< "\n Key not found in the BST !";
		return rootptr;
	}

	else if (key < rootptr -> data)
		rootptr -> lchild = bst_deletion(rootptr -> lchild, key);

	else if (key > rootptr -> data)
		rootptr -> rchild = bst_deletion(rootptr -> rchild, key);

	else
	{
		// found the key to be deleted !
		// case 1: if it is a leaf node
		if(rootptr -> lchild == NULL && rootptr -> rchild == NULL)
		{
			delete rootptr;	// rootptr is free but still has an address - dangling pointer
			rootptr = NULL;	// rootptr address is relieved
		}

		// case 2: only one child
		else if(rootptr -> lchild == NULL)	// only child is at left
		{
			bstnode* temp = rootptr;
			rootptr = rootptr -> rchild;
			delete temp;
		}

		else if(rootptr -> rchild == NULL)	// only child is at right
		{
			bstnode* temp = rootptr;
			rootptr = rootptr -> lchild;
			delete temp;
		}

		// case 3: node to be removed has both lchild and rchild
		else
		{
			bstnode* temp = findMin(rootptr -> rchild);
			rootptr -> data = temp -> data;
			rootptr -> rchild = bst_deletion(rootptr -> rchild, temp -> data);
		}
	}

	return rootptr;

}


bstnode* get_child(bstnode* rootptr, int key, char child)
{
	bstnode* reqd_node = NULL;;
	reqd_node = bst_search(rootptr, key, 0);

	if(reqd_node == NULL)
		return NULL;

	if(child == 'l')
	// return info of left child
		return reqd_node -> lchild;
	else
		return reqd_node -> rchild;

}

int main()
{
	int node_count, i, key, starting_height;
	char more = 'n';
	int choice;
	FILE *reader;

	reader = fopen("inputs.txt", "r");
	if(!reader)
	{
		cout<< "\nError in reading file...";
		exit(0);
	}

	fscanf(reader, "%d", &node_count);
	
	// a tree is always accessed by a pointer to its root node. rootptr below isn't the root node itself - 
	// rather it just stores the address of the root of the tree - initially tree will be empty so rootptr
	// just points to NULL

	cout<< "\nCreating initial BST...\n";
	bstnode* rootptr = NULL;

	for(i = 0; i < node_count; i++)
	{
		// read input numbers and insert into initial tree
		fscanf(reader, "%d", &key);

		/*
		 rootptr is a local variable of main - so if we pass rootptr to bst_insertion() via value, when we
		 return from that function we will not see the changes made in main. There are 3 ways to handle:
		 1. We can declare the rootptr as global
		 2. we can return the root as bstnode* from insert() and assign it again to rootptr in main
		 3. we can pass a pointer to rootptr itself while calling insert() - so in insert() function we
		    have bstnode** root - double pointer, and return type of insert() can be simply void - hence
		    changes are made to root inside insert() (using *root), it will be reflected in rootptr of main.
		*/

		bst_insertion(&rootptr, key);
		
	}


	do
	{
		cout<< "\nIn-Order traversal of the given tree: \n---------------------------------------------\n";
		inorder_visualization(rootptr);

		cout<< "\n\nList of operations on the BST \n--------------------------";
		cout<< "\n1. Search a key";
		cout<< "\n2. Insert a key";
		cout<< "\n3. Delete a key";
		cout<< "\n4. Get child details";

		cout<< "\nEnter your choice: ";
		cin>> choice;

		starting_height = 0;
		bstnode* result = NULL;
		bstnode* l = NULL;
		bstnode* r = NULL;

		switch(choice)
		{
			case 1:		cout<< "\nEnter key to be searched: ";
						cin>> key;
						result = bst_search(rootptr, key, starting_height);
						if(result)					// if not NULL
							cout << "\nKey value found: "<<result->data;
						break;

			case 2:		cout<< "\nEnter key to be inserted: ";
						cin>> key;
						bst_insertion(&rootptr, key);
						break;

			case 3: 	cout<< "\nEnter key to be deleted: ";
						cin>> key;
						rootptr = bst_deletion(rootptr, key);
						break;

			case 4: 	cout<< "\nEnter node data for its child details: ";
						cin>> key;
						// assuming key given always exists in tree already
						l = get_child(rootptr, key, 'l');
						r = get_child(rootptr, key, 'r');
						cout<< "\n\nNode : "<< key;

						if(l) 
							cout<< "\tleft child: "<< l -> data;
						else
							cout<< "\tleft child: NULL";
						if(r) 
							cout<< "\tright child: "<< r -> data;
						else
							cout<< "\tright child: NULL";


						break;

			default:	cout<< "\nInvalid choice !";
						break;
		}

		cout<< "\n\nAnother operation ? (Enter y for yes or n to quit) ";
		cin>> more;


	} while(more == 'y' || more == 'Y');

	return 0;
}