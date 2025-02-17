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
TEST(AVL, Random1000InsertRemove)
{
	srand(0);

	AVLTree<int, int> testTree;
	std::set<int> items;

	//Add 50 items
	for(size_t counter = 0; counter < 1000; counter++)
	{
		int random = rand();
		testTree.insert(std::make_pair(random, random));
		items.insert(random);
		EXPECT_TRUE(verifyAVL(testTree));
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
	for(auto it = items.begin(); it != items.end(); it++)
	{
		EXPECT_EQ(*it, testTree.find(*it)->second);
	}

	// Remove Items
	for(auto it = items.begin(); it != items.end(); it++)
	{
		
		testTree.remove(*it);
		//std::cout << "testTree.remove(" << *it << "); " << std::endl;
		EXPECT_TRUE(verifyAVL(testTree));
		// verifies each remove
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.empty());

}

TEST(AVL, SlideInsertion0){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(20,1));
	avl.insert(std::make_pair(30,1)); // should cause zig zig
	avl.insert(std::make_pair(15,1));
	avl.insert(std::make_pair(25,1));
	avl.insert(std::make_pair(12,1)); // should cause zig zag
	avl.insert(std::make_pair(5,1));
	avl.insert(std::make_pair(3,1)); // zig zig
	avl.insert(std::make_pair(8,1)); // zig zag

	// verifying entire tree both directions
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(20, avl.root_->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getKey()); // 10
	EXPECT_EQ(20, avl.root_->getLeft()->getParent()->getKey()); // 10->parent
	EXPECT_EQ(30, avl.root_->getRight()->getKey()); // 30
	EXPECT_EQ(20, avl.root_->getRight()->getParent()->getKey()); // 30->parent

	Node<int, int>* leftRoot =  avl.root_->getLeft(); // 30
	Node<int, int>* rightRoot =  avl.root_->getRight(); // 10
	// 10 links
	EXPECT_EQ(5, leftRoot->getLeft()->getKey());
	EXPECT_EQ(12, leftRoot->getRight()->getKey());
	EXPECT_EQ(leftRoot, leftRoot->getLeft()->getParent());
	EXPECT_EQ(leftRoot, leftRoot->getRight()->getParent());
	// 30 links
	EXPECT_EQ(25, rightRoot->getLeft()->getKey());
	EXPECT_EQ(nullptr, rightRoot->getRight());
	EXPECT_EQ(rightRoot, rightRoot->getLeft()->getParent());
	
	Node<int, int>* leftNode = leftRoot->getLeft(); // 5
	Node<int, int>* rightNode = leftRoot->getRight(); // 12
	// 5 links
	EXPECT_EQ(3, leftNode->getLeft()->getKey());
	EXPECT_EQ(8, leftNode->getRight()->getKey());
	EXPECT_EQ(5, leftNode->getLeft()->getParent()->getKey());
	EXPECT_EQ(5, leftNode->getRight()->getParent()->getKey());
	// 12 links
	EXPECT_EQ(nullptr, rightNode->getLeft());
	EXPECT_EQ(15, rightNode->getRight()->getKey());
	EXPECT_EQ(rightNode, rightNode->getRight()->getParent());
}
TEST(AVL, SlideInsertion1){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(20,1));
	avl.insert(std::make_pair(30,1)); // should cause zig zig
	avl.insert(std::make_pair(15,1));
	avl.insert(std::make_pair(25,1));
	avl.insert(std::make_pair(12,1)); // should cause zig zag
	avl.insert(std::make_pair(5,1));
	avl.insert(std::make_pair(3,1)); // zig zig
	avl.insert(std::make_pair(8,1)); // zig zag
	avl.insert(std::make_pair(28,1)); // zig zag

	// verifying entire tree both directions
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(20, avl.root_->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getKey()); // 10
	EXPECT_EQ(20, avl.root_->getLeft()->getParent()->getKey()); // 10->parent
	EXPECT_EQ(28, avl.root_->getRight()->getKey()); // 29
	EXPECT_EQ(20, avl.root_->getRight()->getParent()->getKey()); // 30->parent

	Node<int, int>* leftRoot =  avl.root_->getLeft(); // 28
	Node<int, int>* rightRoot =  avl.root_->getRight(); // 10
	// 10 links
	EXPECT_EQ(5, leftRoot->getLeft()->getKey());
	EXPECT_EQ(12, leftRoot->getRight()->getKey());
	EXPECT_EQ(leftRoot, leftRoot->getLeft()->getParent());
	EXPECT_EQ(leftRoot, leftRoot->getRight()->getParent());
	// 28 links
	EXPECT_EQ(25, rightRoot->getLeft()->getKey());
	EXPECT_EQ(30, rightRoot->getRight()->getKey());
	EXPECT_EQ(rightRoot, rightRoot->getLeft()->getParent());
	EXPECT_EQ(rightRoot, rightRoot->getRight()->getParent());
	
	Node<int, int>* leftNode = leftRoot->getLeft(); // 5
	Node<int, int>* rightNode = leftRoot->getRight(); // 12

	EXPECT_EQ(3, leftNode->getLeft()->getKey());
	EXPECT_EQ(8, leftNode->getRight()->getKey());
	EXPECT_EQ(5, leftNode->getLeft()->getParent()->getKey());
	EXPECT_EQ(5, leftNode->getRight()->getParent()->getKey());
	// 12 links
	EXPECT_EQ(nullptr, rightNode->getLeft());
	EXPECT_EQ(15, rightNode->getRight()->getKey());
	EXPECT_EQ(rightNode, rightNode->getRight()->getParent());
}
TEST(AVL, SlideInsertion2){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(20,1));
	avl.insert(std::make_pair(30,1)); // should cause zig zig
	avl.insert(std::make_pair(15,1));
	avl.insert(std::make_pair(25,1));
	avl.insert(std::make_pair(12,1)); // should cause zig zag
	avl.insert(std::make_pair(5,1));
	avl.insert(std::make_pair(3,1)); // zig zig
	avl.insert(std::make_pair(8,1)); // zig zag
	avl.insert(std::make_pair(28,1)); // zig zag
	avl.insert(std::make_pair(17,1)); // zig zig

	// verifying entire tree both directions
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(20, avl.root_->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getKey()); // 10
	EXPECT_EQ(20, avl.root_->getLeft()->getParent()->getKey()); // 10->parent
	EXPECT_EQ(28, avl.root_->getRight()->getKey()); // 29
	EXPECT_EQ(20, avl.root_->getRight()->getParent()->getKey()); // 30->parent

	Node<int, int>* leftRoot =  avl.root_->getLeft(); // 28
	Node<int, int>* rightRoot =  avl.root_->getRight(); // 10
	// 10 links
	EXPECT_EQ(5, leftRoot->getLeft()->getKey());
	EXPECT_EQ(15, leftRoot->getRight()->getKey());
	EXPECT_EQ(leftRoot, leftRoot->getLeft()->getParent());
	EXPECT_EQ(leftRoot, leftRoot->getRight()->getParent());
	// 28 links
	EXPECT_EQ(25, rightRoot->getLeft()->getKey());
	EXPECT_EQ(30, rightRoot->getRight()->getKey());
	EXPECT_EQ(rightRoot, rightRoot->getLeft()->getParent());
	EXPECT_EQ(rightRoot, rightRoot->getRight()->getParent());
	
	Node<int, int>* leftNode = leftRoot->getLeft(); // 5
	Node<int, int>* rightNode = leftRoot->getRight(); // 15

	EXPECT_EQ(3, leftNode->getLeft()->getKey());
	EXPECT_EQ(8, leftNode->getRight()->getKey());
	EXPECT_EQ(5, leftNode->getLeft()->getParent()->getKey());
	EXPECT_EQ(5, leftNode->getRight()->getParent()->getKey());
	// 15 links
	EXPECT_EQ(12, rightNode->getLeft()->getKey());
	EXPECT_EQ(17, rightNode->getRight()->getKey());
	EXPECT_EQ(rightNode, rightNode->getRight()->getParent());
	EXPECT_EQ(rightNode, rightNode->getLeft()->getParent());
}
TEST(AVL, SlideInsertion3){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(20,1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(30,1)); // should cause zig zig
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(15,1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(25,1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(12,1)); // should cause zig zag
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(5,1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(3,1)); // zig zig
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(8,1)); // zig zag
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(28,1)); // zig zag
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(17,1)); // zig zig
	EXPECT_TRUE(verifyAVL(avl));
	avl.insert(std::make_pair(2,1)); // changes root!

	// verifying entire tree both directions
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(10, avl.root_->getKey());
	EXPECT_EQ(5, avl.root_->getLeft()->getKey()); // 5
	EXPECT_EQ(10, avl.root_->getLeft()->getParent()->getKey()); // 5->parent
	EXPECT_EQ(20, avl.root_->getRight()->getKey()); // 20
	EXPECT_EQ(10, avl.root_->getRight()->getParent()->getKey()); // 20->parent

	Node<int, int>* leftRoot =  avl.root_->getLeft(); // 5
	Node<int, int>* rightRoot =  avl.root_->getRight(); // 20
	// 5 links
	EXPECT_EQ(3, leftRoot->getLeft()->getKey());
	EXPECT_EQ(8, leftRoot->getRight()->getKey());
	EXPECT_EQ(leftRoot, leftRoot->getLeft()->getParent());
	EXPECT_EQ(leftRoot, leftRoot->getRight()->getParent());
	// 20 links
	EXPECT_EQ(15, rightRoot->getLeft()->getKey());
	EXPECT_EQ(28, rightRoot->getRight()->getKey());
	EXPECT_EQ(rightRoot, rightRoot->getLeft()->getParent());
	EXPECT_EQ(rightRoot, rightRoot->getRight()->getParent());
	
	Node<int, int>* leftNode = rightRoot->getLeft(); // 15
	Node<int, int>* rightNode = rightRoot->getRight(); // 28
	// 15 links
	EXPECT_EQ(12, leftNode->getLeft()->getKey());
	EXPECT_EQ(17, leftNode->getRight()->getKey());
	EXPECT_EQ(15, leftNode->getLeft()->getParent()->getKey());
	EXPECT_EQ(15, leftNode->getRight()->getParent()->getKey());
	// 28 links
	EXPECT_EQ(25, rightNode->getLeft()->getKey());
	EXPECT_EQ(30, rightNode->getRight()->getKey());
	EXPECT_EQ(rightNode, rightNode->getRight()->getParent());
	EXPECT_EQ(rightNode, rightNode->getLeft()->getParent());
	// 3 links
	leftNode = leftRoot->getLeft();
	EXPECT_EQ(2, leftNode->getLeft()->getKey());
	EXPECT_EQ(leftNode, leftNode->getLeft()->getParent());
}
TEST(AVL, SlideRemove0){
	// slide 42
	AVLTree<int, int> avl;

	avl.insert(std::make_pair(20, 1));
	avl.insert(std::make_pair(30, 1));
	avl.insert(std::make_pair(10, 1));
	avl.insert(std::make_pair(12, 1));
	avl.insert(std::make_pair(25, 1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(8, 1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.remove(30); // zig zig
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(10, avl.root_->getKey());
	EXPECT_EQ(5, avl.root_->getLeft()->getKey());
	EXPECT_EQ(20, avl.root_->getRight()->getKey());
	EXPECT_EQ(12, avl.root_->getRight()->getLeft()->getKey());

}
TEST(AVL, SlideRemove1){
	// slide 43
	AVLTree<int, int> avl;

	avl.insert(std::make_pair(20, 1));
	avl.insert(std::make_pair(22, 1));
	avl.insert(std::make_pair(10, 1));
	avl.insert(std::make_pair(12, 1));
	avl.insert(std::make_pair(25, 1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(11, 1));
	EXPECT_TRUE(verifyAVL(avl));
	avl.remove(20); // zig zag - left right
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(12, avl.root_->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getKey());
	EXPECT_EQ(22, avl.root_->getRight()->getKey());
	EXPECT_EQ(nullptr, avl.root_->getRight()->getLeft());

	// verify links in the up direction too
	EXPECT_EQ(nullptr, avl.root_->getParent());
	EXPECT_EQ(12, avl.root_->getLeft()->getParent()->getKey());
	EXPECT_EQ(12, avl.root_->getRight()->getParent()->getKey());
	EXPECT_EQ(11, avl.root_->getLeft()->getRight()->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getRight()->getParent()->getKey());

}
TEST(AVL, SlideRemove2){
	// slide 45
	AVLTree<int, int> avl;

	avl.insert(std::make_pair(20, 1));
	avl.insert(std::make_pair(30, 1));
	avl.insert(std::make_pair(10, 1));
	avl.insert(std::make_pair(15, 1));
	avl.insert(std::make_pair(25, 1));
	avl.insert(std::make_pair(8, 1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(35, 1));
	avl.insert(std::make_pair(28, 1));
	avl.insert(std::make_pair(12, 1));
	avl.insert(std::make_pair(17, 1));
	avl.insert(std::make_pair(14, 1));

	EXPECT_TRUE(verifyAVL(avl));
	avl.remove(8); // zig zag
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(20, avl.root_->getKey());
	EXPECT_EQ(12, avl.root_->getLeft()->getKey());
	EXPECT_EQ(30, avl.root_->getRight()->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getLeft()->getKey());
	EXPECT_EQ(15, avl.root_->getLeft()->getRight()->getKey());
}
TEST(AVL, SlideRemove3){
	// slide 46
	AVLTree<int, int> avl;

	avl.insert(std::make_pair(20, 1));
	avl.insert(std::make_pair(30, 1));
	avl.insert(std::make_pair(10, 1));
	avl.insert(std::make_pair(15, 1));
	avl.insert(std::make_pair(25, 1));
	avl.insert(std::make_pair(8, 1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(35, 1));
	avl.insert(std::make_pair(28, 1));
	avl.insert(std::make_pair(12, 1));
	avl.insert(std::make_pair(17, 1));
	avl.insert(std::make_pair(14, 1));

	EXPECT_TRUE(verifyAVL(avl));
	avl.remove(30); // zig zag
	EXPECT_TRUE(verifyAVL(avl));

	EXPECT_EQ(15, avl.root_->getKey());
	EXPECT_EQ(10, avl.root_->getLeft()->getKey());
	EXPECT_EQ(20, avl.root_->getRight()->getKey());
	EXPECT_EQ(17, avl.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(8, avl.root_->getLeft()->getLeft()->getKey());
	EXPECT_EQ(12, avl.root_->getLeft()->getRight()->getKey());
	EXPECT_EQ(14, avl.root_->getLeft()->getRight()->getRight()->getKey());
}
// testing remove normally
TEST(AVL, Insert1Remove1){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	EXPECT_TRUE(verifyAVL(avl));

    avl.remove(10);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_TRUE(avl.empty());

}
TEST(AVL, Insert2RRemove1C){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(20,1));
	EXPECT_TRUE(verifyAVL(avl));

    avl.remove(20);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(avl.end(), avl.find(20));
}
TEST(AVL, Insert2LRemove1C){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(5,1));
	EXPECT_TRUE(verifyAVL(avl));

    avl.remove(5);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(avl.end(), avl.find(5));
}
TEST(AVL, Insert2RRemove1R){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(20,1));
	EXPECT_TRUE(verifyAVL(avl));

    avl.remove(10);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(avl.end(), avl.find(10));
	EXPECT_EQ(20, avl.root_->getKey());
}
TEST(AVL, Insert2LRemove1R){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(5, 1));
	EXPECT_TRUE(verifyAVL(avl));

    avl.remove(10);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(avl.end(), avl.find(10));
	EXPECT_EQ(5, avl.root_->getKey());
}
TEST(AVL, SwapRemoveRoot0){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(20, 1));
	EXPECT_TRUE(verifyAVL(avl));

	avl.remove(10);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(20, avl.root_->getKey());
}
TEST(AVL, SwapRemoveRoot1){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(20, 1));
    avl.insert(std::make_pair(50, 1));
	EXPECT_TRUE(verifyAVL(avl));

    avl.remove(10);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(20, avl.root_->getKey());
}

// normal removes
// not gonna test basic case 0
// case 2 and 1
TEST(AVL, removeCase2_0){
	AVLTree<int, int> avl;
	// insert elements
	avl.insert(std::make_pair(10,1));
	avl.insert(std::make_pair(5, 1));
	avl.insert(std::make_pair(20, 1));

    avl.insert(std::make_pair(50, 1));
	avl.insert(std::make_pair(15, 1));
	EXPECT_TRUE(verifyAVL(avl));

	avl.remove(20);
	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_EQ(avl.end(), avl.find(20));
}

//random removes
TEST(AVL, insertRemove66){
	AVLTree<int, int> testTree;
	std::set<int> items;
    for(size_t counter = 0; counter < 66; counter++)
	{
		int random = rand();
		testTree.insert(std::make_pair(random, random));
		items.insert(random);
	}
	EXPECT_TRUE(verifyAVL(testTree));
    // testTree.print();
    int i = 0;
    for(auto it = items.begin(); it != items.end(); it++)
    {   
		testTree.remove(*it);
		EXPECT_TRUE(verifyAVL(testTree));
        ++i;
	}
}
// edge remove
TEST(AVL, rootRemove){
	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));

	testTree.remove(testTree.root_->getKey());

	EXPECT_TRUE(!testTree.empty());
	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.root_ != nullptr);
}

