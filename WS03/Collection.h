/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #3 (PART 1)
Collection Module 
File	Collection.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Sep 28, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include "Book.h"
namespace sdds {
    template <typename T, unsigned C>
    class Collection {
        //=Private Class Members=
        T m_items[C]; //T: the type of an element of the managed array, called m_items , C: an unsigned integer representing the capacity of the collection (the size of the managed array); this is the maximum number of items that can be included in the collection.

        unsigned m_size{ 0 }; //total num of items currently stored

        static T m_smallestItem; //an object of type T to store smallest item. This object will be returned by corresponding public static member function

        static T m_largestItem; //An object of Type T to store largest item. This object will be returned by corresponding public static member function

    protected: //Protected Instance Members
        //a modifier to receive an object of type T, as unmodifiable reference. It sets m_smallestItem to the received object if the received object is smaller than it.
        void setSmallestItem(const T& t) {
            if (t < m_smallestItem) {
                m_smallestItem = t;
            }
        }

        //a modifier to receive an object of type T, as unmodifiable reference. It sets m_largestItem to the received object if the received object is larger than it.
        void setLargestItem(const T& t) {
            m_largestItem = (t > m_largestItem) ? t : m_largestItem;
        }


        //a mutator operator to receive an array index and return corresponding element from m_items array.
        const T& operator[](size_t index) const {
            if (index < m_size) {
                return m_items[index];
            }
            else {
                static T t{};
                return t;
            }
        }


        //a mutator to increase by 1 the size count of elements stored in the collection.
        void incrSize() {
            m_size++;
        }

    public: //Public Class Members
        Collection(){} //default constructor 

        Collection(int num) {}

        //returns the current smallest item stored in the class attribute.
        T getSmallestItem() const {
            return m_smallestItem;
        }

        //returns the current largest item stored in the class attribute.
        T getLargestItem() const {
            return m_largestItem;
        }

        //Public Instance Members
        //a query to return current number of items
        unsigned size() const {
            return m_size;
        }

        //a query to return capacity of the collection
        unsigned capacity() const {
            return C;
        }

        //a mutator to receive as parameter an unmodifiable reference to object of type T
        virtual bool operator+=(const T& t) {
           
            //If the collection doesn't have room for more items (the size is the same as capacity), this function does nothing and returns false
            bool cap = false;

            if (m_size < capacity()) {
                //updates the smallest/largest to the value of parameter by calling the respective private member functions
                setSmallestItem(t);
                setLargestItem(t);

                //adds the received object as a new item to the end of the collection of the collection
                m_items[m_size] = t;

                //updates the size of the collection (number of items stored).
                incrSize();
                   
                //returns true
                cap = true;
            }
            return cap;
        }

        
        //a query to receive a reference to an ostream object, and to insert into it all items existing in the collection
        void print(std::ostream& os) const {
            os << "[";
                for (auto i = 0u; i < m_size; ++i) {
                    os << m_items[i];
                    if (i < m_size - 1) {
                        os << ",";
                    }
                }
                os << "]" << std::endl;
               
        }

        void add(const T& t) {
            //if not empty
            if (m_size != 0){
            //find next open spot 
            auto n_spot = 0u;
            while (n_spot < m_size && t > m_items[n_spot]) {
                n_spot++;
            }

            //shift all items to make room 
            for (auto i = m_size; i > n_spot; --i) {
                m_items[i] = m_items[i - 1];
            }

            //add t to n_spot and increase the size
            m_items[n_spot] = t;
            incrSize();
            }
            else { 
                m_items[m_size++] = t;
            }
        }

    };

    // Definitions of m_smallestItem and m_largestItem
    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = T{ 9999 }; //Define it outside the class definition and initialize it to 9999
    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem = T{-9999}; // Define it outside the class definition and initialize it to -9999.

    //Specialize the definition of m_smallestItem object for T = Book and C = 10 so that it stores empty string ("") as title, 1 as number of chapters, and 10000 as number of pages.
    template <>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    //Specialize the definition of m_largestItem object for T = Book and C = 10 so that it stores empty string ("") as title, 10000 as number of chapters, and 1 as number of pages.
    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

    //specialize the initializations of m_smallestItem and m_largestItem objects: when T = Book and C = 72, the values stored {"", 1, 10000} and {"", 10000, 1}, respectively
    template <>
    Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

    template <>
    Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);

    //specialize the print() function when T = Book and C = 10 to print Book object's data differently, on multiple rows; see sample output for a hint on exact formatting of output.
    template <>
    void Collection<Book, 10>::print(std::ostream& os) const {
        os << "| ";
        for (auto i = 0u; i < 75; ++i) {
            os << "-";
        }
        os << "| " << std::endl;
        for (auto i = 0u; i < m_size; ++i) {
            os<< "| " << m_items[i];
            if (i < m_size - 1) {
                os <<" |" << std::endl;;
            }
        }
        os << " |" << std::endl<< "| ";
        for (auto i = 0u; i < 75; ++i) {
            os << "-";
        }
        os << "|" << std::endl;
    }

    //specialize the print() function when T = Book and C = 72 to print data in the same way as the previous specialization.
    template <>
    void Collection<Book, 72>::print(std::ostream& os) const {
        os << "| ";
        for (auto i = 0u; i < 75; ++i) {
            os << "-";
        }
        os << "| " << std::endl;
        for (auto i = 0u; i < m_size; ++i) {
            os << "| " << m_items[i];
            if (i < m_size - 1) {
                os << " |" << std::endl;;
            }
        }
        os << " |" << std::endl << "| ";
        for (auto i = 0u; i < 75; ++i) {
            os << "-";
        }
        os << "|" << std::endl;
    }
}
#endif

