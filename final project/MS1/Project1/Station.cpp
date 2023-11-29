/*************** MS 1 - Station Module -  Station.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-06

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/

/*
The Station module manages information about a station on the assembly line, which holds a specific item and fills customer orders.
*/


#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Station.h"

namespace sdds {
	//Class Variables
	size_t Station::m_widthField = 0; // init m_widthField to 0
	unsigned int Station::id_generator = 0; // init id_generator to 0

	//custom 1-argument constructor
	Station::Station(const std::string line)
	{
		if (!line.empty()) {
			//generate id
			++id_generator;
			s_ID = id_generator;

			//upon instantiation, a Station object receives a reference to an unmodifiable std::string. This string contains a single record (one line) that has been retrieved from the input file specified by the user.
			std::vector<std::string> tokens;
			size_t next_pos = 0;
			bool more = true;
			//this constructor uses a Utilities object (defined locally) to extract each token from the record and populates the Station object accordingly.
			while (tokens.size() <= 4) {
				tokens.push_back(extractToken(line, next_pos, more));
			}

			//this constructor assumes that the string contains 4 fields separated by the delimiter, in the following order:
		
			//name of the item
			s_name = tokens[0];

			//starting serial number
			s_SN = std::stoi(tokens[1]); //modifying back to int

			//quantity in stock
			s_stock = std::stoi(tokens[2]); //modifying back to int

			//description
			s_desc = tokens[3];

			//updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField.
			if (m_widthField < s_name.length()) {
				m_widthField = s_name.length();

				setFieldWidth(m_widthField);
			}
		}
		else {
			throw std::string("ERROR: Can't read line.\n");
		}
	}


	//returns the name of the current Station object
	const std::string& Station::getItemName() const
	{
		return s_name;
	}

	//returns the next serial number to be used on the assembly line and increments m_serialNumber
	size_t Station::getNextSerialNumber()
	{
		return s_SN++;
	}

	//returns the remaining quantity of items in the Station object
	size_t Station::getQuantity() const
	{
		return s_stock;
	}

	//ubtracts 1 from the available quantity; should not drop below 0.
	void Station::updateQuantity()
	{
		if (s_stock - 1 >= 0) {
			--s_stock;
		}
	}

	//inserts information about the current object into stream os.
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setfill('0') << std::setw(3) << s_ID << " | "
			<< std::setfill(' ') << std::setw(m_widthField) << std::left << s_name << " | "
			<< std::setfill('0') << std::setw(6) << std::right << s_SN << " | ";
		if (full) {
			os << std::setw(4) << std::setfill(' ') << std::right << s_stock << " | " << s_desc << std::endl;
		}
		else {
			os << std::endl;
		}

	}

}