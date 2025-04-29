#include <iostream> // For input-output operations
#include <vector>   // For using dynamic array (vector)
#include <omp.h>    // For OpenMP parallelization
#include <ctime>    // For measuring execution time

using namespace std;

// Function to merge two sorted parts of the array
void merge(vector<int> &arr, int l, int m, int r)
{
    vector<int> temp;  // Temporary vector to store merged result
    int left = l;      // Starting index of left subarray
    int right = m + 1; // Starting index of right subarray

    // Merge the two subarrays into temp
    while (left <= m && right <= r)
    {
        if (arr[left] <= arr[right])
        {
            temp.push_back(arr[left]);
            left++;
        }
        else
        {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // Copy remaining elements from left subarray (if any)
    while (left <= m)
    {
        temp.push_back(arr[left]);
        left++;
    }

    // Copy remaining elements from right subarray (if any)
    while (right <= r)
    {
        temp.push_back(arr[right]);
        right++;
    }

    // Copy sorted elements back into original array
    for (int i = l; i <= r; i++)
    {
        arr[i] = temp[i - l];
    }
}

// Recursive function to perform parallel merge sort
void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2; // Find mid index

// Split the sorting into two parallel sections
#pragma omp parallel sections
        {
#pragma omp section
            mergeSort(arr, l, m); // Sort first half

#pragma omp section
            mergeSort(arr, m + 1, r); // Sort second half
        }

        merge(arr, l, m, r); // Merge the sorted halves
    }
}

int main()
{
    int n; // Number of elements
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n); // Declare a vector of size n

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i]; // Input array elements

    // Start timer before sorting
    clock_t start = clock();

    mergeSort(arr, 0, n - 1); // Call merge sort

    // End timer after sorting
    clock_t end = clock();

    cout << "Sorted array using Merge Sort: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    // Calculate time taken in seconds
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Merge sort time in seconds: " << duration << endl;

    return 0;
}
