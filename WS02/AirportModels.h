/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #2 (PART 1)
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date:      :  Sep 23, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H


extern int cout;

namespace sdds
{
    struct Airport {
        std::string a_code{}; // a string representing the Airport code
        std::string a_name{}; // a string representing the Airport name
        std::string a_city{}; // a string representing the Airport city
        std::string a_state{}; // a string representing the Airport state
        std::string a_country{}; // a string representing the Airport country
        double a_latitude{}; // a floating-point number in double precision representing the latitude of the airport
        double a_longitude{}; // a floating-point number in double precision representing the longitude of the airport

        // Overload the insertion operator to output an Airport object to an output stream
        friend std::ostream& operator<<(std::ostream& os, const Airport&);
    };

    class AirportLog {
        //dynamic array of Airport objects
        Airport* airports{ nullptr };
        size_t numAir{ 0 };//counter
    public:
        void setToDefault();

        //Default constructor
        AirportLog() {};

        //A one argument constructor that receives a filename as a parameter 
        AirportLog(const char * fileName);

        //destrcutor
        ~AirportLog();

        //copy constructor
        AirportLog(const AirportLog&);

        //copy assigment 
        AirportLog& operator=(const AirportLog&);

        //moves
        AirportLog(AirportLog&&) noexcept;
        AirportLog& operator=(AirportLog&&)noexcept;

        //addAirport() is a modifier that receives a constant reference to an Airport object
        void addAirport(const Airport&);

        //is a query that receives two C-style strings as paramenters representing the state name and the country name
        AirportLog findAirport(const char* state, const char* country);

        //a query that will return the Airport in the dynamic array at the index provided
        const Airport& operator[](size_t) const;

        //s a casting operator that will convert the current object to a size_t value.
        operator size_t() const;
    };

}

#endif // !SDDS_AIRPORTMODELS_H
