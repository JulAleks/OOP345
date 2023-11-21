/*************** WS 07_01 - CovidCollection Module -  CovidCollection.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-06

 I have done all the coding by myself and only copied the code that my professor
 provided to complete my workshops and assignments.
**************************************************************************************/

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H


#include <iostream>
#include <vector>
#include <string>


namespace sdds {
	//This module defines a simple structure called Covid, capable of storing information about a covid details for a particular city
	struct Covid {
		std::string c_county{}; //country (as a string)
		std::string c_city{}; //city (as a string)
		std::string c_variant{}; //variant (as a string)
		int c_year{}; //year (as an integer)
		size_t c_numCase{}; //number of cases (as an unsigned integer)
		size_t c_numDeath{}; //number of deaths (as an unsigned integer)
	};

	//Also, define a class called CovidCollection that manages a collection of objects of type Covid. 
	class CovidCollection {
		std::vector<Covid>corona; //Choose an appropriate STL container to store the collection.

	public:
		CovidCollection() {}; //default

		CovidCollection(const std::string);//custome one arrg constructor, gets name

		void display(std::ostream& out) const; //print the content of the collection into the parameter
	};

	//Free Helpers
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid); //inserts one Covid object into the first parameter
	std::string trimSpace(const std::string& str); //trimmer
}  

#endif