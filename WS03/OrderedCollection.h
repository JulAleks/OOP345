/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #3 (PART 2)
OrderedCollection Module
File	OrderedCollection.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Sep 28, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

#include "Collection.h"


namespace sdds {
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        virtual bool operator+=(const T& t) {
            bool cap = false;
            if (this) {
                this->setSmallestItem(t);
                this->setLargestItem(t);
                this->add(t);
                cap = true;
            }
            return cap;
           
        }










          
    };



}


#endif