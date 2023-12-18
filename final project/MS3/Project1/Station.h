/*************** MS 3 - Station Module -  Station.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The Station module manages information about a station on the assembly line, which holds a specific item and fills customer orders.
*/
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <string>
#include "Utilities.h"

namespace sdds {

	class Station : public Utilities {
		//Instance Variable
		int s_ID{}; //the id of the station (integer)
		std::string s_name{}; //the name of the item handled by the station (string)
		std::string s_desc{}; //the description of the station (string)
		unsigned int s_SN{}; //the next serial number to be assigned to an item at this station (non-negative integer)
		unsigned int s_stock{}; //the number of items currently in stock (non-negative integer)

		//Class Variables
		static size_t m_widthField; // the maximum number of characters required to print to the screen the item name for any object of type Station. Initial value is 0.
		static unsigned int id_generator; // a variable used to generate IDs for new instances of type Station. Every time a new instance is created, the current value of the id_generator is stored in that instance, and id_generator is incremented. Initial value is 0.

	public:
		Station() {}; //default
		Station(const std::string); //custom 1-argument constructor
		const std::string& getItemName() const; // returns the name of the current Station object
		size_t getNextSerialNumber(); //returns the next serial number to be used on the assembly line and increments m_serialNumber
		size_t getQuantity() const;// returns the remaining quantity of items in the Station object
		void updateQuantity();// subtracts 1 from the available quantity; should not drop below 0
		void display(std::ostream& os, bool full) const;// inserts information about the current object into stream os.
	};
}

#endif