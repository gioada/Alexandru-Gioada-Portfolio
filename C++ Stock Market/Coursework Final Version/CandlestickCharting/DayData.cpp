#include "DayData.h"
#include <string>


CandleStickData::CandleStickData(){
	_high = 0;
	_open = 0;
	_close = 0;
	_low = 0;
	_market = 0;
	_volume = 0;
	_date = "";

}

void CandleStickData::AssignDate(string date) {
	_date = date;
}
void CandleStickData::AssignOpen(int open) {
	_open = open;
}
void CandleStickData::AssignHigh(int high) {
	_high = high;
}
void CandleStickData::AssignClose(int close) {
	_close = close;
}
void CandleStickData::AssignLow(int low) {
	_low = low;
}
void CandleStickData::AssignMarket(double market) {
	_market = market;
}
void CandleStickData::AssignVolume(double volume) {
	_volume = volume;
}
string CandleStickData::GetDate() { return _date; }
int CandleStickData::GetHigh() { return _high; }
int CandleStickData::GetOpen() { return _open; }
int CandleStickData::GetClose() { return _close; }
int CandleStickData::GetLow() { return _low; }
double CandleStickData::GetMarket() { return _market; }
double CandleStickData::GetVolume() { return _volume; }

//fdsdfas