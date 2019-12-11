#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;

struct Node
{  
    Node* left; 
    Node* right;
    int data;
  
    Node(int _data)
        :data(_data)
    {}
};

void print(Node *root, int level=0)
{
    if (root != nullptr)
    {
        print(root->right,level+1);
        cout << setw(level*2) << " " << root->data <<endl;
        print(root->left, level+1);
    }
}


// Task 1
Node* insert(int value, Node * &root)
{
    if(root == nullptr)
    {
        root = new Node(value);
        return root;
    }
    else if(value < root->data)
    {
        return insert(value, root->left);
    }
    else if(value > root->data)
    {
        return insert(value, root->right);
    }
    else
    {
        cout << "Error: Bin Search Tree Can't contain two nodes with same value\n";
        return nullptr;
    }
    
}

void delete_tree(Node *&root)
{
    if(root == nullptr)
        return;

    delete_tree(root->left);
    delete_tree(root->right);
    
    delete root;
    root = nullptr;

}

// Task 2
Node* lowest_common_ancestor(Node* n1, Node *n2, Node* root)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    int min_data = min(n1->data, n2->data);
    int max_data = max(n1->data, n2->data);

    if(root->data > min_data && root->data < max_data)
    {
        return root;
    }
    // if both x and y are smaller than root, LCA exists in left subtree
	else if (root->data > max_data)
    {
		return lowest_common_ancestor(n1, n2, root->left);
    }
	// if both x and y are greater than root, LCA exists in right subtree
	else  if (root->data < min_data)
    {
		return lowest_common_ancestor(n1, n2, root->right);
    }

}

// Task 3
Node* k_smallest_element(Node *root, int k) 
{ 
    stack<Node*> stk; 
    Node *current = root; 
  
    while( current != nullptr ) 
    { 
        stk.push(current); 
        current = current->left; 
    } 
  
 
    while( !stk.empty() ) 
    { 
        current = stk.top();
        stk.pop();
        if( --k == 0 ) 
        { 
            break; 
        } 
  
        if( current->right ) 
        { 
            current = current->right; 
            while( current ) 
            { 
                stk.push(current);
                current = current->left; 
            } 

        } 
    } 
    if(k != 0)
    {
        cout<<"Wrong parameters\n";
        return nullptr;
    }

    /* node having k-th element or NULL node */
    return current; 
} 



int main()
{
    Node *root = nullptr;
    insert(10, root);
    insert(8,  root);
    insert(12, root);
    Node *n1 = insert(7,  root);
    insert(9,  root);
    insert(11, root);
    Node *n2 = insert(13, root);
    print(root);


    // delete_tree(root);
    print(root);
    Node *lowest = lowest_common_ancestor(n1,n2, root);
    if(lowest)
        cout<<lowest->data<<endl;
    else 
        cout<<"incorrect node\n";

    Node *k_smallest = k_smallest_element(root,5);
    cout<<k_smallest->data<<endl;
    return 0;
}