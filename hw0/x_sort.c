# include <stdio.h>
#include <stdlib.h>
// A simple program to sort an array of integers in C

/* YOUR WORK HERE */

// Input: An array of integers and its length
// Output: Nothing
// Side Effect: The input array is sorted from least to greatest

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
	// an integer, mx, is initialized as the first element of the passed array
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
	// iterates over the array, constantly updating the bigggest vaule until it runs out of array
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
    // output array
    int output[n];
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void sort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

/* END YOUR WORK */

/* FEEDBACK FUNCTIONS */

// Input: An array of integers and its length
// Output: 1 if the array is sorted least to greatest, 0 otherwise
// Side Effect: None
int is_sorted(int *arr, int len)
{
	int i = 0;
	while (i < (len - 2))
	{
		if (arr[i] > arr[i+1])
		{
			return 0;
		}
		i++;
	}
	return 1;
}

// The special main function

int main()
{
	int test_arr[10] = {8,6,4,2,0,1,3,5,7,9};
	sort(test_arr, 10);
	if (is_sorted(test_arr, 10))
	{
		printf("Good job!\n");
	} else {
		printf("Keep it up!\n");
	}
	return 0;
}
