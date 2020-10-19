// code for sorting numbers

/*
	input format:
	Line 1: no. of integers to sort (n)
	Line 2 to n+1 : one number in each line
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

#define b 10				// number of buckets for radix sort

void series_display(vector <int> v, int sorted)
{
	if (sorted)
		cout<< "\nNumbers after sort \n-------------------\n";
	else
		cout<< "\nNumbers before sort \n-------------------\n";

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

int find_ith_sig_digit(int number, int i)
{
	// finds the ith significant digit of an integer from right
	int div = i - 1;
	while(div > 0)
	{
		number = number/10;
		div--;
		if(number == 0)
			break;
	}

	if(number == 0)
		return 0;
	else
		return number % 10;
}

void bubble_sort(vector <int> &v, char sort_order)
{
	cout<<"\nPerforming bubble sort.....";

	int n = v.size();
	int i, j, temp, modified;

	for(i = 0; i < n-1; i++)
	{
		modified = 0;	// will work as a flag to indicate if the array is already sorted from i to n-1
		for(j = 0; j < (n - 1 - i); j++)
		{
			if(v[j] > v[j+1])
			{
				// swap and send heavier/bigger element towards the right
				swap(&v[j], &v[j+1]);
				modified = 1;
			}
		}

		if(!modified)
			break;
	}

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order
}

void selection_sort(vector <int> &v, char sort_order)
{
	cout<<"\nPerforming selection sort.....";

	int n = v.size();
	int i, j, temp, smallest, smallest_pos, found_small;

	for(i = 0; i < n-1; i++)
	{
		smallest = v[i];
		found_small = 0;
		for(j = i+1; j < n; j++)
		{
			if(v[j] < smallest)
			{
				smallest = v[j];
				smallest_pos = j;
				found_small = 1;
			}
		}

		if(found_small)
			// swap elements at smallest_pos and i
			swap(&v[i], &v[smallest_pos]);

	}

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order
}


void insertion_sort(vector <int> &v)
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
				// can also pass without & because vector elements are passed as references by default
				j--;
			}
			else
				break;
		}
	}



}

void radix_sort(vector <int> &v, char sort_order)
{
	cout<< "\nPerforming radix sort.....";

	int n = v.size();
	int d = 0; 				// max number of digits = number of passes 
	vector <vector <int> > buckets(b);		// one bucket for each digit 0-9
	int i, j, k;

	// first find the biggest number 
	int max = v[0];
	for(i = 1; i < n; i++)
	{
		if(v[i] > max)
			max = v[i];
	}

	// get the max no. of digits in it
	while(max > 0)
	{
		max = max/10;
		d++;
	}

	i = 1;	// starting from 1st significant digit from right
	while(i <= d)
	{
		// each pass for sorting
		for(j = 0; j < n; j++)
			buckets[find_ith_sig_digit(v[j], i)].push_back(v[j]);

		int v_pos = 0;
		for(j = 0; j < b; j++)
		{
			for(k = 0; k < buckets[j].size(); k++)
				// placing the elements from ith significant digit from bucket j into the actual array
				v[v_pos++] = buckets[j][k];

			// clearing out bucket j
			buckets[j].clear();
		}

		cout<<"\nAfter pass "<<i;
		series_display(v, 1);
		i++;
	}

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order	
}


void counting_sort(vector <int> &v, char sort_order)
{
	cout<< "\nPerforming counting sort.....";

	int n = v.size();
	int i, min, max, shifted_index;

	// first find the range of input numbers
	min = max = v[0];

	for(i = 1; i < n; i++)
	{
		if(v[i] < min)
			min = v[i];
		if(v[i] > max)
			max = v[i];
	}

	// this range will be range of the upcoming arrays
	// also, to save space in auxiliary arrays, do a change of variables
	int arr_range = max - min + 1;
	vector <int> sumCounts(arr_range, 0); // stores the cumulative sums of numbers at its index in array

	// get the number counts
	for(i = 0; i < n; i++)
	{
		// array index starts from 0, but mine logical array starts from min - so a change of variables
		shifted_index = v[i] - min;
		sumCounts[shifted_index]++;
	}

	// get the cumulative sums in sumCounts
	for(i = 1; i < arr_range; i++)
		sumCounts[i] += sumCounts[i-1];

	series_display(sumCounts, 0);
	// sort the numbers as per their cumulative sums in another array
	vector <int> sorted(n+1);

	// read the numbers from original array from right to left to get  STABLE SORT
	for(i = n-1; i >= 0; i--)
	{
		/*
		 have to use elements of sumCount as indices in new array; but since sumCount has all elements as 
		 positive nonzero values, so index 0 in new array won't have any element
		*/
		shifted_index = v[i] - min;
		sorted[sumCounts[shifted_index]] = v[i];

		// decrease value at sumCounts[shifted_index] by 1, so that if there are repeated elements, they
		// can be placed at the proper index the next time
		sumCounts[shifted_index]--;
	}
	series_display(sorted, 0);

	// copy values from sorted[1...n] to v[0...n-1]
	v.assign(sorted.begin()+1, sorted.end());

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order	

}


