/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS (Network Information Security)
Lab-no:      Lab-2
Description: Implement Multiplicative Cipher
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
string encrypt(string data, int key)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = (((data[i] - 'a') * key)) % 26;
    }
    return data;
}

string decrypt(string data, int key)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = (extendedEuclidianAlgorithm(key, 26) * data[i]) % 26;
    }
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
        int key = keys[(rand()) % 12];
        cout << "Key Used:" << key << endl;
        string encrypted_text = encrypt(message, key);
        cout << "Encrypted Text:" << endl;
        print_string(encrypted_text);
        string decrypted_text = decrypt(encrypted_text, key);
        cout << "Decrypted Text:" << endl;
        print_string(decrypted_text);
    }
    return 0;
}