#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template<typename T>
class HashMap
{

    struct HashEntry{
        string key;
        T data;
        HashEntry(string _key) : key(_key)
        {}
    };
    vector<HashEntry*> table;

    int (*hash)(const char*, int size);


public: 
    HashMap(int size, int (*_hash)(const char*, int))
        :table(size, nullptr), hash(_hash)
    {}

    ~HashMap()
    {
        for (auto &entry : table)
        {
            delete entry;
        }
    }

    T& operator[](const char* key)
    {
        int id = hash(key, table.size());
        
        if(id > table.size())
        {
            table.resize(table.size() + id + 1, nullptr);
        }

        if(table[id] == nullptr)
        {
            table[id] = new HashEntry(key);
        }

        return table[id]->data;
    }

    vector<string> keys()
    {
        vector<string> keys_vec;
        for (auto &entry : table)
        {
            keys_vec.push_back(entry->key);
        }
    }

    typedef typename vector<HashEntry*>::iterator table_it;
    class Iterator
    {
        table_it current;
        vector<HashEntry*> *table_ref;
    public:

        Iterator(const table_it& _curr,  vector<HashEntry*>  *_table_ref)
            :current(_curr), table_ref(_table_ref)
        {}
        //prefix
        Iterator& operator++() 
        { 
            while(++current != table_ref->end())
            {
                if(*current != nullptr)
                {
                    break;
                }
            }
            return *this; 
        } 

        bool operator!=(const Iterator& other)
        {
            return current != other.current;
        }

        const T& operator*() 
        {
            return (*current)->data; 
        }
    };

    Iterator begin()
    {
        table_it it = table.begin();
        while(it != table.end())
        {
            if(*it != nullptr)
            {
                break;
            }
            ++it;
        }
        return Iterator(it, &table);
    }

    Iterator end()
    {
        return Iterator(table.end(),&table);
    }

};

int hash_func1(const char* key, int size)
{
    unsigned int hash = 0;
	int c;

	while (c = *key++)
    {
	    hash += c;
    }

	return hash % size;
}



int main()
{

    HashMap<string> hm(40, hash_func1);

    hm["John"] = "Smith";

    hm["Backo"] = "Backov";
    HashMap<string>::Iterator it = hm.begin();

    hm["Bojko"] = "Borisov";

    while(it!= hm.end())
    {
        cout<<*it<<endl;
        ++it;
    }


    return 0;
}
