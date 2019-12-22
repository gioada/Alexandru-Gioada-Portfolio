#pragma once

#include <string>

using std::string;
class CandleStickData
{

private:
	string _date;
	int _high;
	int _open;
	int _close;
	int _low;
	double _market;
	double _volume;


public:
	CandleStickData();
	void AssignDate(string date);
	void AssignOpen(int open);
	void AssignHigh(int high);
	void AssignClose(int close);
	void AssignLow(int low);
	void AssignMarket(double market);
	void AssignVolume(double volume);
	string GetDate();
	int GetHigh();
	int GetOpen();
	int GetClose();
	int GetLow();
	double GetMarket();
	double GetVolume();

};