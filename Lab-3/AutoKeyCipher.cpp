/*********************************************************
Written by:  Jenil J Gandhi
Subject:     Network Information Security
Lab-no:      Lab-03
Description: Implement Autokey cipher
Guidance by: Prof Mrudang T Mehta
Date:        27/12/2021
*********************************************************/
#include <bits/stdc++.h>
using namespace std;

string encrypt(string plainText, vector<int> &keyStream)
{
    string txt = "";
    for (int i = 0; i < plainText.size() - 1; i++)
    {
        char x = plainText[i];
        keyStream.push_back(x - 'a');
    }
    for (int i = 0; i < keyStream.size(); i++)
    {
        int addend = (keyStream[i] + (plainText[i] - 'a')) % 26;
        txt += (addend + 'a');
    }
    return txt;
}

string decrypt(string txt, vector<int> keyStream)
{
    string dec = "";
    for (int i = 0; i < txt.size(); i++)
    {
        int sub = ((txt[i] - 'a') - keyStream[i]) % 26;
        if (sub < 0)
        {
            sub += 26;
        }

        dec += (sub + 'a');
    }
    return dec;
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        string plainText;
        cout << "Enter plain text:";
        cin >> plainText;
        int key = -1;
        cout << "Enter Key:";
        cin >> key;
        vector<int> keyStream;
        keyStream.push_back(key);
        string encryptedText = encrypt(plainText, keyStream);
        cout << "Encrypted Text: " << encryptedText << endl;
        string decryptedText = decrypt(encryptedText, keyStream);
        cout << "Decrypted Text: " << decryptedText << endl;
    }
    return 0;
}