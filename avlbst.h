#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
    

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    using BinarySearchTree<Key, Value>::nodeSwap;
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key, Value>* Node, AVLNode<Key, Value>* Parent);
    void performRotations(AVLNode<Key, Value>* gParent, AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    int findZig(AVLNode<Key, Value>* gParent, AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    void resetHeight(AVLNode<Key, Value>* root);
    void removeFix(AVLNode<Key, Value>* Parent);
};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
   //std::cout << "got here correctly" << std::endl;
    // TODO
    AVLNode<Key,Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_);
    bool end = false;
    if(this->empty()){
        BinarySearchTree<Key, Value>::root_ = static_cast<Node<Key, Value>*>(newNode);
        newNode->setParent(nullptr);
        return;
    }
    else{
        while(end == false){
            if(new_item.first == temp->getKey()){
                temp->setValue(new_item.second);
                return;
            }
            if(new_item.first > temp->getKey()){
                if(temp->getRight() != nullptr){
                temp = temp->getRight();
                }
                else{
                    end = true;
                }
            }
            else if(new_item.first < temp->getKey()){
                if(temp->getLeft() != nullptr){
                temp = temp->getLeft();
                }
                else{
                    end = true;
                }
            }
        }
        if(new_item.first > temp->getKey()){
            temp->setRight(newNode);
            temp->getRight()->setParent(temp);
    }
        else if(new_item.first < temp->getKey()){
            temp->setLeft(newNode);
            newNode->setParent(temp);
        }
    }
    newNode->setHeight(BinarySearchTree<Key, Value>::findHeight(newNode));
    /////tstd::cout << "set Node " << newNode->getItem().first << " height to " << BinarySearchTree<Key, Value>::findHeight(newNode) << std::endl;
    if(newNode->getParent() != nullptr){
        /////tstd::cout << "got to check" << std::endl;
        if(BinarySearchTree<Key, Value>::findHeight(newNode->getParent()) != newNode->getParent()->getHeight()){
            newNode->getParent()->setHeight(BinarySearchTree<Key, Value>::findHeight(newNode->getParent()));
            insertFix(newNode->getParent(), newNode);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    //////tstd::cout << "removing " << key << std::endl;
    if(BinarySearchTree<Key, Value>::internalFind(key) == nullptr){
        return;
    }
    //////////////tstd::cout << "height reset" << std::endl;
    // TODO
    AVLNode<Key,Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
    AVLNode<Key, Value>* parent = temp->getParent();
    //if Key is not in tree
    if(temp == nullptr){
        return;
    }
    //if two children
     if(temp->getLeft() != nullptr && temp->getRight() != nullptr){
          ////////////////tstd::cout << "2 child swap" << std::endl;
        nodeSwap(temp, static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::successor(temp)));
        parent = temp->getParent();
    }
    Node<Key, Value>* tempChild = nullptr;
    if(temp->getLeft() != nullptr){
        tempChild = temp->getLeft();
    }
    else if(temp->getRight() != nullptr){
        tempChild = temp->getRight();
    }
    //if no children and not root
    if(temp != static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_)){
          ////////////////tstd::cout << "removing no child" << std::endl;
        if(tempChild != nullptr){
            tempChild->setParent(temp->getParent());
        }
        if(temp->getParent()->getLeft() == temp){
            temp->getParent()->setLeft(tempChild);
            delete temp;
            //tstd::cout << "deleted " << key << std::endl;
            //this->printRoot(BinarySearchTree<Key, Value>::root_);
            return removeFix(parent);
        }
        else if(temp->getParent()->getRight() == temp){
            temp->getParent()->setRight(tempChild);
            delete temp;
            //tstd::cout << "deleted " << key << std::endl;
            //this->printRoot(BinarySearchTree<Key, Value>::root_);
            return removeFix(parent);
        }
    }
    // gets here if key is root

    //////////////tstd::cout << "removing root" << std::endl;
    if(tempChild != nullptr){
        tempChild->setParent(nullptr);
    }
    BinarySearchTree<Key, Value>::root_ = tempChild;
    delete temp;
    ////this->printRoot(BinarySearchTree<Key, Value>::root_);
    //////////////tstd::cout << "rem call 3" << std::endl;
    removeFix(parent);
}
    

