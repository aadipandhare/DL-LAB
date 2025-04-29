#include <iostream> // For input-output operations
#include <vector>   // For using dynamic array (vector)
#include <omp.h>    // For OpenMP parallelization
#include <ctime>    // For measuring execution time

using namespace std;

// Function to perform parallel bubble sort
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();  // Get size of array
    bool swapped = true; // Variable to track if any swapping happened

    // Continue loop until no elements are swapped
    while (swapped)
    {
        swapped = false; // Assume no swap happens in this iteration

// Parallelize the 'for' loop using OpenMP
#pragma omp parallel for
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]); // Swap if elements are out of order
                swapped = true;           // Set swapped to true to continue loop
            }
        }
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

    bubbleSort(arr); // Call bubble sort

    // End timer after sorting
    clock_t end = clock();

    cout << "Sorted array using Bubble Sort: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    // Calculate time taken in seconds
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Bubble sort time in seconds: " << duration << endl;

    return 0;
}
