/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					   OOP345 Workshop - #1 (PART 2)
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date:      :  Sep 15, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "RideRequest.h"

using namespace std;

double g_taxrate;
double g_discount;

namespace sdds
{

	//copy constructor
	RideRequest::RideRequest(const RideRequest& rhs)
	{
		*this = rhs; //using equal operator to copy the constructor 
	}

	//equal assigment 
	RideRequest& RideRequest::operator=(const RideRequest&rhs)
	{
		if (this != &rhs) { //checking that it isn'ts self assigment 

			//in case extraDetails of the left hand side object isn't nullptr, delete and null it to prevent memory leak
			if (extraDetails != nullptr) {
				delete[] extraDetails;
				extraDetails = nullptr;
			}

			//copy the name from the right object to the left hand side
			strcpy(custName, rhs.custName);

			//checking the rhs extraDetails isn't nullptr to prevent trying to copy an empty sting
			if (rhs.extraDetails != nullptr) {
				extraDetails = new char[strlen(rhs.extraDetails) + 1];
				strcpy(extraDetails, rhs.extraDetails);
			}
			//copying price and discount of right hand side to left. 
			price = rhs.price; 
			discount = rhs.discount;
		}
		return *this; //returning object
	}

	//destructor
	RideRequest::~RideRequest() {
		delete[] extraDetails;
		extraDetails = nullptr;
	}

	//reading from the file 
	void RideRequest::read(istream& is)
	{
		RideRequest t; //temp object 
		string t_detail; //sting for reading the details to be read from istream
		char t_disc, del=','; //char for reading the discount letter, and a char variable with the delimter

		if (is.good()) { //checking the the istream is in good 

			//using egtline to read the the name and the string ignoring the delimiter
			is.getline(t.custName, NSIZE, del);
			getline(is, t_detail, del);

			//creating a new dynamic extraDetails char based on the length of the sting and copying it
			t.extraDetails = new char[t_detail.length() + 1];
			strcpy(t.extraDetails, t_detail.c_str());

			//getting input of price and discount, ignoring the delimiter
			is >> t.price;
			is.ignore();
			is >> t_disc;
			is.ignore();

			//checking if the discount is 'Y', if so assign true to discount bool
			t.discount = t_disc == 'Y';
		}
		*this = t; //assign current object to the temp object, usinh equal assigment 
	}

	void RideRequest::display() const
	{
		static int i = 0; //counter

		//print the counter
		cout << left << setw(2) << ++i << ". ";

		//If no customer name has been stored in the current object, print "No Ride Request"
		if (custName[0] == '\0') {
			cout << "No Ride Request" << endl;
		}
		else //if there is name, meaning there is a rider, display the riders request
		{ 
			//calculate the total price with tax
			double taxedPrice = price + (price * g_taxrate);

			//print the riders info
			cout << left << setw(10) << custName << "|" << left << setw(25) << extraDetails << "|" << fixed << setprecision(2) << left << setw(12) << taxedPrice << "|";

			//if there is discount, apply the dicount and dispay the new price
			if (discount) {
				double priceWithDisc = taxedPrice - g_discount;
				cout << right << setw(13) << priceWithDisc;
			}
			cout << endl; 
		}
	}
}