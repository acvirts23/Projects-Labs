/*
 Filename   : SearchTree.hpp
 Author     : Gary M. Zoppetti
 Course     : CSCI 362
 Description: Binary search tree class,
                a basis for implementing associative ADTs
 	like set and map.
*/

/************************************************************/
// Macro guard

#ifndef SEARCHTREE_HPP
#define SEARCHTREE_HPP

/************************************************************/
// System includes

#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations

using std::ostream;
using std::queue;

/************************************************************/

template<typename T>
struct Node
{
 using NodePtr = Node*;

 // DONE
 Node (const T& d = T ())
 :
   data(d),
   left(nullptr),
   right(nullptr),
   parent(nullptr)

 {
   // Initialize data, left, right, and parent in
   //   the member initialization list.
   // left, right, and parent should be set to nullptr.
   // The body of this constructor should be empty.
 }

 // DONE
 Node (const T& d, NodePtr l, NodePtr r, NodePtr p)
 :
   data(d),
   left(l),
   right(r),
   parent(p)
 {
   // Initialize data, left, right, and parent in
   //   the member initialization list.
   // The body of this constructor should be empty.
 }

 //**

 T        data;
 NodePtr  left;
 NodePtr  right;
 NodePtr  parent;
};

/************************************************************/

// Forward declaration
template <typename T>
class SearchTree;

/************************************************************/

template <typename T>
struct TreeIterator
{
 friend class SearchTree<T>;

 using Self = TreeIterator<T>;
 using NodePtr = Node<T>*;
 using ConstNodePtr = const Node<T>*;

 using difference_type = ptrdiff_t;
 using iterator_category = std::bidirectional_iterator_tag;

 using value_type = T;
 using pointer = const T*;
 using reference = const T&;

 TreeIterator ()
   : m_nodePtr ()
 { }

 explicit
 TreeIterator (ConstNodePtr n)
   : m_nodePtr (n)
 { }

 // TODO
 reference
 operator* () const
 {
   return m_nodePtr -> data;
 }

 // Return address of node's data member.
 pointer
 operator-> () const
 {
   return &*this;
 }

 // Pre-increment
 Self&
 operator++ ()
 {
   m_nodePtr = increment (m_nodePtr);
   return *this;
 }

 // Post-increment
 // TODO
 Self
 operator++ (int)
 {
   // Increment iterator so it points to in-order successor.
   // Return appropriate iterator.

   Self temp (*this);
   m_nodePtr = increment(m_nodePtr);
   return temp;
 }

 // Pre-decrement
 Self&
 operator-- ()
 {
   m_nodePtr = decrement (m_nodePtr);

   return *this;
 }

 // Post-decrement
 // TODO
 Self
 operator-- (int)
 {
   Self temp (*this);
   m_nodePtr = decrement(m_nodePtr);
   return temp;
 }

 bool
 operator== (const Self& i) const
 {
   return m_nodePtr == i.m_nodePtr;
 }

 bool
 operator!= (const Self& i) const
 {
   return m_nodePtr != i.m_nodePtr;
 }

private:
 //cases:
 //1: n->right exists and has no left, return n->right
 //2: n->right exists and has a left, return the leftmost of that subtree
 //3: n->right does not exist and parent->left == n, return parent
 //4: n->right does not exist and parent->left != n (n is in the right subtree), return first parent > n->data
 //  or return first parent whos parent == searchNode head, which means it is header

 static ConstNodePtr
 increment (ConstNodePtr n)
 {
   if (n->right != nullptr && n->right->left == nullptr)
   {
     return n -> right;
   }

   if (n->right != nullptr && n->right->left != nullptr)
   {
     n = n -> right;
     while (n -> left != nullptr)
       {
         n = n->left;
       }
     return n;
   }
  if (n->right == nullptr && n->parent -> left == n)
   {
     return n->parent;
   }

  if (n->right == nullptr && n->parent->left != n)
  {
   auto nextParent = n->parent;
  
   while (nextParent != nullptr)
   {
     if (nextParent->data > n->data)
       return nextParent;

      else
        nextParent = nextParent->parent;
   }
 
   }

 }

