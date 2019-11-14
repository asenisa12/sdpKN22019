# **Advanced iterators**

### **Task 1:**
    Implement Iterator that:
        * is skipping every element bigger than given number N
        * is deleting  every element it iterates
    

### **Task 2:**
    Implement a class named "Sequence", representing sequence of elements where
    the beginning and the end are set with iterators. (Look at the implementation here:
    https://github.com/stranxter/lecture-notes/blob/master/homeworks/Problems%20in%20Programming.pdf)

### **Task 3:**
    With the given class Sequence implement the following operations:
        a) addIndex(s) - from sequence s creates new  sequence of std::pair-s where the first element of the pair is
            index representing position of element in the seuence and the second one is iterator referencing it
        b) append(s1, s2) - returns sequence of the squence s1 and s2 appended


# **DFS**
    DFS visual representation
    https://www.codingame.com/learn/DFS

### **Task 1:**
    Implement DFS algorithm using stack which traverses throgh labyrinth represented by 2d array
    that looks like this:

        0 # * # # # * #
        * # * * * # * #
        * # # # * # * #  # - wall
        * * * * * # * #  * - free space
        # # # # * # * #  0 - start
        * * * * * * * *  1 - end
        * * # # # * * 1


### **Task 2:** 
    TBD