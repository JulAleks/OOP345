/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #4 (PART 2)   
File	CheeseParty.cpp
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 07, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#include <iomanip>
#include <iostream>
#include <string>
#include "CheeseParty.h"


namespace sdds {
    CheeseParty::CheeseParty(size_t num)
    {
        if (num > 0) {

            dairyParty = new const Cheese*[num];
            for (size_t i = 0; i < num; ++i) {
                dairyParty[i] = nullptr;
            }
        }
    }
    void CheeseParty::setEmpty()
    {
        delete[] dairyParty;
        dairyParty = nullptr;
    }

    CheeseParty::CheeseParty(CheeseParty& rhs)
    {
       *this = rhs;
    }

    CheeseParty& CheeseParty::operator=(const CheeseParty& rhs)
    {
        if (this != &rhs && rhs.p_num > 0) {
            // Clear existing resources
            setEmpty(); // Clearing DMA and setting to empty

            // Copy p_num from rhs
            p_num = rhs.p_num;

            // Allocate a new array of Cheese pointers
            dairyParty = new const Cheese * [p_num];

            // Copy each Cheese object from rhs
            for (auto i = 0u; i < p_num; ++i) {
                if (rhs.dairyParty[i] != nullptr) {
                    dairyParty[i] = rhs.dairyParty[i];
                }
                else {
                    dairyParty[i] = nullptr;
                }
            }

            // Copy p_name from rhs
            p_name = rhs.p_name;
        }
        return *this;
    }

    CheeseParty::CheeseParty(CheeseParty&& rhs) noexcept
    {
        *this = std::move(rhs);
    }

    CheeseParty& CheeseParty::operator=(CheeseParty&& rhs) noexcept
    {
        if (this != &rhs && rhs.p_num > 0) {
            setEmpty(); //clearing DMA and setting to empty
            p_num = std::move(rhs.p_num);

            //moving rhs to lhs
            dairyParty = std::move(rhs.dairyParty);
            p_name =rhs.p_name;

            //cleaning 
            rhs.p_num = 0;
            rhs.dairyParty = nullptr;
        }
        return *this;
     
    }

    CheeseParty::~CheeseParty()
    {
        setEmpty();
    }

    bool CheeseParty::sameCheese(const Cheese& rhs) const  
    {
        bool found = false;
        for (size_t i = 0; i < p_num; ++i) {
            if (dairyParty[i] == &rhs) {
                found = true;
                i = p_num;
            }
        }
        return found;
    }

    CheeseParty& CheeseParty::addCheese(const Cheese& rhs)
    {
        //if the parameter is already in the array, this function does nothing.
        if (!sameCheese(rhs)) {
            // temp cheese
            const Cheese** t_party = new const Cheese * [p_num + 1];

            // copy current cheese to temp
            for (auto i = 0u; i < p_num; ++i) {
                t_party[i] = dairyParty[i];
            }

            // if the parameter is not in the array, this function resizes the array to make room for the parameter (if necessary) and stores the address of the parameter in the array (your function should not make a copy of the parameter).
            t_party[p_num] = &rhs;
            ++p_num;


            // empty current cheese if not empty
            if (dairyParty != nullptr) {
                setEmpty();
            }


            // update lhs cheese to temp
            dairyParty = t_party;
        }
        //  return current instance.
        return *this;
    }

    CheeseParty& CheeseParty::removeCheese()
    {
        size_t i_cheese = 0;
        // searches the array for 0 weight cheeses and sets the pointer in the array to nullptr if such a cheese is found.
        for (auto i = 0u; i < p_num; ++i) {
            if (dairyParty[i]->getWeight() == 0) { 
             
                //shifting all cheeses in the party
                for (auto j = i + 1u; j < p_num; ++j) {
                    dairyParty[j - 1] = dairyParty[j];
                }

                dairyParty[p_num - 1] = nullptr; // setting the lest place to nptr
                --p_num; //reducting tot cheeses
            }
            else{
                //if we got cheese that isn't empty ignore and move on
                dairyParty[i_cheese] = dairyParty[i];
                ++i_cheese;
            }
        }
        return *this;
    }

    //printing the party using the custom div from CheeseShop
    std::ostream& CheeseParty::print(std::ostream& os) const
    {
       div(1, 26, p_name);
        if (dairyParty == nullptr) {
            os << "This party is just getting started!" << std::endl;
        }
        else {
            for (auto i = 0u; i < p_num; i++) {
                if (dairyParty[i] != nullptr) {
                    os << *dairyParty[i];
                }
                else {
                    os << std::endl;
                }
               
            }
        }
        div(2, 26, "");
        return os;
    }


   //overload
    std::ostream& operator<<(std::ostream& os, const CheeseParty& p)
    {
        p.print(os);
       
        return os;
    }

}
