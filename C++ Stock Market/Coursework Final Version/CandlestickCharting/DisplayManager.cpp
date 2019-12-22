#include "DisplayManager.h"
#include "DataManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include<sstream>  
using std::cout;
using std::endl;

DisplayManager::DisplayManager(DataManager &manager) {
	dm = manager;
	
}
void DisplayManager::DisplayIndicator(FileManager &fm,string indicator)
{
	cout << std::right << std::setw(6) << indicator << endl;
	fm.WriteToFile(indicator);
}
void DisplayManager::DisplayTitle(FileManager& fm, string title, int dayAmount, int offsetLength)
{

	for (int i = 0; i <= (dayAmount+offsetLength)/2; i++)
	{
		
		if (i == ((dayAmount + offsetLength) / 2))
		{
			cout << title;
			fm.WriteToFile(title);
		}
		else
		{
			
			cout << _blankPlot;
			//c is created because blankPlot can't be passed directly to WriteToFile
			char c = _blankPlot;
			fm.WriteToFile(c);
		}
	}
}
void DisplayManager::PrintDates(FileManager& fm, int xSize) {
	//Date displayed once every 3 days as the space taken by displaying a date is 
	//of 3 units on the x axis
	
	xSize += -1;
	int lastElementIndex = ((int)(dm.GetDataSetVector().size()-1));
	char word;
	string indicator;


		for (int i = (lastElementIndex - (xSize)); i <= lastElementIndex; i += 3)
		{
			if (i == (lastElementIndex - (xSize)))
			{
				//The first date outputted on the left corner
				int propIndex = lastElementIndex - (lastElementIndex  - xSize);
				cout << _blankPlot;
				word = _blankPlot;
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[propIndex].GetDate()[0];
				word = dm.GetDataSetVector()[propIndex].GetDate()[0];
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[propIndex].GetDate()[1];
				word = dm.GetDataSetVector()[propIndex].GetDate()[1];
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[propIndex].GetDate()[2];
				word = dm.GetDataSetVector()[propIndex].GetDate()[2];
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[propIndex].GetDate()[3];
				word = dm.GetDataSetVector()[propIndex].GetDate()[3];
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[propIndex].GetDate()[4];
				word = dm.GetDataSetVector()[propIndex].GetDate()[4];
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[propIndex].GetDate()[5];
				word = dm.GetDataSetVector()[propIndex].GetDate()[5];
				fm.WriteToFile(word);
				cout << _blankPlot;
				fm.WriteToFile(word);
			}

			else
			{
				//prints 4th and 5th letter and separates them by comma
				cout << dm.GetDataSetVector()[lastElementIndex - i].GetDate()[4];
				word = dm.GetDataSetVector()[lastElementIndex - i].GetDate()[4];
				fm.WriteToFile(word);
				cout << dm.GetDataSetVector()[lastElementIndex - i].GetDate()[5];
				word = dm.GetDataSetVector()[lastElementIndex - i].GetDate()[5];
				fm.WriteToFile(word);
				cout << _blankPlot;
				word = _blankPlot;
				fm.WriteToFile(word);
			}

		}
	
	cout << endl;
	fm.AddEndLine();
	for (int i = 0; i <= xSize/2; i++)
	{
		if (i == xSize / 2)
		{
			
			indicator = _dateIndicator;
			cout << indicator;
			fm.WriteToFile(indicator);
		}
		else {
			word = _blankPlot;
			cout << word;
			fm.WriteToFile(word);
		}
	}
	cout << endl;
}
void DisplayManager::PrintXAxis(FileManager &fm,int dayAmount,int offsetLength) {
	char word;
	//Empty space offset before the graph starts
	for (int i = 0; i < offsetLength; i++)
	{
		word = _blankPlot;
		cout << word;
		fm.WriteToFile(word);
	}
	
	
	int count = 0;
	//stick is printed once every 3 days
	for (int i = 0; i < dayAmount; i++)
	{

		if (i == 0)
		{
			
			word = _xAxisCorner;
			cout << word;
			fm.WriteToFile(word);
		}

		if (count == 0)
		{
			
			word = _xAxisStick;
			cout << word; 
			fm.WriteToFile(word);
			count++;
		}
		else if (count == 1)
		{
			
			word = _xAxisLine;
			cout << word; 
			fm.WriteToFile(word);
			count++;
		}
		else if (count == 2)
		{
			 
			word = _xAxisLine;
			cout << word;
			fm.WriteToFile(word);
			count = 0;
		}
	}
}
void DisplayManager::DisplayCandleStickGraph(FileManager& fm,int dayAmount, int offsetLength)
{
	/*opy of the vector with the total values is created
	this is because dm.GetShrunkTotalVector() cannot 
	be passed directly to dm.ReturnValueIndex()
	*/
	vector<int> shrunkTotalVector = dm.GetShrunkTotalVector();
	dm.BubbleSort(shrunkTotalVector);
	//the x axis size is equal to the size of the total data set (amount of days)
	int xSize = (int)dm.GetDataSetVector().size();
	if (dayAmount > xSize)
	{
		dayAmount = xSize;
	}

	DisplayTitle(fm,_candleStickTitle,dayAmount,offsetLength);
	cout << endl;
	fm.AddEndLine();
	cout << std::right << std::setw(6) << _priceIndicator<<endl;
	string indicator = _priceIndicator;
	fm.WriteToFile(indicator);
	fm.AddEndLine();

	char word;
	//the y axis starts at the top and moves downards
	for (int y = (int)(dm.GetShrunkTotalVector().size() - 1); y >= 0; y--)
	{

		//axis is printed and written to file
		cout << std::right << std::setw(6) << shrunkTotalVector[y] << _straightBar;
		fm.PrintYAxis(shrunkTotalVector[y], 6);
		

		for (int x = dayAmount-1; x >= 0; x--)
		{
			CandleStickData day = dm.GetDataSetVector()[x];	
			bool priority = false, plotted = false, bearish = false;
			int startIndexBar = 0, endIndexBar = 0, startIndexHigh = 0, startIndexLow = 0;
				
			//Where each section of the candle stick starts and/or ends
			startIndexBar = dm.ReturnValueIndex(shrunkTotalVector, day.GetOpen());
			endIndexBar = dm.ReturnValueIndex(shrunkTotalVector, day.GetClose());
			startIndexHigh = dm.ReturnValueIndex(shrunkTotalVector, day.GetHigh());
			startIndexLow = dm.ReturnValueIndex(shrunkTotalVector, day.GetLow());

			if (startIndexBar < endIndexBar)
			{
				//swap the open and close indexes so its easier to plot
				int temp = startIndexBar;
				startIndexBar = endIndexBar;
				endIndexBar = temp;
			}
			if (day.GetOpen()> day.GetClose())
			{bearish = false;}
			else
			{bearish = true;}

			//Logic to either make the candle stick bearish or bullish
			if (y == dm.ReturnValueIndex(shrunkTotalVector, day.GetOpen()) && !bearish)
			{
				word = _bullishBar;
				plotted = true;
				priority = true;
			}
			else if (y == dm.ReturnValueIndex(shrunkTotalVector, day.GetClose()) && bearish)
			{
				word = _bearishBar;
				plotted = true;
				priority = true;
			}
			//fills the bar between the open and close indexes
			if (y < startIndexBar && y >= endIndexBar)
			{
				if (bearish == true)
				{
					
					word = _bearishBar;
					plotted = true;
					priority = true;
				}
				else
				{
					
					word = _bullishBar;
					plotted = true;
					priority = true;
				}
			}
			//straight bar printed at the start of the high index
			if (y == dm.ReturnValueIndex(shrunkTotalVector, day.GetHigh()) && dm.CheckOverlap(y, shrunkTotalVector, day.GetOpen()) && dm.CheckOverlap(y, shrunkTotalVector, day.GetClose()) && !priority)
			{
				word = _straightBar;
				plotted = true;
			}
			//straight bar printed between the high index and the open index
			if (y<startIndexHigh && y>startIndexBar && !priority)
			{
				word = _straightBar;
				plotted = true;
				
			}
			//straight bar printed at the end of the low index
			if (y == dm.ReturnValueIndex(shrunkTotalVector, day.GetLow()) && dm.CheckOverlap(y, shrunkTotalVector, day.GetOpen()) && dm.CheckOverlap(y, shrunkTotalVector, day.GetClose()) && !priority)
			{
				word = _straightBar;
				plotted = true;
				
			}
			//straight bar printed between the low index and the close index
			if (y<endIndexBar && y>startIndexLow && !priority)
			{
				word = _straightBar;
				plotted = true;
				
			}
			if (!plotted)
			{
				
				word = _blankPlot;
				
			}
			cout << word;
			fm.WriteToFile(word);	
		}
		cout << endl;
		fm.AddEndLine();
		
	}
	PrintXAxis(fm, dayAmount,offsetLength);
	cout << endl;
	fm.AddEndLine();

	PrintDates(fm, dayAmount);
	cout << endl;
	cout << endl;
	fm.AddEndLine();
	fm.AddEndLine();
	fm.AddEndLine();
		
	
	

}
void DisplayManager::DisplayMovingAverage(FileManager& fm,int dayAmount, int offsetLength) {
	
	vector<int> shrunkSet = dm.GetShrunkAverageVector();
	dm.BubbleSort(shrunkSet);
	vector<int> averageSet = dm.GetAverage9Vector();
	int xSize = (int)averageSet.size();
	if (dayAmount > xSize)
	{
		dayAmount = xSize;
	}
	
	DisplayTitle(fm, _movingAverageTitle, dayAmount, offsetLength);
	cout << endl;
	cout << endl;
	fm.AddEndLine();
	char wordToPrint;
	cout << std::right << std::setw(6) << _priceIndicator << endl;
	string indicator = _priceIndicator;
	fm.WriteToFile(indicator);
	fm.AddEndLine();


	
	for (int y = (int)(shrunkSet.size()-1); y >= 0; y--)
	{
		cout << std::right << std::setw(6) << shrunkSet[y] << _straightBar;
		fm.PrintYAxis(shrunkSet[y], 6);
		for (int x = 0; x <= dayAmount - 1; x++)
		{
			
				if (x >= 9 && y == dm.ReturnValueIndex(shrunkSet, dm.GetAverage9Vector()[x]) )
				{
					
					wordToPrint = _xPlot;
					cout << wordToPrint;


				}
				else if (x >= 18 && y == dm.ReturnValueIndex(shrunkSet, dm.GetAverage18Vector()[x]))
				{
					
					wordToPrint = _oPlot;
					cout << wordToPrint;

				}
				else
				{
					
					wordToPrint = _blankPlot;
					cout << wordToPrint;
				}
			
				fm.WriteToFile(wordToPrint);
				
		}
		cout << endl;
		fm.AddEndLine();
	}

	PrintXAxis(fm, dayAmount,offsetLength);
	cout << endl;
	fm.AddEndLine();

	PrintDates(fm, dayAmount);
	cout << endl;
	cout << endl;
	fm.AddEndLine();
	fm.AddEndLine();
	fm.AddEndLine();

}
void DisplayManager::DisplayBarChart(FileManager& fm,int dayAmount, int offsetLength) {
	int xSize = (int)dm.GetDataSetVector().size();
	if (dayAmount > xSize)
	{
		dayAmount = xSize;
	}
	DisplayTitle(fm, _volumeTitle, dayAmount, offsetLength);
	cout << endl;
	fm.AddEndLine();
	cout << std::right << std::setw(6) << _volumeIndicator << endl;
	vector<double> shrunkV = dm.GetShrunkVolumeVector();
	dm.BubbleSort(shrunkV);
	char wordToPrint;

	


	for (int y = (int)(shrunkV.size() - 1); y >= 0; y--)
	{
		cout << std::right << std::setw(2) << (int)(shrunkV[y]/1000000000) << " Bil" << '|';
		fm.PrintYAxis((int)(shrunkV[y] / 1000000000),6);
		for (int x = dayAmount-1; x >= 0; x--)
		{
			CandleStickData day = dm.GetDataSetVector()[x];
			int index  = dm.ReturnValueIndex(shrunkV, dm.GetDataSetVector()[x].GetVolume());
			
			if (dm.GetDataSetVector()[x].GetOpen() > dm.GetDataSetVector()[x].GetClose() && (y == dm.ReturnValueIndex(shrunkV, dm.GetDataSetVector()[x].GetVolume()) || y < index))
			{
				cout << _bullishBar;
				wordToPrint = _bullishBar;
			}
			else if (dm.GetDataSetVector()[x].GetOpen() < dm.GetDataSetVector()[x].GetClose()&&(y == dm.ReturnValueIndex(shrunkV, dm.GetDataSetVector()[x].GetVolume()) || y < index))
			{
				cout << _bearishBar;
				wordToPrint = _bearishBar;
			}
				
				
			else 
			{
				wordToPrint = _blankPlot;
				cout << wordToPrint;
				
			
			}
			fm.WriteToFile(wordToPrint);
		}

		cout << endl;
		fm.AddEndLine();
	}
	
	PrintXAxis(fm, dayAmount,offsetLength);
	cout << endl;
	fm.AddEndLine();
	PrintDates(fm, dayAmount);
	cout << endl;
	cout << endl;
	fm.AddEndLine();
	fm.AddEndLine();
	fm.AddEndLine();
}
void DisplayManager::DisplayRSI(FileManager& fm,int dayAmount, int offsetLength) {
	int xSize = (int)dm.GetDataSetVector().size();
	if (dayAmount > xSize)
	{
		dayAmount = xSize;
	}
	DisplayTitle(fm, _rsiTitle, dayAmount, offsetLength);
	cout << endl;
	fm.AddEndLine();
	cout << std::right << std::setw(6) << _rsiIndicator << endl;
	double gain=0, loss=0, prevgain=0, prevloss=0;
	char wordToPrint;
	vector<int> yaxis;
	/*creates a Y axis for the graph
	its done here because it requires no data*/
	for (int i = 10; i <= 100; i+=10)
	{
		yaxis.push_back(i);
	}
	int maxSize = (int)(dm.GetRsiVector().size() - 1);
	if (dayAmount > maxSize)
	{
		dayAmount = maxSize;
	}


	for (int y = 100; y >= 0; y-=10)
	{
		cout << std::right << std::setw(6) << y << _straightBar;
		fm.PrintYAxis(y, 6);
		for (int x = dayAmount-1 ; x >=0 ; x--)
		{
				/*there are only 10 values in the y axis vector
				so the index has to be timed by 10
				to match the y values*/
				if (y == dm.ReturnValueIndex(yaxis, dm.GetRsiVector()[x]) * 10)
				{
					
					wordToPrint = _xPlot;
					cout << wordToPrint;
				}
				else if (y == 30 || y == 70)
				{
					
					wordToPrint = _dashPlot;
					cout << wordToPrint;

				}
				else
				{
					
					wordToPrint = _blankPlot;
					cout << wordToPrint;
				}
				fm.WriteToFile(wordToPrint);
		}
		cout << endl;
		fm.AddEndLine();
		
	}
	
	PrintXAxis(fm, dayAmount,offsetLength);
	cout << endl;
	fm.AddEndLine();
	PrintDates(fm, dayAmount);
	cout << endl;
	cout << endl;
	fm.AddEndLine();
	fm.AddEndLine();
	fm.AddEndLine();
}