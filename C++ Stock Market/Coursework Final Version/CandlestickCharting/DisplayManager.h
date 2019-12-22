#pragma once
#include "DataManager.h"
#include "FileManager.h"
class DisplayManager 
{

private:
	DataManager dm;
	const char _bullishBar = char(178);
	const char _bearishBar = char(176);
	const char _xAxisCorner = char(192);
	const char _xAxisLine = char(196);
	const char _xAxisStick = char(194);
	const char _straightBar = '|';
	const char _xPlot = 'X';
	const char _oPlot = 'O';
	const char _dashPlot = '-';
	const char _blankPlot = ' ';
	const string _dateIndicator = "-Date-";
	const string _priceIndicator = "-Price-";
	const string _volumeIndicator = "-Volume-";
	const string _rsiIndicator = "-RSI-";
	const string _candleStickTitle = "Candlestick Chart";
	const string _volumeTitle = "Volume Graph";
	const string _movingAverageTitle = "Moving average (X - 9 Day) , (O - 18 Day)";
	const string _rsiTitle = "Relative Strength Index (14 Day)";
	/*prints the X axis*/
	void PrintXAxis(FileManager& fm, int dayAmount,int offsetLength);
	/*Prints the dates under the X axis*/
	void PrintDates(FileManager& fm, int xSize);
	
public:
	DisplayManager(DataManager &manager);
	/*Displays the indicator above the y axis values such as -Price-*/
	void DisplayIndicator(FileManager& fm,string indicator);
	/*Displays the Title above a graph*/
	void DisplayTitle(FileManager& fm, string title,int dayAmount,int offsetLength);
	/*Outputs the Candle Stick Graph to the console*/
	void DisplayCandleStickGraph(FileManager &fm,int dayAmount,int offsetLength);
	/*Outputs the Moving Average Graph to the console*/
	void DisplayMovingAverage(FileManager& fm,int dayAmount, int offsetLength);
	/*Outputs the Bar Chart to the console*/
	void DisplayBarChart(FileManager& fm,int dayAmount, int offsetLength);
	/*Outputs the RSI to the console*/
	void DisplayRSI(FileManager& fm,int dayAmount, int offsetLength);
};

