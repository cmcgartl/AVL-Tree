# CS104 HW6 BST/AVL Test Builder

## An Introduction to Google Test (Gtest)

Gtest is a framework released by google for testing c++ programs. It is one of the tools we have been using to test your code, so it may look familiar from labs and testing suites.

Here is a sample gtest testcase:

```
TEST(BST, SampleCase)
{
	//Initialize tree
	BinarySearchTree<std::string, std::string> testTree;

	//Perform operations on the tree
	testTree.insert(std::make_pair("test", "value"));

	//Checks the structure of the tree
	EXPECT_TRUE(verifyBST(testTree));

	//Perform additional checks
	EXPECT_EQ("value", testTree.find("test")->second);
}
```

Let's break down the parts:
- `TEST(BST, SampleCase)` - this line defines the testcase. Although it looks a bit like a function, this is not c++ syntax and unique to Gtest. `TEST` is a macro that takes two "parameters": `BST` and `SampleCase`. The first parameter is the name of the test suite (generally the name of the class you are testing) and the second is the name of the testcase (should general describe what the testcase is testing).
- `BinarySearchTree<std::string, std::string> testTree;
   testTree.insert(std::make_pair("test", "value"));` - these lines are normal c++ code, here you perform operations on the object you are testing
- `EXPECT_EQ("value", testTree.find("test")->second);` - Here is a Gtest MACRO called `EXPECT_EQ`. It takes two parameters and checks to make sure that they are the same. If they are not, the testcase will fail and produce an error and outputs the values of the two parameters. In this case, the expected result of the find function call on the bst should be `value`
-  `EXPECT_TRUE(verifyBST(testTree));` - Here is another Gtest MACRO called `EXPECT_TRUE`. It takes one parameter checks to see if is passed into it is true and fails the testcase if it is not. We have written a verifyBST function that you can use (more details about what it does below) and it will return a true/false value in addition to an error message that Gtest will display on failure.

## Testcases
We have provided 4 testcases for you in the files `test_bst.cpp` and `test_avl.cpp`. You can add more testcases to those files. The `Sample` testcase is a simple testcase to show you how a testcase will generally look. The `Random50InsertRemove` gives you an idea of the difficulty of our **stress** tests, but is not used for actual testing (we have other similar testcases). Note that it is still possible to get a majority of the points on this assignment without passing this testcase.

## CheckBST/AVL funtions
**IMPORTANT: MAKE SURE TO READ THIS PART TO UNDERSTAND OUR CHECKER FUNCTION**

We have provided you with a checkBST and a checkAVL function. These are some of the functions we will be using to check your BST and AVL trees, we have provided them to help with your testing process as they are quite complex. However they are **not** the only checks we will be running on your code. You are expected to perform additional checks ontop of these functions.

What they check: The bst/avl properities of your trees. For checkBST, it will confirms that for every node, the left child is smaller and the right child is greater. For checkAVL, it will check for the BST property and then also confirm that the tree is balanced at every node.

**Limitations**: These functions do not check for specific values within your tree. If there are extra/missing nodes, this function will not return an error as long as the structure of your tree is valid. If this function segfaults/infintely loops, then you have an issue within your tree. This function will work properly if all the pointers in your tree are correct, however missconfigured pointers may result in infinite loops or segfaults.

**How to use it**: Call the verifyBST/AVL function on your tree within a `EXEPCT_TRUE` MACRO. Failing to do so will result in the error message not being displayed and the test case will continue without being aware of the issue.


## Running the testcases
1. Copy this directory into your `hw6` folder
2. Open a docker shell and cd into `bst_avl_testcase_builder`
3. Running the testcases:
   - `make` - Runs bst and avl testcases (Be sure to scroll up to see output of bst testcases)
   - `make run_bst` - Runs only bst testcases
   - `make run_avl` - Runs only avl testcases
   - `make valgrind` - Runs both bst and avl testcases with valgrind (Be sure to scroll up to see the valgrind output of bst)
   - `make valgrind_bst` - Runs only bst testcases with valgrind
   - `make valgrind_avl` - Runs only avl testcases with valgrind

