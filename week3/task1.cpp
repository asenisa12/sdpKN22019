#include <iostream> 
using namespace std; 

template <typename T> 
class LList 
{ 
    int size;
    class Node 
    { 
        friend class LList;
        T data; 
        Node* next;
        Node* prev;

    public:
        Node(T value)
            :data(value), next(nullptr), prev(nullptr)
        {
        }
    };

    Node *rootNode, *topNode; 

  
public:

    class Iterator 
    { 
    public: 
    Iterator()  : 
        currentNode (rootNode) { } 
  
    Iterator(const Node* pNode) : 
        currentNode (pNode) { } 
  
        Iterator(const Iterator &other) 
        { 
            this->currentNode = other.currentNode; 
        } 
  
        // Prefix ++ overload 
        Iterator& operator++() 
        { 
            if (currentNode) 
                currentNode = currentNode->next; 
            return *this; 
        } 
  
        // Postfix ++ overload 
        Iterator operator++(int) 
        { 
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        } 
  
        bool operator!=(const Iterator& iterator) 
        { 
            return currentNode != iterator.currentNode; 
        } 
  
        const T& operator*() 
        { 

            return currentNode->data; 
        } 
  
    private: 
        const Node* currentNode; 
    };

    LList<T>() :rootNode(nullptr), topNode(nullptr), size(0)
    { 
    }

    ~LList<T>()
    {
        if(topNode != nullptr)
        {
            do{
                Node *curTop = topNode;
                topNode = topNode->prev;

                delete curTop;

            }while(topNode->prev != nullptr);
        }
    }
  
    Iterator begin() 
    { 
        return Iterator(rootNode); 
    } 
  

    Iterator end() 
    { 
        return Iterator(nullptr); 
    } 
  
    int get_size()
    {
        return size;
    }

    void push_back(T value)
    {
        Node *new_node = new Node(value);
        push_back_node(new_node);
        size++;
    }

    T& operator[](int id){
        Node *current;
        if(id < size / 2)
        {
            current = rootNode;
            for(int i = 0; i<id; i++)
            {
                current = current->next;
            }
            return current->data;
        }
        else
        {
            current = topNode;
            for(int i = size - (id+1); i>0; i--)
            {
                current = current->prev;
            }

        }
        
        return current->data;
    }


    //task 2
    void partition(int x)
    {

        Node *current = rootNode;
        
        for(int i=0; i<size; i++)
        {
            if(current->data >= x)
            {
                Node *higher = current;
                current = current->next;
                
                remove_node(higher);
                push_back_node(higher);

                higher->next = nullptr;
            }
            else
            {
               current = current->next;
            }
            
            
        }

    }

private: 
    void remove_node(Node *node)
    {
        if(node->prev != nullptr)
        {
            node->prev->next = node->next;
        }else
        {
            rootNode = node->next;
        }
        
        node->next->prev = node->prev;
    }
    
    void push_back_node(Node *new_node)
    {
        if(topNode != nullptr)
        {
            new_node->prev = topNode;
            topNode->next = new_node;
            topNode = new_node;
        }else
        {
            rootNode = new_node;
            topNode = rootNode;
        }
    }

}; 
  
int main()
   
{

    LList<int> l;
    l.push_back(6);
    l.push_back(7);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(8);

    for (LList<int>::Iterator it = l.begin(); it != l.end();it++)
    {
        cout<<(*it)<<" ";
    }
    cout<<endl;

    l.partition(5);
    for(size_t i = 0; i < l.get_size(); i++)
    {
        cout<< "l["<<i<<"]: "<< l[i] <<endl;
    }


    return 0;
}