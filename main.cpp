#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <random>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
int random_number(const int& a, const int& b)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(a, b);

    return dist(mt);
}
void paths(std::vector<bool> pathnode, int n, std::vector<std::vector<int>>&matrix)
{
    for(int ind1=0; ind1<n; ind1++)
    {
        std::vector <int> row;
        for(int ind2=0; ind2<n; ind2++)
            {
                 row.push_back(0);
            }
        matrix.push_back(row);
    }
    int s = 0;
    int t = n - 1;
    int k, l,v;
    for (int index = 1; index <= t; index++)
    {
        pathnode[index] = false;
    }
        pathnode[s] = true;
        int u = s;
        for (int j = 1; j < n - 1; j++)
        {
            k = random_number(0, n - j - 1);
            l = 0;
        for (v = 0; v < n; v++)
        {
            if (pathnode[v])
                continue;
            if (l == k)
                break;
            l++;
        }
        matrix[u][v] = 1;
        pathnode[v] = true;
        if (v == t)
            break;
        u = v;
    }

}

void Cycles(std::vector<bool> cyclenode,int n,std::vector<std::vector<int>>&matrix)
{
    for(int ind1=0; ind1<n; ind1++)
    {
        std::vector <int> row;
        for(int ind2=0; ind2<n; ind2++)
            {
                 row.push_back(0);
            }
        matrix.push_back(row);
    }
    int initial=0;
    initial=random_number(0,n-1);
    for(int index=0;index<n;index++)
        if(index!=initial)
        {
            cyclenode[index]=false;
        }
     cyclenode[initial]=true;
     int u=0;
     u=initial;
     int k,l;
     for(int ind=0;ind<=n-1;ind++)
     {
         k=random_number(0,n-ind-1);
         l=0;
         int v=0;
         for(v=0;v<n;v++)
         {
             if(cyclenode[v])
                 continue;
             if(l==k)
                 break;
             l++;
         }
         if(u==v)
            ind=ind-1;
         else
         {
          matrix[u][v]=1;
          cyclenode[v]=true;
         }
         if(v==initial)
             break;
         u=v;
     }
}