 // Return in-order predecessor of "n".
 static ConstNodePtr
 decrement (ConstNodePtr n)
 {
   if (n->left != nullptr)
   {
     n = n -> left;
     while (n->right != nullptr)
     {
       n = n->right;
     }
     return n;
   }

   if (n->parent->right == n)
   {
     return n->parent;
   }
   ConstNodePtr temp = n;
   while (temp->data >= n->data)
   {
     if (temp == temp->parent->parent)
     {
       return temp->parent;
     }
     temp = temp->parent;
   }
   return temp;
 }

 // FOR TESTING, otherwise would be PRIVATE
public:

 ConstNodePtr m_nodePtr;
};

/************************************************************/

template <typename T>
class SearchTree
{
 friend class TreeIterator<T>;

public:

 // DO NOT MODIFY type aliases!
 using value_type = T;
 using pointer =  T*;
 using const_pointer = const T*;
 using reference = T&;
 using const_reference = const T&;

 using iterator = TreeIterator<T>;
 using const_iterator = TreeIterator<T>;

 // Header parent points to root of tree or is nullptr
 //   if the tree is empty.
 // Header left points to LARGEST node or is nullptr
 //   if the tree is empty. 
 // Header right points to SMALLEST node or is nullptr
 //   if the tree is empty.
 // size represents the number of elements in the tree.
 SearchTree ()
   : m_header (), m_size (0)
 {
 }

 // Copy constructor
 // TODO
 SearchTree (const SearchTree& t)
 {
 }

 ~SearchTree ()
 {
   clear ();
 }

 // Return whether the tree is empty.
 // DONE
 bool
 empty () const
 {
   return m_size == 0;
 }

 // Return the size.
 // DONE
 size_t
 size () const
 {
   return m_size;
 }

 int
 depth () const
 {
   return depth (m_header.parent);
 }
  // Return an iterator pointing to the smallest element.
 // DONE
 iterator
 begin ()
 {
   return iterator(m_header.right);
 }

 // DONE
 const_iterator
 begin () const
 {
   return const_iterator(m_header.right);
 }

 // Return an iterator pointing one beyond the last element,
 //   i.e. the header node.
 // DONE
 iterator
 end ()
 {
   return iterator(&m_header);
 }

 // DONE
 const_iterator
 end () const
 {
   return const_iterator(&m_header);
 }

 iterator
 find (const T& v) const
 {
   // Call private helper method
   ConstNodePtr n = findHelper (v);
   if (n == nullptr)
   {
     // Wasn't found so return end ()
     n = &m_header;
   }
   return iterator (n);
 }

 std::pair<iterator, bool>
 insert (const T& v)
 {
   NodePtr insertedNode = insert (v, m_header.parent, &m_header);
   bool inserted = insertedNode != nullptr;
   if (inserted)
   {
     // Update header right to point to smallest node
     if (m_header.right == nullptr || v < m_header.right->data)
       m_header.right = insertedNode;
     // Update header left to point to largest node
     if (m_header.left == nullptr || v > m_header.left->data)
       m_header.left = insertedNode;
   }

   return { iterator (insertedNode), inserted };
 }

 size_t
 erase (const T& v)
 {
   // Update header right to point to smallest node
   if (m_header.right != nullptr && v == m_header.right->data)
     m_header.right =
       const_cast<NodePtr> (iterator::increment (m_header.right));
   // Update header left to point to largest node
   else if (m_header.left != nullptr && v == m_header.left->data)
     m_header.left =
       const_cast<NodePtr> (iterator::decrement (m_header.left));
  
   bool erased = erase (v, m_header.parent, &m_header);
   // If we erased the last value set header left and right to nullptr
   if (erased && empty ())
     m_header.left = m_header.right = nullptr;
  
   return erased ? 1 : 0;
 }

