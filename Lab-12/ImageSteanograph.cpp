/*********************************************************
Written by:  Jenil J Gandhi
Subject:     Network and information security
Lab-no:      Lab-12
Description: Image steganography
Guidance by: Prof Mrudang T Mehta
Date:        10/03/2022
*********************************************************/
#include <bits/stdc++.h>
using namespace std;
int IMG_SIZE = 4;

vector<vector<int>> getSteagnoObj(vector<vector<int>> image, vector<bool> message)
{
    vector<vector<int>> steanoImage;
    int c = 0;
    for (auto x : image)
    {
        vector<int> temp;
        for (auto pixel : x)
        {
            int px = pixel;
            bool messageBit = message[c++];
            if (messageBit == 1 && pixel % 2 == 0)
            {
                px += 1;
            }
            else if (messageBit == 0 && pixel % 2 == 1)
            {
                px -= 1;
            }
            temp.push_back(px);
        }
        steanoImage.push_back(temp);
    }
    return steanoImage;
}

vector<int> getOriginalMessage(vector<vector<int>> stegoObj)
{
    vector<int> decodedMessage;
    for (auto x : stegoObj)
    {
        for (auto pixel : x)
        {
            decodedMessage.push_back(pixel % 2);
        }
    }
    return decodedMessage;
}

double getLoss(vector<vector<int>> image, vector<vector<int>> stegoImage)
{
    double loss = 0;
    for (int i = 0; i < IMG_SIZE; i++)
    {
        for (int j = 0; j < IMG_SIZE; j++)
        {
            loss += ((image[i][j] - stegoImage[i][j]) * (image[i][j] - stegoImage[i][j]));
        }
    }
    loss /= (16);
    return loss;
}

double getPSNR(int r, double MSE)
{
    return 10 * log10(double(r * r) / MSE);
}

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        vector<vector<int>> image{{50, 25, 49, 79}, {78, 23, 78, 80}, {49, 52, 90, 201}, {100, 59, 70, 75}};
        vector<bool> message;
        for (int i = 0; i < 16; i++)
        {
            bool tmp;
            cin >> tmp;
            message.push_back(tmp);
        }
        vector<vector<int>> stegoImage = getSteagnoObj(image, message);
        vector<int> decodedMessage = getOriginalMessage(stegoImage);

        cout << "Stego Image:\n";
        for (auto x : stegoImage)
        {
            for (auto pixel : x)
            {
                cout << pixel << " ";
            }
            cout << endl;
        }

        cout << "Decoded Message\n";
        for (auto x : decodedMessage)
        {
            cout << x << " ";
        }
        cout << endl;

        double loss = getLoss(image, stegoImage);
        cout << "MSE Loss: " << loss << endl;
        cout << "PSNR:" << getPSNR(255, loss);
    }
    return 0;
}