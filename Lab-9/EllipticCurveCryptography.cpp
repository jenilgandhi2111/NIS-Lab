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
int D_LOW = 2;
int D_HIGH = 10;

void fin()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}
class EccParameters
{
public:
    int a, b, p;
};
void print_pair(pair<int, int> p)
{
    cout << "<" << p.first << " " << p.second << ">" << endl;
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

int getRandomseedV1(int low = 0, int high = INT_MAX)
{
    srand(time(0));
    return low + (rand() % high);
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

class PublicKey
{
public:
    pair<int, int> e1;
    pair<int, int> e2;
    EccParameters params;
};

class KeySetup
{
public:
    PublicKey publicKey;
    int privateKey;

    void printSetup()
    {
        cout << "Public Key (e1,e2,Ep) => (<" << publicKey.e1.first << "," << publicKey.e1.second << ">,<" << publicKey.e2.first << "," << publicKey.e2.second << ">)\n";

        cout << "Private Key:" << this->privateKey << endl;
    }
};

pair<int, int> scalarAddition(pair<int, int> point1, pair<int, int> point2, EccParameters params)
{
    int x1 = point1.first;
    int y1 = point1.second;
    int x2 = point2.first;
    int y2 = point2.second;

    // would store answer in point1
    if (point1.first != point2.first)
    {
        // Case-1
        int xn = (x2 - x1);
        if (xn < 0)
        {
            xn += params.p;
        }
        int lambda = ((y2 - y1) % params.p * (getInverse(xn, params.p))) % params.p;

        if (lambda < 0)
        {
            lambda += params.p;
        }

        int x3 = ((lambda * lambda) - x1 - x2) % params.p;
        int y3 = (lambda * (x1 - x3) - y1) % params.p;
        point1.first = x3;
        point1.second = y3;
    }
    else if (point1.first == point2.first)
    {
        // Case-2
        int lambda = ((3 * x1 * x1 + params.a) * getInverse(2 * y1, params.p)) % params.p;

        int x3 = (lambda * lambda - (2 * x1)) % params.p;
        int y3 = (lambda * (x1 - x3) - y1) % params.p;
        point1.first = x3;
        point1.second = y3;
    }
    if (point1.first < 0)
    {
        point1.first = params.p + point1.first;
    }
    if (point1.second < 0)
    {
        point1.second = params.p + point1.second;
    }

    return point1;
}

pair<int, int> scalarMultiplication(pair<int, int> point, int n, EccParameters params)
{
    pair<int, int> point1 = point;
    pair<int, int> point2 = point;
    for (int i = 0; i < n - 1; i++)
    {
        point1 = scalarAddition(point1, point2, params);
    }
    return point1;
}

KeySetup keyGeneration(vector<pair<int, int>> generatedPoints, EccParameters params)
{
    int idx = getRandomseedV1(0, generatedPoints.size() - 1);
    pair<int, int> e1 = generatedPoints[idx];

    int d = getRandomseedV1(D_LOW, D_HIGH);

    pair<int, int> e2 = scalarMultiplication(e1, d, params);

    KeySetup setup;
    PublicKey publicKey;
    publicKey.e1 = e1;
    publicKey.e2 = e2;
    setup.publicKey = publicKey;
    setup.privateKey = d;

    return setup;
}

pair<pair<int, int>, pair<int, int>> encryption(pair<int, int> message, PublicKey publicKey, EccParameters params)
{
    int r = getRandomseedV1(2, 20);
    r = 1;
    pair<int, int> e1 = publicKey.e1;
    pair<int, int> e2 = publicKey.e2;

    pair<int, int> c1 = scalarMultiplication(e1, r, params);
    pair<int, int> c2 = scalarAddition(message, scalarMultiplication(e2, r, params), params);

    return make_pair(c1, c2);
}

pair<int, int> decryption(pair<int, int> c1, pair<int, int> c2, KeySetup setup, EccParameters params)
{
    pair<int, int> right = scalarMultiplication(c1, setup.privateKey, params);
    right.second = right.second * -1;

    pair<int, int> msg = scalarAddition(c2, right, params);

    return msg;
}

int main()
{
    fin();
    int tt;
    cin >> tt;
    cout << "----------------------------------------------------------------\n";
    int c = 0;
    while (tt--)
    {
        cout << "Case: #" << ++c << endl;
        int a, b, p;
        cin >> a >> b >> p;
        EccParameters curveParams;
        curveParams.a = a;
        curveParams.b = b;
        curveParams.p = p;
        vector<pair<int, int>> points = GeneratePoints(curveParams);
        // printPoints(points);

        keyGeneration(points, curveParams);
        KeySetup setup = keyGeneration(points, curveParams);

        setup.printSetup();
        char message;
        cin >> message;

        pair<int, int> message_point = points[message - 'a'];

        cout << "Message Point: ";
        print_pair(message_point);

        pair<pair<int, int>, pair<int, int>> encrypted = encryption(message_point, setup.publicKey, curveParams);

        cout << "C1: ";
        print_pair(encrypted.first);
        cout << "C2: ";
        print_pair(encrypted.second);

        pair<int, int> decrypted = decryption(encrypted.first, encrypted.second, setup, curveParams);

        int i;
        for (i = 0; i < points.size(); i++)
        {
            if (points[i].first == decrypted.first && points[i].second == decrypted.second)
            {
                break;
            }
        }

        cout << "Decrypted Message: " << char(i + 'a') << endl;
        cout << "----------------------------------------------------------------\n";
    }
    return 0;
}