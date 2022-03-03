/*********************************************************
Written by:  Jenil J Gandhi
Subject:     Network and information security
Lab-no:      Lab-06
Description: Implement Hill Cipher
Guidance by: Prof Mrudang T Mehta
Date:        20/01/2022
*********************************************************/
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> getAdjoint(vector<vector<int>> matrix)
{
    vector<vector<int>> retMat{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    retMat[0][0] = (matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1]);
    cout << "Here3" << endl;
    retMat[1][0] = -1 * ((matrix[1][0] * matrix[2][2]) - (matrix[1][2] * matrix[2][0]));
    retMat[2][0] = (matrix[1][0] * matrix[2][1]) - (matrix[2][0] * matrix[1][1]);
    retMat[0][1] = -1 * ((matrix[0][1] * matrix[2][2]) - (matrix[0][2] * matrix[2][1]));
    retMat[1][1] = (matrix[0][0] * matrix[2][2]) - (matrix[2][0] * matrix[0][2]);
    retMat[2][1] = -1 * ((matrix[0][0] * matrix[2][1]) - (matrix[0][1] * matrix[2][0]));
    retMat[0][2] = (matrix[0][1] * matrix[1][2]) - (matrix[0][2] * matrix[1][1]);
    retMat[1][2] = -1 * ((matrix[0][0] * matrix[1][2]) - (matrix[0][2] * matrix[1][0]));
    retMat[2][2] = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    return (retMat);
}
int getDeterminant(vector<vector<int>> matrix)
{
    int det = 0;
    det += (matrix[0][0]) * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1]));
    det -= (matrix[0][1]) * ((matrix[1][0] * matrix[2][2]) - (matrix[1][2] * matrix[2][0]));
    det += (matrix[0][2]) * ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0]));
    return det;
}

vector<vector<int>> convertStringToMatrix(string s, int row, int col)
{
    vector<vector<int>> mat;
    int strcntr = 0;
    for (int i = 0; i < row; i++)
    {
        vector<int> v;
        for (int j = 0; j < col; j++)
        {
            v.push_back((s[strcntr++] - 'a') % 26);
        }
        mat.push_back(v);
    }
    return mat;
}

string convertString(string s, int matLen)
{
    int paddingChars = matLen - int(s.size() % matLen);
    if (paddingChars == matLen)
    {
        return s;
    }
    else
    {
        for (int i = 0; i < paddingChars; i++)
        {
            s.push_back('z');
        }
        return s;
    }
}

void printMatrix(vector<vector<int>> v)
{
    for (auto x : v)
    {
        for (auto y : x)
        {
            cout << y << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> multiplyMatrix(vector<vector<int>> k1, vector<vector<int>> m)
{
    int R1, C1, R2, C2;
    R1 = m.size();
    R2 = k1.size();
    C1 = m[0].size();
    C2 = k1[0].size();

    vector<vector<int>> multipliedMatrix;

    for (int i = 0; i < R1; i++)
    {
        vector<int> v;
        for (int j = 0; j < C2; j++)
        {
            int res = 0;
            for (int k = 0; k < R2; k++)
            {
                res += ((m[i][k] * k1[k][j]));
            }

            v.push_back(res % 26);
        }
        multipliedMatrix.push_back(v);
    }
    return multipliedMatrix;
}

vector<vector<int>> encrypt(vector<vector<int>> key, vector<vector<int>> message)
{
    return multiplyMatrix(key, message);
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

string matrixToString(vector<vector<int>> matrix)
{
    string retStr = "";
    for (auto x : matrix)
    {
        for (auto ch : x)
        {
            retStr += (ch + 'a');
        }
    }
    return retStr;
}
vector<vector<int>> decrypt(vector<vector<int>> key, vector<vector<int>> message)
{
    int determinant = (getDeterminant(key)) % 26;
    determinant = getInverse(determinant, 26);
    vector<vector<int>> adj = getAdjoint(key);
    for (int i = 0; i < adj.size(); i++)
    {
        for (int j = 0; j < adj[0].size(); j++)
        {
            adj[i][j] = (adj[i][j] * determinant) % 26;
            if (adj[i][j] < 0)
            {
                adj[i][j] += 26;
            }
        }
    }
    vector<vector<int>> multipliedMatrix = multiplyMatrix(adj, message);
    return multipliedMatrix;
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int matDim;
        cin >> matDim;

        string key, message;
        cin >> key;
        cin >> message;

        if (key.size() / matDim != matDim)
        {
            cout << "Key length must be of length " << matDim * matDim << endl;
            exit(0);
        }
        vector<vector<int>> keyMatrix = convertStringToMatrix(key, matDim, matDim);

        string paddedMessage = convertString(message, matDim);

        vector<vector<int>> messageMatrix = convertStringToMatrix(paddedMessage, paddedMessage.size() / matDim, matDim);

        cout << "KeyMatrix:\n";
        printMatrix(keyMatrix);

        cout << "Message Matrix:\n";
        printMatrix(messageMatrix);

        vector<vector<int>> mul = encrypt(keyMatrix, messageMatrix);

        cout << "Encrypted Matrix:\n";
        printMatrix(mul);

        vector<vector<int>> decryptedMsg = decrypt(keyMatrix, mul);
        cout << "Decrypted Matrix:\n";
        printMatrix(decryptedMsg);
        cout << "Decrypted String:\n";
        cout << matrixToString(decryptedMsg);
    }
    return 0;
}