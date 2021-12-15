/*********************************************************
Written by:  Jenil J Gandhi
Subject:     Network Information Security
Lab-no:      Lab-1
Description: Implement Ceaser Cipher Algorithm
Guidance by: Prof Mrudang T Mehta
Date:        09/12/2021
*********************************************************/
#include <bits/stdc++.h>
using namespace std;
int I_WIDTH = 30;
int C_WIDTH = 3;

void fin()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

string encrypt(string raw_msg, int key)
{
    cout << setw(I_WIDTH) << "Plain Text:";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        cout << setw(C_WIDTH) << raw_msg[i] << " ";
    }
    cout << endl;
    cout << setw(I_WIDTH) << "Plain Text Mapping:";

    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] - 'a';
        cout << setw(C_WIDTH) << int(raw_msg[i]) << " ";
    }
    cout << endl;
    cout << setw(I_WIDTH) << "Key:";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        cout << setw(C_WIDTH) << key << " ";
    }
    cout << endl;
    cout << setw(I_WIDTH) << "Plain Text + Key:";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] + key;
        cout << setw(C_WIDTH) << int(raw_msg[i]) << " ";
    }
    cout << endl;

    cout << setw(I_WIDTH) << "(Plain Text + Key)%26:";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] % 26;
        cout << setw(C_WIDTH) << int(raw_msg[i]) << " ";
    }
    cout << endl;
    cout << setw(I_WIDTH) << "Cipher Text:";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] + 'a';
        cout << setw(C_WIDTH) << raw_msg[i] << " ";
    }
    cout << endl;

    return raw_msg;
}

string decrypt(string raw_msg, int key, bool print = true)
{
    print ? cout << setw(I_WIDTH) << "Cipher Text:" : cout << "";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        print ? cout << setw(C_WIDTH) << raw_msg[i] << " " : cout << "";
    }
    print ? cout << endl : cout << "";
    print ? cout << setw(I_WIDTH) << "Cipher Text Mapping:" : cout << "";

    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] - 'a';
        print ? cout << setw(C_WIDTH) << int(raw_msg[i]) << " " : cout << "";
    }
    print ? cout << endl : cout << "";
    print ? cout << setw(I_WIDTH) << "Key:" : cout << "";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        print ? cout << setw(C_WIDTH) << key << " " : cout << "";
    }
    print ? cout << endl : cout << "";
    print ? cout << setw(I_WIDTH) << "Cipher Text - Key:" : cout << "";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] - key;
        print ? cout << setw(C_WIDTH) << int(raw_msg[i]) << " " : cout << "";
    }
    print ? cout << endl : cout << "";

    print ? cout << setw(I_WIDTH) << "(Cipher Text - Key)%26:" : cout << "";
    for (int i = 0; i < raw_msg.size(); i++)
    {

        if (raw_msg[i] < 0)
        {
            raw_msg[i] = raw_msg[i] + 26;
        }
        print ? cout << setw(C_WIDTH) << int(raw_msg[i]) << " " : cout << "";
    }
    print ? cout << endl : cout << "";

    print ? cout << setw(I_WIDTH) << "Plain Text:" : cout << "";
    for (int i = 0; i < raw_msg.size(); i++)
    {
        raw_msg[i] = raw_msg[i] + 'a';
        print ? cout << setw(C_WIDTH) << raw_msg[i] << " " : cout << "";
    }
    print ? cout << endl : cout << "";
    return raw_msg;
}

void cryptAnalysis(string encrypted_text, string original_text)
{
    // normally in cryptanalysis we are not known with original key
    // but here for reference we are passing the original text.
    // to confirm the key.
    int key = 1;
    for (; key < 26; key++)
    {
        string enc = encrypted_text;
        string msg = decrypt(enc, key, false);
        cout << msg << "   ";
        if (msg == original_text)
        {
            cout << "Key Found:" << key;
        }
        cout << endl;
    }
}

int main()
{
    fin();
    int tt;
    cin >> tt;
    int c = 0;
    cout << "-------------------------------------------------------------------" << endl;
    while (tt--)
    {
        cout << "Case #" << ++c << endl;
        string raw_msg;
        cin >> raw_msg;
        int key;
        cin >> key;

        cout << "Encryption" << endl
             << endl;
        string encrypted_msg = encrypt(raw_msg, key);
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Decryption" << endl
             << endl;
        string decrypted_msg = decrypt(encrypted_msg, key);
        cout << "-------------------------------------------------------------------" << endl;
        cout << "CryptAnalysis" << endl
             << endl;
        cryptAnalysis(encrypted_msg, decrypted_msg);
        cout << "-------------------------------------------------------------------" << endl;
    }
}