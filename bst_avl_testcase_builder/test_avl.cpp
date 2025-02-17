#include "check_avl.h"

#include <gtest/gtest.h>

#include <set>

TEST(AVL, SampleCase)
{
	//Initialize tree
	AVLTree<std::string, std::string> testTree;

	//Perform operations on the tree
	testTree.insert(std::make_pair("test", "value"));

	//Checks the structure of the tree
	EXPECT_TRUE(verifyAVL(testTree));

	//Perform additional checks
	EXPECT_EQ("value", testTree.find("test")->second);
}

TEST(AVL, Random50InsertRemove)
{
	srand(0);

	AVLTree<int, int> testTree;
	std::set<int> items;

	//Add 50 items
	for(size_t counter = 0; counter < 50; counter++)
	{
		int random = rand();
		testTree.insert(std::make_pair(random, random));
		items.insert(random);
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
	for(auto it = items.begin(); it != items.end(); it++)
	{
		EXPECT_EQ(*it, testTree.find(*it)->second);
	}

	//Remove Items
	for(auto it = items.begin(); it != items.end(); it++)
	{
		testTree.remove(*it);
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.empty());

}