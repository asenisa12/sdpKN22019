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
// Task 2
    void minLeaf_helper(Leaf *leaf, T &min)
    {
        if(leaf != nullptr)
        {
            if(leaf->data < min)
            {
                min = leaf->data;
            }
            minLeaf_helper(leaf->leaf[Left],min);
            minLeaf_helper(leaf->leaf[Right],min);
        }
    }
public:
    void minLeaf()
    {
        assert(root != nullptr);
        T min = root->data;
        minLeaf_helper(root, min);

        cout<<"Min leaf: " << min << endl;
    }

// Task 3
private:
    void printLevel_helper(Leaf *leaf, int level)
    {
        if(leaf==nullptr)
            return;

        if(level == 1)
            cout << leaf->data << " ";

        printLevel_helper(leaf->leaf[Left],level - 1);
        printLevel_helper(leaf->leaf[Right],level - 1);
        
    }
public:
    void printLevel(int level)
    {
        assert(root != nullptr);
        cout << "Level "<< level << ": ";
        printLevel_helper(root, level);
        cout << endl;
    }

// Task 4
    void printTreeIndexed()
    {
        assert(root != nullptr);
        vector<Leaf*> level;
        
        level.push_back(root);
        int level_cnt = 0;

        while(!level.empty())
        {
            vector<Leaf*> new_level;

            int col_cnt = 0;
            for(Leaf *l : level)
            {
                cout << l->data;
                cout << " (" << level_cnt << "," << col_cnt++ << "), ";
                if(l->leaf[Left] != nullptr)
                {
                    new_level.push_back(l->leaf[Left]);
                }
                if(l->leaf[Right] != nullptr)
                {
                    new_level.push_back(l->leaf[Right]);
                }
            }
            
            cout << endl;

            level_cnt++;
            level = new_level;
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
    t.minLeaf();

    t.printLevel(3);

    Tree<int> t2;
    t2.addLeaf(12);
    t2.addLeaf(21,{Left});
    t2.addLeaf(41,{Right});
    t2.addLeaf(14,{Left,Left});
    t2.addLeaf(6,{Left,Right});
    t2.addLeaf(7,{Right,Left});
    t2.addLeaf(9,{Right,Right});
    t2.printTreeIndexed();

    return 0;
}
