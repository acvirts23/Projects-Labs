/*
  Filename   : RadixSort.cc
  Author     : Andrew Virts
  Course     : CSCI 362-02
  Assignment : Lab 5, radix sort
  Description:
*/

/************************************************************/
// System includes

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <queue>

/************************************************************/
// Local includes

#include "Timer.hpp"

/************************************************************/
// Using declarations

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::uniform_int_distribution;
using std::minstd_rand;

/************************************************************/
// Function prototypes/global vars/type definitions

void
radixSort (vector<int>& v, int maxDigits);

/************************************************************/

int
main (int argc, char* argv[])
{
  cout << endl;
  Timer<> timer;

  cout << "N ==> ";
  size_t N;
  cin >> N;

  cout << "d ==> ";
  int d;
  cin >> d;
  cout << endl;

  int boundary = pow (10,d)-1;
  minstd_rand gen(0);
  uniform_int_distribution<int> thing (0, boundary);
  vector<int> A(N);
  for (size_t i = 0; i < N; ++i)
  {
    A[i] = thing(gen);
  }

  vector<int> ACopy(A);

  timer.start();
  radixSort(A,d);
  timer.stop();
  cout << "Radix time:      " << timer.getElapsedMs() << " ms \n";

  timer.start();
  sort(ACopy.begin(), ACopy.end());
  timer.stop();
  cout << "std::sort time:  " << timer.getElapsedMs() << " ms \n";
  cout << endl;

  if (A == ACopy)
  {
    cout << "Sorted? yes\n";
  } 
  else
  {
    cout << "Sorted? no\n";
  }
}

/************************************************************/

void
radixSort (vector<int>& v, int maxDigits)
{
  vector<queue<int> > vec(10);
  int max = pow (10, maxDigits);

  for (size_t i = 1; i < max; i*=10)
  {
    for (size_t j = 0; j < v.size(); ++j)
    {
      vec[(v[j]/i) % 10].push(v[j]);
    }
    size_t start = 0;
    for (size_t k = 0; k < 10; ++k)
    {
      while ( !vec[k].empty() )
      {
        v[start] = vec[k].front();
        ++start;
        vec[k].pop();
      }
    }
  }
  
}

/*
  N      d=2       d=4      d=8      std (d=8)
  ====   =======   =======  =======  =========
  100e6  2418.51   4726.38  9365.97  xxx.xx
  200e6  4857.58   
  400e6  ...

  Discussion
  ==========
  ...



*/