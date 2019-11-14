#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<char>> maze = 
    {{'0', '#', '*', '#', '#', '#', '*', '#'},
     {'*', '#', '*', '*', '*', '#', '*', '#'},
     {'*', '#', '#', '#', '*', '#', '*', '#'},
     {'*', '*', '*', '*', '*', '#', '*', '#'},
     {'#', '#', '#', '#', '*', '#', '*', '#'},
     {'*', '*', '*', '*', '*', '*', '*', '*'},
     {'*', '*', '#', '#', '#', '*', '*', '1'}};

struct Pos
{
    int X,Y;
    Pos(int _x, int _y):X(_x),Y(_y)
    {}
} start(0,0);

char& cell(const Pos &p)
{
    return maze.at(p.Y)[p.X];
}

void printMaze()
{
    for(auto &row : maze)
    {
        for(auto &cell : row)
        {
            cout<<cell<<" ";
        }
        cout<<endl;
    }
}

void push_pos(stack<Pos> &s, const Pos &pos)
{
    try
    {
        if(maze.at(pos.Y).at(pos.X) == '*' ||
            maze.at(pos.Y).at(pos.X) == '1')
        {
            s.push(pos);
        }
    }
    catch(std::out_of_range)
    {}
}

void dfs()
{
    stack<Pos> s;
    s.push(start);

    while (!s.empty())
    {
        Pos pos = s.top();
        s.pop();

        cell(pos) = '.';
        int count = 0;
        for (int x(pos.X + 1), y(pos.Y + 1); count < 2; x -= 2, y -= 2)
        {
            push_pos(s, {pos.X, y});
            push_pos(s, {x, pos.Y});
            count++;
        }

        printMaze();
        cin.get();

    }

}


int main()
{
    dfs();
    printMaze();
    return 0;
}
