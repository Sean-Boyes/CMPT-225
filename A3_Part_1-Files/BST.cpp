/*
 * BST.cpp
 * 
 * Description: Binary Search Tree (BST) data collection ADT class.
 *              Link-based implementation.
 *
 * Class invariant: Duplicated elements are not allowed.
 *                  It is always a BST.
 * 
 * Author: Inspired from our textbook
 * Date of last modification: June 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this BST class.
// Why? Because we shall use these prototypes when creating our "marking"
// test driver. So, if our test driver cannot call the methods of you BST 
// class because the prototype of these public methods don't match, 
// we won't be able to successfully mark your assignment.

bool DEBUG = false;

void LOG(string debugMsg) {
   if (DEBUG) cout << debugMsg << endl;
}

/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {
     
	  // shallow copy
     root = aBST.root;
     elementCount = aBST.elementCount;
   }
   
   // Overloaded oeprator
   // Description: Assignment (=) operator: copy (assign) "rhs" BST 
   //              object to "this" BST object such that both objects
   //              are an exact, yet independent, copy of each other.
   void BST::operator=(const BST & rhs) {
      // must be empty first
      // deep copy
      BSTNode* rootNode = new BSTNode;
      root->element = rhs.root->element;
      elementCount = rhs.elementCount;
      rootNode->left = overloadedAssignmentR(rootNode->left, (BSTNode*)&rhs.root->left);
      rootNode->right = overloadedAssignmentR(rootNode->right, (BSTNode*)&rhs.root->right);
   }                
   
   BSTNode* BST::overloadedAssignmentR(BSTNode* lhsCurrent, const BSTNode* rhsCurrent) {
      if ((BST*)&rhsCurrent == nullptr) return nullptr;
      // pre-order traversal
      BSTNode* newNode = new BSTNode;
      newNode->element = rhsCurrent->element;
      lhsCurrent->left = overloadedAssignmentR(lhsCurrent->left, rhsCurrent->left); // go further down left
      lhsCurrent->right = overloadedAssignmentR(lhsCurrent->right, rhsCurrent->right); // go further down right
      return newNode; // go back up
   }

   // Destructor 
   BST::~BST() {
      // to do
      elementCount = 0;
      deconstructorR(root);
   }

   void BST::deconstructorR(BSTNode* current) {
      if (current == nullptr) return;
      deconstructorR(current->left);
      // delete node
      delete current;
      deconstructorR(current->right);
   }                
   
   
/* BST Public Interface */
 
   // Description: Returns the number of elements currently stored in the BST.   
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     
   
      // to do
      return elementCount;
   }

   // Description: Inserts an element into the BST.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the BST.
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the BST.
   // Exception: Throws the exception "UnableToInsertException" when "newElement" 
   //            cannot be inserted into the BST. 
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
  
      // to do
      // Throw exception if newElement is not a WordPair
      if (typeid(newElement) != typeid(WordPair)) {
         throw UnableToInsertException();
      }

      // Allocate memory
      LOG("creating new element");
      BSTNode* newNode = new BSTNode;
      newNode->element = newElement;

      // Cover empty case
      if (root == nullptr) {
         LOG("I am root");
         root = newNode;
         elementCount = 1;
         return;
      }
      // Begin recursion
      LOG("startign recursion");
      if (insertR(newNode, root) == false) {
         throw UnableToInsertException();
      }
      else {
         elementCount += 1;
      }

	  return;
	  
   } 
   
   // Description: Recursive insertion into a BST.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              BST. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
	  // to do

      // check root
      if (newBSTNode->element == current->element) {
         // Throw exception if newElement is already in BST
         LOG("Thowing exception");
         throw ElementAlreadyExistsException();
      }
      // check right
      else if (newBSTNode->element > current->element) {
         LOG("[R] going right");
         if (current->right == nullptr) {
            LOG("[CR] connecting pointer to right");
            current->right = newBSTNode;
            return true;
         }
         // current = current->right;
         insertR(newBSTNode, current->right);
         return true;
      }
      // check left
      else {
         LOG("[L] going left");
         if (current->left == nullptr) {
            LOG("[CL] connecting pointer to left");
            current->left = newBSTNode;
            return true;
         }
         // current = current->left;
         insertR(newBSTNode, current->left);      
         return true;
      }
      // insert failed
      return false;
   }

   
   // Description: Retrieves "targetElement" from the BST.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: BST is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the BST is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the BST.
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(log2 n)
   /* Feel free to use the provided code below.
      You can add to it, if you find it necessary to do so,
	  or you can replace it using your own implementation. */ 
   WordPair& BST::retrieve(WordPair & targetElement) const {
      
     if (elementCount == 0)  
        throw EmptyDataCollectionException("BST is empty.");
	
     WordPair& translated = retrieveR(targetElement, root);
	 
     return translated;
   }

   // Description: Recursive retrieval from a BST.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the BST.
   // Postcondition: This method does not change the BST.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {

	  // to do
      if (targetElement == current->element) {
         return current->element;
      }
      else if (targetElement > current->element){
         // check right
         if (current->right == nullptr) {
            throw ElementDoesNotExistException();
         }
         // current = current->right;
         return retrieveR(targetElement, current->right);
      }
      else {
         // check left
         if (current->left == nullptr) {
            throw ElementDoesNotExistException();
         }
         // current = current->left;
         return retrieveR(targetElement, current->left);      
      }

   }  
   
   // Description: Traverses the BST in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: BST is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the BST is empty.
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(n) 
   /* Feel free to use the provided code below.
      You can add to it, if you find it necessary to do so,
	  or you can replace it using your own implementation. */   
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
     if (elementCount == 0)  
       throw EmptyDataCollectionException("BST is empty.");

     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive "in order" traversal of a BST.   
   // Postcondition: This method does not change the BST. 
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
   
	  // to do 
      if (current == nullptr) return;
      traverseInOrderR(visit, current->left);
      visit(current->element);
      traverseInOrderR(visit, current->right);
   }