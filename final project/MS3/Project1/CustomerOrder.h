/*************** MS 3 - CustomerOrder Module -  CustomerOrder.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The CustomerOrder module contains all the functionality for processing customer orders as they move from Station to Station along the assembly line. 
The Station where a given order currently rests fills a request for one item of that station, if there is any such request.
*/

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Utilities.h"
#include "Station.h"
namespace sdds {
    struct Item   
    {
        std::string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const std::string& src) : m_itemName(src) {};
    };

	class CustomerOrder : public Utilities {

        //Instance Variables
        std::string m_name{""}; //the name of the customer(e.g., John, Sara, etc)
        std::string m_product{""}; //the name of the product being assembled(e.g., Desktop, Laptop, etc) 
        size_t m_cntItem{0}; //a count of the number of items in the customer's order
        Item** m_lstItem{}; //a dynamically allocated array of pointers.

        //Class Variable
        static size_t m_widthField; //the maximum width of a field, used for display purposes

    public:
        CustomerOrder(); 

        void setEmpty(); //set empty

        //a custom 1-argument constructor 
        CustomerOrder(const std::string&);

        //will throw
        CustomerOrder(const CustomerOrder&);
        
        //copy operator= should be deleted
        CustomerOrder& operator=(const CustomerOrder&) = delete;

        CustomerOrder(CustomerOrder&& ord) noexcept; //move copy construct
        CustomerOrder& operator=(CustomerOrder&&) noexcept; //move assign

        ~CustomerOrder(); //destructor

        //returns true if all the items in the order have been filled
        bool isOrderFilled() const;

        //eturns true if all items specified by itemName have been filled.
        bool isItemFilled(const std::string& itemName) const;

        //this modifier fills one item in the current order that the Station specified in the first parameter handles.
        void fillItem(Station& station, std::ostream& os);

        //this query displays the state of the current object in the format
        void display(std::ostream& os) const;
	};

}

#endif