#pragma once
#include <string>
#include <vector>
#include "DayData.h"
using std::vector;
//this class takes care of the data processing stuff
class DataManager
{
private:
	/*vector of classes containing data about each day
	its data is copied to different vectors so the data can be 
	sorted individually whist preserving the order in which the 
	data for each day has been saved
	*/
	vector<CandleStickData> _dataSet;
	vector<string> _dateValues;
	vector<int> _totalValues;
	vector<int> _shrunkTotalValues;
	vector<int> _highValues;
	vector<int> _closeValues;
	vector<int> _averageValues9;
	vector<int> _averageValues18;
	vector<int> _shrunkAverageValues;
	vector<int> _rsiValues;
	vector<double> _volumeValues;
	vector<double> _shrunkVolumeValues;

public:
	DataManager();
	vector<int> GetShrunkTotalVector();
	vector<int> GetHighVector();
	vector<int> GetCloseVector();
	vector<int> GetAverage9Vector();
	vector<int> GetAverage18Vector();
	vector<int> GetShrunkAverageVector();
	vector<int> GetRsiVector();
	vector<double> GetVolumeVector();
	vector<double> GetShrunkVolumeVector();
	vector<CandleStickData> GetDataSetVector();
	//Appends a CandleStickData class to the _dataSet vector
	void AppendCandleStick(CandleStickData &day);
	//Sorts the inputted vector
	void BubbleSort(vector<int>& vector);
	void BubbleSort(vector<double>& vector);
	/*Moves the data from all CandleStickData classes 
	from the _dataSet vector into separate vectors for separate
	sorting independent of day order to be done on them
	*/
	void PopulateTotalVector();
	/*Explicitly sorts the _totalValues vector*/
	void SortTotalValuesVector();
	/*Explicitly sorts the _volumeValues vector*/
	void SortVolumeData();
	/*Shrinks the _totalValues vector by the inputted resolution Scale*/
	void ShrinkTotalVector(int resolutionScale);
	/*Shrinks the _averageValues vector by the inputted resolution Scale*/
	void ShrinkAverageVector(int resolutionScale);
	/*Shrinks the _volumeValues vector by the inputted resolution Scale*/
	void ShrinkVolumeVector(int resolutionScale);
	/*Appends a values to the _averageValues9 vector*/
	void AppendAverage9(int& value);
	/*Appends a values to the _averageValues18 vector*/
	void AppendAverage18(int& value);
	/*Calculates and populates the _shrunkAverageValues vector*/
	void CalculateMovingAverage();
	/*Explicitly sorts the _shrunkAverageValues vector*/
	void SortShrunkAverageVector();
	/*Calculates and populates the _rsiValues vector*/
	void CalculateRSI();
	/*Checks if a value has the same index and the inputted index on the 
	given vector*/
	bool CheckOverlap(int index, vector<int>& initial, int value);
	/*Returns the index of the value within the vector i.e. its position*/
	int ReturnValueIndex(vector<int>& list, int value);
	/*Returns the index of the value within the vector i.e. its position*/
	int ReturnValueIndex(vector<double>& list, double value);
	
};

