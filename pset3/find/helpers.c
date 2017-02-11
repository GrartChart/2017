/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

void swap(int* a, int* b);
bool binarySearch(int key, int array[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool binarySearch(int key, int stack[], int min, int max)
{
    // TODO: implement a searching algorithm
    
    if (min >= max)
    {
        return false;
    }
    else
    {
    int midpoint = (min + max) / 2; // finds the midpoint of the array of values //
    
    if (stack[midpoint] == key || stack[max] == key || stack[min] == key) // checks if midpoint/max/min are needle //
    {
        return true;
    }
    else if (stack[midpoint] > key)
    {
         return binarySearch(key, stack, min, midpoint - 1); // recursive function call with adjusted min/max // 
    }
    else if (stack[midpoint] < key)    
    {
        return binarySearch(key, stack, midpoint + 1, max); // recursive function call with adjusted min/max // 
    }
    return false;
    }
}

void sort(int values[], int n) // sorts the array // 
{
    int swapped = -1; // creates a variable to track whether any swaps occur //
    while (swapped != 0) // loops until no swaps occur //
    {
        swapped = 0; 
        for (int i = 0; i < (n-1); i++)
        {
            if (values[i] > values[i+1])
            {
                swap(&values[i], &values[i+1]); //calls swap function below //
                swapped++; // increments swapped if any swaps occur //
            }
        }
    }
}

void swap(int* a, int* b) // swap function used above //
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool search(int value, int values[], int n) //returns results from binarySearch function //
{
    return binarySearch(value, values, 0, n);
}