/*************** MS 3 - CustomerOrder Module -  CustomerOrder.cpp ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
 Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <algorithm>
#include "CustomerOrder.h"

namespace sdds {

	size_t CustomerOrder::m_widthField = 0u; //initialize static var

	CustomerOrder::CustomerOrder()
	{
		setEmpty();
	}

	void CustomerOrder::setEmpty()
	{
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	/*a custom 1-argument constructor that takes a reference to an unmodifiable string.
	This constructor uses a local Utilities object to extract the tokens from the string and populate the current instance. The fields in the string are (separated by a delimiter):
     -  Customer Name
     - Order Name
     -  the list of items making up the order (at least one item)
	After finishing extraction, this constructor updates CustomerOrder::m_widthField if the current value is smaller than the value stored in Utilities::m_widthField*/
	CustomerOrder::CustomerOrder(const std::string& line) {
		bool more = true;
		size_t startPos = 0u;
		
		try {
			//getting orders 
			m_name = extractToken(line, startPos, more);
			m_product = extractToken(line, startPos, more);
			char delimiter = getDelimiter();
			m_cntItem = count(line.begin(), line.end(), delimiter)-1;

			//if there is at least one item dealloc
			if (m_cntItem > 0) {
				m_lstItem = new Item * [m_cntItem];

				for (auto i = 0u; more; i++) {
					m_lstItem[i] = new Item(std::move(trimSpace(extractToken(line, startPos, more))));
				}
			}
			//get max width
			m_widthField = std::max(getFieldWidth(), m_widthField);
		}
		catch (const std::string& err) {
			std::cout << err;
		}
	}

	//a CustomerOrder object should not allow copy operations. The copy constructor should throw an exception if called and the copy operator= should be deleted.
	CustomerOrder::CustomerOrder(const CustomerOrder& ord)
	{
		throw std::string("ERROR: Cannot make copies.");
	}


	//a move constructor. This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the declaration and the definition.
	CustomerOrder::CustomerOrder(CustomerOrder&& ord) noexcept
	{
		*this = std::move(ord);               
	}

	// move assignment operator
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& ord) noexcept
	{
		if (this != &ord) {
			if (m_lstItem) {
				for (auto i = 0u; i < m_cntItem; ++i) {
					delete m_lstItem[i];
				}
				setEmpty();
			}
			//move
			m_name = ord.m_name;
			m_product = ord.m_product;
			m_cntItem = ord.m_cntItem;
			m_lstItem = ord.m_lstItem;

			//dealloc
			ord.m_name = "";
			ord.m_product = "";
			ord.m_cntItem = 0u;
			ord.m_lstItem = nullptr;

			if (ord.m_lstItem) {
				for (auto i = 0u; i < ord.m_cntItem; ++i)
					delete ord.m_lstItem[i];

				ord.setEmpty();
			}
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem) {
			for (auto i = 0u; i < m_cntItem; ++i)
				delete m_lstItem[i];
			setEmpty();
		}
	}

	//returns true if all the items in the order have been filled; false otherwise
	bool CustomerOrder::isOrderFilled() const
	{
		int count = 0;
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_isFilled) {
				count++;
			}
		} 
		return static_cast<int>(m_cntItem) == count;
	}

	// returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool ok = true;
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == itemName) {
					ok = false;
			}
		}
		return ok;
		}

		
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool filled = false; 
		for (auto i = 0u; i < m_cntItem && !filled; ++i) { //looping until item is not filled or reach the end of items
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) { //making sure that we have the item and it wasn't filled 

				if (station.getQuantity() > 0) { //if the order contains items handled, and the Station's inventory contains at least one item
					//this function fills the order with one single item
					//It subtracts 1 from the inventory and updates Item::m_serialNumber and Item::m_isFilled
					station.updateQuantity(); 
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber(); 
					m_lstItem[i]->m_isFilled = true; 
					os << "    Filled "<< m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					filled = true; //exiting loop, item is filled	 
				}
				else
					os << "    Unable to fill "<< m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;	
			}
			else {
				; //if the order doesn't contain the item handled, this function does nothing
			}
		}
	}

	//displays the state of the current object in the format
	void CustomerOrder::display(std::ostream& os) const
	{
		os << this->m_name << " - "<< m_product<< std::endl;    
		for (auto i = 0u; i < m_cntItem; ++i) {
			os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
			   << std::left << std::setw(CustomerOrder::m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName
			   <<" - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}	
	}
}