#include <iostream>
#include "simulate.h"


using namespace std;

queue<Customer> bankQueue;
EventList eList;
int totalNum = 0;
float sumTime = 0;
float maxTime = 0;
float maxWaitTime = 0;
float sumWaitTime = 0;
int maxLength = 0;


int main()
{	
	fstream out;
	out.open("output.txt");
	if (!out)
	{
		throw("can not open the file.");
	}
	int currentTime = 0;
	out<<"t = 0:  Simulation begins" << endl;   //write data to file
	ReadData("arrivalfile2.txt");
	int flag = 1;
	while (!eList.isEmpty())
	{
		Event tempE = eList.DelEvent();
		if (flag == 1)
		{
			flag = 0;
			currentTime = tempE.getTime();
		}
		if (tempE.getEType() == Arrival)          //Process arrival event
		{
			if (currentTime >= tempE.getTime())
				currentTime = tempE.getTime();
			out << "t = " << currentTime << ": Arrival event" << endl;
			bool atFront = bankQueue.empty();
			bankQueue.push({ tempE.getTime(), tempE.getServiceTime() });//insert customer int teller queue
			if (atFront)
			{
				int departureTime = currentTime + tempE.getServiceTime();   //get the departureTime
				Event ev(departureTime, Departure);
				eList.AddEvent(ev);
			}
			currentTime = currentTime + tempE.getServiceTime();
			int size = bankQueue.size();
			if (size > maxLength) maxLength = size;   //get the max size of queue
		}
		else                                   //Process departure event	
		{
			if (currentTime >= tempE.getTime())
				currentTime = tempE.getTime();
			out << "t = " << currentTime << ": Departure event" << endl;

			/*figure the time*/
			Customer cusTime = bankQueue.front();            
			float bankTime = (float) (currentTime - cusTime.arriveTime);
			float waitTime = bankTime - cusTime.transactionTime;
			sumTime += bankTime;
			if (bankTime > maxTime) maxTime = bankTime;
			sumWaitTime += waitTime;
			if (waitTime > maxWaitTime) maxWaitTime = waitTime;
			/*figure time end*/

			bankQueue.pop();              //delete the front customer
			if (!bankQueue.empty())
			{
				Customer nowCustomer = bankQueue.front();
				int departureTime = currentTime + nowCustomer.transactionTime;   //get the departureTime
				Event ev(departureTime, Departure);
				eList.AddEvent(ev);
				currentTime = currentTime + nowCustomer.transactionTime;
			}
			else
			{
				flag = 1;
			}

		}
	}
	out << endl;
	out << "Total number of customers = " << totalNum << endl;
	out << "Average amount of time in the bank = " << sumTime / totalNum << " minutes" <<endl;
	out << "Maximum amount of time in the bank = " << maxTime << " minutes" << endl;
	out << "Average amount of time waiting = " << sumWaitTime / totalNum << " minutes" << endl;
	out << "Maximum amount of time waiting = " << maxWaitTime <<" minutes" << endl;
	out << "Maximum length of line = " << maxLength <<" customers"<< endl;
	out.close();
	return 0;
}