template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key, Value>* fixNode)
{
    // TODO
    //////////////tstd::cout << "remove fix called" << std::endl;
    int leftHeight = 0;
    int rightHeight = 0;
    if(fixNode == nullptr){
        ////////////tstd::cout << "nullptr return" << std::endl;
        return;
    }
    AVLNode<Key, Value>* fixNodeParent = fixNode->getParent();
    //tstd::cout << "fixing node: " << fixNode->getKey() << std::endl;
    if(fixNode->getLeft() != nullptr){
        leftHeight = fixNode->getLeft()->getHeight();
        //tstd::cout << "left subHeight: " << fixNode->getLeft()->getHeight() << std::endl;
    }
    else{
        //tstd::cout << "left subHeight: " << 0 << std::endl;
    }
    if(fixNode->getRight() != nullptr){
        rightHeight = fixNode->getRight()->getHeight();
        //tstd::cout << "right subHeight: " << fixNode->getRight()->getHeight() << std::endl;
    }
    else{
    }
    if(!BinarySearchTree<Key, Value>::checkBalance(fixNode)){
    AVLNode<Key, Value>* Parent = nullptr;
    AVLNode<Key, Value>* Node = nullptr;
    AVLNode<Key, Value>* grandParent = fixNode;
    if(fixNode->getLeft() != nullptr){
        leftHeight = BinarySearchTree<Key, Value>::findHeight(fixNode->getLeft());
    }
    else{
        leftHeight = 0;
    }
    if(fixNode->getRight() != nullptr){
        rightHeight = BinarySearchTree<Key, Value>::findHeight(fixNode->getRight());
    }
    else{
        rightHeight = 0;
    }
    if(leftHeight > rightHeight){
        Parent = fixNode->getLeft();
    }
    else{
        Parent = fixNode->getRight();
    }
    //if parent is left child
    if(fixNode->getLeft() == Parent){
        if(Parent->getLeft() != nullptr){
            leftHeight = BinarySearchTree<Key, Value>::findHeight(Parent->getLeft());
        }
        else{
            leftHeight = 0;
        }
        if(Parent->getRight() != nullptr){
            rightHeight = BinarySearchTree<Key, Value>::findHeight(Parent->getRight());
        }
        else{
            rightHeight = 0;
        }
        if(leftHeight >= rightHeight){
            Node = Parent->getLeft();
        }
        else{
            Node = Parent->getRight();
        }
    }
    //if parent is right child
    else if(fixNode->getRight() == Parent){
        if(Parent->getLeft() != nullptr){
            leftHeight = BinarySearchTree<Key, Value>::findHeight(Parent->getLeft());
        }
        else{
            leftHeight = 0;
        }
        if(Parent->getRight() != nullptr){
            rightHeight = BinarySearchTree<Key, Value>::findHeight(Parent->getRight());
        }
        else{
            rightHeight = 0;
        }
        if(rightHeight >= leftHeight){
            Node = Parent->getRight();
        }
        else{
            Node = Parent->getLeft();
        }
    }

    performRotations(grandParent, Parent, Node);
    return removeFix(fixNodeParent);
}
else if(fixNode->getHeight() == BinarySearchTree<Key, Value>::findHeight(fixNode)){
    resetHeight(static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_));
    return;
}
else{
    fixNode->setHeight(BinarySearchTree<Key, Value>::findHeight(fixNode));
    return removeFix(fixNodeParent);
}

resetHeight(static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_));

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* Parent, AVLNode<Key, Value>* Node)
{
    // TODO
    if(Parent == nullptr || Parent->getParent() == nullptr){
        return;
    }
    AVLNode<Key, Value>* grandParent = Parent->getParent();
    int grandHeight = BinarySearchTree<Key, Value>::findHeight(grandParent);
    if(grandParent->getHeight() == grandHeight){
        return;
    }
    else{
        grandParent->setHeight(grandHeight);
        if(BinarySearchTree<Key, Value>::checkBalance(grandParent)){
            return insertFix(grandParent, Parent);
        }
        else{
            performRotations(grandParent, Parent, Node);
        }
    }
   resetHeight(static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_));
}

