#pragma once
#include <string>
#include <fstream>
#include <iostream>

class BMPreader {
	std::ifstream ifs;
	std::string filename;
	std::ostream &log;
public:
	BMPreader(std::ostream& ios = std::cout);
	std::string get_filename();

	bool openBMP(const std::string& filename);
	void displayBMP();
	void closeBMP();
	~BMPreader();
};
