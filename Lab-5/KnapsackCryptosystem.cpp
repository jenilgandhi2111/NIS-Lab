/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS
Lab-no:      Lab-05
Description: Implement Knapsack Cryptosystem
Guidance by: Prof Ami Shah
Date:        13/01/2022
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
            return t1;
        }
        else
        {
            return t1;
        }
    }
}
int getInverse(int a, int n)
{
    int ans = extendedEuclidianAlgorithm(a, n);
    if (ans < 0)
    {
        ans += n;
    }
    return ans;
}
void print_vec(vector<int> v)
{
    for (auto x : v)
    {
        cout << x << " ";
    }
    cout << endl;
}
int getRandomseed(int low = 0, int high = INT_MAX)
{
    srand(time(0));
    return low + (rand() % high);
}

vector<int> generateSuperincreasingSequence(int length)
{
    vector<int> seq;
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        int seed;
        if (i == 0)
        {
            seed = getRandomseed(0, 10);
        }
        else if (i == 1)
        {
            seed = getRandomseed(seq[0] + 1, seq[0] + 100);
        }
        else
        {
            seed = getRandomseed(sum + 1, sum + 100);
        }
        seq.push_back(seed);
        sum += seed;
    }
    seq.push_back(sum);
    return seq;
}
vector<int> getWeightedKey(vector<int> publicKey, int w, int m)
{
    vector<int> private_key;
    for (auto x : publicKey)
    {
        private_key.push_back((w * x) % m);
    }
    return private_key;
}

class keySetup
{
public:
    vector<int> publickKey;
    vector<int> privateKey;
    int m, w;
};
keySetup keyGeneration(int len)
{
    vector<int> privateKey = generateSuperincreasingSequence(len);
    int sum = privateKey.back();
    privateKey.pop_back();
    // print_vec(privateKey);
    int m = sum;
    int w;
    for (int i = 3; i < m; i++)
    {
        if (__gcd(i, m) == 1)
        {
            w = i;
            break;
        }
    }
    // cout << "Sum: " << sum << endl;
    // cout << "M: " << m << " W:" << w << endl;
    vector<int> publicKey = getWeightedKey(privateKey, w, m);
    // print_vec(publicKey);
    keySetup setup;
    setup.privateKey = privateKey;
    setup.publickKey = publicKey;
    setup.m = m;
    setup.w = w;
    return setup;
}
vector<int> getBinaryVector(int num, int len)
{
    vector<int> bin;
    while (num > 0)
    {
        bin.insert(bin.begin(), num % 2);
        num /= 2;
        len--;
        if (len == 0)
        {
            break;
        }
    }
    if (len > 0)
    {
        while (len > 0)
        {
            bin.insert(bin.begin(), num % 2);
            len--;
        }
    }
    return bin;
}
int encrypt(int message, vector<int> public_key, int m, int w)
{
    vector<int> binVec = getBinaryVector(message, public_key.size());
    int s = 0;
    cout << "Binary Vector:";
    print_vec(binVec);
    for (int i = 0; i < public_key.size(); i++)
    {
        if (binVec[i] == 1)
        {
            s += (public_key[i]);
        }
    }
    return s;
}
int decrypt(int s, int w, int m, vector<int> privateKey)
{
    int inverse = getInverse(w, m);
    inverse = (inverse * s) % m;
    cout << "D: " << inverse << endl;
    vector<int> ans;
    for (int i = privateKey.size() - 1; i >= 0; i--)
    {
        if (inverse >= privateKey[i])
        {
            inverse -= privateKey[i];
            ans.push_back(1);
        }
        else
        {
            ans.push_back(0);
        }
    }
    reverse(ans.begin(), ans.end());
    cout << "After Decryption:";
    print_vec(ans);
}
int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int message;
        cin >> message;
        int len = log2(message);
        cout << "Length of key: " << len << endl;
        keySetup setup = keyGeneration(len + 2);
        cout << "Public Key:";
        print_vec(setup.publickKey);
        cout << "Private Key:";
        print_vec(setup.privateKey);
        cout << "(M,W):(" << setup.m << "," << setup.w << ")\n";
        int c = encrypt(message, setup.publickKey, setup.m, setup.w);
        cout << "Cipher Text: " << c << endl;
        decrypt(c, setup.w, setup.m, setup.privateKey);
    }
}