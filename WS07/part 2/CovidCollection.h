/*************** WS 07_02 - CovidCollection Module -  CovidCollection.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-11

 I have done all the coding by myself and only copied the code that my professor
 provided to complete my workshops and assignments.
**************************************************************************************/

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H


#include <iostream>
#include <vector>
#include <string>
#include <list> 

namespace sdds {
	//This module defines a simple structure called Covid, capable of storing information about a covid details for a particular city
	struct Covid {
		std::string c_county{}; //country (as a string)
		std::string c_city{}; //city (as a string)
		std::string c_variant{}; //variant (as a string)
		int c_year{}; //year (as an integer)
		size_t c_numCase{}; //number of cases (as an unsigned integer)
		size_t c_numDeath{}; //number of deaths (as an unsigned integer)

		std::string c_severty{ "General" }; //Update the Covid structure to include a field representing severity status of the infection in a city (as a string); this field should be initialized to General
	};

	//Also, define a class called CovidCollection that manages a collection of objects of type Covid. 
	class CovidCollection {
		std::vector<Covid>corona; //Choose an appropriate STL container to store the collection.

	public:
		CovidCollection() {}; //default

		CovidCollection(const std::string);//custome one arrg constructor, gets name

		//print the content of the collection into the parameter
		//Task #1 Update this function's prototype to receive a second parameter country. This parameter should have the default value ALL if the client doesn't provide it (don't overload the function).
		void display(std::ostream& out, const std::string& country = "ALL") const;

		//Task #2 Sort the collection of Covid objects in ascending order based on the field received as parameter.
		//The parameter should have a default value of country.
		void sort(const std::string& field = "country");

		//Task #3 
		//Search in the collection for a city in the specified country where the variant from the first parameter has caused more deaths than the last parameter.
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;

		//Task #4
		//collection of Covid objects from the current instance where the number of deaths is at least as the value specified as parameter.
		std::list<Covid> getListForDeaths(unsigned int deaths) const;

		//Task #5
		//updates the status of each city. If the number of deaths is greater than 300, the status should be EPIDEMIC, if it is less than 50, it should be EARLY; for anything else, the status should be MILD
		void updateStatus();
	};

	//Free Helpers
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid); //inserts one Covid object into the first parameter
	std::string trimSpace(const std::string& str); //trimmer
	void printbar(); //bar printer
}  

#endif