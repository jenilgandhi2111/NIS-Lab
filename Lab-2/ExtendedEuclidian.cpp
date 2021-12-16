/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS (Network and Information Security)
Lab-no:      Lab-2
Description: Implement Extended Euclidian Algorithm
Guidance by: Prof Ami Shah
Date:        16/12/2021
*********************************************************/
#include <bits/stdc++.h>
using namespace std;

int extendedEuclidianAlgorithm(int a, int n)
{

    if (__gcd(a, n) != 1)
    {
        return -1;
    }
    int r1 = n, r2 = a, t1 = 0, t2 = 1;
    while (r2 > 0)
    {
        int q = r1 / r2;
        int r = r1 - (q * r2);
        r1 = r2;
        r2 = r;
        int t = t1 - (q * t2);
        t1 = t2;
        t2 = t;
    }
    if (r1 == 1)
    {
        if (t1 < 0)
        {
            return t1 + 26;
        }
        else
        {
            return t1;
        }
    }
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int a, n;
        cin >> a >> n;
        cout << extendedEuclidianAlgorithm(a, n);
    }
    return 0;
}