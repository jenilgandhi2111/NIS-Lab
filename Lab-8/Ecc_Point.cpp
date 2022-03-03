/*********************************************************
Written by:  Jenil J Gandhi
Subject:     Network Information security
Lab-no:      Lab-08
Description: Implement Point generation for ECC
Guidance by: Prof Ami Shah.
Date:        17/02/2022
*********************************************************/
#include <bits/stdc++.h>
using namespace std;

class EccParameters
{
public:
    int a, b, p;
};

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

int squareAndMultiply(int base, int power, int mod)
{
    int z = 1;
    vector<int> binVec = getBinaryVector(power);
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

vector<pair<int, int>> GeneratePoints(EccParameters params)
{
    vector<pair<int, int>> points;
    for (int x = 0; x < params.p; x++)
    {
        int y = (int(x * x * x) + params.a * (x) + params.b) % params.p;
        if (y == 0)
        {
            pair<int, int> point1 = make_pair(x, 0);
            points.push_back(point1);
            continue;
        }
        int qr = squareAndMultiply(y, (params.p - 1) / 2, params.p);
        if (qr == 1 || y == 1)
        {
            int initial = y;
            while (!((int(sqrt(initial)) * int(sqrt(initial))) == int(initial)))
            {
                initial = initial + params.p;
            }
            pair<int, int> point1 = make_pair(x, int(sqrt(initial)) % params.p);
            pair<int, int> point2 = make_pair(x, params.p - int(sqrt(initial)));
            points.push_back(point1);
            points.push_back(point2);
        }
    }
    return points;
}

void printPoints(vector<pair<int, int>> points)
{
    for (auto x : points)
    {
        cout << "<" << x.first << " , " << x.second << ">\n";
    }
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int a, b, p;
        cin >> a >> b >> p;
        EccParameters curveParams;
        curveParams.a = a;
        curveParams.b = b;
        curveParams.p = p;
        vector<pair<int, int>> points = GeneratePoints(curveParams);
        printPoints(points);
    }
    return 0;
}