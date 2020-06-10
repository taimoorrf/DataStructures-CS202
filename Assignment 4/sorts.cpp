#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include"list.cpp"
#include<stdlib.h>
#include<time.h>
#include<algorithm>
							/**Helper functions**/
//=====================================================================================

void MakeList(List<long>* &list, vector<long> numbers)
{
	for (int i = 0; i < numbers.size(); i++)
	{
		list->insertAtHead(numbers[i]);
	}
}

ListItem<long>* MergeLists(ListItem<long>* &list1, ListItem<long>* &list2)
{
	ListItem<long>* finalList = NULL;
	
	if (list1 == NULL && list2 != NULL)
	{
		return list2;
	}

	else if (list2 == NULL && list1 != NULL)
	{
		return list1;
	}

	if(list1->value > list2->value)
    {
		finalList = list2;
		finalList->next = MergeLists(list2->next, list1);
	}
	else
    {
		finalList = list1;
		finalList->next = MergeLists(list2, list1->next);
	}
	
	return finalList;

}


void MergeHelper(ListItem<long>* &temp)
{
	if(temp->next == NULL)
	{
		return;
	} 

	ListItem<long>* temp1 = temp;
	ListItem<long>* temp2 = temp;


	//Traversing to the middle of the list
	int i = 0;
	int size = 0;
	ListItem<long>* traverser = temp;
	while (traverser != NULL)
	{
		size++;
		traverser = traverser->next;
	} 

	while (i < size/2)
	{
        	temp2 = temp2->next;
        	i++;
	}

	//Breaking list in 2
	temp1 = temp2->prev;
	temp1->next = NULL;
    	temp1 = temp;
    	temp2->prev = NULL;	
	
	//Further partitioning list
	MergeHelper(temp1);
	MergeHelper(temp2);


	temp = MergeLists(temp1, temp2);

}

void QSArrayHelper(int array[], int s, int e)
{
	if (s >= e)
	{
		return;
	}

	//Partitioning
	int pivot = array[e];
	int j = s;
	int i = s;
	while (i <= e-1)
	{
		if (array[i] <= pivot)
		{
			swap(array[i], array[j]);
			j++;
		}
		
		i++;
	}

	swap(array[j], array[e]);
	
	//Sorting left side of the array recursively
	QSArrayHelper(array, s, j-1);

	//Sorting right side of the array recursively
	QSArrayHelper(array, j+1, e);
}

void QSListHelper(ListItem<long>* head, ListItem<long>* tail)
{
	if (head != tail && tail != NULL && head != tail->next)
	{
		//Partitioning
		int pivot = tail->value;
		//cout<<pivot<<endl;
		ListItem<long>* i = head->prev;
		ListItem<long>* j = head;
		long val;
		while (j != tail)
		{
			val = j->value;
			if (val <= pivot)
			{
				if (i != NULL)
				{
					i = i->next;
				}

				else
				{
					i = head;
				}

				swap(i->value, j->value);
			}

			j = j->next;
		}


		if (i != NULL)
		{
			i = i->next;
		}

		else
		{
			i = head;
		}
		
		swap(i->value, tail->value);
	
		//Sorting left side of the list recursively
		QSListHelper(head, i->prev);

		//Sorting right side of the list recursively
		QSListHelper(i->next, tail);
	}

}



//=====================================================================================
vector<long> InsertionSort(vector<long> nums)	
{
	int value;
	int index;
	long list[nums.size()];
	
	for (int i = 0; i < nums.size(); i++)
	{
		list[i] = nums[i];
	}
	
	int i = 1;
	
	while (i < nums.size())
	{
		value = list[i];
		index = i;
		while (index > 0 && list[index - 1] > value)
		{
			list[index] = list[index - 1];
			index--;
		}

		list[index] = value;
		i++;
	}

	for (int j = 0; j < nums.size(); j++)
	{
		nums[j] = list[j];
	}
	
	return nums;
}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{;
	List<long>* numbers = new List<long>;
	MakeList(numbers, nums);

	ListItem<long>* listHead = numbers->getHead();
	MergeHelper(listHead);

	nums.clear();

	while(listHead != NULL)
	{
		nums.push_back(listHead->value);
		listHead = listHead->next;
	}

	return nums;

}

//=====================================================================================
vector<long> QuickSortArray(vector<long> nums)
{
	int list[nums.size()];
	for (int i = 0; i < nums.size(); i++)
	{
		list[i] = nums[i];
	}	

	QSArrayHelper(list, 0, nums.size()-1);

	int size = nums.size();
	nums.clear();

	for (int i = 0; i < size; i++)
	{
		nums[i] = list[i];
	}

	return nums;
}

//=====================================================================================
vector<long> QuickSortList(vector<long> nums)
{
	List<long>* numbers = new List<long>;
	MakeList(numbers, nums);

	ListItem<long>* head = numbers->getHead();
	ListItem<long>* tail = numbers->getTail();

	QSListHelper(head, tail);

	ListItem<long>* temp = head;
	nums.clear();
	while(temp != NULL)
	{
		nums.push_back(temp->value);
		temp = temp->next;
	}


	return nums;

}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
	MinHeap heap(nums.size());
	for (int i = 0; i < nums.size(); i++)
	{
		heap.insertKey(nums[i]);
	}

	vector<long> list;
	long min;

	for (int i = 0; i < nums.size(); i++)
	{
		min = heap.extractMin();
		list.push_back(min);		
	}

	return list;

}

//=====================================================================================
vector<long> QueenOfAllSorts(vector<long> nums)
{
	int size = nums.size();
	int largest = nums[0];
	int smallest = nums[0];
	for (int i = 0; i < size; i++)	
	{
		if (nums[i] > largest)
		{
			largest = nums[i];
		}

		if (nums[i]<smallest)
		{
			smallest = nums[i];
		}
	}

	List<long>** numbers = new List<long>* [largest - smallest + 1];
	
	for (int i = 0; i < size; i++)
	{
		numbers[i] = new List<long>;
	}

	for(int i = 0; i < size; i++)
	{
		numbers[nums[i] - smallest]->insertAtHead(nums[i]); 
	}

	nums.clear();
	
	ListItem<long>* temp = NULL;

	for (int i = 0; i < size; i++)
	{
		if (numbers[i] != NULL)
		{
			temp = numbers[i]->getHead();
		}

		while(temp != NULL)
		{
			nums.push_back(temp->value);
			temp = temp->next;
		}
	}

	return nums;
}

#endif
