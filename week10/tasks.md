## **Exam preparation**


## **Binary trees**
You are given the structure below that represents binary seearch tree (бинарно наредено дърво):
```cpp
  struct Node{
    Node* left;
    Node* right;
    int data;
    Node(int _data):data(_data){}
  } 
```
Using it the following problems:


### **Task 1:**
    Write functions:
      insert(int value, Node *root) that inserts new Node in three starting from the given root
      delete_tree(int value, Node *&root) delete three starting from the given root

### **Task 2:**
    Write function "Node* lowest_common_ancestor(Node* n1, Node *n2, Node* root); "
    that finds the the lowest common ancestor of n1 and n2 in a Binary Search Tree starting from root
    For example:
        n4
       / \
     n6  n3
         / \
        n1 n2    the lowest common ancestor of n1 and n2 is n3 and the one for n2 and n6 is n4

### **Task 3:**
    Write function that prints the value of K’th smallest element in BST


### **For self-preparation**
    Using the datastructure above implement:
      * function minLeaf(Node *root) which prints the smallest element from tree
      * function printLevel(int level) that takes as argument integer indicating a level of the tree and prints all elements on that level
      * function bool check_balanced(Node *root) to check if a binary tree is balanced (search using google "balanced tree" or "балансирано дърво")
      * "Task 2 and 3" from week 8 using Node-s to represent tree
      * "Task 1" from week 9 using std::string containing 'L'-s and 'R'-s representing left and right direction respectively
      * "Task 5" from week 9
      * (optional) all of the remaining tasks from week 7 to 10
