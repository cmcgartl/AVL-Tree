##AVL Tree and Binary Search Tree Implementation

##Overview
This project contains a full implmementation of Binary Search Tree and Self Balancing Binary Search Tree (AVL Tree), which ensures logarithmic time complexity for search, insertion, deletion operations

##Features
**Binary Search Tree (BST):**
-Supports insertion, deletion, and search, with worst case linear time complexity with imbalances

**Self Balancing Binary Search Tree (AVL):**
-automatically balances left and right subtrees after insertion and deletion
-worst case O(logn) for search, insertion, deletion
-implements left, right, and "zig zag" rotatinos to balance

##How to Run
-run git clone <url> clone the repository into a new/desired folder
-To run test cases, cd into bst_testcase_builder and run make
-To use for other programs, use #include avlbst.h in your .cpp file

**Example Usage**

int main(){
    int main() {
    AVLTree<int, std::string> tree;
    
    tree.insert(std::make_pair(10, "Root"));
    tree.insert(std::make_pair(5, "Left Child"));
    tree.insert(std::make_pair(15, "Right Child"));

    std::cout << "Tree after insertions:" << std::endl;
    tree.printRoot(tree.getRoot());  // Print the AVL tree
    tree.find("10"); //returns an iterator to the pair (10, "Root")
    return 0;
}
