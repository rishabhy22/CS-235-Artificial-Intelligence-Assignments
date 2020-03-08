#include <bits/stdc++.h>
using namespace std;

#define l long int
#define ll long long int
#define ull unsigned long long int
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
#define mp make_pair
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

#define POP_SIZE 200

random_device rd;
mt19937 re(rd());

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1.0);

l randNum(l low,l high)
{ 
    uniform_int_distribution<l> dist(low, high);
    return dist(re);
}

double randDou()
{
    return distribution(generator);
}

struct chromosome
{
    l *grOfStu;
    l fitVal;
    double p;
    vector<vl> gene;
};

struct Population
{
    chromosome c[POP_SIZE];
};

l* getGroup(vl studentMarks,chromosome c)
{
    l groupNum, attrSum, prevSum = LONG_MAX;
    l *ans = new l[2];
    fu(i,0,c.gene.size())
    {
        attrSum = 0;
        fu(j,0,c.gene[i].size())
        {
            attrSum += abs(c.gene[i][j] - studentMarks[j]);
        }
        if(attrSum<prevSum)
        {
            groupNum = i;
            prevSum = attrSum;
        }
    }
    ans[0] = groupNum;
    ans[1] = prevSum;
    return ans;
}
 
chromosome fitness(chromosome c,vector<vl> &marks)
{
    l *fNm, fitVal=0;
    l *grOfStu=new l[marks.size()];
    uml m;
    fu(i, 0, marks.size())
    {
        fNm = getGroup(marks[i], c);
        fitVal += (fNm[1]*fNm[1])%LONG_MAX;
        grOfStu[i] = fNm[0];
        ++m[fNm[0]];
    }
    c.fitVal = fitVal;
    c.grOfStu = grOfStu;
    fu(i, 0, c.gene.size())
    {
        fu(j,0,c.gene[i].size())
        {
            c.gene[i][j] = 0;
        }
    }
    fu(i, 0, marks.size())
    {
        fu(j, 0, c.gene[grOfStu[i]].size())
        {
            c.gene[grOfStu[i]][j] += marks[i][j];
        }
    }
    fu(i,0,c.gene.size())
    {
        fu(j,0,c.gene[i].size())
        {
            if(m[i])
                c.gene[i][j] = c.gene[i][j]/m[i];
        }
    }
    return c;
}

Population initPop(l k,l m,l (*marksMinMax)[2],vector<vl> &marks)
{
    Population p;
    int z = 0;
    l totVal=0;
    while(z++<POP_SIZE)
    {
        fu(i,0,k)
        {
            p.c[z - 1].gene.pb(vl());
            fu(j,0,m)
            {
                p.c[z-1].gene[i].pb(randNum(marksMinMax[j][0], marksMinMax[j][1]));
            }
        }
        totVal += (p.c[z - 1] = fitness(p.c[z - 1], marks)).fitVal;
    }
    fu(z,0,POP_SIZE)
    {
        p.c[z].p = (double)p.c[z].fitVal / totVal;
    }
    return p;
}