int partition(vector <int> &v, int low, int high)
{
	int pivot = v[low]; // making first element as pivot
	int pivot_index = high;

	for(int i = high; i >= low + 1; i--)
	{
		if(v[i] > pivot)
		{
			swap(v[i], v[pivot_index]);		// elements > pivot being pushed to right side 
			pivot_index--;
		}
	}

	// put pivot to pivot_index - pivot is placed at correct position by now
	swap(v[low], v[pivot_index]);

	return pivot_index;

} 


void quick_sort(vector <int> &v, int low, int high)
{
	if(low < high)
	{
		int pivot_index = partition(v, low, high);
		quick_sort(v, low, pivot_index - 1);
		quick_sort(v, pivot_index + 1, high);
	}
}


void two_way_merge(vector <int> &v, int low, int mid, int high)
{
	vector <int> auxiliary;
	int aux_count = 0;
	int list1_low = low, list1_high = mid, list2_low = mid+1, list2_high = high;

	while ((list1_low <= list1_high) && (list2_low <= list2_high))
	{
		if(v[list1_low] < v[list2_low])
		{
			auxiliary.push_back(v[list1_low++]);
			aux_count++;
		}

		else
		{
			auxiliary.push_back(v[list2_low++]);
			aux_count++;
		}
	}

	for( ; list1_low <= list1_high; list1_low++)
	{
		// if elemenmts remaining in list 1, just put the remaining list 1 into auxiliary
		auxiliary.push_back(v[list1_low]);
		aux_count++;
	}

	for( ; list2_low <= list2_high; list2_low++)
	{
		// if elemenmts remaining in list 2, just put the remaining list 2 into auxiliary
		auxiliary.push_back(v[list2_low]);
		aux_count++;
	}

	// copy the final auxiliary to v[low...high]
	aux_count = 0;
	for(int i = low; i <= high; i++)
		v[i] = auxiliary[aux_count++];

}

