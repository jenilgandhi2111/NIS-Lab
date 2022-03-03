/*********************************************************
Written by:  Jenil J Gandhi
Subject:     NIS
Lab-no:      Lab-03
Description: Implement Playfair cipher
Guidance by: Prof Mrudang T Mehta
Date:        07/01/2022
*********************************************************/
#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> generatePlayfairSquare(string message)
{
    map<char, bool> taken;
    vector<vector<char>> square;
    for (int j = 0; j < 5; j++)
    {
        vector<char> v(5, 0);
        square.push_back(v);
    }
    int i;
    int shift = 0;

    replace(message.begin(), message.end(), 'i', '!');
    replace(message.begin(), message.end(), 'j', '!');

    // Generating playfair square
    for (i = 0; i < message.size(); i++)
    {
        if (taken[message[i]] == true)
        {
            shift++;
            continue;
        }

        int col = (i - shift) % 5;
        int row = (i - shift) / 5;
        square[row][col] = message[i];
        taken[message[i]] = true;
    }

    int cntr = i - shift;
    for (; cntr < 25; cntr++)
    {
        char letter = 0;
        for (int k = 0; k < 26; k++)
        {
            char m = 'a' + k;
            if (m == 'i' || m == 'j')
            {
                m = '!';
            }
            if (taken[m] == false)
            {
                letter = m;
                taken[m] = true;
                break;
            }
        }
        int row = cntr / 5;
        int col = cntr % 5;
        square[row][col] = letter;
    }
    return square;
}

string convertToSplits(string message)
{
    vector<char> msg;
    for (int i = 0; i < message.size(); i++)
    {
        msg.push_back(message[i]);
    }
    int change = 0;
    while (true)
    {

        int c = change;
        for (int i = 0; i < int(msg.size() / 2); i++)
        {
            if (msg[i * 2] == msg[i * 2 + 1])
            {
                msg.insert(msg.begin() + i * 2 + 1, 'x');
                change++;
            }
        }
        if (c == change)
        {
            break;
        }
    }
    string m = "";
    for (auto x : msg)
    {
        m += x;
    }
    if (m.size() % 2 == 1)
    {
        m += 'x';
    }
    return m;
}

vector<int> findIndex(vector<vector<char>> square, char c)
{
    vector<int> point;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (c == square[i][j])
            {
                point.push_back(i);
                point.push_back(j);
                return point;
            }
        }
    }
    return point;
}

void print_vec(vector<int> p)
{
    cout << "<" << p[0] << "," << p[1] << ">" << endl;
}

string encrypt(vector<vector<char>> square, string message)
{
    string enc = "";
    for (int i = 0; i < int(message.size() / 2); i++)
    {
        char a, b;
        a = message[i * 2];
        b = message[i * 2 + 1];
        if (a == 'i' || a == 'j')
        {
            a = '!';
        }
        if (b == 'i' || b == 'j')
        {
            b = '!';
        }
        vector<int> p1 = findIndex(square, a);
        vector<int> p2 = findIndex(square, b);

        int row1, row2, col1, col2;
        if (p1[0] == p2[0])
        {
            // Same Row Case-1
            row1 = p1[0];
            row2 = row1;
            col1 = (p1[1] + 1) % 5;
            col2 = (p2[1] + 1) % 5;
        }
        else if (p1[1] == p2[1])
        {
            // Same column Case-2
            col1 = p1[1];
            col2 = col1;
            row1 = (p1[0] + 1) % 5;
            row2 = (p2[0] + 1) % 5;
        }
        else
        {
            // Different row and columns Case-3
            row1 = p1[0];
            row2 = p2[0];
            col1 = p2[1];
            col2 = p1[1];
        }

        enc += square[row1][col1];
        enc += square[row2][col2];
    }
    return enc;
}

string decrypt(vector<vector<char>> square, string message)
{
    string dec = "";
    for (int i = 0; i < int(message.size() / 2); i++)
    {
        char a, b;
        a = message[i * 2];
        b = message[i * 2 + 1];
        if (a == 'i' || a == 'j')
        {
            a = '!';
        }
        if (b == 'i' || b == 'j')
        {
            b = '!';
        }
        vector<int> p1 = findIndex(square, a);
        vector<int> p2 = findIndex(square, b);

        int row1, row2, col1, col2;
        if (p1[0] == p2[0])
        {
            // Same Row Case-1
            row1 = p1[0];
            row2 = row1;
            col1 = (p1[1] - 1) % 5;
            col2 = (p2[1] - 1) % 5;
            if (col1 < 0)
            {
                col1 += 5;
            }
            if (col2 < 0)
            {
                col2 += 5;
            }
        }
        else if (p1[1] == p2[1])
        {
            // Same column Case-2
            col1 = p1[1];
            col2 = col1;
            row1 = (p1[0] - 1) % 5;
            row2 = (p2[0] - 1) % 5;
            if (row1 < 0)
            {
                row1 += 5;
            }
            if (row2 < 0)
            {
                row2 += 5;
            }
        }
        else
        {
            // Different row and columns Case-3
            row1 = p1[0];
            row2 = p2[0];
            col1 = p2[1];
            col2 = p1[1];
        }

        dec += square[row1][col1];
        dec += square[row2][col2];
    }
    return dec;
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        string key;
        cin >> key;

        string message;
        cin >> message;

        cout << "Playfair Square :\n";
        vector<vector<char>> square = generatePlayfairSquare(key);
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                cout << square[j][k] << " ";
            }
            cout << endl;
        }

        string splitMsg = convertToSplits(message);
        cout << "Split message:  ";
        cout << splitMsg << endl;
        cout << "Encrypted Text: ";
        string encryptedMessage = encrypt(square, splitMsg);
        cout << encryptedMessage << endl;
        cout << "Decrypted Text: ";
        string decryptedMessage = decrypt(square, encryptedMessage);
        cout << decryptedMessage << endl;
    }
    return 0;
}