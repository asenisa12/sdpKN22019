# **Binary trees**

### **Task 1:**
    Implement class representing binary tree

### **Task 2:**
    Implement function minLeaf(tree) which prints the smallest element from tree

### **Task 3:**
    Implement function printRow(tree, level) that takes as arguments:
        * tree - reference to an instance of the class from the first task
        * level - integer indicating a level of the tree
    And prints all elements on that level


### **Task 4:**
    Implement function printTreeIndexed(tree) which prints all elements from tree
    with their level and their position on it. For example this three:
       (12)
        / \
     (21)   (41)
     / \     / \
   (14) (6) (7) (9)

   should give output that looks like this:
    12 (0,0),
    21 (1,0), 41 (1,1)
    14 (2,0), 6 (2,1), 7 (2,2), 9 (2,3)