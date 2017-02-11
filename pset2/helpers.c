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
    
    if (stack[midpoint] == key || stack[max] == key || stack[min] == key)
    {
        return true;
    }
    else if (stack[midpoint] > key)
    {
         return binarySearch(key, stack, min, midpoint - 1);
    }
    else if (stack[midpoint] < key)    
    {
        return binarySearch(key, stack, midpoint + 1, max);
    }
    return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int swapped = -1; // creates a variable to track whether any swaps occur //
    while (swapped != 0)
    {
        swapped = 0; 
        for (int i = 0; i < (n-1); i++)
        {
            if (values[i] > values[i+1])
            {
                swap(&values[i], &values[i+1]); //calls swap function below //
                swapped++;
            }
        }
    }
}

void swap(int* a, int* b) // * indicates a and b are pointers so are passed by reference rather than by value //
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool search(int value, int values[], int n)
{
    return binarySearch(value, values, 0, n);
}