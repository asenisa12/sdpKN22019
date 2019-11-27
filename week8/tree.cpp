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


    int get_height(Leaf *leaf)
    {
        if(leaf == nullptr) return -1;

        return max(get_height(leaf->leaf[Left]), get_height(leaf->leaf[Right])) + 1;
    }

    //task1
    bool is_balanced_helper(Leaf *leaf)
    {
        if(leaf == nullptr) return true;

        int height_diff = abs(get_height(leaf->leaf[Left]) - get_height(leaf->leaf[Right]));

        if(height_diff > 1)
        {
            return false;
        }
        else
        {
            return is_balanced_helper(leaf->leaf[Left]) &&
                is_balanced_helper(leaf->leaf[Right]);
        }
        
    }
public:

    bool is_balanced()
    {
        return is_balanced_helper(root);
    }
    
//task2
private:
    bool check_trees(Leaf* t1, Leaf *t2)
    {
        if(t1 == nullptr)
        {
            return false;
        }
        if(t1->data == t2->data && is_matching(t1, t2))
        {
            return true;
        }

        return check_trees(t1->leaf[Left],t2) || check_trees(t1->leaf[Right],t2);

    }

    bool is_matching(Leaf* t1, Leaf *t2)
    {
        if(t1 == nullptr && t2 == nullptr)
        {
            return true;
        }
        
        if(t1 == nullptr || t2 == nullptr)
        {
            return false;
        }

        if(t1->data != t2->data)
        {
            return false;
        }

        return is_matching(t1->leaf[Left], t2->leaf[Left]) && 
            is_matching(t1->leaf[Right], t2->leaf[Right]);
    }

public:
    bool isSubtree(const Tree<T> &t)
    {
        if(t.root == nullptr)
            return true;
        return check_trees(root, t.root);
    }


//task3
private:
    void copy_to_vector(Leaf *leaf, vector<int> &vec)
    {
        if(leaf == nullptr) return;
        
        copy_to_vector(leaf->leaf[Left],  vec);
        
        vec.push_back(leaf->data);
        
        copy_to_vector(leaf->leaf[Right], vec);

    }

public:
    bool is_bin_search_tree()
    {
        vector<int> vec;
        copy_to_vector(root, vec);
        
        for (int i = 1; i < vec.size(); i++)
        {
            if(vec[i] <= vec[i-1]) return false;
        }
        return true;
    }

};


int main()
{
    Tree<int> t;
    t.addLeaf(1);
    // t.addLeaf(2,{Left});
    t.addLeaf(2,{Right});
    t.addLeaf(3,{Right,Left});
    t.addLeaf(3,{Right,Right});

    // t.addLeaf(3,{Left,Right});
    // t.addLeaf(3,{Left,Left});
    // t.print();

    std::cout<< t.is_balanced() << std::endl;

    Tree<int> t2;
    t2.addLeaf(10);
    t2.addLeaf(8,{Left});
    t2.addLeaf(12,{Right});
    t2.addLeaf(7,{Left,Left});
    t2.addLeaf(9,{Left,Right});
    t2.addLeaf(11,{Right,Left});
    t2.addLeaf(13,{Right,Right});
    std::cout<< t2.is_bin_search_tree() << std::endl;
    std::cout<< t.is_bin_search_tree() << std::endl;

    Tree<int> t3;
    t3.addLeaf(8);
    t3.addLeaf(7,{Left});
    t3.addLeaf(9,{Right});

    std::cout<< t2.isSubtree(t) << std::endl;
    return 0;
}
