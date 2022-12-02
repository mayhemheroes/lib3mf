
#include <iostream>
#include <string>
#include <algorithm>

#include "lib3mf_dynamic.hpp"

using namespace Lib3MF;

void ExtractInfoExample(std::string sFileName) {
	auto wrapper = Lib3MF::CWrapper::loadLibrary("lib3mf.so");
	PModel model = wrapper->CreateModel();
	
	// Import Model from 3MF File
	{
		PReader reader = model->QueryReader("3mf");
		reader->SetStrictModeActive(false);
		reader->ReadFromFile(sFileName);
	}
}


int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << std::endl;
		std::cout << "fuzz model.3mf" << std::endl;
		return 0;
	}
	
	try {
		ExtractInfoExample(argv[1]);
	}
	catch (ELib3MFException &e) {
		std::cout << e.what() << std::endl;
		return e.getErrorCode();
	}
	return 0;
}
