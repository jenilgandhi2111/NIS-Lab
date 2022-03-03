/*********************************************************
Written by:  Jenil J Gandhi
Subject:     Network and information security
Lab-no:      Lab-07
Description: Implement elgamal cryptosystem
Guidance by: Prof Ami Shah
Date:        02/02/2022
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
int getRandomseedV1(int low = 0, int high = INT_MAX)
{
    srand(time(0));
    return low + (rand() % high);
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

// write this function.
int generatePrimes()
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
    return p;
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
int getInverse(int a, int n)
{
    int ans = extendedEuclidianAlgorithm(a, n);
    if (ans < 0)
    {
        ans += n;
    }
    return ans;
}
vector<int> getZStar(int num)
{
    vector<int> zstar;
    for (int i = 2; i < num; i++)
    {
        if (__gcd(i, num) == 1)
        {
            zstar.push_back(i);
        }
    }
    return zstar;
}

bool checkPrimitiveRoot(int n, int p)
{
    set<int> mods;
    for (int i = 0; i < p - 1; i++)
    {
        mods.insert(squareAndMultiply(n, i, p));
    }
    // cout << mods.size() << endl;
    if (mods.size() == p - 1)
    {
        return true;
    }
    return false;
}

int selectE1(int p)
{
    vector<int> zstar = getZStar(p);
    for (auto x : zstar)
    {
        if (checkPrimitiveRoot(x, p))
        {
            return x;
        }
    }
    return -1;
}

int selectD(int num)
{
    vector<int> zstar = getZStar(num);
    while (true)
    {
        int seed = getRandomseedV1(0, zstar.size());
        int value = zstar[seed];
        if (value >= 1 && value <= num - 2)
        {
            return value;
        }
    }
}

class PublicKey
{
public:
    int e1, e2, p;
    PublicKey() {}
    PublicKey(int e1, int e2, int p)
    {
        this->e1 = e1;
        this->e2 = e2;
        this->p = p;
    }
};

class KeySetup
{
public:
    PublicKey publickey;
    int privateKey;
    KeySetup(PublicKey publickey, int privateKey)
    {
        this->publickey = publickey;
        this->privateKey = privateKey;
    }
};

KeySetup generateKeys()
{
    int p = generatePrimes();
    cout << "P: " << p << endl;
    int e1 = selectE1(p);
    cout << "E1: " << e1 << endl;
    int d = selectD(p);
    int e2 = squareAndMultiply(e1, d, p);
    cout << "E2: " << d << endl;
    PublicKey publickey = PublicKey(e1, e2, p);
    int privateKey = d;
    KeySetup setup = KeySetup(publickey, privateKey);
    return setup;
}

vector<int> ElgamalEncryption(int number, PublicKey publicKey)
{
    vector<int> encrypted_message;
    vector<int> zstar = getZStar(publicKey.p);
    int seed = getRandomseedV1(0, zstar.size());
    int r = zstar[seed];
    // r = 4;
    int c1 = squareAndMultiply(publicKey.e1, r, publicKey.p);
    int c2 = (squareAndMultiply(publicKey.e2, r, publicKey.p) * (number % publicKey.p)) % publicKey.p;
    encrypted_message.push_back(c1);
    encrypted_message.push_back(c2);
    return encrypted_message;
}

int ElgamalDecryption(vector<int> cipherText, int privateKey, int p)
{
    int c1 = cipherText[0];
    int c2 = cipherText[1];
    int ans = getInverse(squareAndMultiply(c1, privateKey, p), p);
    ans = ans * (c2 % p);
    ans = ans % p;
    return ans;
}

int main()
{
    fin();
    int tt;
    cin >> tt;
    int c = 0;
    cout << "-------------------------------------------------------------------\n";
    while (tt--)
    {
        cout << "Case #" << ++c << endl;
        int message;
        cin >> message;
        KeySetup keysetup = generateKeys();
        PublicKey publickey = keysetup.publickey;
        int privateKey = keysetup.privateKey;
        vector<int> enc = ElgamalEncryption(message, publickey);
        cout << "C1:" << enc[0] << " C2:" << enc[1] << endl;
        cout << "DecryptedText: " << ElgamalDecryption(enc, privateKey, publickey.p);
        cout << "\n-------------------------------------------------------------------\n";
    }
    return 0;
}