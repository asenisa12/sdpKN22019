#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <map>
using namespace std;


class DWGraph
{
    unordered_map<int, vector<int>> vertices;

    struct edge_hash
    {
        //Cantor piring function
        int operator() (const std::pair<int, int> &pair) const
        {
            int v1 = pair.first;
            int v2 = pair.second;

            return ((v1 + v2) * (v1 + v2 + 1))/2 + v2;
        }
    };

    unordered_map<pair<int,int>, int, edge_hash> edges;
public:

    void addEdge(int vertex1, int vertex2, int weight)
    {
        vertices[vertex1].push_back(vertex2);
        edges[make_pair(vertex1, vertex2)] = weight;
    }

    void print()
    {
        for (auto &vertex : vertices)
        {
            cout << "edge (" << vertex.first << ")\n";
            for(auto &neigh : vertex.second)
            {
                cout << "--- to " << neigh << " --- weight - ";
                cout << edges[make_pair(vertex.first, neigh)] << endl;
            }
            cout << endl;
        }
    }

// Task 2
    bool areConnected(int vertex1, int vertex2)
    {
        if(vertex1 == vertex2)
        {
            return true;
        }

        unordered_map<int,bool> visited;
        queue<int> q;
        q.push(vertex1);

        while(!q.empty())
        {
            int v = q.back();
            visited[v] = true;
            q.pop();

            for(auto &neigh : vertices[v])
            {
                if(neigh == vertex2)
                {
                    return true;
                }

                if(!visited[neigh])
                {
                    q.push(neigh);
                }
            }
        }
        return false;
    }


// Task 3
    void dfs(vector<int> cur_path,int weight, int cur_vert, int vertex2, 
        unordered_map<int,bool> &visited, map<int, vector<vector<int>> > &paths)
    {
        weight += cur_path.empty()? 0 : edges[make_pair(cur_path.back(), cur_vert)];
        cur_path.push_back(cur_vert);
        visited[cur_vert] = true;

        for(auto &neigh : vertices[cur_vert])
        {
            if(neigh == vertex2)
            {
                int new_weight = weight + edges[make_pair(cur_vert, neigh)];
                paths[new_weight].push_back(cur_path);
                paths[new_weight].back().push_back(neigh);
            }

            if(!visited[neigh])
            {
                dfs(cur_path, weight, neigh, vertex2, visited, paths);
            }
        }
    }
    void printKSmallest(int vertex1, int vertex2, int K)
    {
        map<int, vector<vector<int>> > paths;
        unordered_map<int,bool> visited;
        stack<int> s;

        s.push(vertex1);

        vector<int> cur_path;
        dfs(cur_path, 0, vertex1, vertex2, visited, paths);

        for(auto & m : paths)
        {
            for(auto &path : m.second)
            {
                if(K-- == 0)
                {
                    return;
                }
                cout<<"weight: "<<m.first<<" ---";
                for(auto &v : path)
                {
                    cout << " " << v;
                }
                cout << endl;
            }

        }
    }

};



int main()
{
    DWGraph d;
    d.addEdge(1,5,100);
    d.addEdge(1,2,10);
    d.addEdge(2,3,30);
    d.addEdge(2,4,20);
    d.addEdge(3,5,40);
    d.addEdge(4,5,10);
    d.addEdge(4,6,5);
    d.addEdge(6,5,5);

    d.print();

    cout << (d.areConnected(6,8)?"":"not ")<<"connected"<<endl;

    d.printKSmallest(1,5,2);

    return 0;
}