template<class Key, class Value>
void AVLTree<Key, Value>::performRotations(AVLNode<Key, Value>* gParent, AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node)
{
    //tstd::cout<< "rotations entered" << std::endl;
    bool gRoot = false;
   if(gParent->getParent() == nullptr){
            gRoot = true;
        }
    //////tstd::cout << "got to rotate" << std::endl;
    if(findZig(gParent, parent, node) == 1){
        //////tstd::cout << "zig 1" << std::endl;
        gParent->setLeft(parent->getRight());
        if(gParent->getLeft() != nullptr){
        gParent->getLeft()->setParent(gParent);
        }
        parent->setParent(gParent->getParent());
        parent->setRight(gParent);
        gParent->setParent(parent);
         if(gRoot){
            BinarySearchTree<Key, Value>::root_ = static_cast<Node<Key, Value>*>(parent);
        }
        else{
            if(parent->getItem().first < parent->getParent()->getItem().first){
                parent->getParent()->setLeft(parent);
            }
            else if(parent->getItem().first > parent->getParent()->getItem().first){
                parent->getParent()->setRight(parent);
            }
        }
    }
    else if(findZig(gParent, parent, node) == 2){
        //////tstd::cout << "zig 2" << std::endl;
        gParent->setRight(parent->getLeft());
        if(gParent->getRight() != nullptr){
        ////////////tstd::cout << "got here incorrectly" << std::endl;
        gParent->getRight()->setParent(gParent);
        }
        parent->setParent(gParent->getParent());
        parent->setLeft(gParent);
        gParent->setParent(parent);
        if(gRoot){
            BinarySearchTree<Key, Value>::root_ = static_cast<Node<Key, Value>*>(parent);
        }
         else{
            if(parent->getItem().first < parent->getParent()->getItem().first){
                parent->getParent()->setLeft(parent);
            }
            else if(parent->getItem().first > parent->getParent()->getItem().first){
                parent->getParent()->setRight(parent);
            }
        }
    }
    else if(findZig(gParent, parent, node) == 3){
        node->setParent(gParent->getParent());
        parent->setRight(node->getLeft());
        if (parent->getRight() != nullptr) {
            parent->getRight()->setParent(parent);
        }
        gParent->setLeft(node->getRight());
        if (gParent->getLeft() != nullptr) {
            gParent->getLeft()->setParent(gParent);
        }
        parent->setParent(node);
        gParent->setParent(node);
        node->setLeft(parent);
        node->setRight(gParent);
        if (node->getParent() != nullptr) {
            if (node->getItem().first < node->getParent()->getItem().first) {
        node->getParent()->setLeft(node);
        } 
        else {
        node->getParent()->setRight(node);
        }
        }       
        else {
            BinarySearchTree<Key, Value>::root_ = static_cast<AVLNode<Key, Value>*>(node);
            node->setParent(nullptr);
        }
    }
    else if(findZig(gParent, parent, node) == 4){
        node->setParent(gParent->getParent());
        gParent->setRight(node->getLeft());
        if (gParent->getRight() != nullptr) {
            gParent->getRight()->setParent(gParent);
        }
        parent->setLeft(node->getRight());
        if (parent->getLeft() != nullptr) {
            parent->getLeft()->setParent(parent);
        }
        parent->setParent(node);
        gParent->setParent(node);
        node->setRight(parent);
        node->setLeft(gParent);
        if (gRoot) {
            BinarySearchTree<Key, Value>::root_ = static_cast<AVLNode<Key, Value>*>(node);
            node->setParent(nullptr);
        } 
        else {
            if (node->getItem().first < node->getParent()->getItem().first) {
                node->getParent()->setLeft(node);
            } else if (node->getItem().first > node->getParent()->getItem().first) {
                node->getParent()->setRight(node);
            }
        }
    }
}

//returns 1 for left zig-zig, 2 for right zig-zig, 3 for left zig-zag, 4 for right zig-zag
template<class Key, class Value>
int AVLTree<Key, Value>::findZig(AVLNode<Key, Value>* gParent, AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node)
{
    if(gParent->getLeft() == parent && parent->getLeft() == node){
        return 1;
    }
    if(gParent->getRight() == parent && parent->getRight() == node){
        return 2;
    }
    if(gParent->getLeft() == parent && parent->getRight() == node){
        return 3;
    }
    if(gParent->getRight() == parent && parent->getLeft() == node){
        return 4;
    }
    return 0;
}

template<class Key, class Value>
void AVLTree<Key, Value>::resetHeight(AVLNode<Key, Value>* root)
{
    if(root == nullptr){
        return;
    }
    resetHeight(root->getLeft());
    resetHeight(root->getRight());
    int newHeight = BinarySearchTree<Key, Value>::findHeight(root);
    root->setHeight(newHeight);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
