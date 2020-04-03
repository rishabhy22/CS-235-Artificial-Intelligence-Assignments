#include <bits/stdc++.h>
using namespace std;

#define l long int
#define ll long long int
#define ull unsigned long lond int
#define fu(i, s, e) for (long long int i = s; i < e; ++i)
#define fd(i, s, e) for (long long int i = s; i >= e; --i)
#define elif else if
#define uml unordered_map<long int, long int>
#define umll unordered_map<long long int, long long int>
#define vl vector<long int>
#define vll vector<long long int>
#define usl unordered_set<long int>
#define usll uordered_set<long long int>
#define pl pair<long int, long int>
#define pll pair<long long int, long long int>
#define pb push_back
#define IOS                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

void f_io()
{
    IOS;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

random_device rd;
mt19937 re(rd());
uniform_int_distribution<int> dist(1, 2);

int randPlayer()
{
    return dist(re);
}

struct MiniMaxNode
{
    int stcksLft, bestOutcome = 0;
    ll parentNode, c1 = -1, c2 = -1, c3 = -1;
    MiniMaxNode(int stcksLft, int parentNode)
        : stcksLft(stcksLft), parentNode(parentNode)
    {
    }
    MiniMaxNode() {}
};

struct GameTree
{
    vector<vector<MiniMaxNode>> nodes;
};

GameTree fillBestOutcome(GameTree g)
{
    ll par;
    fd(i, g.nodes.size() - 1, 1)
    {
        fu(j, 0, g.nodes[i].size())
        {
            par = g.nodes[i][j].parentNode;
            if (!(i % 2))
            {
                g.nodes[i - 1][par].bestOutcome = g.nodes[i - 1][par].bestOutcome < g.nodes[i][j].bestOutcome ? g.nodes[i - 1][par].bestOutcome : g.nodes[i][j].bestOutcome;
                if (g.nodes[i - 1][par].bestOutcome == 0)
                {
                    g.nodes[i - 1][par].bestOutcome = 1;
                }
            }
            else
            {
                g.nodes[i - 1][par].bestOutcome = g.nodes[i - 1][par].bestOutcome > g.nodes[i][j].bestOutcome ? g.nodes[i - 1][par].bestOutcome : g.nodes[i][j].bestOutcome;
                if (g.nodes[i - 1][par].bestOutcome == 0)
                {
                    g.nodes[i - 1][par].bestOutcome = -1;
                }
            }
        }
    }
    return g;
}

GameTree cnstrctGameTree(int totSticks)
{
    cout << "Training AI please wait...\n";
    GameTree g;
    int k;
    g.nodes.pb(vector<MiniMaxNode>());
    g.nodes[0].pb(MiniMaxNode(totSticks, -1));
    fu(i, 1, totSticks + 1)
    {
        if (!(i % 3))
            cout << "...\n";
        g.nodes.pb(vector<MiniMaxNode>());
        fu(j, 0, g.nodes[i - 1].size())
        {
            k = g.nodes[i - 1][j].stcksLft;
            if (k == 0)
                continue;
            if (k > 0)
            {
                g.nodes[i].pb(MiniMaxNode(--k, j));
                g.nodes[i - 1][j].c1 = g.nodes[i].size() - 1;
                if (!k)
                {
                    if (!(i % 2))
                        g.nodes[i][g.nodes[i].size() - 1].bestOutcome = 1;
                    else
                        g.nodes[i][g.nodes[i].size() - 1].bestOutcome = -1;
                }
            }
            if (k > 0)
            {
                g.nodes[i].pb(MiniMaxNode(--k, j));
                g.nodes[i - 1][j].c2 = g.nodes[i].size() - 1;
                if (!k)
                {
                    if (!(i % 2))
                        g.nodes[i][g.nodes[i].size() - 1].bestOutcome = 1;
                    else
                        g.nodes[i][g.nodes[i].size() - 1].bestOutcome = -1;
                }
            }
            if (k > 0)
            {
                g.nodes[i].pb(MiniMaxNode(--k, j));
                g.nodes[i - 1][j].c3 = g.nodes[i].size() - 1;
                if (!k)
                {
                    if (!(i % 2))
                        g.nodes[i][g.nodes[i].size() - 1].bestOutcome = 1;
                    else
                        g.nodes[i][g.nodes[i].size() - 1].bestOutcome = -1;
                }
            }
        }
    }
    return g;
}

void AITurn(GameTree &g, ll &currNode, int &pick, int &lvl)
{
    int best = INT_MIN;
    ll nxtBstNode;
    if (g.nodes[lvl][currNode].c1 != -1)
    {
        if (best < g.nodes[lvl + 1][g.nodes[lvl][currNode].c1].bestOutcome)
        {
            best = g.nodes[lvl + 1][g.nodes[lvl][currNode].c1].bestOutcome;
            nxtBstNode = g.nodes[lvl][currNode].c1;
            pick = 1;
        }
    }
    if (g.nodes[lvl][currNode].c2 != -1)
    {
        if (best < g.nodes[lvl + 1][g.nodes[lvl][currNode].c2].bestOutcome)
        {

            best = g.nodes[lvl + 1][g.nodes[lvl][currNode].c2].bestOutcome;
            nxtBstNode = g.nodes[lvl][currNode].c2;
            pick = 2;
        }
    }
    if (g.nodes[lvl][currNode].c3 != -1)
    {
        if (best < g.nodes[lvl + 1][g.nodes[lvl][currNode].c3].bestOutcome)
        {
            best = g.nodes[lvl + 1][g.nodes[lvl][currNode].c3].bestOutcome;
            nxtBstNode = g.nodes[lvl][currNode].c3;
            pick = 3;
        }
    }

    currNode = nxtBstNode;
    ++lvl;
}

void afterPlay(GameTree &g, ll &currNode, int &lvl, int noOfSticks)
{
    ll nxtBstNode;
    if (g.nodes[lvl][currNode].c1 != -1)
    {
        if (g.nodes[lvl + 1][g.nodes[lvl][currNode].c1].stcksLft == noOfSticks)
        {
            nxtBstNode = g.nodes[lvl][currNode].c1;
        }
    }
    if (g.nodes[lvl][currNode].c2 != -1)
    {
        if (g.nodes[lvl + 1][g.nodes[lvl][currNode].c2].stcksLft == noOfSticks)
        {
            nxtBstNode = g.nodes[lvl][currNode].c2;
        }
    }
    if (g.nodes[lvl][currNode].c3 != -1)
    {
        if (g.nodes[lvl + 1][g.nodes[lvl][currNode].c3].stcksLft == noOfSticks)
        {
            nxtBstNode = g.nodes[lvl][currNode].c3;
        }
    }
    currNode = nxtBstNode;
    ++lvl;
}

void pickSticksAndCheck(int &pick, int &noOfSticks)
{
    cin >> pick;
    while (pick < 1 || pick > 3)
    {
        cout << "Please enter value between 1 and 3 : ";
        cin >> pick;
    }
    while (pick > noOfSticks)
    {
        cout << "Not possible ,Only " << noOfSticks << " sticks left\nEnter Again : ";
        cin >> pick;
    }
    noOfSticks -= pick;
}

int main()
{
    int opNo, playerNo, noOfSticks, pick, lvl = 0, _lvl = 0, win = -1;
    ll currNode = 0, _currNode = 0;
    GameTree g, _g;
    cout << "                         Hello\n\n             Welcome to the game of sticks...\n\nHow do you want to play the game?\n\n"
         << "1) Against AI ?\n      OR\n2) See a game of AI vs. AI ? ...\n---->";
    cin >> opNo;
    while (!(opNo >= 1 && opNo <= 2))
    {
        cout << "Enter valid value ? \n";
        cin >> opNo;
    }
    cout << "Enter the number of sticks : ";
    cin >> noOfSticks;
    while (noOfSticks < 1)
    {
        cout << "Please enter a value between 2 to 53 : ";
        cin >> noOfSticks;
    }

    switch (opNo)
    {
    case 1:
        cout << "\nPlayer 1 : AI\nPlayer 2 : You\nChoosing Starting player randomly...\n";
        playerNo = randPlayer();
        cout << "Player starting is " << playerNo << " .\n";

        // g = cnstrctGameTree(noOfSticks);
        // g = fillBestOutcome(g);
        // fu(i,0,g.nodes.size())
        // {
        //     fu(j,0,g.nodes[i].size())
        //     {
        //         cout << g.nodes[i][j].stcksLft<<":"<<g.nodes[i][j].bestOutcome<<",";
        //     }
        //     cout <<"\n";
        // }

        if (playerNo == 2)
        {
            cout << "Your Turn Initially\nPick between 1 to 3 sticks : ";

            pickSticksAndCheck(pick, noOfSticks);

            playerNo = 1;
        }
        g = cnstrctGameTree(noOfSticks);
        g = fillBestOutcome(g);
        while (noOfSticks > 0)
        {
            cout << "------- " << noOfSticks << " sticks left -------\n";
            if (playerNo == 1)
            {
                AITurn(g, currNode, pick, lvl);

                noOfSticks = g.nodes[lvl][currNode].stcksLft;
                if (noOfSticks == 0)
                    win = 2;
                cout << "AI's Turn\nAI picked " << pick << " sticks\n";
                playerNo = 2;
            }
            else
            {
                cout << "Your Turn\nPick between 1 to 3 sticks : ";

                pickSticksAndCheck(pick, noOfSticks);

                afterPlay(g, currNode, lvl, noOfSticks);

                if (noOfSticks == 0)
                    win = 1;
                playerNo = 1;
            }
        }
        cout << "Player " << win << " wins...\n";
        break;
    case 2:
        cout << "\nPlayer 1 : AI 1\nPlayer 2 : AI 2\nChoosing Starting player randomly...\n";
        playerNo = randPlayer();
        cout << "Player starting is " << playerNo << " .\n";
        cout << "------- " << noOfSticks << " sticks left -------\n";
        if (playerNo == 1)
        {
            cout << "AI 1's Turn Initially\n";
            g = cnstrctGameTree(noOfSticks);
            g = fillBestOutcome(g);

            AITurn(g, currNode, pick, lvl);
            cout <<"AI 1 picked " << pick << " sticks\n";
            noOfSticks = g.nodes[lvl][currNode].stcksLft;
            _g = cnstrctGameTree(noOfSticks);
            _g = fillBestOutcome(_g);
            playerNo = 2;
        }
        else
        {
            cout << "AI 2's Turn Initially\n";
            _g = cnstrctGameTree(noOfSticks);
            _g = fillBestOutcome(_g);

            AITurn(_g, _currNode, pick, _lvl);
            cout <<"AI 2 picked " << pick << " sticks\n";
            noOfSticks = _g.nodes[_lvl][_currNode].stcksLft;
            g = cnstrctGameTree(noOfSticks);
            g = fillBestOutcome(g);
            playerNo = 1;
        }
        while (noOfSticks > 0)
        {
            cout << "------- " << noOfSticks << " sticks left -------\n";
            system("pause");
            if (playerNo == 1)
            {
                AITurn(g, currNode, pick, lvl);
                cout << "AI 1's Turn\nAI 1 picked " << pick << " sticks\n";
                noOfSticks = g.nodes[lvl][currNode].stcksLft;

                if (noOfSticks == 0)
                    win = 2;

                afterPlay(_g,_currNode,_lvl,noOfSticks);

                playerNo = 2;
            }
            else
            {
                AITurn(_g, _currNode, pick, _lvl);
                cout << "AI 2's Turn\nAI 2 picked " << pick << " sticks\n";
                noOfSticks = _g.nodes[_lvl][_currNode].stcksLft;

                if (noOfSticks == 0)
                    win = 1;

                afterPlay(g,currNode,lvl,noOfSticks);

                playerNo = 1;
            }
        }
        cout << "Player " << win << " wins...\n";
        break;
    default:
        break;
    }
    system("pause");
    return 0;
}