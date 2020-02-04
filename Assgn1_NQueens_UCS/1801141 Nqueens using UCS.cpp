/*
Name : Rishabh Yadav
Roll Number : 1801141
*/


#include<bits/stdc++.h>
using namespace std;

#define l long int
#define ll long long int
#define ull unsigned long lond int
#define fu(s,e) for(long long int i=s;i<e;++i)
#define fd(s,e) for(long long int i=s;i>=e;--i)
#define elif else if
#define uml unordered_map<long int,long int>
#define umll unordered_map<long long int,long long int>
#define vl vector<long int>
#define vll vector<long long int>
#define usl unordered_set<long int>
#define usll uordered_set<long long int>
#define pl pair<long int,long int>
#define pll pair<long long int,long long int>
#define pb push_back

int SIZE = 8;
struct ChessBoardData
{
    string board;
    int cost;
    ChessBoardData(string board,int cost)
        :board(board),cost(cost)
        {
        }
};
ChessBoardData initChessBoard()
{
    auto i=3;
    string arr;
		fu(0,SIZE)
			fu(0,SIZE)
				arr+='0';
		return ChessBoardData(arr,0);
}
	int find(string arr)
	{
	    int i;
		for(i=0;i<SIZE;i++)
		{
			int flag = 0;
			for(int j=0;j<SIZE;j++)
			{
				if(arr[SIZE*i+j] == '1')
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
				return i;
		}
		return i;
	}
	bool isValid(string arr)
	{
		for(int i=0;i<SIZE;i++)
		{
			int rowSum = 0;
			int colSum = 0;
			for(int j=0;j<SIZE;j++)
			{
				rowSum+=arr[SIZE*i+j]-'0';
				colSum+=arr[SIZE*j+i]-'0';
			}
			if(rowSum > 1 || colSum > 1)
				return false;
		}
		for(int i=0;i<SIZE;i++)
		{
			int leftSum = 0;
			int rightSum = 0;
			for(int j=0;j+i<SIZE;j++)
			{
				leftSum+=arr[SIZE*j+j+i]-'0';
				rightSum+=arr[SIZE*(j+i)+j]-'0';
			}
			if(leftSum > 1 || rightSum > 1)
				return false;
		}
		for(int i=0;i<2*SIZE-1;i++)
		{
			int leftSum = 0;
			int rightSum = 0;
			if(i<SIZE)
			{
			   for(int j=0;i-j>=0;j++)
			   {
				   leftSum+=arr[SIZE*j+i-j]-'0';
			   }
			}
			else
			{
			   for(int j=i-SIZE+1;j<SIZE;j++)
			   {
			       rightSum+=arr[SIZE*j+i-j]-'0';
			   }
			}
			if(leftSum > 1 || rightSum > 1)
				return false;
		}
		return true;
	}

	void display(string arr)
	{
		for(int i=0;i<SIZE;i++)
		{
			for(int j=0;j<SIZE;j++)
			{
				if(arr[SIZE*i+j]=='1')
                    printf("* ");
				else
                    printf("_ ");
			}
		printf("\n");
		}
	}
struct compareBoard
{
    bool operator()(ChessBoardData const& c1, ChessBoardData const& c2)
    {
        return c1.cost > c2.cost;
    }
};
int main()
{
        ChessBoardData sol = initChessBoard();
        priority_queue<ChessBoardData, vector<ChessBoardData>,compareBoard> ucs;
        int count = 1;
        ucs.push(sol);
        while(!(ucs.empty()))
        {
                ChessBoardData c = ucs.top();
                ucs.pop();
                string probableAns = c.board;
                if(!(isValid(probableAns)))
                    continue;
                int i = find(probableAns);
                if(i==SIZE)
                {
                        cout<<"Solution Number"<<count<<"\n";
                        display(probableAns);
                        cout<<"\n\n";
                        count++;
                }
                else
                {
                    for(int j=0;j<SIZE;j++)
                    {
                        probableAns = probableAns.substr(0, SIZE*i+j)+"1"+probableAns.substr(SIZE*i+j+1);
                        ucs.push(ChessBoardData(probableAns,c.cost+1));
                        probableAns = c.board;
                    }
                }

        }
        return 0;
}
