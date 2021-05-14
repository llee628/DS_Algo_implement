#include<iostream>
#include<vector>
using namespace std;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(vector<int>& arr, int begin, int end){
	/**
	* make all the value which is smaller than the pivot point on the left of the pivot point and
	* all the value which is larger than the pivot point on the right of the pivot point
	*
	* return: the final position of the pivot point
	*/

	int pivot = arr[end]; //Assign the last element of the array as pivot point
	int i = begin - 1; 

	for (int j = begin; j < end; j += 1){
		if (arr[j] < pivot){
			i += 1;
			swap(&arr[i], &arr[j]);
		}
	}

	//After the loop, now i is at the last position of the red value(the value smaller than pivot)
	//swap the first blue value(the value greater than pivot) with pivot point to finish the partition
	i += 1;
	swap(&arr[i], &arr[end]);
	int pivot_position = i;
	return pivot_position;

}

void QuickSort(vector<int>& arr, int begin, int end){
	if (begin < end){
		int pivot_position = partition(arr, begin, end);
		QuickSort(arr, begin, pivot_position-1);
		QuickSort(arr, pivot_position+1, end);

	}
}

void printArray(vector<int>& arr, int size){
	for (int i = 0; i < size; i += 1){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main(){
	//test case 1
	cout<<"test case 1:\n";
	vector<int> test1 = {3, 4, 5, 1, 2};
	int n1 = test1.size();

	cout<<"original:\n";
	printArray(test1, n1);
	QuickSort(test1, 0, n1-1);

	cout<<"sorted:\n";
	printArray(test1, n1);

	//test case 2
	cout<<"test case 2:\n";
	vector<int> test2 = {9, 4, 1, 6, 7, 3, 8, 2, 5};
	int n2 = test2.size();

	cout<<"original:\n";
	printArray(test2, n2);
	QuickSort(test2, 0, n2-1);

	cout<<"sorted:\n";
	printArray(test2, n2);

	//test case 3
	cout<<"test case 3:\n";
	vector<int> test3 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int n3 = test3.size();

	cout<<"original:\n";
	printArray(test3, n3);
	QuickSort(test3, 0, n3-1);

	cout<<"sorted:\n";
	printArray(test3, n3);

	//test case 4
	cout<<"test case 4:\n";
	vector<int> test4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int n4 = test4.size();

	cout<<"original:\n";
	printArray(test4, n4);
	QuickSort(test4, 0, n4-1);

	cout<<"sorted:\n";
	printArray(test4, n4);

	return 0;

}








