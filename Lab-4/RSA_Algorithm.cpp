/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS
Lab-no:      Lab-04
Description: Implement RSA Algorithm
Guidance by: Prof Ami Shah
Date:        08/01/2022
*********************************************************/
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <cstdlib>
int K = 500;
float ACCEPTING_FACTOR = 0.7;
int PRIME_RANGE = 200;
using namespace std;
void fin()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}
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
        cout << setw(20) << x << " ";
    }
    cout << setw(20) << endl;
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
int getRandomSeed()
{
    srand(time(0));
    int num = (rand()) % INT_MAX;
    return num % 2 == 0 ? num - 1 : num;
}

bool millerRabinPrimalityTest(int n)
{
    int k, m = -1;
    int nm1 = n - 1;
    for (int i = 1; pow(2, i) < n; i++)
    {
        if (nm1 % int(pow(2, i)) == 0)
        {
            k = i;
        }
    }
    m = nm1 / int(pow(2, k));
    int upper = 2, lower = n - 2;
    int a = 2 + getRandomSeed() % (n - 4);
    int b = squareAndMultiply(a, m, n);

    if (b % n == 1)
    {
        return true;
    }
    for (int i = 0; i < k - 1; i++)
    {
        if (b % n == n - 1)
        {
            return true;
        }
        else
        {
            b = (b * b) % n;
        }
    }
    return false;
}

vector<int> generatePrimes()
{
    int p = -1, q;
    bool flag1 = false, flag2 = false;
    while (!flag1)
    {
        int temp;
        temp = getRandomSeed() % (PRIME_RANGE);
        int pos = 0, neg = 0;
        for (int i = 0; i < K; i++)
        {
            if (millerRabinPrimalityTest(temp))
            {
                pos++;
            }
            else
            {
                neg++;
            }
        }
        if (pos >= ACCEPTING_FACTOR * K)
        {
            flag1 = true;
            p = temp;
        }
    }
    cout << setw(20) << "P: " << p << endl;

    // Generating Q
    // Sleeping to get different random numbers
    Sleep(1000);

    while (!flag2)
    {
        int temp;
        temp = getRandomSeed() % (PRIME_RANGE);
        int pos = 0, neg = 0;
        for (int i = 0; i < K; i++)
        {
            if (millerRabinPrimalityTest(temp))
            {
                pos++;
            }
            else
            {
                neg++;
            }
        }
        if (pos >= ACCEPTING_FACTOR * K)
        {
            flag2 = true;
            q = temp;
        }
    }
    cout << setw(20) << "Q: " << q << endl;
    vector<int> primes;
    primes.push_back(p);
    primes.push_back(q);
    return primes;
}
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

int encrypt(int m, int e, int n)
{
    return squareAndMultiply(m, e, n);
}
int decrypt(int c, int d, int n)
{
    return squareAndMultiply(c, d, n);
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

void print_char_vec(vector<char> v)
{
    for (auto x : v)
    {
        cout << x;
    }
    cout << endl;
}
void print_int_vec(vector<int> v)
{
    for (auto x : v)
    {
        cout << x << " ";
    }
    cout << endl;
}

void RSAAlgorithm(string message)
{
    vector<int> primes = generatePrimes();
    int p = primes[0];
    int q = primes[1];
    int n = p * q;
    cout << setw(20) << "N: " << n << endl;
    int totient = (p - 1) * (q - 1);
    cout << setw(20) << "Totient(N): " << totient << endl;
    int e;
    for (int i = 3;; i++)
    {
        if (__gcd(totient, i) == 1)
        {
            e = i;
            break;
        }
    }
    cout << setw(20) << "Public key (n,e): (" << n << "," << e << ")" << endl;
    int d = getInverse(e, totient);
    cout << setw(20) << "Private key (n,d): (" << n << "," << d << ")" << endl;

    //  ******************ENCRYPTION********************

    vector<int> enc;
    for (int i = 0; i < message.size(); i++)
    {
        enc.push_back(encrypt(message[i], e, n));
    }
    cout << setw(20) << "Encrypted Text ----> ";
    print_int_vec(enc);

    //  ******************DECRYPTION********************
    vector<char> dec;
    for (int i = 0; i < message.size(); i++)
    {
        dec.push_back(char(decrypt(enc[i], d, n)));
    }
    cout << setw(20) << "Decrypted Text ----> ";
    print_char_vec(dec);
}

int main()
{
    fin();
    int tt;
    int c = 0;
    cin >> tt;
    cout << "------------------------------------------------------------------\n";
    while (tt--)
    {
        cout << "Case #" << ++c << endl;
        string message;
        cin >> message;
        RSAAlgorithm(message);
        cout << "------------------------------------------------------------------\n";
    }
    return 0;
}