void merge_sort(vector <int> &v, int low, int high)
{
	// for less than 16 elements, insertion sort is more efficient - can use it too - here not shown
	if(low < high)
	{
		int mid = (low + high) / 2;
		merge_sort(v, low, mid);
		merge_sort(v, mid+1, high);
		two_way_merge(v, low, mid, high);
		series_display(v, 0);
	}

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

void max_heap_deletion(vector <int> &h, int outside_heap)
{
	int current_heap_size = h.size() - outside_heap;
	// swap the heap root first with rightmost node (last element on heap) - then build heap again 
	// till current_heap_size - 1

	int max = h[0];
	int max_among_children;
	swap(h[0], h[current_heap_size - 1]);
	// the line below is needed for just build and delete heap - but not needed for heapsort
	// h.erase(h.begin() + (current_heap_size - 1));

	// swapped max_heap element went to its sorted position - so now build-heap from remaining elements
	current_heap_size--;


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

}

void heap_sort(vector <int> &v, char sort_order)
{
	int max, i;
	vector <int> heap_array;	// don't actually need this additional array - but need in this setting
	
	for(i = 0; i < v.size(); i++)
		build_max_heap(heap_array, v[i]);

	for(i = 0; i < heap_array.size(); i++)
		// in iteration i, i elements are currently out of heap (sorted position already) 
		max_heap_deletion(heap_array, i);

	v.clear();
	v = heap_array;

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order	

}


void shell_sort(vector <int> &v, char sort_order)
{
	/*
	 improved insertion sort : 
	 - insertion sort compares adjacent elements - but here we compare only the distant set of elements
	 - distance notion measured by gaps - initial gap = floor(n/2) - after that, gap = floor(gap/2)
	 - at final pass, gap = 1 => adjacent elements to be compared and swapped if needed-like insetion sort
	*/
	int n = v.size();
	int gap = n/2;
	int pass = 1;

	while(gap > 0)
	{
		int comparer = 0;		
		// stores the index with which if gap is added, becomes the index of the adjacent element
		// to compare - hence always compare v[comparer] and v[comparer + gap]

		int traversed_until = comparer + gap;	
		// stores the index until which sorting is done in current pass

		while(traversed_until < n) 	// until the end of the array
		{
			if(v[comparer] > v[comparer + gap])
			{
				while((comparer >= 0) && (v[comparer] > v[comparer + gap]))
				{
					// comparison condition is also required again in while() because in subsequent runs of
					// while(), if comparison is not satisfied then we have to stop anymore comparisons
					swap(v[comparer], v[comparer +  gap]);
				
					// check if more swapping possible at the LHS of traversed_until gap elements apart
					comparer = comparer - gap;
				}
			}

			// shift one position towards right for traversed_until-so comparer is gap elements behind
			traversed_until++;
			comparer = traversed_until - gap;
			
		}

		gap /= 2;
		cout<< "\nAfter pass "<< pass;
		series_display(v, 0);
		pass++;
			
	}

	if(sort_order == 'd')	// ascending order (default)
		reverse(v.begin(), v.end());	// made in descending order
}


int main()
{
	int num_count, i, in;
	vector <int> inputs;
	char more = 'n';
	char sort_order;
	int choice;
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
		// creating a copy of original array which will be modified for every sorting method
		vector <int> to_sort(inputs);

		// display original array (unsorted) - flag is 0 for unsorted and 1 for sorted
		series_display(to_sort, 0);

		cout<< "\nList of sorting techniques \n--------------------------";
		cout<< "\n1. Bubble sort";
		cout<< "\n2. Selection sort";
		cout<< "\n3. Insertion sort";
		cout<< "\n4. Quick sort";
		cout<< "\n5. Merge sort";
		cout<< "\n6. Heap sort";
		cout<< "\n7. Shell sort";
		cout<< "\n8. Radix sort";
		cout<< "\n9. Counting sort";

		cout<< "\nEnter your choice: ";
		cin>> choice;

		cout<< "\nPress a for ascending or d for descending order of sort: ";
		cin>> sort_order;

		switch(choice)
		{
			case 1:		// iterative - comparison sort
						bubble_sort(to_sort, sort_order);
						break;



			case 2:		// iterative - comparison sort
						selection_sort(to_sort, sort_order);
						break;



			case 3: 	// iterative - comparison sort
						insertion_sort(to_sort);
						if(sort_order == 'd')	// ascending order (default)
							reverse(to_sort.begin(), to_sort.end());	// made in descending order	
						break;



			case 4: 	// recursive - divide and conquer - comparison sort
						quick_sort(to_sort, 0, num_count - 1);
						if(sort_order == 'd')	// ascending order (default)
							reverse(to_sort.begin(), to_sort.end());	// made in descending order	
						break;



			case 5: 	// recursive - divide and conquer - comparison sort
						merge_sort(to_sort, 0, num_count - 1);
						if(sort_order == 'd')	// ascending order (default)
							reverse(to_sort.begin(), to_sort.end());	// made in descending order	
						break;



			case 6: 	// iterative - uses heap structure
						heap_sort(to_sort, sort_order);
						break;



			case 7:		// iterative - comparison sort - works like improved insertion sort
						shell_sort(to_sort, sort_order);
						break;



			case 8:		// counting based	
						radix_sort(to_sort, sort_order);
						break;



			case 9:		// counting based
						counting_sort(to_sort, sort_order);
						break;

			default:	cout<< "\nInvalid choice !";
						break;
		}

		series_display(to_sort, 1);
		to_sort.clear();
		cout<< "\nSort again ? (Enter y for yes or n to quit) ";
		cin>> more;


	} while(more == 'y' || more == 'Y');

	return 0;
}
