#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
using namespace std;

template<typename T>
class HashTable
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
    HashTable(int size, int (*_hash)(const char*, int))
        :table(size, nullptr), hash(_hash)
    {}

    ~HashTable()
    {
        for (auto &entry : table)
        {
            delete entry;
        }
    }

    T& operator[](const string& key)
    {
        int id = hash(key.c_str(), table.size());
        
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

    bool hasKey(const string& key)
    {
        int id = hash(key.c_str(), table.size());
        
        if(id > table.size())
        {
            return false;
        }

        return table[id] != nullptr;
    }

    vector<string> keys()
    {
        vector<string> keys_vec;
        for (auto &entry : table)
        {
            if(entry != nullptr)
            {
                keys_vec.push_back(entry->key);
            }
        }
        return keys_vec;
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
        for(; it != table.end(); ++it)
        {
            if(*it != nullptr)
            {
                break;
            }
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


void count_word(const string &filename)
{

    ifstream file(filename);
    string line; 
    HashTable<int> w_counter(100, hash_func1);
    while (getline(file, line))
    {
        int word_start = 0;
        int word_end = 0;
        do
        {
            word_end = line.find(' ', word_start);
            word_end = (word_end == string::npos)? line.size() : word_end;
            
            string word = line.substr(word_start, word_end - word_start);
            if(w_counter.hasKey(word))
            {
                w_counter[word]++;
            }
            else
            {
                w_counter[word] = 1;
            }
            
            word_start = word_end + 1;
        } while (word_end != line.size());
    }

    for (auto &key : w_counter.keys())
    {
        cout << key << " " << w_counter[key] << endl;
    }

}


int main()
{

    HashTable<string> ht(40, hash_func1);

    ht["John"] = "Smith";
    ht["Ivan"] = "Ivanov";
    ht["Pehso"] = "Peshov";


    HashTable<string>::Iterator it = ht.begin();
    while(it!= ht.end())
    {
        cout<<*it<<endl;
        ++it;
    }
    cout<<endl;

    count_word("text.txt");


    return 0;
}
