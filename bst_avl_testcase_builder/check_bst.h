// check_bst.h - implements functions to check that BSTs are correct and valid

#ifndef CHECK_BST_H
#define CHECK_BST_H

#include "publicified_bst.h"

#include <gtest/gtest.h>

#include <set>
#include <iostream>

// forward declarations
template<typename Key, typename Value>
testing::AssertionResult checkValidTraversal(Node<Key, Value>* current);

/* Verifies that tree is a valid binary tree.
   That is, each node is greater than its
   predecessor in the tree structure, and
   the parent->child and child->parent pointers
   of all nodes match up.

   This function should **gracefully**
   deal with errors in the tree structure, and
   print a helpful error message telling the user
   what is wring when it finds one.

   Return value is true if the tree is valid, and false if it is not.
*/
template<typename Key, typename Value>
testing::AssertionResult isValidTree(BinarySearchTree<Key, Value> & tree)
{
	// empty trees are always valid
	if(tree.root_ == nullptr)
	{
		return testing::AssertionSuccess();
	}
	else
	{
		return checkValidTraversal(tree.root_);
	}
}

// author credit: Chris Hailey
template<typename Key, typename Value>
testing::AssertionResult checkValidTraversal(Node<Key, Value>* current)
{
		if(current->getLeft()!=NULL){
			if(!(current->getLeft()->getKey() < current->getKey())){
				return testing::AssertionFailure() << "The left child of "<<current->getKey()<<" is "<<current->getLeft()->getKey()<<" which is larger than its parent and not allowed for a left child in a BST";
			}
			if(current->getLeft()->getParent()!=current){
				return testing::AssertionFailure() <<"The left child of "<<current->getKey()<<" does not have its parent set correctly";
			}
			Node<Key, Value>* predecessor = current->getLeft();
			while(predecessor->getRight()!=NULL){
				predecessor = predecessor->getRight();
			}
			if(!(predecessor->getKey()< current->getKey())){
				return testing::AssertionFailure() << "The predecessor of "<<current->getKey()<<" is "<< predecessor->getKey()<<" which is larger than what it is predecessing";
			}

			testing::AssertionResult traversalResult = checkValidTraversal(current->getLeft());

			if(!traversalResult){
				return traversalResult;
			}
		}
		if(current->getRight()!=NULL)
		{
			if(!(current->getKey() < current->getRight()->getKey()))
			{
				return testing::AssertionFailure() << "The right child of "<<current->getKey()<<" is "<<current->getRight()->getKey()<<" which is less than its parent and not allowed for a right child";
			}
			if(current->getRight()->getParent()!=current)
			{
				return testing::AssertionFailure() << "the right child of "<<current->getKey()<<" does not have its parent set correctly";
			}

			testing::AssertionResult traversalResult = checkValidTraversal(current->getRight());

			if(!traversalResult)
			{
				return traversalResult;
			}
		}

		return testing::AssertionSuccess();
}

/* Top-level testing function.
   Makes sure that the passed tree is valid and consistent,
   and prints an error if it is not.

   Returns true iff there are no errors.
*/ 
template<typename Key, typename Value>
testing::AssertionResult verifyBST(BinarySearchTree<Key, Value> & tree)
{
	testing::AssertionResult validResult = isValidTree(tree);

	if(!validResult)
	{
		std::cerr << ">> Binary tree structure is broken!" << std::endl;
		std::cerr << ">> Tree was:" << std::endl;
		tree.print();
		return validResult;
	}

	return testing::AssertionSuccess();

}

#endif
