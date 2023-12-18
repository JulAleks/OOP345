/*************** MS 3 - Work Station Module - Workstation.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/

#include <iostream>
#include <string>
#include <deque>
#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> g_pending; 
	std::deque<CustomerOrder> g_completed; 
	std::deque<CustomerOrder> g_incomplete;


	/*a custom 1-argument constructor -- receives a reference to an unmodifiable reference to std::string and passes it to the Station base class. */
	Workstation::Workstation(const std::string& str):Station(str)
	{
	}

	// this modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	// attempts to move the order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder()
	{	
		bool ok=false; 
		if (!m_orders.empty()) {
			//if the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station; otherwise do nothing
			if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0) { 
				//if there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
				if (!nextStat) {
					if (m_orders.front().isOrderFilled()) {  //if completed move to incomplete
						g_completed.push_back(std::move(m_orders.front()));
					}
					else {//if not completed
						g_incomplete.push_back(std::move(m_orders.front()));
					}
				}
				else {
					*nextStat += std::move(m_orders.front()); //move to next stat
				}
				m_orders.pop_front();
				//if an order has been moved, return true
				ok = true;
			}
			else {
				ok = false; //false otherwise.
			}
		}
		return ok;
	}

	//this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation
	void Workstation::setNextStation(Workstation* station)
	{
		nextStat = station;
	}

	//this query returns the address of next Workstation
	Workstation* Workstation::getNextStation() const
	{
		return nextStat;
	}

	void Workstation::display(std::ostream& os) const
	{
		//if the current object is the last Workstation in the assembly line this query inserts: ITEM_NAME --> End of Line
		
		if (nextStat == nullptr) {
			os << getItemName() << " --> " << "End of Line";
		}
		//this query inserts the name of the Item for which the current object is responsible into stream os following the format: ITEM_NAME --> NEXT_ITEM_NAME
		else {
			os << getItemName() << " --> " << nextStat->getItemName();
		}
		//in either case, the message is terminated with \n
		os<< std::endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}