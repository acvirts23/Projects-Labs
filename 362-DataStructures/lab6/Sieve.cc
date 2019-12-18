/*
Filename   : Sieve.cc
Author     : Andrew C. Virts
Course     : CSCI 362-02
Assignment : Lab 6, Sieve of Eratosthenes
Description: Calculates the number of prime numbers from 0 to N 
and returns the amount of time it took to calculate
*/

/************************************************************/
// System includes

#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <string>
#include <iterator>
#include <iomanip>

/************************************************************/
// Local includes

#include "Timer.hpp"

/************************************************************/
// Using declarations

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::set;
using std::cerr;
using std::vector;
using std::string;
using std::stoul;
using std::setprecision;

/************************************************************/
// Function prototypes/global vars/type definitions

set<unsigned>
sieveSet (unsigned N);

set<unsigned>
sieveVector (unsigned N);

/************************************************************/

int
main (int argc, char* argv[])
{
    Timer<> T;
    if (argc != 3)
    {
      cerr << "Usage: " << argv[0] << " <Type> <Number>" << endl;
      exit (EXIT_FAILURE);
    }

    string arg1 (argv[1]);
    string arg2 (argv[2]);
    unsigned long N = stoul (arg2);
    if (arg1 == "set")
    {
        T.start();
        auto primeSet = sieveSet(N);
        T.stop();
        cout << endl;
        cout << "Pi[" << N << "] = " << primeSet.size() << " (using a set)" << endl;
        cout << "Time: " << setprecision(2) << T.getElapsedMs() << " ms\n";
    }

    if (arg1 == "vector")
    {
        T.start();
        auto primeVector = sieveVector(N);
        T.stop();
        cout << endl;
        cout << "Pi[" << N << "] = " << primeVector.size() << " (using a vector)" << endl;
        cout << "Time: " << T.getElapsedMs() << " ms\n";
    }
    cout << endl;
  
    return EXIT_SUCCESS;
}

/************************************************************/

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
set<unsigned>
sieveSet (unsigned N)
{
    set<unsigned> primeSet;
    for (unsigned i = 2; i <= N; ++i) 
    {
        primeSet.insert (i);
    }


    auto i = primeSet.begin();
    while (*i * *i <= N)
    {
        unsigned f = *i;
        for (unsigned j = *i; (j*f)<= N; ++j)
        {
            primeSet.erase(j*f);
        }
        ++i;
    }
    return primeSet;
}

/************************************************************/

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
set<unsigned>
sieveVector (unsigned N)
{
    set<unsigned> primeSet;

    vector<bool> primeVector (N);
    primeVector[0] = false;
    primeVector[1] = false;
    for (unsigned i = 2; i <= N; ++i) 
    {
        primeVector[i] = true;
    }

    unsigned num = 2;
    while (num * num <=N)
    {
        for (unsigned j = 2; (j * num) <= N; ++j)
        {
            if (primeVector[num * j] == true )
            {
                primeVector[num * j] = false;

            }
        }
        ++num;
    }

    for (unsigned i = 0; i < N; i++)
    {
        if (primeVector[i] == true)
        {
            primeSet.insert (i+2);
        }
    }
    return primeSet;
}



/*

  N       10,000,000    20,000,000   40,000,000
  =============================================
  set        2239.90       4810.81     10527.80
  vector      198.68        401.96       820.10

  The vector version of this program performed MUCH better and faster then the set version
  
*/
