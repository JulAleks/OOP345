/*************** MS 3 - Utilities Module -  Utilities.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The Utilities module supports the parsing of input files, which contain information used to setup and configure the assembly line.
*/
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
#include <string>

namespace sdds {

	class Utilities {
		//Instance Variable
		size_t m_widthField{ 1 }; //specifies the length of the token extracted; used for display purposes; default value is 1.

		//Class Variable
		static char m_delimiter;  //separates the tokens in any given std::string object. All Utilities objects in the system share the same delimiter
	public:
		//Member Functions
		Utilities() {};
		void setFieldWidth(size_t newWidth); //sets the field width of the current object to the value of parameter newWidth
		size_t getFieldWidth() const; //returns the field width of the current object
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);// extracts a token from string str referred to by the first parameter.

		//Class Functions
		static void setDelimiter(char newDelimiter); //sets the delimiter for this class to the character received
		static char getDelimiter(); //returns the delimiter for this class

	};
	//helper to trim
	std::string trimSpace(const std::string& str);
}

#endif 
