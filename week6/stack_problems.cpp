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
        if(maze.at(pos.Y).at(pos.X) == '*' )
        {
            s.push(pos);
        }
    }
    catch(std::out_of_range)
    {}
}
//task1
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


// F0(x) = x
// F1(x) = 2*x
// Fn(x) = 3*Fn-1(x) + 2*Fn-2(x)
void findFn(int x, int n)
{
    int cnt = 1;
    stack<int> s;
    s.push(x);
    s.push(2*x);

    while(cnt < n)
    {
        int f1 = s.top();
        s.pop();
        int f2 = s.top();
        s.pop();
        s.push(f1);
        s.push(3*f1 + 2*f2);

        cout<<s.top()<<endl;

        cnt++;
    }
}


int main()
{
    // dfs();
    findFn(1,3);
    return 0;
}
