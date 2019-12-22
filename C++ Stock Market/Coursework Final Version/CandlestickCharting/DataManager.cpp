#include "DataManager.h"
#include <vector>
#include <iostream>
#include <string>


DataManager::DataManager() {

}

vector<int> DataManager::GetRsiVector() {
	return _rsiValues;
}

vector<int> DataManager::GetShrunkTotalVector() {
	return _shrunkTotalValues;
}
vector<CandleStickData> DataManager::GetDataSetVector() {
	return _dataSet;
}
vector<int> DataManager::GetHighVector() {
	return _highValues;
}

vector<int> DataManager::GetCloseVector() {
	return _closeValues;
}
vector<int> DataManager::GetAverage9Vector() {
	return _averageValues9;
}
vector<int> DataManager::GetAverage18Vector() {
	return _averageValues18;
}
vector<double> DataManager::GetVolumeVector() {
	return _volumeValues;
}
vector<double> DataManager::GetShrunkVolumeVector() {
	return _shrunkVolumeValues;
}
vector<int> DataManager::GetShrunkAverageVector() {
	return _shrunkAverageValues;
}

void DataManager::AppendAverage9(int& value) {
	_averageValues9.push_back(value);
}
void DataManager::AppendAverage18(int& value) {
	_averageValues18.push_back(value);
}
void DataManager::AppendCandleStick(CandleStickData& day) {
	_dataSet.push_back(day);
}
//data is sorted
void DataManager::BubbleSort(std::vector<int> &vector)
{
	/*each element is compared to the one after it.
	If the one after it smaller, they swap places*/
	for (int i = 0; i < vector.size(); i++)
	{
		int temp;
		for (int x = 0; x < vector.size() - 1; x++)
		{
			if (vector[x] > vector[x + 1])
			{
				temp = vector[x];
				vector[x] = vector[x + 1];
				vector[x + 1] = temp;
			}
		}

	}
		
	
}
//data is sorted
void DataManager::BubbleSort(vector<double>& vector) {
	/*each element is compared to the one after it.
	If the one after it smaller, they swap places*/
	for (int i = 0; i < vector.size(); i++)
	{

		double temp;
		for (int x = 0; x < vector.size() - 1; x++)
		{
			if (vector[x] > vector[x + 1])
			{
				temp = vector[x];
				vector[x] = vector[x + 1];
				vector[x + 1] = temp;
			}
		}

	}
}


//values from the data set are copied over to new separate vectors
void DataManager::PopulateTotalVector() {
	for (int i = 0; i < _dataSet.size(); i++)
	{
	
		_totalValues.push_back(_dataSet[i].GetHigh());
		_totalValues.push_back(_dataSet[i].GetOpen());
		_totalValues.push_back(_dataSet[i].GetClose());
		_totalValues.push_back(_dataSet[i].GetLow());


		_closeValues.push_back(_dataSet[i].GetClose());
		_highValues.push_back(_dataSet[i].GetHigh());
		_volumeValues.push_back(_dataSet[i].GetVolume());
		_dateValues.push_back(_dataSet[i].GetDate());
	}
	
}

//these voids are here to explicitly sort the vectors
void DataManager::SortTotalValuesVector() {

	BubbleSort(_totalValues);
}
void DataManager::SortVolumeData() {
	BubbleSort(_volumeValues);
}
void DataManager::SortShrunkAverageVector() {
	BubbleSort(_shrunkAverageValues);
}

//Shrinks vector based on resolution  scale
void DataManager::ShrinkTotalVector(int resolutionScale) {
	
	
	int DIFF = _totalValues[(_totalValues.size() - 1)] - _totalValues[0];
	float add = DIFF / resolutionScale;
	for (int i = resolutionScale; i >= 0; i--)
	{

		_shrunkTotalValues.push_back(_totalValues[0] + i * add);
	}

}
//same as above
void DataManager::ShrinkAverageVector(int resolutionScale) {
	vector<int> vector = _averageValues9;
	BubbleSort(vector);
	int DIFF = vector[(vector.size() - 1)] - vector[0];
	float add = DIFF / resolutionScale;
	for (int i = resolutionScale; i >= 0; i--)
	{

		_shrunkAverageValues.push_back(vector[0] + i * add);
	}
	
}
//save as above
void DataManager::ShrinkVolumeVector(int resolutionScale) {
	double DIFF = _volumeValues[(_volumeValues.size() - 1)] - _volumeValues[0];
	double add = DIFF / resolutionScale;
	for (int i = resolutionScale; i >= 0; i--)
	{

		_shrunkVolumeValues.push_back(_volumeValues[0] + i * add);
	}
}


