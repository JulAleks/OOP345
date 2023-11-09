/*/////////////////////////////////////////////////////////////////////////
					   OOP345 Workshop - #1 (PART 1)
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date:      :  Sep 11, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#define NSIZE 10

extern double g_taxrate;
extern double g_discount;

namespace sdds
{
	extern int cout;
	

	class RideRequest {
		// a C-style null-terminated string of up to 10 characters *including the null byte terminator* representing the name of the customer.
		char custName[NSIZE + 1];

		// a C-style null-terminated string of up to 25 characters *including the null byte terminator* representing the extra details about the ride (e.g., a description or special requirements the customer made).
		char *extraDetails;

		//the price of the ride as a floating-point number in double precision
		double price;

		//a Boolean flag indicating whether the ride receives a discount
		bool discount;

	public:
		//Sets to default
		void setToDefault();

		//Default constructor
		RideRequest();

		// Copy constructor
		RideRequest(const RideRequest&);

		// Assignment operator
		RideRequest& operator=(const RideRequest& other);

		//a modifier that receives an `istream` reference.
		void read(std::istream&);

		// a query that displays to the screen the content of an `Ride Request` instance in the following format:
		void display() const;

		const char getName() const;
		const char* extraDetails() const;
		const double getPrice;
		bool isDisc() const;
	};
	
	
}


#endif // !RideRequest.h
