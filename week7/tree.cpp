#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
using namespace std;

enum LeafId : short
{
    Left,
    Right
};

template<typename T>
class Tree
{
    struct Leaf
    {
        T data;
        Leaf *leaf[2];
        Leaf(const T &_data, Leaf *right = nullptr, Leaf *left = nullptr)
            :data(_data)
        {
            leaf[Left] = left;
            leaf[Right] = right;
        }
    } *root;
    
    void deleteTree(Leaf *leaf)
    {   if(leaf == nullptr)
            return;
        deleteTree(leaf->leaf[Left]);
        deleteTree(leaf->leaf[Right]);
        
        delete leaf;
        leaf = nullptr;
    }

public:
    Tree():root(nullptr)
    {}

    ~Tree()
    {
        deleteTree(root);
    }

    void addLeaf(const T& x,const vector<LeafId> &trace = vector<LeafId>(0))
    {
        if(trace.empty())
        {
            assert(root == nullptr);
            root = new Leaf(x);
            return;
        }

        Leaf *current = root;
        for (int i = 0; i < trace.size()-1; i++)
        {
            assert(current != nullptr);
            current = current->leaf[trace[i]];
        }
    
        assert(current->leaf[trace.back()] == nullptr);
        current->leaf[trace.back()] = new Leaf(x);
    }

    void print()
    {
        print_helper(root, 0);
    }
private:

    void print_helper(Leaf *current, int level)
    {
        if (current != nullptr)
        {
            print_helper(current->leaf[Right],level+1);
            cout << setw(level*2) << " " << current->data <<endl;
            print_helper(current->leaf[Left], level+1);
        }
    }


};


int main()
{
    Tree<int> t;
    t.addLeaf(1);
    t.addLeaf(2,{Left});
    t.addLeaf(2,{Right});
    t.addLeaf(3,{Right,Left});
    t.addLeaf(3,{Right,Right});
    t.addLeaf(3,{Left,Right});
    t.addLeaf(3,{Left,Left});
    t.print();

    return 0;
}