//Returns the index of the passed value relative to its closes position in the vector
int DataManager::ReturnValueIndex(vector<int>& list, int value) {
	int previousNumber = 0;
	int previousindex;
	int currentindex;
	//Loops through the whole vector
	for (int i = 0; i < list.size(); i++)
	{

		int currentNumber;
		currentNumber = list[i];
		//If the passed value is equal to the first or less than the first element in vector
		if (value == list[i] || value < list[0])
		{
			return i;
		}
		//If the passed value is equal to the last or more than the last element in vector
		if (value > list[list.size()-1])
		{
			return list.size() - 1;
		}
		
	
		//If the value is in between 2 elements in the vector
		if (previousNumber < value && currentNumber > value)
		{
			
			previousindex = i - 1;
			currentindex = i;
			//finds the difference between the value and the element above and below it
			//i.e If value = 5.2 and the vector is from 1 to 10, it will figure out the difference
			//between the value and 5 and the value and 6
			int diff1 = (previousNumber - value) * (previousNumber - value);
			int diff2 = (currentNumber - value) * (currentNumber - value);
			if (diff1 < diff2)
			{
				return previousindex;
			}
			else
			{
				return currentindex;
			}

		}
		previousNumber = currentNumber;
	}
}

//Same as above but with an argument of type double
//Returns the index of the passed value relative to its closes position in the vector
int DataManager::ReturnValueIndex(vector<double>& list, double value) {
	double previousNumber = 0;
	double previousindex;
	int currentindex;
	for (int i = 0; i < list.size(); i++)
	{
		double currentNumber;
		currentNumber = list[i];

		if (value == list[i] || value < list[0])
		{
			return i;
		}

		//last
		if (value > list[list.size()-1])
		{
			return list.size() - 1;
		}

		

		if (previousNumber < value && currentNumber > value)
		{
			previousindex = i - 1;
			currentindex = i;

			double diff1 = (previousNumber - value) * (previousNumber - value);
			double diff2 = (currentNumber - value) * (currentNumber - value);
			if (diff1 < diff2)
			{
				return previousindex;
			}
			else
			{
				return currentindex;
			}

		}
		previousNumber = currentNumber;
	}
}

//Checks if the index of a value in a vector overlaps the index argument
bool DataManager::CheckOverlap(int index, vector<int>& initial, int value) {
	if (ReturnValueIndex(initial, value) != index)
	{
		return true;
	}
	return false;
}

void DataManager::CalculateMovingAverage() {
	//close value vector needs to be sorted before this happens
	int days = 0, average9 = 0, average18 = 0;
	int period = 9,period2= 18;
	days = _dataSet.size();
	
	//toadd = dataSet[dataSet.size()-1].GetClose(); FIRST ELEMENT
	//toadd = dataSet[0].GetClose(); LAST ELEMENT
	for (int i = 0; i < days; i++)
	{
		int toadd = 0;
		int toadd2 = 0;


		if (i>= period)
		{
			for (int x = i-(period-1); x <= i; x++)
			{
				toadd += _closeValues[_closeValues.size()-x];
			}
		
		}
		if (i >= period2)
		{
			for (int x = i - (period2-1); x <= i; x++)
			{
				toadd2 += _closeValues[_closeValues.size() - x];
			}
			
		}
		average9 = toadd / (period-1);
		average18 = toadd2 / (period2-1);

		AppendAverage9(average9);
		AppendAverage18(average18);

	
	}
	
	

}

void DataManager::CalculateRSI() {
	double change, gain, loss;
	double prevgain, prevloss;
	double avgain, avloss;
	double rsi = 0;
	double rs;
	avgain = 0;
	avloss = 0;
	double totalgain = 0, totalloss = 0;


		for (int i = 1; i < _closeValues.size(); i++)
		{
			change = _closeValues[i - 1] - _closeValues[i];
			gain = 0;
			loss = 0;
			//logic deciding if the price change was a loss or a gain
			if (change > 0)
			{
				loss = change;
				gain = 0;
			}
			else
			{
				gain = -1 * change;
				loss = 0;
			}
			totalgain += gain;totalloss += loss;

			if (i == 14)
			{
				avgain = (totalgain) / i;
				avloss = (totalloss) / i;
			}



			//formula for rsi
			avgain = (avgain * (i - 1) + gain) / i;
			avloss = (avloss * (i - 1) + loss) / i;
			rsi = 100 - (100 / (1 + (avgain / avloss)));
			_rsiValues.push_back(rsi);



		}

	
}



//day 1: 5 money
//day2 : 3 money
//change = -2 money =>loss = 2