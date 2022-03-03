/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS
Lab-no:      Lab-04
Description: Implement Square and multiply
Guidance by: Prof Ami Shah
Date:        08/01/2022
*********************************************************/
#include <bits/stdc++.h>
using namespace std;

vector<int> getBinaryVector(int num)
{
    vector<int> bin;
    while (num > 0)
    {
        bin.insert(bin.begin(), num % 2);
        num /= 2;
    }
    return bin;
}

void print_vec(vector<int> c)
{
    for (auto x : c)
    {
        cout << x << " ";
    }
    cout << endl;
}

int squareAndMultiply(int base, int power, int mod)
{
    int z = 1;
    vector<int> binVec = getBinaryVector(power);
    // print_vec(binVec);
    for (int i = 0; i < binVec.size(); i++)
    {
        int x = binVec[i];
        z = (z * z) % mod;
        if (x == 1)
        {
            z = (z * base) % mod;
        }
    }
    return z;
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int base, power, mod;
        cin >> base >> power >> mod;
        cout << squareAndMultiply(base, power, mod);
    }
    return 0;
}