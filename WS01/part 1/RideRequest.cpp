/*/////////////////////////////////////////////////////////////////////////
					   OOP345 Workshop - #1 (PART 1)
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date:      :  Sep 11, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <iomanip>
#include <string>
#include "RideRequest.h"

using namespace std;

double g_taxrate;
double g_discount;

namespace sdds
{
	//default setter
	void RideRequest::setToDefault()
	{
		custName[0] = '\0';
		extraDetails[0] = '\0';
		price = 0.0;
		discount = false;
	}

	//Default constructor
	RideRequest::RideRequest() {
		setToDefault();
	}

	//a modifier that receives an `istream` reference.
	void RideRequest::read(istream& is)
	{
		char disc, delimiter;
		//If the `istream` is in a good state, this function will attempt to read from the `istream` and store the information read into the current object.
		if (is.good() && is.getline(custName, NSIZE, ',') && is.getline(extraDetails, ISIZE, ',') && is >> price >> delimiter >> disc){
			//The discount status can be of two values: `'Y'` if a discount should be applied and `'N'` otherwise.
			disc == 'Y' ? discount = true : discount = false;

			// ignore next line
			is.ignore(10, '\n');
		}
		else {
			; //If the `istream` object is not in a good state then this function will do nothing.
		}
	}

	// a query that displays to the screen the content of an `Ride Request` instance in the following format
	void RideRequest::display()
	{
		static int counter=0;
		//print the counter
		std::cout << left << setw(2) << ++counter << ". ";

		//If no customer name has been stored in the current object, this query should print:COUNTER.No Ride Request
		if (custName[0] == '\0') {
			std::cout<< "No Ride Request" << endl;
		}
		else { //if there is name printing based on istructions 
			double taxedPrice = price + (price * g_taxrate);
			std::cout << left << setw(10) << custName << "|" << left << setw(25) << extraDetails << "|" << fixed << setprecision(2) << left << setw(12) << taxedPrice << "|" ;
			if (discount) {
				double priceWithDisc = taxedPrice - g_discount;
				std::cout<< right << setw(13) << priceWithDisc;
			}
			std::cout << endl;
		}
	}
}