Population GAHomogen(Population p,vector<vl> &marks)
{
    l z, i, totVal, itrNo = 500;
    Population nxtP;
    double offset,prob;
    while(itrNo--)
    {
        if(!(itrNo%25))
            printf("...\n");
        z = 0, i = 0, totVal = 0, offset = 0.0, prob = randDou();
        while(z<POP_SIZE)
        {
            offset += (p.c[i].p);
            if (prob>offset)
            {
                nxtP.c[z].gene = p.c[i].gene;
                totVal += (nxtP.c[z] = fitness(nxtP.c[z], marks)).fitVal;
                z++;
                offset = 0.0;
            }
            else
            {
                prob = randDou();
            }
            i++;
            if (i >= POP_SIZE)
                i = 0;
        }
        fu(i,0,POP_SIZE)
        {
            nxtP.c[i].p = (double)nxtP.c[i].fitVal / totVal;
        }
        p = nxtP;
        nxtP = Population();
        totVal = 0;
        l crossNum = randNum(1,POP_SIZE-1), crossPnt;
        usl s;
        s.insert(crossNum);
        vl temp;
        fu(i, 0, POP_SIZE - 1)
        {
            
            if(s.find(i)!=s.end())
                continue;
            while ((s.size() < POP_SIZE / 2) && (s.find(crossNum) != s.end()))
            {
                crossNum = randNum(i+1, POP_SIZE-1);
            }
            s.insert(crossNum);
            crossPnt = randNum(0, p.c[i].gene.size()-1);
            fu(j, crossPnt, p.c[i].gene.size())
            {
                temp = p.c[i].gene[j];
                p.c[i].gene[j] = p.c[crossNum].gene[j];
                p.c[crossNum].gene[j] = temp;
            }
            totVal += (p.c[i] = fitness(p.c[i], marks)).fitVal;
            totVal += (p.c[crossNum] = fitness(p.c[crossNum], marks)).fitVal;
        }
        fu(i, 0, POP_SIZE)
        {
            p.c[i].p = (double)p.c[i].fitVal / totVal;
        }
        if(itrNo&&!(itrNo%25)&&itrNo!=500)
        {
            l mutChrom = randNum(0, POP_SIZE - 1);
            l mutGene = randNum(0, p.c[mutChrom].gene.size());
            totVal -= p.c[mutChrom].fitVal;
            fu(i, 0, p.c[mutChrom].gene[mutGene].size())
            {
                l num = p.c[mutChrom].gene[mutGene][i];
                p.c[mutChrom].gene[mutGene][i] = randNum(num/2,2*num);
            }
            totVal += (p.c[mutChrom] = fitness(p.c[mutChrom], marks)).fitVal;
            p.c[mutChrom].p = (double)p.c[mutChrom].fitVal / totVal;
        }
    }
    return p;
}

bool compFit(chromosome a,chromosome b)
{
    return a.fitVal < b.fitVal;
}

void prntPop(Population p,l n)
{
    fu(i,0,POP_SIZE)
    {
        cout << "Chromosome " << i + 1<< " --> ";
        fu(j,0,p.c[i].gene.size())
        {
            cout << "Group " << j + 1 << " : ";
            fu(k,0,p.c[i].gene[j].size())
            {
                cout << p.c[i].gene[j][k] << " ";
            }
        }
        cout << "\nDivision : ";
        printf("The Homogeneous Division is as follows : \n");
        fu(j, 0, n)
        {
            cout<<"Student "<<j+1<<" : "<<p.c[i].grOfStu[j]+1<<"\n";
        }
        cout << "\n";
        printf("Fitness Value : %ld\n",p.c[i].fitVal);
    }
}

void prntChromo(chromosome c,l n)
{
    cout << "Chromosome " << " :-- \n";
    fu(i,0,c.gene.size())
    {
        cout << "Group " << i + 1 << " : ";
        fu(j,0,c.gene[i].size())
        {
            cout << c.gene[i][j] << " ";
        }
    }
    cout << "\nDivision : ";
    printf("The Homogeneous Division is as follows : \n");
    fu(j, 0, n)
    {
        cout<<"Student "<<j+1<<" : "<<c.grOfStu[j]+1<<"\n";
    }
    cout << "\n";
    printf("Fitness Value : %ld\n",c.fitVal);
}

int main()
{
    l n,m,k,d;
    Population p;
    cout<<"No. of students in classroom ? : ";
    scanf("%ld",&n);
    cout<<"No. of groups to be formed ? : ";
    scanf("%ld",&k);
    cout<<"No.of subjects ? : ";
    scanf("%ld",&m);
    vector<vl> marks(n);
    l marksMinMax[m][2];
    fu(i,0,m)
    {
        marksMinMax[i][0] = LONG_MAX;
        marksMinMax[i][1] = LONG_MIN;
    }
    cout<<"Enter marks of each of "<<n<<" students in "<<m<<" subjects : \n";
    fu(i,0,n)
    {
        printf("Marks of student %ld : ",i+1);
        fu(j,0,m)
        {
            scanf("%ld", &d);
            marks[i].pb(d);
            marksMinMax[j][0] = marksMinMax[j][0] > d ? d : marksMinMax[j][0];
            marksMinMax[j][1] = marksMinMax[j][1] < d ? d : marksMinMax[j][1];
        }
    }
    p = initPop(k, m, marksMinMax, marks);
    printf("Waiting for Calculation...\n");
    p = GAHomogen(p, marks);
    sort(p.c, p.c + POP_SIZE, compFit);
    //To print whole population in descending order uncomment "prntPop(p,n)"
    //prntPop(p,n);
    cout << "\n\n\nBest Group Division :--\n"<<"\n";
    prntChromo(p.c[0], n);
    system("pause");
    return 0;
}