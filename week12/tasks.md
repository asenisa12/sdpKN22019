# **Trie**

### **Tasks:**
    Implement class representing Trie containing chars. It should have the following methods:
        * Constructor/Destructor
        * void addLeaf(vector<int> path, const T &value) - creates leaf on position specified by the argument path (every elemnth in it represents i-th subtree)
         for example addLeaf({2,1}, 'C') would change:
             A                       A
            /|\                     /|\
          C  B  G       to        C  B  G
         / \  / | \              / \  / | \
        J  U R  O  M            J  U R  O  M
                /\                     /|\
               W  E                   W E C    
        * void getLeaf(vector<int> path) - gets value of leaf indexed by the variable path. For example on the top tree getLeaf({2,1,0}) will return 'W' and  getLeaf({}) will return 'A'.
        * void print() - that prints all leafs
        * void printWords() - prints all words that could be written by traversing the leafs. For example for the top Trie the method ouputs:
            A
            AC
            ACJ
            AB
            ....... and so on
        * bool wordIsContained(const std::string &word) returns if word is contained in the trie.

