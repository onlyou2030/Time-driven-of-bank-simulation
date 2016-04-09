#ifndef SIMULATE_H_
#define SIMULATE_H_

#include <queue>
#include <fstream>
#include <iostream>

using namespace std;

#define MAX 100

//event class
enum EventType{ Arrival, Departure };  //event type

struct Customer
{
	int arriveTime;
	int transactionTime;
};

//extern queue<Customer> bankQueue;

class Event
{
public:
	Event(int _time, EventType _eType, int _serviceTime=0)
	{
		time = _time;
		eType = _eType;
		serviceTime = _serviceTime;
	}
	Event(){};
	int getTime() { return time; }
	EventType  getEType() {return eType;}
	int getServiceTime() {return serviceTime;}
	void printEvent();
private:
	int time;         //arrive/leave time
	EventType eType;  //event type
	int serviceTime;  //if arrive,add the service time
};

//event list
class EventList
{
private:
	Event *events;
	int count;  //list length
public:
	EventList()
	{
		events = new Event[MAX];
		count = 0;
	}
	void AddEvent(Event evt);          //add event to the list

	Event DelEvent();                  //The minimum time given top priority

	bool isEmpty(){ return count == 0; }  //isEmpty
	bool isFull(){ return count == MAX; }  //isFull
	int length(){ return count; }          //get the length
};


//data
extern EventList eList;
extern int totalNum ;
extern float sumTime;
extern float maxTime;
extern float maxWaitTime;
extern float sumWaitTime;
extern int maxLength ;

//function
void ReadData(char *fileName);                       //read data from file


#endif