#include <iostream>
#include <map>
#include <utility>
#include <queue>

using namespace std;

typedef pair <int,int> pii;

int isSolve(pii u);
int isTarget(pii u);
void print_BFS(pii dinh_xet, map<pii, int> visit,queue <pii> openT);
void create_Status(pii dinh_xet, map<pii, int> visit,queue <pii> &openT,map<pii,int>&saveOPENT);

void BFS(int jug1,int jug2,int target)
{
    queue <pii> openT;
    map <pii,int> visit;
    queue <pii> closeT;
    map <pii,int> saveOPENT;

    openT.push(make_pair(0,0));

    while (!openT.empty())
    {
        auto dinh_xet = openT.front();

        visit[dinh_xet]=1;
        openT.pop();
            create_Status(dinh_xet,visit,openT,saveOPENT);
            visit[dinh_xet] = 1;
            print_BFS(dinh_xet,visit,openT);

        if (isTarget(dinh_xet))
        {
            continue;
        }
        // openT.pop();
    }
    
}
void print_BFS(pii dinh_xet, map<pii, int> visit,queue <pii> openT)
{
    cout<<"Xet Dinh : " <<"("<< dinh_xet.first<<","<<dinh_xet.second<<")"<<endl;
    cout<<"OPENT    : ";
    while (!openT.empty())
    {
        cout<<"("<< openT.front().first<<","<<openT.front().second<<")";
        openT.pop();
    }
    cout<<endl;
        cout<<"CLOSE    : ";
    for (auto it = visit.begin();it != visit.end();it++)
    {
        cout<<"("<<it->first.first<<","<<it->first.second<<")";
    }
    cout<<endl<<endl;
    
    
}
void create_Status(pii dinh_xet, map<pii, int> visit,queue <pii> &openT,map<pii,int>&saveOPENT)
{
    int jug1 = 4, jug2 = 3, target = 2;

    if (dinh_xet.first == 0 && dinh_xet.second == 0)
    {
        // fill 1
        if (visit[{jug1, dinh_xet.second}] != 1)
        {
            openT.push({jug1, dinh_xet.second});
            saveOPENT[{jug1, dinh_xet.second}] = 1;
        }
        // fill 2
        if (visit[{dinh_xet.first, jug2}] != 1)
        {
            openT.push({dinh_xet.first, jug2});
            saveOPENT[{dinh_xet.first, jug2}] = 1;
        }
    }
    else
    {
            // fill 1
    if (visit[{jug1, dinh_xet.second}] != 1 && isSolve({jug1,dinh_xet.second}))
    {
   if (saveOPENT[{jug1, dinh_xet.second}]!=1)
            {openT.push({jug1, dinh_xet.second});}
        saveOPENT[{jug1, dinh_xet.second}] = 1;
    }
    // fill 2
    if (visit[{dinh_xet.first, jug2}] != 1 && isSolve({dinh_xet.first, jug2}))
    {   
        if (saveOPENT[{dinh_xet.first, jug2}] != 1)
        {
        openT.push({dinh_xet.first, jug2});
        }
        saveOPENT[{dinh_xet.first, jug2}] = 1;
    }

    // transfer jug 1 -> jug 2
    if (visit[openT.front()] != 1)
    {
        int d = jug2 - dinh_xet.second;
        if (dinh_xet.first >= d)
        {
            int c = dinh_xet.first - d;
            if (visit[{c, jug2}] != 1 && isSolve({c, jug2}))
            {
                if (saveOPENT[{c, jug2}] != 1) {
                openT.push({c, jug2});
                }
                saveOPENT[{c, jug2}] = 1;
            }
        }
        else
        {
            int c = dinh_xet.first + dinh_xet.second;
            if (visit[{0, c}] != 1 && isSolve({0, c}))
            {
                if (saveOPENT[{0, c}] != 1) {
                openT.push({0, c});
                }
                saveOPENT[{0, c}] = 1;
            }
        }
    }
    // transfer jug 2 -> jug 1
    if (visit[openT.front()] != 1)
    {
        int d = jug1 - dinh_xet.first;
        if (dinh_xet.second >= d)
        {
            int c = dinh_xet.second - d;
            if (visit[{jug1, c}] != 1 && isSolve({jug1, c}))
            {
                if (saveOPENT[{jug1, c}] != 1)
                {
                openT.push({jug1, c});
                }
                saveOPENT[{jug1, c}] = 1;
            }
        }
        else
        {
            int c = dinh_xet.first + dinh_xet.second;
            if (visit[{c, 0}] != 1 && isSolve({c, 0}))
            {
                if (saveOPENT[{c, 0}] != 1)
                {
                openT.push({c, 0});
                }
                saveOPENT[{c, 0}] = 1;
            }
        }
    }

    // empty 2
    if (visit[{dinh_xet.first, 0}] != 1 && isSolve({dinh_xet.first, 0}))
    {
        if (saveOPENT[{dinh_xet.first, 0}] !=1 )
        {
        openT.push({dinh_xet.first, 0});
        }
        saveOPENT[{dinh_xet.first, 0}] =1; 
    }
    // empty 1
    if (visit[{0, dinh_xet.second}] != 1 && isSolve({0, dinh_xet.second}))
    {
        if (saveOPENT[{0, dinh_xet.second}] != 1)
        {
        openT.push({0, dinh_xet.second});
        }
        saveOPENT[{0, dinh_xet.second}] = 1;
    }
    }
}
int isSolve(pii u)
{
    int jug1 = 4, jug2 = 3;
    if (u.first < 0 || u.second < 0 || u.first > jug1 || u.second > jug2)
    {
        return 0;
    }
    else
        return 1;
}
int isTarget(pii u)
{
    int target = 2;
    if (u.first == target || u.second == target)
    {
        return 1;
    }
    else
        return 0;
}
int main()
{
    BFS(4,3,2);
}