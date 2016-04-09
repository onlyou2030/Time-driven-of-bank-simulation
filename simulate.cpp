#include "simulate.h"
#include <fstream>

//add event to the list
void EventList::AddEvent(Event evt)
{
	if (!isFull())
	{
		events[count] = evt;
		count++;
	}
}


//The minimum time given top priority
Event EventList::DelEvent()
{
	if (!isEmpty())
	{
		int min = events[0].getTime();
		int minindex = 0;

		for (int i = 1; i < count; i++)
		{
			if (events[i].getTime() < min)
			{
				min = events[i].getTime();
				minindex = i;
			}
		}
		if (events[minindex].getEType() == Arrival)  //departurn first,arrival second
			for (int i = 0; i < count; i++)
				if (events[i].getTime() == events[minindex].getTime() && events[i].getEType() == Departure) minindex = i;
		Event et = events[minindex];
		events[minindex] = events[count - 1];
		count--;
		return et;
	}
	else
		throw("delete error");
}



//read data from file
void ReadData(char *fileName)
{
	fstream in;
	in.open(fileName);
	if (!in)
	{
		throw("can not open the file.");
	}
	int i = 0, temp1 = 0, temp2 = 0;
	while (!in.eof())
	{
		totalNum++;
		in >> temp1 >> temp2;
		Event ev(temp1, Arrival, temp2);
		eList.AddEvent(ev);
		//cout << temp1 << " " << temp2 << endl;
	}
	in.close();
}