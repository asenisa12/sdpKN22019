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
//Task 1
public:
    void getLeafValue(const vector<LeafId> &trace, T &value)
    {

        Leaf *current = root;
        for (LeafId id : trace)
        {
            if(current != nullptr)
            {
                current = current->leaf[id];
            }
            else
            {
                cout<<"wrong trace!"<<endl;
                return;
            }
            
        }
        value = current->data;
    }

// Task 2
private:
    Leaf* generateBSTfromArray_helper(const vector<T> &array,
        int start, int end)
    {
        if(end < start)
        {
            return nullptr;
        }
        int mid = (start + end) / 2;
        Leaf *leaf = new Leaf(array[mid]);
        leaf->leaf[Left] = generateBSTfromArray_helper(array, start, mid - 1);
        leaf->leaf[Right] = generateBSTfromArray_helper(array, mid + 1, end);

        return leaf;
    }
public:
    void generateBSTfromArray(const vector<T> &array)
    {
        deleteTree(root);
        root = generateBSTfromArray_helper(array, 0, array.size() - 1);
    }

// Task 3
private:
    int calcExp_helper(Leaf* leaf)
    {
        if(leaf->data == '+')
        {
            return calcExp_helper(leaf->leaf[Left]) + calcExp_helper(leaf->leaf[Right]);
        }

        if(leaf->data == '*')
        {
            return calcExp_helper(leaf->leaf[Left]) * calcExp_helper(leaf->leaf[Right]);
        }

        return leaf->data - '0';
    }
public:
    int calculateExpression()
    {
        return calcExp_helper(root);
    }

// Task 4
private:
    int countPathsWithsum_helper(Leaf *leaf, int targetSum, int currentSum)
    {
        if(leaf == nullptr) return 0;

        currentSum += leaf->data;
        int paths_count = 0;
        if(currentSum == targetSum)
        {
            paths_count++;
        }
        else
        {
            paths_count += countPathsWithsum_helper(leaf->leaf[Left], targetSum, currentSum);
            paths_count += countPathsWithsum_helper(leaf->leaf[Right], targetSum, currentSum);
        }
        return paths_count;
    }
public:
    int countPathsWithsum(int targetSum)
    {
        return countPathsWithsum_helper(root, targetSum, 0);
    }

//Task 5
private:
    Leaf*& getMinLeaf(Leaf *&leaf)
    {
        if(leaf->leaf[Left] == nullptr)
        {
            return leaf;
        }
        return getMinLeaf(leaf->leaf[Left]);
    }

    void remove_helper(const T &x, Leaf *&leaf)
    {
        if(leaf == nullptr)
        {
            cout << "Error: no leaf with value: " << x << endl;
        }
        else if(x < leaf->data)
        {
            remove_helper(x, leaf->leaf[Left]);
        }
        else if(x > leaf->data)
        {
            remove_helper(x, leaf->leaf[Right]);
        }
        else if (x == leaf->data )
        {
            if(leaf->leaf[Right] == nullptr)
            {
                Leaf *tmp = leaf;
                leaf = leaf->leaf[Left];
                delete tmp;
            }
            else
            {
                Leaf *&min_leaf = getMinLeaf(leaf->leaf[Right]);
                Leaf *min_save = min_leaf;
                min_leaf = min_leaf->leaf[Right];

                min_save->leaf[Left] = leaf->leaf[Left];
                min_save->leaf[Right] = leaf->leaf[Right];

                Leaf *tmp = leaf;
                leaf = min_save;
                delete tmp;
            }
        }
    }
public:
    void remove(const T &x)
    {
        remove_helper(x, root);
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

    // std::cout<< t.is_balanced() << std::endl;

    Tree<int> t2;
    t2.addLeaf(10);
    t2.addLeaf(8,{Left});
    t2.addLeaf(12,{Right});
    t2.addLeaf(7,{Left,Left});
    t2.addLeaf(9,{Left,Right});
    t2.addLeaf(11,{Right,Left});
    t2.addLeaf(13,{Right,Right});
    t2.print();
    int value;
    t2.getLeafValue({Right, Right}, value);
    std::cout<< value << std::endl;

    Tree<int> t3;
    t3.generateBSTfromArray({1,3,6,7,12,24,35,45});
    t3.print();

    Tree<char> t4;
    t4.addLeaf('+');
    t4.addLeaf('*',{Left});
    t4.addLeaf('+',{Right});
    t4.addLeaf('2',{Left,Left});
    t4.addLeaf('2',{Left,Right});
    t4.addLeaf('3',{Right,Left});
    t4.addLeaf('1',{Right,Right});
    t4.print();
    std::cout<< t4.calculateExpression() << std::endl;
    
    Tree<int> t5;
    t5.addLeaf(1);
    t5.addLeaf(2,{Left});
    t5.addLeaf(1,{Right});
    t5.addLeaf(1,{Left,Left});
    t5.addLeaf(3,{Left,Right});
    t5.addLeaf(2,{Right,Left});
    t5.addLeaf(3,{Right,Right});
    t5.print();
    std::cout<< t5.countPathsWithsum(4) << std::endl;


    t2.remove(8);
    t2.print();
    return 0;
}