[01] -> (10, 0)
[02] -> (20, 0)
[03] -> (30, 0)
[04] -> (40, 0)
[05] -> (50, 0)
[06] -> (60, 0)
[07] -> (70, 0)
[08] -> (80, 0)
[09] -> (90, 0)
[10] -> (100, 0)
[11] -> (110, 0)
[12] -> (120, 0)
[13] -> (130, 0)
[14] -> (140, 0)
[15] -> (150, 0)
[16] -> (160, 0)
[17] -> (170, 0)
[18] -> (180, 0)
[19] -> (190, 0)
moving from: 80 to: 40
moving from: 40 to: 20
moving from: 20 to: 10
internal height of 10 = 1
calculated height of 10 = 1
moving from: 20 to: 30
internal height of 30 = 1
calculated height of 30 = 1
internal height of 20 = 2
calculated height of 20 = 2
moving from: 40 to: 60
moving from: 60 to: 50
internal height of 50 = 1
calculated height of 50 = 1
moving from: 60 to: 70
internal height of 70 = 1
calculated height of 70 = 1
internal height of 60 = 2
calculated height of 60 = 2
internal height of 40 = 3
calculated height of 40 = 3
moving from: 80 to: 140
moving from: 140 to: 120
moving from: 120 to: 100
moving from: 100 to: 90
internal height of 90 = 1
calculated height of 90 = 1
moving from: 100 to: 110
internal height of 110 = 1
calculated height of 110 = 1
internal height of 100 = 2
calculated height of 100 = 2
moving from: 120 to: 130
moving from: 130 to: 125
internal height of 125 = 1
calculated height of 125 = 1
internal height of 130 = 2
calculated height of 130 = 2
internal height of 120 = 3
calculated height of 120 = 3
moving from: 140 to: 160
moving from: 160 to: 150
internal height of 150 = 1
calculated height of 150 = 1
moving from: 160 to: 180
moving from: 180 to: 170
internal height of 170 = 1
calculated height of 170 = 1
moving from: 180 to: 190
internal height of 190 = 1
calculated height of 190 = 1
internal height of 180 = 2
calculated height of 180 = 2
internal height of 160 = 3
calculated height of 160 = 3
internal height of 140 = 4
calculated height of 140 = 4
internal height of 80 = 5
calculated height of 80 = 5
moving from: 80 to: 40
moving from: 40 to: 20
moving from: 20 to: 10
internal height of 10 = 1
calculated height of 10 = 1
moving from: 20 to: 30
internal height of 30 = 1
calculated height of 30 = 1
internal height of 20 = 2
calculated height of 20 = 2
moving from: 40 to: 60
moving from: 60 to: 50
internal height of 50 = 1
calculated height of 50 = 1
moving from: 60 to: 70
internal height of 70 = 1
calculated height of 70 = 1
internal height of 60 = 2
calculated height of 60 = 2
internal height of 40 = 3
calculated height of 40 = 3
moving from: 80 to: 140
moving from: 140 to: 120
moving from: 120 to: 100
moving from: 100 to: 90
internal height of 90 = 1
calculated height of 90 = 1
moving from: 100 to: 110
internal height of 110 = 1
calculated height of 110 = 1
internal height of 100 = 2
calculated height of 100 = 2
moving from: 120 to: 130
moving from: 130 to: 125
internal height of 125 = 1
calculated height of 125 = 1
internal height of 130 = 2
calculated height of 130 = 2
internal height of 120 = 3
calculated height of 120 = 3
moving from: 140 to: 160
moving from: 160 to: 150
internal height of 150 = 1
calculated height of 150 = 1
moving from: 160 to: 180
moving from: 180 to: 170
internal height of 170 = 1
calculated height of 170 = 1
moving from: 180 to: 190
internal height of 190 = 1
calculated height of 190 = 1
internal height of 180 = 2
calculated height of 180 = 2
internal height of 160 = 3
calculated height of 160 = 3
internal height of 140 = 4
calculated height of 140 = 4
internal height of 80 = 5
calculated height of 80 = 5
