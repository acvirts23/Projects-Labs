/*
  Filename   : LastSorting.cc
  Author 	: Tristan M Kieffer and Andrew Virts
  Course 	: CSCI 362, Section 02
  Assignment : Out of Sorts Lab
  Description: Implement quick, insertion, merge, and shell sort.
  count comparisons for each as well
*/

/************************************************************/
// System includes

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <random>

/************************************************************/
// Local includes
#include "Timer.hpp"

/************************************************************/
// Using declarations

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::swap;

/************************************************************/
// Function prototypes/global vars/typedef's

// Perform a merge sort on 'v'
// Return the number of comparisons performed
// Additionally, you'll want a helper function to allow for recursion
size_t
mergeSort (vector<int>& v);

// Perform a quicksort on 'v'
// Return the number of comparisons performed
// Additionally, you'll want a helper function to allow for recursion
size_t
quickSort (vector<int>& v);

// Quick Sort helper function, does the actual sorting and recursion
// returns the number of compares from the quickSort, or the numComparisons
// from an insertion sort if v.size() is <= 20
size_t
quickSort (vector<int>& v, size_t left, size_t right);

// Perform an insertion sort from 'begin' up to but NOT including 'end'
// Return the number of comparisons performed
size_t
insertionSort (vector<int>& v, size_t begin, size_t end);

// Perform a Shell sort
// Return the number of comparisons performed
size_t
shellSort (vector<int>& v);

// Do a median of 3 on vector v
// returns the pivot value
int
median3(vector<int>& v, size_t left, size_t right);

/************************************************************/

int 	 
main (int argc, char* argv[])
{

    cout << "N     	==> ";
    size_t N;
    cin >> N;

    vector<int> mergeVec;

    std::random_device randomFill;
    std::mt19937 generator(randomFill());
    std::uniform_int_distribution<int> dist(1,9999);

    Timer< > t;


    for (size_t i = 0; i < N; ++i)
   	 mergeVec.push_back(dist(generator));

/*
    for (size_t i = 0; i < N; ++i)
    {
   	 cout << mergeVec[i] << " ";
    }
    cout << "\n";
	*/
   	 

    vector<int> quickVec = mergeVec;
    vector<int> shellVec = mergeVec;
    vector<int> stdVec = mergeVec;

    t.start();
    size_t shellCompares = shellSort(quickVec);
    t.stop();
    printf("Quick time: %.2f ms \n", t.getElapsedMs());
    cout << "Quick compares: " << shellCompares << "\n";

/*
	t.start();
	size_t shellCompares = shellSort(shellVec);
	t.stop();
	printf("Shell time: %.2f ms \n", t.getElapsedMs());
    cout << "Shell compares: " << shellCompares << "\n";
	*/

    std::sort(stdVec.begin(), stdVec.end());

    if (quickVec == stdVec)
    {
   	 cout << "Sort ok? yes\n";
    }
    else
   	 cout << "Sort ok? no\n";
    
    


    return EXIT_SUCCESS;
}

/************************************************************/
/*
size_t
quickSort(vector<int>& v)
{
    return quickSort(v, 0, v.size());
}
*/


/************************************************************/
/*
size_t
quickSort (vector<int>& v, size_t left, size_t right)
{
    size_t numComparisons = 0;
    if (left + 10 <= right)
    {
   	 int pivot = median3(v, left, right-1);
   	 cout << "the pivot is: " << pivot << "\n";
   	 int i = left;
   	 int j = right - 1;

   	 for( ; ; )
   	 {
   		 while(v[++i] < pivot)
   		 {
   			 ++numComparisons;
   		 }

   		 while(pivot < v[--j])
   		 {
   			 ++numComparisons;
   		 }

   		 if (i < j)
   		 {
   			 swap(v[i], v[j]);
   			 ++numComparisons;
   		 }
   			 
   		 else
   			 break;
   	 }

   	 //restore pivot
   	 swap (v[i], v[right-1]);

   	 quickSort(v, left, i - 1);
   	 quickSort(v, i, right, numComparison);
    } else
   	 numComparisons += insertionSort(v, left, right);
    
    return numComparisons;
}
*/	


/************************************************************/

//works. Done
size_t
insertionSort (vector<int>& v, size_t begin, size_t end)
{
size_t numComparisons = 0;
for (size_t i = begin; i < end; ++i)
{
	int k = v[i];
   	size_t j = i;
	if (j >= 1)
	{
   		while (k < v[j - 1])
   		{
   			v[j] = v[j - 1];

   			--j;
   		}
		++numComparisons;  

   	v[j] = k;
	}
}
    return numComparisons;
}    

/************************************************************/
int
median3(vector<int>& v, size_t left, size_t right)
{
    int center = (left + right) / 2;

    cout << "left: " << v[left] << "\n";
    cout << "right: " << v[right] << "\n";
    cout << "center: " << v[center] << "\n";
    

    if (v[center] < v[left])
   	 swap(v[left], v[center]);

    if (v[right] < v[left])
   	 swap(v[left], v[right]);

    if (v[right] < v[center])
   	 swap(v[center], v[right]);

    swap(v[center], v[right-1]);
    cout << "Pivot Location: " << v[right - 1] << "\n";
    return v[right-1];
}

/************************************************************/
size_t
shellSort (vector<int>& v)
{
size_t numCompares = 0;
size_t temp;
int h = 1;

for (int h = 1; h <= v.size()/6; h = 3*h+1)
{

}
	while (h > 0)
	{
		for  (size_t i = 1; i < v.size(); ++i)
		{
			temp = v[i];
			int j = i;
			while (j >= 1 && temp < v[j-1])
			{
		 		++numCompares;
		 		v[j] = v[j-h];
		 		--j;
			}
		v[j] = temp;
		}
	h = h/3;
	}
	 
return numCompares;
}
