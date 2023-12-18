/*************** MS 3 - Work Station Module - Workstation.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The Workstation module consists of three double-ended queues of CustomerOrder and the Workstation class.
*/
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <string>
#include <deque>
#include "CustomerOrder.h"
namespace sdds {

	//global variables, Each queue is accessible outside this module's translation unit.
	extern std::deque<CustomerOrder> g_pending; //holds the orders to be placed onto the assembly line at the first station.
	extern std::deque<CustomerOrder> g_completed; //holds the orders that have been removed from the last station and have been completely filled.
	extern std::deque<CustomerOrder> g_incomplete; //holds the orders that have been removed from the last station and could not be filled completely.


	class Workstation : public Station {
		//Instance Variables
		std::deque<CustomerOrder> m_orders; //is a double-ended-queue with CustomerOrders entering the back and exiting the front. These are orders that have been placed on this station to receive service (or already received service).
		Workstation* nextStat{ nullptr }; //Parameter defaults to nullptr

	public:
		//Member Functions
		Workstation() {}; //default

		//a custom 1-argument constructor -- receives a reference to an unmodifiable reference to std::string and passes it to the Station base class. 
		Workstation(const std::string &);


		//Since a Workstation object represents a single location on the assembly line for filling customer orders with items, the object cannot be copied or moved. 
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;

		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		void fill(std::ostream& os); //this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.

		bool attemptToMoveOrder();//attempts to move the order order at the front of the queue to the next station in the assembly line :

		void setNextStation(Workstation* station); //this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation.Parameter defaults to nullptr.

		Workstation* getNextStation() const;  //this query returns the address of next Workstation

		void display(std::ostream& os) const; //this query inserts the name of the Item for which the current object is responsible into stream os

		Workstation& operator+=(CustomerOrder&& newOrder); //moves the CustomerOrder referenced in parameter newOrder to the back of the queue.





	

	};







}

#endif 
