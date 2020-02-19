/*
Name : Rishabh Yadav
Roll Number : 1801141
*/

#include<bits/stdc++.h>
using namespace std;

#define li long int
#define ll long long int
#define ull unsigned long lond int
#define fu(i,s,e) for(long long int i=s;i<e;++i)
#define fd(i,s,e) for(long long int i=s;i>=e;--i)
#define elif else if
#define uml unordered_map<long int,long int>
#define umll unordered_map<long long int,long long int>
#define pl pair<long int,long int>
#define vl vector<long int>
#define vll vector<long long int>
#define usl unordered_set<long int>
#define sl set<long int>
#define usll uordered_set<long long int>
#define pl pair<long int,long int>
#define pll pair<long long int,long long int>
#define pb push_back
typedef  pair<li, li> iPair;
void delV(vector<vector<pl>>&g,li u)
{

    li l=g[u].size();
    for(long int i=0;i<l;++i)
    {
        
        for(long int j=0;j<g[g[u][i].first].size();++j)
        {
            if(g[g[u][i].first][j].first==u)
            {
               g[g[u][i].first].erase(g[g[u][i].first].begin()+j);
            }
                
        }  
    }
    g[u].clear();
    li k=0;
}
struct Graph
{
    li V, E;
    vector< pair<int, iPair> > edges;
    Graph(int V)
    {
        this->V = V;
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w,{u,v}});
    }

    int kruskalMST();
};

struct DisjointSets
{
    int *parent, *rnk;
    int n;

    DisjointSets(int n)
    {

        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            parent[i] = i;
        }
    }

    int find(int u)
    {

        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else 
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::kruskalMST()
{
    int mst_wt = 0; 

    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v)
        {
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

li MSTheuristic(vector<vector<pl>>g,int currCity)
{
    Graph graph(g.size()-1);
    int k=0;
    for(long int i=0;i<g.size();++i)
    {
        
        if(i!=currCity)
        {
            for(auto j:g[i])
            {
                if(i<j.first&&g[i].size()>0&&j.first!=currCity)
                {
                    graph.addEdge(i,j.first,j.second);
               
                }
            }
        }
    }
    return graph.kruskalMST();
}

int opFind(vector<pl> opNode,int v)
{
    for(int i=0;i<opNode.size();++i)
    {
        if(opNode[i].first==v)
            return i;
    }
    return -1;
}
void Astar(li **adjMatrix,vector<vector<pl>>&g,int v)
{
    li minDistance=0,heuCost,currentCity,lastCity=0;
    usl visited;
    vl path;
    vector<pl> opNode;
    heuCost=minDistance+adjMatrix[0][0]+MSTheuristic(g,0);
    opNode.pb({0,heuCost});
    while(visited.size()!=v)
    {
        int minIndex=0;
        for(int i=1;i<opNode.size();++i)
        {
            if(opNode[minIndex].second>opNode[i].second)
                minIndex=i;
        }
        currentCity=opNode[minIndex].first;
        visited.insert(currentCity);
        path.pb(currentCity);
        minDistance+=adjMatrix[lastCity][currentCity];
        opNode.erase(opNode.begin()+minIndex);
        for(int i=0;i<g[currentCity].size();++i)
        {
            if(visited.find(g[currentCity][i].first)==visited.end())
            {  
                heuCost=MSTheuristic(g,currentCity)+minDistance+adjMatrix[currentCity][g,g[currentCity][i].first];
                int currOpIndex=opFind(opNode,g[currentCity][i].first);
                if(currOpIndex==-1)
                     opNode.pb({g[currentCity][i].first,heuCost});
                else
                {
                    if(heuCost<opNode[currOpIndex].second)
                        opNode[currOpIndex].second=heuCost;
                    
                }
                
            }
        }
        if(g[currentCity].size())
            delV(g,currentCity);
        lastCity=currentCity;
    }
minDistance+=adjMatrix[lastCity][0];
printf("The Path for the salesman is : ");
for(auto i:path)
{
    printf("%ld -> ",i);
}
    printf("%ld\nMinimum Possible Distance is : %ld",0,minDistance);
}
int main()
{
    li v,**adjMatrix;
    printf("Enter the number of cities : ");
    cin>>v;
    vector<vector<pl>>g(v);
    adjMatrix=new li *[v];
    for(long int i=0;i<v;++i)
        adjMatrix[i]=new li [v];
    printf("Enter the distance between cities in adjacency matrix : \n");
    for(long int i=0;i<v;++i)
    {
        for(long int j=0;j<v;++j)
        {
            scanf("%ld",&adjMatrix[i][j]);
            if(adjMatrix[i][j]!=0)
                g[i].pb({j,adjMatrix[i][j]});
        }
    }
    Astar(adjMatrix,g,v);
    printf("\n");
    system("pause");
    return 0;
}
