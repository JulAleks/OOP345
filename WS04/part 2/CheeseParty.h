/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #4 (PART 2)
Cheese Party Module
File	CheeseParty.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 07, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include "Cheese.h"
#include "CheeseShop.h"
namespace sdds {

    class CheeseParty {
        //This class should have attributes to store and manage a dynamically-allocated array of pointers to objects of type Cheese: const sdds::Cheese** (each element of the array points to an object of type Cheese). 
        //Very Important: This class is responsible for managing the array of pointers but is not managing the life of Cheese objects.
        const Cheese** dairyParty{};
        std::string p_name{ "Cheese Party" };
        size_t p_num{};

    public:
        //a default constructor
        CheeseParty() {};
        CheeseParty(size_t num);
        void setEmpty(); //shutting the party down

        //law of 5
        CheeseParty(CheeseParty&); //copy construct
        CheeseParty& operator=(const CheeseParty&); //equal assignment 

        CheeseParty(CheeseParty&&) noexcept; //copy construct
        CheeseParty& operator=(CheeseParty&&) noexcept; //equal move assignment 

        ~CheeseParty();
      
        bool sameCheese(const Cheese&)const;

        // a modifier that adds a cheese object to the array of pointers.
        CheeseParty& addCheese(const Cheese&);

        //a modifier that removes any cheeses from the array that have a 0 weight.
        CheeseParty& removeCheese();

        //print the cheeses
        std::ostream& print(std::ostream& os) const;

    };

    //overload <<
    std::ostream& operator<<(std::ostream& os, const CheeseParty&);











}
#endif 