/*
 Filename   : ArrayDriver.cc
 Author     : Andrew Virts
 Course     : CSCI 362-02
 Assignment : N/A
 Description: Test some, but NOT ALL, methods of the Array class.
*/  

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <cassert>

/************************************************************/
// Local includes

#include "Array.hpp"

/************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::string;
using std::ostringstream;

/************************************************************/
// Function prototypes/global vars/typedefs

void
printTestResult (const string& test,
 	const string& expected,
 	const ostringstream& actual);

/************************************************************/

int     
main (int argc, char* argv[])
{       
 Array<int> A;

 // For holding the actual result
 ostringstream output;
 // Put the actual result into the output stream
 output << A;
 printTestResult ("no-arg ctor", "[ ]", output);

 // Must clear the output stream each time
 output.str ("");
 output << A.empty ();
 // "1" for true, "0" for false
 printTestResult ("empty", "1", output);
 A.push_back (5);
 A.push_back (10);
 A.push_back (15);

 output.str ("");
 output << A;
 printTestResult ("push_back", "[ 5 10 15 ]", output);

 output.str ("");
 output << A.size ();
 printTestResult ("size", "3", output);
 A.pop_back ();
 A.pop_back ();

 output.str ("");
 output << A;
 printTestResult ("pop_back", "[ 5 ]", output);

 /************************************************************/
 // Convert the following tests to use printTestResult
 /************************************************************/
 for (int i = 0; i < 10; ++i)
   A.insert (A.begin (), i);
 
 //insert
 output.str ("");
 output << A;
 printTestResult ("Insert", "[ 9 8 7 6 5 4 3 2 1 0 5 ]", output);

 //erase
 for (Array<int>::iterator i = A.begin (); i != A.end (); )
   i = A.erase (i);

 output.str("");
 output << A;
 printTestResult ("Erase", "[ ]", output);

 // Size ctor, with a fill value.
 Array<int> B (3, 9);
 
 output.str("");
 output << B;
 printTestResult ("Size ctor", "[ 9 9 9 ]", output);

 // Range ctor.
 Array<int> C (B.begin (), B.begin () + 2);

 output.str("");
 output << C;
 printTestResult ("Range ctor", "[ 9 9 ]", output);

 // Assignment operator.
 B = A;
\
output.str ("");
output << B;
printTestResult ("Assignment Operator", "[ ]", output);

 //insert at beginning
 for (int i = 0; i < 5; ++i)
   B.insert (B.begin (), i);

 output.str ("");
 output << B;
 printTestResult("Insert at beginning", "[ 4 3 2 1 0 ]", output);

 /************************************************************/
 // START WRITING YOUR TESTS HERE
 /************************************************************/

 // Test range ctor (a different case than I test above)
 Array<int> E;
 E.push_back (2);
 E.push_back (4);
 E.push_back (6);
 E.push_back (8);
 E.push_back (10);
 E.push_back (12);
 E.push_back (14);
 E.push_back (16);
 E.push_back (18);
 E.push_back (20);

 Array<int> D (E.begin (), E.begin () + 7);
 output.str ("");
 output << D;
 printTestResult("Range Ctor 2", "[ 2 4 6 8 10 12 14 ]", output);

 // Test copy ctor
 Array<int> F (D);
 output.str ("");
 output << F;
 printTestResult("Copy ctor", "[ 2 4 6 8 10 12 14 ]", output);

 // Test capacity
 output.str ("");
 output << F.capacity();
 printTestResult ("Capacity", "7", output);

 output.str ("");
 F.insert (F.end(), 15);
 output << F.capacity ();
 printTestResult ("Capacity 2", "14", output);

 // Test subscript operator
 output.str ("");
 output << F[4];
 printTestResult("Subscript Operator", "10", output);

 // Test reserve
 output.str ("");
 F.reserve (3);
 output << F.capacity ();
 printTestResult ("Reserve if space < capacity", "14", output);

 output.str ("");
 F.reserve (500);
 output << F.capacity ();
 printTestResult ("Reserve if space > capacity", "500", output);

 // Test resize
 Array<int> G;
 G.push_back (0);
 G.push_back (1);
 G.push_back (2);
 G.push_back (3);
 G.push_back (4);
 G.push_back (5);
 G.push_back (6);
 G.push_back (7);
 G.push_back (8);

 output.str ("");
 G.resize (5, 0);
 output << G;
 printTestResult ("Resize with size > newSize", "[ 0 1 2 3 4 ]", output);

 // Resize with newSize > size
 output.str ("");
 G.resize (12, 5);
 output << G;
 printTestResult ("Resize with newSize > size", "[ 0 1 2 3 4 5 5 5 5 5 5 5 ]", output);

 // Test dereferencing iterators
 output.str ("");
 output << *G.begin () + 5;
 printTestResult ("Dereferencing iterator", "5", output);

 // Test dereferencing const iterators
 const Array<int> W(G);
 output.str ("");
 output << *W.begin ();
 printTestResult ("Dereferencing const iterator", "0", output);

  return EXIT_SUCCESS;
}

/************************************************************/

void
printTestResult (const string& test,
 	const string& expected,
 	const ostringstream& actual)
{
 cout << "Test: " << test << endl;
 cout << "==========================" << endl;
 cout << "Expected: " << expected << endl;
 cout << "Actual  : " << actual.str () << endl;
 cout << "==========================" << endl << endl;

 // Ensure the two results are the same
 assert (expected == actual.str ());
}

/************************************************************/

