#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void swap(int *xp, int *yp)
{
	int temp;
	temp = *xp;
	*xp = *yp;
	*yp = temp;
}


void heap_display(vector <int> v)
{
	cout<< "\nHeap \n-------------------\n";

	for(int i = 0; i < v.size(); i++)
		cout<< v[i] <<" ";
}

void build_max_heap(vector <int> &h, int key)
{
	// first push key at the end
	int pushed_index = h.size();
	h.push_back(key);

	while(pushed_index > 0)
	{
		// keep checking if the "parents" follow max-heap property or not - if not then swap
		if((pushed_index % 2 == 0) && (h[pushed_index] > h[pushed_index/2 - 1]))
		{
			swap(h[pushed_index], h[pushed_index/2 - 1]);
			pushed_index = pushed_index/2 - 1;
		}

		else if((pushed_index % 2 != 0) && (h[pushed_index] > h[pushed_index/2]))
		{
			swap(h[pushed_index], h[pushed_index/2]);
			pushed_index = pushed_index/2;
		}

		else
			break;
	}

}

int max_heap_deletion(vector <int> &h)
{
	int current_heap_size = h.size();
	// swap the heap root first with rightmost node (last element on heap) - then build heap again 
	// till current_heap_size - 1

	int max = h[0];
	int max_among_children;
	swap(h[0], h[current_heap_size - 1]);
	h.erase(h.begin() + (current_heap_size - 1));
	current_heap_size = h.size();

	// cout<<"\ntil now:";
	// heap_display(h);
	int leaf_adjuster_index = 0;
	int left_child = 2*leaf_adjuster_index+1;
	int right_child = 2*leaf_adjuster_index+2;

	while(left_child < current_heap_size)
	{
		// check if any right child of current node exists
		if(right_child >= current_heap_size)
		{
			// if no, just compare with life child and swap if permissible
			if(h[leaf_adjuster_index] < h[left_child])
			{
				swap(h[leaf_adjuster_index], h[left_child]);
				leaf_adjuster_index = left_child;
			}
			else
				break;
		}

		else
		{
			// both children of current node exist
			max_among_children = (h[left_child] > h[right_child]) ? left_child : right_child;
			if(h[leaf_adjuster_index] < h[max_among_children])
			{
				swap(h[leaf_adjuster_index], h[max_among_children]);
				leaf_adjuster_index = max_among_children;
			}
			else
				break;
		}
		
		left_child = 2*leaf_adjuster_index+1;
		right_child = 2*leaf_adjuster_index+2;


	}

	return max;
}

int main()
{
	int node_count, i, key, max;
	char more = 'n';
	int choice;
	vector <int> heap_array;
	FILE *reader;

	reader = fopen("heap_inputs.txt", "r");
	if(!reader)
	{
		cout<< "\nError in reading file...";
		exit(0);
	}

	fscanf(reader, "%d", &node_count);
	for(i = 0; i < node_count; i++)
	{
		// read input numbers and insert into initial tree
		fscanf(reader, "%d", &key);
		build_max_heap(heap_array, key);
		
	}
	
	do
	{
		heap_display(heap_array);

		cout<< "\n\nList of operations on the Max-heap \n--------------------------";
		cout<< "\n1. Insert a key";
		cout<< "\n2. Delete a key";

		cout<< "\nEnter your choice: ";
		cin>> choice;


		switch(choice)
		{

			case 1:		cout<< "\nEnter key to be inserted: ";
						cin>> key;
						build_max_heap(heap_array, key);
						break;

			case 2: 	max = max_heap_deletion(heap_array);
						cout<<"\nDeleted element = "<<max;
						heap_display(heap_array);
						break;

			default:	cout<< "\nInvalid choice !";
						break;
		}

		cout<< "\n\nAnother operation ? (Enter y for yes or n to quit) ";
		cin>> more;


	} while(more == 'y' || more == 'Y');

	return 0;
}