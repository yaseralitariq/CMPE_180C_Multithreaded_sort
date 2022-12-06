#include <iostream>
#include <sys/time.h>
#include <stdlib.h> 
#include <time.h> 
using namespace std;

#define size 1000000
int partition(int arr[], int start, int end)
{
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(int arr[], int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}
 
int main()
{
 
    
    int arr[size];
    srand(time(NULL)); 
    for(int i = 0; i < size; i++){
      arr[i] = rand() % 100;
   }
   struct timeval t1, t2; 
   gettimeofday(&t1, NULL); 
 
    quickSort(arr, 0, size - 1);
 
    gettimeofday(&t2, NULL); 


  // time in seconds 
  double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; 
  // time in milliseconds 
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; 

  cout << "\nTime taken for Quick Sort without Multi-threading " << elapsedTime << "ms"<<endl; 
 
 
    return 0;
}
