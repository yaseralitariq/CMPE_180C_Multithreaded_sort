#include <iostream> 
#include <stdlib.h> 
#include <time.h> 
#include <pthread.h> 
#include <sys/time.h>
using namespace std; 

#define MAX_THREAD 4
#define MAX 1000000

int a[MAX]; 
int part = 0; 

void *merge_sort(void *arg) 
{ 
  // finding current thread number 
  int thread_part = part++; 

  // calculating start and end 
  int start = thread_part * (MAX / 4); 
  int end = (thread_part + 1) * (MAX / 4); 

  // calculating mid 
  int mid = (start + end) / 2; 
  if (start < end) { 
    int i, j, k; 
    int n1 = mid - start + 1; 
    int n2 = end - mid; 

    // creating temp arrays 
    int L[n1], R[n2]; 

    for (i = 0; i < n1; i++) 
      L[i] = a[start + i]; 
    for (j = 0; j < n2; j++) 
      R[j] = a[mid + 1 + j]; 

    i = 0; 
    j = 0; 
    k = start; 
    while (i < n1 && j < n2) { 
      if (L[i] <= R[j]) { 
        a[k] = L[i]; 
        i++; 
      } 
      else { 
        a[k] = R[j]; 
        j++; 
      } 
      k++; 
    } 
    while (i < n1) { 
      a[k] = L[i]; 
      i++; 
      k++; 
    } 
    while (j < n2) { 
      a[k] = R[j]; 
      j++; 
      k++; 
    } 
  } 
} 

void merge_call() 
{ 
  // calculating start and end 
  int start = 0, end = MAX - 1; 

  // calculating mid 
  int mid = (start + end) / 2; 
  if (start < end) { 
    int i, j, k; 
    int n1 = mid - start + 1; 
    int n2 = end - mid; 

    // creating temp arrays 
    int L[n1], R[n2]; 

    for (i = 0; i < n1; i++) 
      L[i] = a[start + i]; 
    for (j = 0; j < n2; j++) 
      R[j] = a[mid + 1 + j]; 

    i = 0; 
    j = 0; 
    k = start; 
    while (i < n1 && j < n2) { 
      if (L[i] <= R[j]) { 
        a[k] = L[i]; 
        i++; 
      } 
      else { 
        a[k] = R[j]; 
        j++; 
      } 
      k++; 
    } 
    while (i < n1) { 
      a[k] = L[i]; 
      i++; 
      k++; 
    } 
    while (j < n2) { 
      a[k] = R[j]; 
      j++; 
      k++; 
    } 
  } 
} 

int main() 
{ 
  // initializing elements of array randomly 
  srand(time(NULL)); 
  for (int i = 0; i < MAX; i++) 
    a[i] = rand() % 100; 

  // t1 and t2 for calculating time for 
  // merge sort 
  struct timeval t1, t2; 
  gettimeofday(&t1, NULL); 
  pthread_t threads[MAX_THREAD]; 

  // creating 4 threads 
  for (int i = 0; i < MAX_THREAD; i++) 
    pthread_create(&threads[i], NULL, 
          merge_sort, (void*)NULL); 

  // joining all 4 threads 
  for (int i = 0; i < MAX_THREAD; i++) 
    pthread_join(threads[i], NULL); 

  merge_call(); 

  // calculating time taken by merge sort 
  gettimeofday(&t2, NULL); 


  // time in seconds 
  double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; 
  // time in milliseconds 
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; 

  cout << "\nTime taken for Merge Sort with multithreading = " << elapsedTime << "ms" << endl; 
  return 0; 
}
