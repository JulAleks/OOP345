/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #1 (PART 2)
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date:      :  Sep 15, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#define NSIZE 10 //max size for the name, including NULL terminator

extern double g_taxrate;
extern double g_discount;

namespace sdds {
    class RideRequest {
        
        char custName[NSIZE]{};
        char* extraDetails{};
        double price{};
        bool discount{};

    public:
        // default constructor
        RideRequest() {};

        // copy constructor
        RideRequest(const RideRequest&);

        // assignment operator
        RideRequest& operator=(const RideRequest&);

        // destructor
        ~RideRequest();

        //reading from file 
        void read(std::istream& is);

        //displaying the input
        void display() const;
    };
}

#endif // !SDDS_RIDEREQUEST_H
