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
  
        Iterator& operator=(Node* pNode) 
        { 
            this->currentNode = pNode; 
            return *this; 
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

    void partition(int x)
    {
        Node *lowerTop = nullptr, *lowerRoot = nullptr;
        Node *higherTop = nullptr, *higherRoot = nullptr;

        Node *current = rootNode;
        while(current != nullptr)
        {
            if(current->data < x)
            {
                if(lowerTop == nullptr)
                {
                    lowerRoot = current;
                    lowerRoot->prev = nullptr;
                    lowerTop = lowerRoot;
                }
                else
                {
                    lowerTop->next = current;
                    current->prev = lowerTop;
                    lowerTop = lowerTop->next;
                }           
            }
            else
            {
                if(higherTop == nullptr)
                {
                    higherRoot = current;
                    higherTop = higherRoot;
                }
                else
                {
                    higherTop->next = current;
                    current->prev = higherTop;
                    higherTop = higherTop->next;
                }
            }
            current = current->next;
        }
    
        higherTop->next = nullptr;
        rootNode = lowerRoot;
        lowerTop->next = higherRoot;
        topNode = higherTop;
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
    l.partition(5);

    for (LList<int>::Iterator it = l.begin(); it != l.end();it++)
    {
        cout<<(*it)<<" ";
    }
    cout<<endl;

    for(size_t i = 0; i < l.get_size(); i++)
    {
        cout<< "l["<<i<<"]: "<< l[i] <<endl;
    }


    return 0;
}