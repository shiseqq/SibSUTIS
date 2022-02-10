#include <iostream>
#include <Windows.h>
#include <wingdi.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

char* img;
BITMAPFILEHEADER Header;
BITMAPINFOHEADER Info;
vector<RGBQUAD> Palette;

int main() {
    ifstream file("CAT256.bmp", ios_base::in | ios_base::binary);
    file.read((char*)&Header, sizeof(Header));
    file.read((char*)&Info, sizeof(Info));
    while (file.tellg() != Header.bfOffBits) {
        RGBQUAD temp;
        file.read(reinterpret_cast<char*>(&temp), sizeof(RGBQUAD));
        Palette.push_back(temp);
    }

    int n = (int)Info.biWidth;
    int m = (int)Info.biHeight;

    LONG A = Info.biWidth;
    Info.biWidth = Info.biHeight;
    Info.biHeight = A;

    ofstream out("result.BMP", ios_base::out | ios_base::binary);
    out.write((char*)&Header, sizeof(BITMAPFILEHEADER));
    out.write((char*)&Info, sizeof(BITMAPINFOHEADER));
    for (auto& i : Palette) {
        out.write((char*)&i, sizeof(RGBQUAD));
    }
    vector<char> tmp, res;
    int k = 0;
    while (true) {
        char temp;
        k++;
        if (k >= n) {
            file.ignore(4-k%4);
            k = 0;
        }
        file.read((char*)&temp, sizeof(char));
        if (file.eof()) {
            break;
        }
        tmp.push_back(temp);
    }
    res.resize(tmp.size());
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            res[j * m + i] = tmp[i * n + j];
        }
    }

    for (int i = n-1; i >=0; --i) {
        for (int j = 0; j < m; ++j) {
            out.write((char*)&res[i * m + j], sizeof(char));
        }
        char temp='0';
        out.write((char*)&temp, sizeof(char));
        
    }
    return 0;
}