// Credit to nico and ignacio
TEST(AVL, Tiebreak){
	AVLTree<int,int> avl;

    avl.insert(std::make_pair(12,0));
    avl.insert(std::make_pair(6,0));
    avl.insert(std::make_pair(15,0));
    avl.insert(std::make_pair(3,0));
    avl.insert(std::make_pair(9,0));
    avl.insert(std::make_pair(14,0));
    avl.insert(std::make_pair(16,0));
    avl.insert(std::make_pair(2,0));
    avl.insert(std::make_pair(5,0));
    avl.insert(std::make_pair(8,0));
    avl.insert(std::make_pair(11,0));
    avl.insert(std::make_pair(13,0));
    avl.insert(std::make_pair(1,0));
    avl.insert(std::make_pair(4,0));
    avl.insert(std::make_pair(7,0));
    avl.insert(std::make_pair(10,0));
    avl.insert(std::make_pair(13,0));

    EXPECT_TRUE(verifyAVL(avl));

    avl.remove(16);
    EXPECT_TRUE(verifyAVL(avl));
}
TEST(AVL, doublerotationZIGZAGRIGHTBREAKTIES)
    {
	//Initialize tree
	AVLTree<int,int> avl;

	avl.insert(std::make_pair(24,0));
	avl.insert(std::make_pair(12,0));
	avl.insert(std::make_pair(29,0));
	avl.insert(std::make_pair(6,0));
	avl.insert(std::make_pair(18,0));
	avl.insert(std::make_pair(26,0));
	avl.insert(std::make_pair(30,0));
	avl.insert(std::make_pair(3,0));
	avl.insert(std::make_pair(9,0));
	avl.insert(std::make_pair(15,0));
	avl.insert(std::make_pair(21,0));
	avl.insert(std::make_pair(25,0));
	avl.insert(std::make_pair(28,0));
	avl.insert(std::make_pair(31,0));
	avl.insert(std::make_pair(2,0));
	avl.insert(std::make_pair(5,0));
	avl.insert(std::make_pair(8,0));
	avl.insert(std::make_pair(11,0));
	avl.insert(std::make_pair(14,0));
	avl.insert(std::make_pair(17,0));
	avl.insert(std::make_pair(20,0));
	avl.insert(std::make_pair(23,0));
	avl.insert(std::make_pair(27,0));
	avl.insert(std::make_pair(1,0));
	avl.insert(std::make_pair(4,0));
	avl.insert(std::make_pair(7,0));
	avl.insert(std::make_pair(10,0));
	avl.insert(std::make_pair(13,0));
	avl.insert(std::make_pair(16,0));
	avl.insert(std::make_pair(19,0));
	avl.insert(std::make_pair(22,0));

	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_TRUE(avl.isBalanced());

	avl.remove(25);


	//checking root
	EXPECT_EQ(12, avl.root_->getKey());


	//verifying if rotated correctly
	EXPECT_EQ(6, avl.root_->getLeft()->getKey());
	EXPECT_EQ(24, avl.root_->getRight()->getKey());
	EXPECT_EQ(18, avl.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(29, avl.root_->getRight()->getRight()->getKey());

	EXPECT_TRUE(avl.isBalanced());
}
TEST(AVL, InsertLeftRotationFull1)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Left Child of 170 (inerting 165)
	testTree.insert(std::make_pair(165,0));

	EXPECT_EQ(80, testTree.root_->getKey());

	//AVLNode<Key,Value>* NodeofInterest = testTree.root_;

	//verifying if Node 120 rotated correctly
	EXPECT_EQ(160, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(180, testTree.root_->getRight()->getRight()->getKey());
	
	//NodeofInterest = NodeofInterest->getRight()->getLeft();

	//Verifying if T1 is now the right child of Node 120
	EXPECT_EQ(140, testTree.root_->getRight()->getLeft()->getRight()->getKey());

	EXPECT_TRUE(testTree.isBalanced());


}
TEST(AVL, InsertLeftRotationFull2)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Right Child of 170 (inerting 175)
	testTree.insert(std::make_pair(175,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if Node 120 rotated correctly
	EXPECT_EQ(160, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(180, testTree.root_->getRight()->getRight()->getKey());
	
	//NodeofInterest = NodeofInterest->getRight()->getLeft();

	//Verifying if T1 is now the right child of Node 120
	EXPECT_EQ(140, testTree.root_->getRight()->getLeft()->getRight()->getKey());

	EXPECT_TRUE(testTree.isBalanced());


}
TEST(AVL, InsertLeftRotationFull3)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Left Child of 190 (inerting 185)
	testTree.insert(std::make_pair(185,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if Node 120 rotated correctly
	EXPECT_EQ(160, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(180, testTree.root_->getRight()->getRight()->getKey());
	
	//NodeofInterest = NodeofInterest->getRight()->getLeft();

	//Verifying if T1 is now the right child of Node 120
	EXPECT_EQ(140, testTree.root_->getRight()->getLeft()->getRight()->getKey());
	
	EXPECT_TRUE(testTree.isBalanced());


}
TEST(AVL, InsertLeftRotationFull4)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Right Child of 190 (inerting 195)
	testTree.insert(std::make_pair(195,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if Node 120 rotated correctly
	EXPECT_EQ(160, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(180, testTree.root_->getRight()->getRight()->getKey());
	
	//NodeofInterest = NodeofInterest->getRight()->getLeft();

	//Verifying if T1 is now the right child of Node 120
	EXPECT_EQ(140, testTree.root_->getRight()->getLeft()->getRight()->getKey());

	EXPECT_TRUE(testTree.isBalanced());


}
TEST(AVL, InsertRIGHTLEFTtRotationFull1)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Left Child of 130 (inerting 125)
	testTree.insert(std::make_pair(125,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if rotated correctly
	EXPECT_EQ(140, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(160, testTree.root_->getRight()->getRight()->getKey());
	
	//NodeofInterest = NodeofInterest->getRight()->getLeft();
	EXPECT_EQ(130, testTree.root_->getRight()->getLeft()->getRight()->getKey());
	EXPECT_EQ(125, testTree.root_->getRight()->getLeft()->getRight()->getLeft()->getKey());

	EXPECT_TRUE(testTree.isBalanced());



}
TEST(AVL, InsertRIGHTLEFTtRotationFull2)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Right Child of 130 (inerting 135)
	testTree.insert(std::make_pair(135,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if rotated correctly
	EXPECT_EQ(140, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(160, testTree.root_->getRight()->getRight()->getKey());
	
	//NodeofInterest = NodeofInterest->getRight()->getLeft();
	EXPECT_EQ(130, testTree.root_->getRight()->getLeft()->getRight()->getKey());
	EXPECT_EQ(135, testTree.root_->getRight()->getLeft()->getRight()->getRight()->getKey());


	EXPECT_TRUE(testTree.isBalanced());



}
TEST(AVL, InsertRIGHTLEFTtRotationFull3)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Left Child of 150 (inerting 145)
	testTree.insert(std::make_pair(145,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if rotated correctly
	EXPECT_EQ(140, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(160, testTree.root_->getRight()->getRight()->getKey());
	
	EXPECT_EQ(150, testTree.root_->getRight()->getRight()->getLeft()->getKey());
	EXPECT_EQ(145, testTree.root_->getRight()->getRight()->getLeft()->getLeft()->getKey());


	EXPECT_TRUE(testTree.isBalanced());

}
TEST(AVL, InsertRIGHTLEFTtRotationFull4)
{
	//Initialize tree

	AVLTree<int, int> testTree;

	testTree.insert(std::make_pair(80,0));
	testTree.insert(std::make_pair(40,0));
	testTree.insert(std::make_pair(120,0));
	testTree.insert(std::make_pair(20,0));
	testTree.insert(std::make_pair(60,0));
	testTree.insert(std::make_pair(100,0));
	testTree.insert(std::make_pair(160,0));
	testTree.insert(std::make_pair(10,0));
	testTree.insert(std::make_pair(30,0));
	testTree.insert(std::make_pair(50,0));
	testTree.insert(std::make_pair(70,0));
	testTree.insert(std::make_pair(90,0));
	testTree.insert(std::make_pair(110,0));
	testTree.insert(std::make_pair(140,0));
	testTree.insert(std::make_pair(180,0));
	testTree.insert(std::make_pair(130,0));
	testTree.insert(std::make_pair(150,0));
	testTree.insert(std::make_pair(170,0));
	testTree.insert(std::make_pair(190,0));

	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.isBalanced());


	//Inserting Right Child of 150 (inerting 155)
	testTree.insert(std::make_pair(155,0));

	EXPECT_EQ(80, testTree.root_->getKey());


	//verifying if rotated correctly
	EXPECT_EQ(140, testTree.root_->getRight()->getKey());
	EXPECT_EQ(120, testTree.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(160, testTree.root_->getRight()->getRight()->getKey());
	
	
	EXPECT_EQ(150, testTree.root_->getRight()->getRight()->getLeft()->getKey());
	EXPECT_EQ(155, testTree.root_->getRight()->getRight()->getLeft()->getRight()->getKey());


	EXPECT_TRUE(testTree.isBalanced());

}
TEST(AVL, DOUBELROTATIONwithBreakingTies)
{
	//Initialize tree
	AVLTree<int,int> avl;

    avl.insert(std::make_pair(12,0));
    avl.insert(std::make_pair(6,0));
    avl.insert(std::make_pair(15,0));
    avl.insert(std::make_pair(3,0));
    avl.insert(std::make_pair(9,0));
    avl.insert(std::make_pair(14,0));
    avl.insert(std::make_pair(16,0));
    avl.insert(std::make_pair(2,0));
    avl.insert(std::make_pair(5,0));
    avl.insert(std::make_pair(8,0));
    avl.insert(std::make_pair(11,0));
    avl.insert(std::make_pair(13,0));
    avl.insert(std::make_pair(1,0));
    avl.insert(std::make_pair(4,0));
    avl.insert(std::make_pair(7,0));
    avl.insert(std::make_pair(10,0));
    avl.insert(std::make_pair(13,0));

	EXPECT_TRUE(verifyAVL(avl));
	EXPECT_TRUE(avl.isBalanced());

    avl.remove(16);


	//checking root
	EXPECT_EQ(6, avl.root_->getKey());


	//verifying if rotated correctly
	EXPECT_EQ(3, avl.root_->getLeft()->getKey());
	EXPECT_EQ(12, avl.root_->getRight()->getKey());
	EXPECT_EQ(9, avl.root_->getRight()->getLeft()->getKey());
	EXPECT_EQ(14, avl.root_->getRight()->getRight()->getKey());
	EXPECT_EQ(15, avl.root_->getRight()->getRight()->getRight()->getKey());
	EXPECT_EQ(2, avl.root_->getLeft()->getLeft()->getKey());
	EXPECT_EQ(5, avl.root_->getLeft()->getRight()->getKey());

	EXPECT_TRUE(avl.isBalanced());

}
TEST(AVL, DuplicateInsertions) {
    AVLTree<int, int> testTree;

    testTree.insert(std::make_pair(10, 10));
    testTree.insert(std::make_pair(10, 11));

    ASSERT_TRUE(verifyAVL(testTree));

    auto node = testTree.find(10);
    ASSERT_NE(node, nullptr); // Ensure the node exists
    ASSERT_EQ(node->second, 11); 
}
TEST(AVL, DuplicateRemovals) {
	AVLTree<int, int> testTree;
	testTree.insert(std::make_pair(10, 10));
	testTree.remove(10);
	testTree.remove(10); // Duplicate removal
	ASSERT_TRUE(verifyAVL(testTree));
}
TEST(AVL, MixedRandomOperations) {
    AVLTree<int, int> testTree;
    std::set<int> items;
    srand(0);
    for (int i = 0; i < 100; ++i) {
        int random = rand();
        if (items.count(random)) {
            testTree.remove(random);
            items.erase(random);
        } else {
            testTree.insert(std::make_pair(random, random));
            items.insert(random);
        }
        ASSERT_TRUE(verifyAVL(testTree));
    }
}
TEST(AVL, LargeRandomInsertRemove) {
	srand(0);
	
	AVLTree<int, int> testTree;
	std::set<int> items;
	size_t numItems = 10000;

	for(size_t counter = 0; counter < numItems; counter++)
	{
		int random = rand();
		testTree.insert(std::make_pair(random, random));
		items.insert(random);
		EXPECT_TRUE(verifyAVL(testTree));
		//std::cout << "insert: " << counter << "\n";
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
	for(auto it = items.begin(); it != items.end(); it++)
	{
		EXPECT_EQ(*it, testTree.find(*it)->second);
	}

	//Remove Items
	int counter = 0;
	for(auto it = items.begin(); it != items.end(); it++)
	{	
		counter++;
		//std::cout << "remove: " << counter << "\n";
		testTree.remove(*it);
	}

	//Verify tree
	EXPECT_TRUE(verifyAVL(testTree));
	EXPECT_TRUE(testTree.empty());
}

TEST(AVL, InClassExcercise)
{
    // This is from Lecture 24: Splay Trees
    AVLTree<int,int> bob;
    
    bob.insert(std::make_pair(1,1));
    bob.insert(std::make_pair(2,2));
    bob.insert(std::make_pair(3,3)); // Should cause rotation
    bob.insert(std::make_pair(12,12)); 
    bob.insert(std::make_pair(9,9)); // Should cause a zig-zag
    bob.insert(std::make_pair(13,13)); // Should case rotation
    
    // Makes sure we balanced the tree correctly after inserting 13
    EXPECT_EQ(9, bob.root_->getKey());
    EXPECT_EQ(2, bob.root_->getLeft()->getKey());
    EXPECT_EQ(12, bob.root_->getRight()->getKey());

    bob.insert(std::make_pair(7,7));
    bob.insert(std::make_pair(4,4));
    bob.insert(std::make_pair(6,6));
    bob.insert(std::make_pair(5,5));
    bob.insert(std::make_pair(8,8));

    // Makes sure 8 is child of 7
    //EXPECT_EQ(8, bob.root_->getLeft()->getRight()->getRight()->getRight()->getKey());
    EXPECT_EQ(6, bob.root_->getKey());
    EXPECT_EQ(8, bob.root_->getRight()->getLeft()->getRight()->getKey());

    bob.remove(4);
    EXPECT_EQ(2, bob.root_->getLeft()->getKey()); // Makes sure we adjusted nodes right

    bob.remove(1);
    EXPECT_EQ(3, bob.root_->getLeft()->getKey());
    EXPECT_EQ(2, bob.root_->getLeft()->getLeft()->getKey());

    EXPECT_TRUE(bob.isBalanced());

    bob.insert(std::make_pair(1,1));
    bob.insert(std::make_pair(14,14));
    bob.insert(std::make_pair(11,11));

    bob.remove(3);
    EXPECT_EQ(9, bob.root_->getKey()); // Causes rotation and has 9 as the root again

    bob.remove(13);
    bob.remove(12);
    bob.remove(11);
    bob.remove(14);
    bob.remove(2);
    bob.remove(5);
    bob.remove(7);
    bob.remove(8);
    bob.remove(9);

}

TEST(AVL, Single_Rotate_Right)
{
	AVLTree<int, int> avl;

	avl.insert(std::make_pair(40,1));
	avl.insert(std::make_pair(30,1));
	avl.insert(std::make_pair(20, 1)); //causes zig-zig

	EXPECT_EQ(30, avl.root_->getKey());
	EXPECT_EQ(20, avl.root_->getLeft()->getKey());
	EXPECT_EQ(40, avl.root_->getRight()->getKey());

}
TEST(AVL, Single_Rotate_Left)
{
	AVLTree<int, int> avl;

	avl.insert(std::make_pair(20,1));
	avl.insert(std::make_pair(30,1));
	avl.insert(std::make_pair(40, 1)); //causes zig-zig

	EXPECT_EQ(30, avl.root_->getKey());
	EXPECT_EQ(20, avl.root_->getLeft()->getKey());
	EXPECT_EQ(40, avl.root_->getRight()->getKey());

}

//Jessica's Contribution
TEST(AVL, OGtest)
{
	AVLTree<int,int> testing;
    testing.insert(std::make_pair(10, 10));
    testing.insert(std::make_pair(12, 1));
    testing.insert(std::make_pair(8, 2));
    testing.insert(std::make_pair(15, 3));
    testing.insert(std::make_pair(18, 4));
	testing.insert(std::make_pair(11, 4));
	EXPECT_TRUE(testing.isBalanced());
	EXPECT_TRUE(verifyAVL(testing));
}
TEST(AVL, ZIGZIGSlideEx)
{
	AVLTree<int,int> testing;

	testing.insert(std::make_pair(20, 4));
    testing.insert(std::make_pair(10, 4));
    testing.insert(std::make_pair(30, 4));
    testing.insert(std::make_pair(25, 4));
    testing.insert(std::make_pair(5, 4));
    testing.insert(std::make_pair(12, 4));
    testing.insert(std::make_pair(8, 4));
    testing.remove(30);
	EXPECT_TRUE(testing.isBalanced());
	EXPECT_TRUE(verifyAVL(testing));
}
TEST(AVL, ZIGZAGinsert)
{
	AVLTree<int,int> testing;

	testing.insert(std::make_pair(10, 10));
    testing.insert(std::make_pair(12, 1));
    testing.insert(std::make_pair(6, 3));
    testing.insert(std::make_pair(8, 2));
    testing.insert(std::make_pair(4, 4));
    testing.insert(std::make_pair(9, 4));
	EXPECT_TRUE(testing.isBalanced());
	EXPECT_TRUE(verifyAVL(testing));
}
TEST(AVL, Remove)
{
	AVLTree<int,int> testing;
	testing.insert(std::make_pair(10, 4));  
    testing.insert(std::make_pair(12, 4));
    testing.insert(std::make_pair(6, 4));
    testing.insert(std::make_pair(14, 4));
    testing.insert(std::make_pair(8, 4));
    testing.insert(std::make_pair(4, 4));
    testing.insert(std::make_pair(9, 4));
    testing.insert(std::make_pair(2, 4));
    testing.remove(14);
	EXPECT_TRUE(testing.isBalanced());
	EXPECT_TRUE(verifyAVL(testing));
}
TEST(AVL, iVal74) 
{
    srand(74); 

    AVLTree<int, int> testTree;
    std::set<int> items;
    testTree.insert(std::make_pair(20,20));
    items.insert(20);
    testTree.insert(std::make_pair(25,25));
    items.insert(25);
    testTree.insert(std::make_pair(13,13));
    items.insert(13);
    testTree.insert(std::make_pair(15,15));
    items.insert(15);
    testTree.insert(std::make_pair(17,17));
    items.insert(17);
    testTree.insert(std::make_pair(19,19));
    items.insert(19);
    testTree.insert(std::make_pair(18,18));
    items.insert(18);

    //Verify tree
    EXPECT_TRUE(verifyAVL(testTree));

    for(auto it = items.begin(); it != items.end(); it++)
    {
        EXPECT_EQ(*it, testTree.find(*it)->second);

    }

    // Remove Items
    for(auto it = items.begin(); it != items.end(); it++)
    {
        testTree.remove(*it);
    }

    //Verify tree
    EXPECT_TRUE(verifyAVL(testTree));
    EXPECT_TRUE(testTree.empty());
}
TEST(AVL, stressTest2)
{
for (int i = 0; i < 100; i++)
{
    srand(i); 

    AVLTree<int, int> testTree;
    std::set<int> items;

    for(size_t counter = 0; counter < 6; counter++)
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

    // Remove Items
    for(auto it = items.begin(); it != items.end(); it++)
    {
        testTree.remove(*it);
    }

    //Verify tree
    EXPECT_TRUE(verifyAVL(testTree));
    EXPECT_TRUE(testTree.empty());
}
}
