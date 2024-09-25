#include "BMPreader.h"
#include <Windows.h>
#include <vector>
#include <iomanip>


BMPreader::BMPreader(std::ostream& ios) :
	log(ios) { }

std::string BMPreader::get_filename() {
	return filename;
}

void BMPreader::displayBMP() {

	if (!ifs.is_open()) {
		std::cerr << "bmp isnt open.\n";
		return;
	}
	
	BITMAPINFOHEADER ihead{};
	ifs.read((char*)&ihead, sizeof(BITMAPINFOHEADER));
	int size = ihead.biSizeImage;
	LONG h = ihead.biHeight;
	LONG w = ihead.biWidth;
	WORD depth = ihead.biBitCount;

	std::vector<int> image{};
	
	if (depth != 24 && depth != 32) {
		std::cerr << "not supported format (" << depth << ") \n";
		return;
	}
	int pix_size = depth / 8;
	char* buffer = new char[size / pix_size];
	int k = 0;
	for (int i = 0; i < h; ++i) 
	{
		for (int j = 0; j < w; ++j)
		{
			ifs.read(buffer+k, 1);
			log << (buffer[k] == 0 ? "0" : "-");
			++k;
			ifs.ignore(pix_size - 1);

		}
		if (w % 2) {
			ifs.ignore(1);
		}
		log << "\n";
	}
	
	for (int i = 0; i < h; ++i)
	{
		k -= w;
		for (int j = 0; j < w; ++j)
		{
			//--k;
			log << (buffer[k]==0? "0" : "-");
			++k;

		}
		k -= w;
		log << "\n";
	}

	log << "image_size=" << size << "\n"
		<< h << " x " << w << "\n"
		<< "depth=" << depth << "\n";

}

bool BMPreader::openBMP(const std::string& filename) {
	if (ifs.is_open()) {
		std::cerr << "bmp is alredy open.\n";
		return false;
	}
	this->filename = filename;
	ifs.open(filename, std::ios::binary);
	BITMAPFILEHEADER fhead{};
	ifs.read((char*)&fhead, sizeof(BITMAPFILEHEADER));
	if (fhead.bfType != 0x4d42) {
		std::cerr << "its not bmp. :_(\n";
		return false;
	}
	return ifs.is_open();;
}

void BMPreader::closeBMP() {
	ifs.close();
}

BMPreader::~BMPreader() {
	closeBMP();
}
