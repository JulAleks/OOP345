/*************** MS 1 - Utilities Module -  Utilities.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-06

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The Utilities module supports the parsing of input files, which contain information used to setup and configure the assembly line.
*/

#include <iostream>
#include <string>
#include "Utilities.h"

namespace sdds {
	//Class Variable
	char Utilities::m_delimiter;

	//sets the field width of the current object to the value of parameter 
	void Utilities::setFieldWidth(size_t newWidth)
	{
		if (newWidth) {
			m_widthField = newWidth;
		}
	}

	//returns the field width of the current object
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	//extracts a token from string str referred to by the first parameter.
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token; //token string
		size_t startPos = next_pos; //init pos

		std::string strTrim = trimSpace(str); //trimming the space of the init str
		size_t endPos = strTrim.find(m_delimiter, startPos); //finidng the end pos

		if (endPos == std::string::npos) {  //if end pos is the end of str, get token from trimmed str and set to false
			token = strTrim.substr(startPos);
			more = false;
		}
		else {
			//else, get token from the trimmed str
			token = strTrim.substr(startPos, endPos - startPos);

			//if token did not get extracted 
			if (token.empty()) {
				more = false;  //no more to extract 
				if (!more) { //delim found in next pos
					throw std::string("Delimiter found next pos");
				}
			}

			more = (next_pos < str.length()); //update if there is more to extract
			next_pos = endPos + 1; //change next pos
		}

		token = trimSpace(token);  //trim the token

		if (token.length() > m_widthField) { //update the max length
			m_widthField = token.length();
		}

		return token; //return token
	}
	

	//sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter)
	{
		if (newDelimiter) {
			m_delimiter = newDelimiter;
		}
	}

	//returns the delimiter for this class.
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

	//trimming helper
	std::string trimSpace(const std::string& str)
	{
		size_t firstSpace = str.find_first_not_of(' ');
		if (std::string::npos == firstSpace) {
			return str;
		}
		size_t lastSpace = str.find_last_not_of(' ');
		return str.substr(firstSpace, (lastSpace - firstSpace + 1));
	}

}

