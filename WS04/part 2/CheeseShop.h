/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #4 (PART 2)
Cheese Shop Module
File	CheeseShop.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 07, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/


#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include "Cheese.h"
namespace sdds {
 
    //This class should have attributes to store the name of the shop and manage a dynamically-allocated array of pointers to dynamically-allocated objects of type Cheese:
    class CheeseShop: public Cheese {
        const Cheese** s_cheese{}; //(each element of the array points to an object of type Cheese)
        std::string s_name{ "No Name" }; //name of the shop
        size_t s_num{}; //num of cheeses
    public:
        CheeseShop() {}; //default constructor
        CheeseShop(const std::string&); //one arg constructor

        void setEmpty(); //setting to an empty cheese

        //law of 5
        CheeseShop(CheeseShop&); //copy construct
        CheeseShop& operator=(const CheeseShop&); //equal assignment 

        CheeseShop(CheeseShop&&) noexcept; //copy construct
        CheeseShop& operator=(CheeseShop&&) noexcept; //equal move assignment 

        ~CheeseShop();

        //a modifier that adds a cheese object to the array of pointers.
        CheeseShop& addCheese(const Cheese&);

        //print the cheeses
        std::ostream& print(std::ostream& os) const;
    };

    //overload <<
    std::ostream& operator<<(std::ostream& os, const CheeseShop&);

    //divider print
    void div(size_t, size_t, const std::string);

    




}

#endif 