 // Delete all nodes, set header's parent, left, and right links to nullptr,
 //   and set size to 0. Utilizes a private, recursive "clear"
 //   declared below.
 // TODO
 void
 clear ()
 {
 }

 void
 printInOrder (ostream& out) const
 {
   printInOrder (out, m_header.parent);
 }

 void
 printLevelOrder (ostream& out) const
 {
   printLevelOrder (out, m_header.parent);
 }

private:

 using Node = struct Node<T>;
 using NodePtr = Node*;
 using ConstNodePtr = const Node*;

 int
 depth (ConstNodePtr r) const
 {
   if (r == nullptr)
     return -1;
   return std::max (depth (r->left), depth (r->right)) + 1;
 }

 // DONE
 NodePtr
 minimum (NodePtr r) const
 {
   if (r -> left != nullptr)
   {
     minimum(r -> left);
   }
   return r;
 }

 // DONE
 NodePtr
 maximum (NodePtr r) const
 {
   if (r -> right != nullptr)
   {
     maximum(r -> right);
   }
   return r;
 }

 // DONE
 ConstNodePtr
 findHelper (const T& v) const
 {
   auto r = m_header.parent;

   while (r != nullptr)
   {
     if (v == r -> data)
       return r;
     else if (v < r -> data)
       r = r -> left;
     else
       r = r -> right;
   }
  
   return nullptr;
 }

 // Insert "v" into the tree rooted at "r".
   // Use "parent" for recursion and setting the parent of the
   //   node containing "v".
 NodePtr
 insert (const T& v, NodePtr& r, NodePtr parent)
 {
   if (r == nullptr)
   {
     Node* root = new Node(v,nullptr,nullptr,parent);
     r = root;
     ++m_size;
     return r;
   }

   if (v < r->data)
   {
     insert(v,r->left,r);
   }
   else if (v > r->data)
   {
     insert(v,r->right,r);
   }

   else
     return nullptr;
 }

 // Erase "v" from the tree rooted at "r".
 // Use "parent" for recursion and updating the parent of the
 //   node containing "v".
 // Return whether the erase succeeded or not.
 bool
 erase (const T& v, NodePtr& r, NodePtr parent)
 {
   

   return r;
 }

 // TODO
 void
 clear (NodePtr r)
 {
   if (r == nullptr)
     return;
  
 }

 void
 printInOrder (ostream& out, NodePtr r) const
 {
   if (r != nullptr)
   {
     printInOrder (out, r->left);
     out << r->data << " ";
     printInOrder (out, r->right);
   }
 }

 // TODO
 // FIXME: This routine is INCORRECT and is only meant to
 //   show you some techniques you MAY want to employ.
 // Rewrite this method to output elements in the form required
 //   by the operator<< below.
 void
 printLevelOrder (ostream& out, NodePtr r) const
 {
   queue<NodePtr> q;
   q.push (r);
   while (!q.empty ())
   {
     r = q.front ();
     q.pop ();
     out << r->data << " ";
     if (r->left != nullptr)
       q.push (r->left);
     if (r->right != nullptr)
       q.push (r->right);
   }
 }

private:

 Node   m_header;
 size_t m_size;
};

/************************************************************/

// Output tree as [ e1 e2 e3 ... en ]
//   with a '|' to indicate the end of a level,
//   and a '-' to indicate a missing node.
// E.g., the tree
//       4
//    2     7
//         6
// should be printed EXACTLY like so: [ 4 | 2 7 | - - 6 - ]
// ONLY print the levels that exist, and ensure each level contains
//   2^k entries (a T object or "-"), where "k" is the level number.
template<typename T>
ostream&
operator<< (ostream& out, const SearchTree<T>& tree)
{
 out << "[ ";
 // For the version you submit, ensure you are using "printLevelOrder"!
 // You may find "printInOrder" useful for early testing, since it's
 //   been written for you.
 //tree.printInOrder (out);
 tree.printLevelOrder (out);
 out << "]";

 return out;
}

/************************************************************/

#endif

/************************************************************/
