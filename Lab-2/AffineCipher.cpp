/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS
Lab-no:      Lab-02
Description: Implement Affine Cipher
Guidance by: Prof Ami Shah
Date:        16/12/2021
*********************************************************/
#include <bits/stdc++.h>
using namespace std;
int keys[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
int extendedEuclidianAlgorithm(int a, int n)
{
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
void print_string(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        cout << char(s[i] + 'a');
    }
    cout << endl;
}
string additiveEncrypt(string data, int key)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = (data[i] + key) % 26;
    }
    return data;
}

string additiveDecrypt(string data, int key)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = (data[i] - key) % 26;
        if (data[i] < 0)
        {
            data[i] = data[i] + 26;
        }
    }
    return data;
}
string encrypt(string data, int key1, int key2)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = (((data[i] - 'a') * key1)) % 26;
    }
    cout << "Step-1: > After (P x K1)%26:    ";
    print_string(data);
    data = additiveEncrypt(data, key2);
    cout << "Step-2: > After (T + K2)%26:    ";
    print_string(data);
    return data;
}

string decrypt(string data, int key1, int key2)
{
    data = additiveDecrypt(data, key2);
    cout << "Step-3: > After (C - K2)%26:    ";
    print_string(data);

    for (int i = 0; i < data.size(); i++)
    {
        data[i] = (extendedEuclidianAlgorithm(key1, 26) * data[i]) % 26;
    }
    cout << "Step-4: > After (T * K1^-1)%26: ";
    print_string(data);
    return data;
}
int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        string message;
        cin >> message;
        srand(time(NULL));
        int k2 = -1;
        while (true)
        {
            k2 = rand() % 26;
            if (k2 != 0)
            {
                break;
            }
        }
        int k1 = keys[(rand()) % 12];

        cout << k1 << " " << k2 << endl;
        cout << "----------------------Encryption----------------------\n"
             << endl;
        string encryptedText = encrypt(message, k1, k2);
        cout << endl;

        cout << "----------------------Decryption----------------------\n"
             << endl;
        string decryptedText = decrypt(encryptedText, k1, k2);
        cout << endl;
        cout << "Decrypted Text is :";
        print_string(decryptedText);
    }
    return 0;
}