#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;


int main()
{
	srand(time(0));
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	ifstream file("CAT256.bmp", ios::binary);
	if (!file) {
		cout << "Reading file error" << endl;
		return 0;
	}
	file.read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
	file.read((char*)&infoHeader, sizeof(BITMAPINFOHEADER));

	ofstream out("C:\\Users\\argon\\Desktop\\ПГИ\\result2.bmp", ios::binary);
	out.write((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
	out.write((char*)&infoHeader, sizeof(BITMAPINFOHEADER));

	while (file.tellg() != fileHeader.bfOffBits) {
		RGBQUAD tmpRGB;
		file.read((char*)&tmpRGB, sizeof(RGBQUAD));
		out.write((char*)&tmpRGB, sizeof(RGBQUAD));
	}
	int count = 0, row = 0;
	while (true) {
		char temp;
		file.read((char*)&temp, 1);
		if (file.eof()) {
			break;
		}

		if (count < 15 || count >= infoHeader.biWidth - 15 || row < 15 || row >= infoHeader.biHeight - 15)
			out.write(to_string(rand() % 255).c_str(), 1);
		else
			out.write((char*)&temp, 1);

		count++;
		if (count == infoHeader.biWidth + 1) {
			count = 0;
			row++;
		}
	}
	out.close();
	return 0;
}
