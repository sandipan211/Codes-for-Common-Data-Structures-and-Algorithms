// code for searching

/*
	input format:
	Line 1: no. of integers to search from (n)
	Line 2 to n+1 : one number in each line

	Console input: key to be searched
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void series_display(vector <int> v)
{
	for(int i = 0; i < v.size(); i++)
		cout<< v[i] <<endl;
}

void swap(int *xp, int *yp)
{
	int temp;
	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void insertion_sort(vector <int> &v, char sort_order)
{
	cout<< "\nPerforming insertion sort.....";

	int n = v.size();
	int i, j;

	/* 
		in insertion sort, at each outer loop iteration, one element is brought to its proper sorted 
		position. Assuming first element is already at proper place, iteration starts from second element.
		At the end of i'th iteration, leftmost (i+1) elements are sorted
	*/
	for(i = 1; i < n; i++)
	{
		j = i;
		while(j > 0)
		{
			if(v[j] < v[j-1])
			{
				// may avoid these repeated swaps - just find the prpoer position and swap outside loop
				swap(&v[j], &v[j-1]);
				j--;
			}
			else
				break;
		}
	}

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order	

}

void linear_search(vector <int> v, int key)
{
	int i;

	for(i = 0; i < v.size(); i++)
	{
		if(v[i] == key)
		{
			cout<< "\nKey found at position "<< i+1;
			break;
		}
	}

	if(i == v.size())
		cout<< "\nKey not in list!";
}

void binary_search(vector <int> v, int key)
{
	// sort the list first - binary search is possible only on a sorted list
	insertion_sort(v, 'a');

	int low = 0;
	int high = v.size() - 1;
	int mid, found = 0;

	while(low < high)
	{
		mid = (low+high) / 2;
		if(v[mid] == key)
		{
			cout<< "\nKey found at position "<< mid+1<<" in the sorted list";
			found = 1;
			break;
		}

		else if (key < v[mid])
			high = mid-1;
		else
			low = mid+1;

	}

	if(!found)
		cout<< "\nKey not in list!";

}
int main()
{
	int num_count, key, choice, i, in;
	vector <int> inputs;
	char more = 'n';
	FILE *reader;

	reader = fopen("inputs.txt", "r");
	if(!reader)
	{
		cout<< "\nError in reading file...";
		exit(0);
	}

	fscanf(reader, "%d", &num_count);
	
	// read input numbers 
	for(i = 0; i < num_count; i++)
	{
		fscanf(reader, "%d", &in);
		inputs.push_back(in);
	}


	do
	{
		// display original array 
		series_display(inputs);

		cout<< "\nEnter key to be searched: ";
		cin>> key;
		cout<< "\nList of searching techniques \n--------------------------";
		cout<< "\n1. Linear search";
		cout<< "\n2. Binary search";

		cout<< "\nEnter your choice: ";
		cin>> choice;

		switch(choice)
		{
			case 1:		linear_search(inputs, key);
						break;

			case 2:		binary_search(inputs, key);
						break;

			default:	cout<< "\nInvalid choice !";
						break;
		}

		cout<< "\nSearch again ? (Enter y for yes or n to quit) ";
		cin>> more;


	} while(more == 'y' || more == 'Y');

	return 0;
}