

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "DayData.h"
#include "DataManager.h"
#include "DisplayManager.h"
#include "FileManager.h"



using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;



void CalculateIndexes(CandleStickData& day, DataManager& dm, int& indexOpen, int& indexClose, int& indexHigh, int& indexLow, vector<int>& testShrunk) {
	//open
	indexOpen = dm.ReturnValueIndex(testShrunk, day.GetOpen());
	//close
	indexClose = dm.ReturnValueIndex(testShrunk, day.GetClose());
	//high
	indexHigh = dm.ReturnValueIndex(testShrunk, day.GetHigh());
	//low
	indexLow = dm.ReturnValueIndex(testShrunk, day.GetLow());
}


void DataProcessing(DataManager& dm,int resolutionScale) {

	//The purpose of the total vector is to get a range of values from which to shrink down to create a proportional y axis
	dm.PopulateTotalVector();

	//Total values vector is sorted
	dm.SortTotalValuesVector();
	//Volume values vector is sorted
	dm.SortVolumeData();

	//Moving average is calculated
	dm.CalculateMovingAverage();
	//RSI is calculated
	dm.CalculateRSI();

	//Data sets are shrunk based on resolution scale
	dm.ShrinkVolumeVector(resolutionScale);
	dm.ShrinkTotalVector(resolutionScale);
	dm.ShrinkAverageVector(resolutionScale);

	//Finally, data is sorted again after being shrunk
	dm.SortShrunkAverageVector();
	
	
} 




int main()
{
	do
	{

	
	const int GRAPHOFFSETLENGTH = 6;
	const int MAXDAYOUTPUT = 220;
	int daysToOutput = 30;
	int resScale = 5;
	int valid = false;
	string input;
	string extension = ".csv";
	cout << "Author:  Alexandru-Dejan Gioada" << endl;
	cout << "SID:  8575605" << endl << endl;

	//File manager class is called, specifying which file to read
	

	cout << "Files that can be opened: " << endl;
	cout << "1. BTChist" << endl;
	cout << "2. BTChist2" << endl;
	cout << "3. BTChist3" << endl;
	cout << "4. BTChist4" << endl << endl;

	
	do
	{
		cout << "Please enter the name or the number of the file to be opened." << endl;
		cin >> input;
		if (input == "1" || input == "BTChist")
		{
			input = "BTChist" + extension;
			valid = true;
		}
		else if (input == "2" || input == "BTChist2")
		{
			input = "BTChist2" + extension;
			valid = true;
		}
		else if (input == "3" || input == "BTChist3")
		{
			input = "BTChist3" + extension;
			valid = true;
		}
		else if (input == "4" || input == "BTChist4")
		{
			input = "BTChist4" + extension;
			valid = true;
		}
		else
		{
			cout << "Invalid input. Please try again. " << endl;
			valid = false;
		}
	} while (valid == false);
	cout << endl;
	valid = false;
	//file is read and data is fetched
	FileManager fm(input);
	fm.ReadFileData();
	cout << endl;

	do
	{
		cin.clear();
		cin.ignore();
		cout << "There are " << fm.GetDManager().GetDataSetVector().size() << " Days worth of data in the file"<<endl;
		cout << "Please input how many days you want displayed"<<endl;
		cout << "The maximum amount of days that can be displayed is "<<MAXDAYOUTPUT << endl;
		cin >> daysToOutput;
		if (daysToOutput<1 || daysToOutput > MAXDAYOUTPUT || daysToOutput> fm.GetDManager().GetDataSetVector().size())
		{
			cout << "Invalid amount, please try again" << endl << endl;
		}
		else
		{
			valid = true;
		}

	} while (valid == false);
	cout << endl;
	valid = false;

	do
	{
		cin.clear();
		cin.ignore();
		cout << "Plase enter the resolution scale" << endl;
		cout << " (How many Y values should be printed)" << endl;
		cin >> resScale;

		if (resScale > 0)
		{
			valid = true;
		}
		else
		{
			cout << "Invalid value" << endl << endl;
		}

	} while (valid == false);
	cout << endl;

	

	
	
	
	
    DataManager dm = fm.GetDManager();
	//resolution scale indicates the amount of values on the Y axis
	
	
	//data is processed (calculated and shrunk based on the resolution scale)
	DataProcessing(dm, resScale);
	cout << endl;
	cout << dm.GetVolumeVector().size()<<endl;

	//Display manager is created
	DisplayManager display(dm);
	//The file for outputting data is opened/created
	fm.StartOutput();
	//Data is being displayed on the console and added to the output file

	display.DisplayCandleStickGraph(fm, daysToOutput,GRAPHOFFSETLENGTH);
	display.DisplayMovingAverage(fm, daysToOutput,GRAPHOFFSETLENGTH);
	display.DisplayBarChart(fm, daysToOutput, GRAPHOFFSETLENGTH);
	display.DisplayRSI(fm, daysToOutput, GRAPHOFFSETLENGTH);

		do
		{
			cin.clear();
			cin.ignore();
			cout << "Would you like to save this to a text file?" << endl;
			cout << "Y/N" << endl;
			cin >> input;
			if (input == "Y" || input == "y")
			{
				fm.SaveFile();
				valid = true;
			}
			else if (input == "N" || input == "n")
			{
				valid = true;
				fm.SaveFile();
				remove("output.txt");
			}
			else
			{
				cout << "Invalid input. Please try again" << endl;
				valid = false;
			}

		} while (valid == false);
	
		valid = false;

		do
		{
			cin.clear();
			cin.ignore();
			cout << "Would you like to open another file?" << endl;
			cout << "Y/N" << endl;
			cin >> input;
			if (input == "Y" || input == "y")
			{
				valid = true;
			}
			else if (input == "N" || input == "n")
			{
				return 0;
			}
			else
			{
				cout << "Invalid input. Please try again" << endl;
			}


		} while (valid == false);


	} while (true);

	return 0;
	
}

