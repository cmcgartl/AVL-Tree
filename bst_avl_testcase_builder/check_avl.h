//
// Auto-checker for AVL trees
//

#ifndef CS104_HW7_TEST_SUITE_CHECK_AVL_H
#define CS104_HW7_TEST_SUITE_CHECK_AVL_H

#include "publicified_avlbst.h"

#include <check_bst.h>

#include <algorithm>

template<typename Key, typename Value>
std::pair<int, testing::AssertionResult> verifyAVLBalanceRecursive(AVLTree<Key, Value> & tree, AVLNode<Key, Value>* currNode);

/**
 * Verifies that an AVL tree is in balance, and returns an assertion failure if any subtree is not.
 * @tparam Key
 * @tparam Value
 * @param tree
 * @return
 */
template<typename Key, typename Value>
testing::AssertionResult checkAVLBalance(AVLTree<Key, Value> & tree)
{
	return verifyAVLBalanceRecursive(tree, dynamic_cast<AVLNode<Key, Value>*>(tree.root_)).second;
}

// recursively checks that a subtree is balanced, and returns the height of the passed node.
// note: if a failure is returned, the height will not be correct, since it isn't needed in higher-up calls.
// This is similar to verifyBalanceRecursive(), but returns an error message if any subtree is out of balance showing where the issue is.
template<typename Key, typename Value>
std::pair<int, testing::AssertionResult> verifyAVLBalanceRecursive(AVLTree<Key, Value> & tree, AVLNode<Key, Value>* currNode)
{
	if (currNode == nullptr)
	{
		return std::make_pair(0, testing::AssertionSuccess());
	}

	std::pair<int, testing::AssertionResult> balanceResultsLeft = verifyAVLBalanceRecursive(tree, currNode->getLeft());
	if(!balanceResultsLeft.second)
	{
		return std::make_pair(0, balanceResultsLeft.second);
	}

	std::pair<int, testing::AssertionResult> balanceResultsRight = verifyAVLBalanceRecursive(tree, currNode->getRight());
	if(!balanceResultsRight.second)
	{
		return std::make_pair(0, balanceResultsRight.second);
	}

	if(std::abs(balanceResultsLeft.first - balanceResultsRight.first) < 2)
	{
		// this subtree is in balance

		int thisNodeHeight = std::max(balanceResultsLeft.first, balanceResultsRight.first) + 1;

		return std::make_pair(thisNodeHeight, testing::AssertionSuccess());
	}
	else
	{
		// this subtree is out of balance
		return std::make_pair(0, (testing::AssertionFailure() << "AVL balance error: subtree rooted at " << currNode->getKey() << " is out of balance!  Left child has height "
						   << balanceResultsLeft.first << ", and right child has height " << balanceResultsRight.first << "."));
	}
}

/* Top-level testing function.
   Makes sure that the passed tree is valid and consistent,
   and prints an error if it is not.

   Returns true iff there are no errors.
*/
template<typename Key, typename Value>
testing::AssertionResult verifyAVL(AVLTree<Key, Value> & tree)
{
	// first verify it as a BST
	testing::AssertionResult bstResult = verifyBST(tree);

	if(!bstResult)
	{
		return bstResult;
	}

	testing::AssertionResult balanceResult = checkAVLBalance(tree);
	if(!balanceResult)
	{
		std::cout << "Balance error!" << std::endl;
		std::cout << "Tree was: " << std::endl;
		tree.print();
	}

	return balanceResult;

}


#endif //CS104_HW7_TEST_SUITE_CHECK_AVL_H
