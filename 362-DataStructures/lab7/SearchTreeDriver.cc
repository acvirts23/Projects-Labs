/*
  Filename   : Hello.cc
  Author     : Gary M. Zoppetti
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Beginning C++ program for Java folks new to 
               the language
*/

/**********************************************************/
// System includes

#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>


/**********************************************************/
// Local includes
#include "SearchTree.hpp"

/**********************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::iterator;

/**********************************************************/
// Function prototypes/global vars/typedefs

/**********************************************************/

int
main (int argc, char* argv[]) 
{
  SearchTree<int> tree;


  //TEST 1

  cout << "Test 1 testing empty\n";
  
  if (tree.empty() == true)
  {
    cout << "is empty = true\n";
  }
   else
    cout << "is not empty = true\n";

  tree.insert(4);

  cout << "tree size is: " << tree.size() << "\n";

  tree.insert(2);
  tree.insert(7);
  tree.insert(6);
  tree.insert(1);

   SearchTree<int>::iterator iter = tree.begin();
   iter.m_nodePtr->data;

  cout << "tree size after 4 inserts is: " << tree.size() << "\n";
  cout << "Value of iterator i is: " << iter.m_nodePtr->data << "\n";


  ++iter;
  cout << "Value of iterator i after increment is: " 
    << iter.m_nodePtr->data << "\n";
  ++iter;

  cout << "Value of iterator i after increment is: " 
    << iter.m_nodePtr->data << "\n";

  ++iter;

  cout << "Value of iterator i after increment is: " 
    << iter.m_nodePtr->data << "\n";

  ++iter;

  cout << "Value of iterator i after increment is: " 
    << iter.m_nodePtr->data << "\n";

    --iter;
    cout << "Value of iterator i after decrement is: " 
    << iter.m_nodePtr->data << "\n";

    --iter;
    cout << "Value of iterator i after decrement is: " 
    << iter.m_nodePtr->data << "\n";

    --iter;
    cout << "Value of iterator i after decrement is: " 
    << iter.m_nodePtr->data << "\n";

    

  
  return EXIT_SUCCESS; 
}

/**********************************************************/
// Function implementations