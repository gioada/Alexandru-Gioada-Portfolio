#pragma once
#include "DataManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

class FileManager
{

private:
	DataManager _dm;
	std::string _inputFileName;
	std::string _outputFileName;
	std::ofstream _outputFS;
	

public:
	FileManager();
	FileManager(std::string fileName);
	void PrintYAxis(int value, int spacing);
	void PrintYAxis(double value, int spacing);
	void ReadFileData();
	void WriteToFile(string& text);
	void WriteToFile(char& character);
	void AddEndLine();
	void SaveFile();
	void StartOutput();
	DataManager GetDManager();
};

