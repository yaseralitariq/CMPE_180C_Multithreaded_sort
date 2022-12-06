#include <bits/stdc++.h>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
using namespace std;

#define MAX_THREAD 4
#define MAX 1000000

int a[MAX];
int part = 0;


void swap (int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}


int partition (int arr[], int low, int high)
{
  int pivot = arr[high]; // pivot
  int i = (low - 1);     // Index of smaller element

  for (int j = low; j <= high - 1; j++)
    {
      // If current element is smaller than the pivot
      if (arr[j] < pivot)
        {
          i++; // increment index of smaller element
          swap (&arr[i], &arr[j]);
        }
    }
  swap (&arr[i + 1], &arr[high]);
  return (i + 1);
}


void quickSort (int arr[], int low, int high)
{
  if (low < high)
    {
      int pi = partition (arr, low, high);
      quickSort (arr, low, pi - 1);
      quickSort (arr, pi + 1, high);
    }
}

void *quick_sort (void *arg)
{
  // finding current thread number
  int thread_part = part++;

  // calculating start and end
  int start = thread_part * (MAX / 4);
  int end = (thread_part + 1) * (MAX / 4);

  // calculating mid
  int mid = (start + end) / 2;
  if (start < end)
    {
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
      while (i < n1 && j < n2)
        {
          if (L[i] <= R[j])
            {
              a[k] = L[i];
              i++;
            }
          else
            {
              a[k] = R[j];
              j++;
            }
          k++;
        }
      while (i < n1)
        {
          a[k] = L[i];
          i++;
          k++;
        }
      while (j < n2)
        {
          a[k] = R[j];
          j++;
          k++;
        }
    }
}

void
quick_call ()
{
  // calculating start and end
  int start = 0, end = MAX - 1;

  // calculating mid
  int mid = (start + end) / 2;
  if (start < end)
    {
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
      while (i < n1 && j < n2)
        {
          if (L[i] <= R[j])
            {
              a[k] = L[i];
              i++;
            }
          else
            {
              a[k] = R[j];
              j++;
            }
          k++;
        }
      while (i < n1)
        {
          a[k] = L[i];
          i++;
          k++;
        }
      while (j < n2)
        {
          a[k] = R[j];
          j++;
          k++;
        }
    }
}

int
main ()
{
  // initializing elements of array randomly
  srand (time (NULL));
  for (int i = 0; i < MAX; i++)
    a[i] = rand () % 100;

  // t1 and t2 for calculating time for
  // merge sort
  struct timeval t1, t2;
  gettimeofday (&t1, NULL);
  pthread_t threads[MAX_THREAD];

  // creating 4 threads
  for (int i = 0; i < MAX_THREAD; i++)
    pthread_create (&threads[i], NULL, quick_sort, (void *)NULL);

  // joining all 4 threads
  for (int i = 0; i < MAX_THREAD; i++)
    pthread_join (threads[i], NULL);

  quick_call ();

  // calculating time taken by merge sort
  gettimeofday (&t2, NULL);

  // time in seconds
  double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  // time in milliseconds
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

  cout << "\nTime taken for Quick Sort with multithreading = " << elapsedTime << "ms" << endl;
  return 0;
}