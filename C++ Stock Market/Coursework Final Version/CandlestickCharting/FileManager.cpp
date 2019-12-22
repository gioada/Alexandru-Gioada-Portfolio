#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include<Windows.h>

using std::cout;
using std::right;
using std::setw;
using std::endl;

FileManager::FileManager(std::string fileName) {
    _inputFileName = fileName;
	_outputFileName = "output.txt";
}

FileManager::FileManager() {

}

void FileManager::ReadFileData() {
	std::ifstream inputFileStream;
	inputFileStream.open(_inputFileName); // hardcoded filename, for now...

	if (inputFileStream.good())
	{


		cout << "Input file is good start processing..." << endl << endl;

		cout.fill(' ');

		string line;
		getline(inputFileStream, line); // read 1st line, skip 1st line (headers), might fail!
		getline(inputFileStream, line); // read 2nd line, might fail!

		while (!inputFileStream.fail()) // check for failbit
		{

			CandleStickData dayData;
			std::stringstream ss(line);

			string date1;
			string date2;
			getline(ss, date1, ','); // read first field from line, might fail
			getline(ss, date2, ','); // read second field from line, might fail
			string date = date1 + date2;
			string trimmedDate = date.substr(1, date.size() - 2);
			//cout << setw(14) << trimmedDate << " " << char(179);
			dayData.AssignDate(trimmedDate);

			cout << std::fixed;

			for (int i = 0; i < 6; i++) { // loops through the remaining 6 columns
				string field;
				double fieldData;
				getline(ss, field, ','); // read next field, might 

				std::stringstream fss(field);
				fss >> fieldData; // try to convert to a double, this might fail !!!
				//cout << setw(14) << std::setprecision(0) << fieldData << " " << char(179);


				//data is assigned to its class depending on the point at which it is in the loop
				if (i == 0) { dayData.AssignOpen((int)fieldData); } //open value is stored in the class
				else if (i == 1) { dayData.AssignHigh((int)fieldData); } //high value is stored in the class
				else if (i == 2) { dayData.AssignLow((int)fieldData); } //low value is stored in the class
				else if (i == 3) { dayData.AssignClose((int)fieldData); } //close value is stored in the class
				else if (i == 4) { dayData.AssignVolume(fieldData); }//volume value is stored in the class
				else if (i == 5) { dayData.AssignMarket((int)fieldData); }//market value is stored in the class


			}
			// the class containing the data for a particular day is appended to a data manager vector
			// which holds all the day classes
			_dm.AppendCandleStick(dayData);
			

			getline(inputFileStream, line); // read next line
		}

	



		if (inputFileStream.eof()) {
			cout << "Reached the end of file marker.  File data read sucessfully." << endl;
		}
		else {
			cout << "Error in input file." << endl;
		}
	}
	else
	{
		cout << "Error opening input file, ";
		cout << "check 'BTChist.csv' exists in correct directory." << endl;
	}

	inputFileStream.close();
}
//String argument is written to file
void FileManager::WriteToFile(string& text) {
	_outputFS << text;
}
void FileManager::WriteToFile(char& character) {
	_outputFS << character;
}
//Y Axis is written to the file
void FileManager::PrintYAxis(int value,int spacing) {

	_outputFS << std::right << std::setw(spacing) << value << '|';
}
//Y Axis is written to the file
void FileManager::PrintYAxis(double value, int spacing) {

	_outputFS << std::right << std::setw(spacing) << value << '|';
}
//New line written to the file
void FileManager::AddEndLine() {
	_outputFS << endl;
}
//File is closed, data written to it is saved
void FileManager::SaveFile() {
	_outputFS.close();
}
//File passed as argument is opened and data output can start
void FileManager::StartOutput() {_outputFS.open(_outputFileName);}

DataManager FileManager::GetDManager() {return _dm;}