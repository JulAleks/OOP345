/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #5 (PART 2)
Collection Module - Template Module
File	Collection.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Oct 15, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include <stdexcept>
#include <string>

namespace sdds {
    template <typename T>
    class Collection {
        std::string c_name{};
        T* arr{};
        size_t c_size{};

       
        //a pointer to a function that returns void and receives two parameters of type const Collection<T>& and const T& in that order.
        //This is the observer function(it observes an event) : when an item has been added to the collection, the class Collection<T> will call this function informing the client about the addition.
        void (*observ)(const Collection<T>&, const T&);

    public:
        Collection(){};

        //Collection(const std::string& name): sets the name of the collection to the string referred to by the parameter and sets all other attributes to their default value
        Collection(const std::string& name) : c_name(name), arr(nullptr), c_size(0), observ(nullptr) {}

        //a query that returns the name of the collection.
        const std::string& name() const {
           return c_name;
        }
       
        //this class doesn't support any copy operations; delete all of them.
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) noexcept = delete;
        Collection& operator=(Collection&&) noexcept = delete;

        void setEmpty() {
            delete[] arr;
            arr = nullptr;
        }

        //a destructor
        ~Collection() {
            setEmpty();
        }

        //a query that returns the number of items in the collection.
        size_t size() const {
            return c_size;
        }

        //stores the address of the callback function(observer) into an attribute.This parameter is a pointer to a function that returns void and accepts two parameters
        //: a collectionand an item that has just been added to the collection.This function is called when an item is added to the collection.
        void setObserver(void (*observer)(const Collection<T>&, const T& observ)) {
            observ = observer;
        }


        //adds a copy of item to the collection, only if the collection doesn't contain an item with the same title.  If the item is not yet in the collection, this function:
        Collection<T>& operator+=(const T& item) {
            //checking if its in the arr
            bool found = false;
            for (size_t i = 0u; i < c_size; i++) {
                //type T has a member function called title() that returns the title of the item(std::string)
                if (arr[i].title() == item.title()) {
                    found = true;
                }
            }

            if (!found) {

                //maikng a temp with new size
                T* t_arr = new T[c_size + 1];
                for (size_t i = 0; i < c_size; i++) {
                    t_arr[i] = arr[i];
                }
                t_arr[c_size] = item;

                setEmpty();
                arr = t_arr;
                ++c_size;

                // if an observer has been registered, this operator calls the observer function passing the current object(*this) and the new item as arguments.
                if (observ) {
                    observ(*this, item);
                }
            }
            //if item is already in the collection, this function does nothing.
            //return
            return *this;
        }



        //returns the item at index idx.
        //if the index is out of range, this operator throws an exception of type std::out_of_range with the message Bad index [IDX]. Collection has [SIZE] items.. Use operator + to concatenate strings.
        T& operator[](size_t idx) const {
            if (idx < c_size) {
                return arr[idx];
            }
            else {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(c_size) + "] items.");
            }
        }



        //returns the address of the item with the title title (type T has a member function called title() that returns the title of the item).
        T* operator[](const std::string& title) const {
            for (auto i = 0u; i < c_size; i++) {
                if (arr[i].title() == title) {
                    return &arr[i];
                }
            }
            return nullptr; // If no such item exists, this function returns nullptr.
        }

       
        //Iterate over all elements in the collection and insert each one into the ostream object (do not add newlines).
        std::ostream& display(std::ostream& os) const {
            for (size_t i = 0; i < c_size; i++) {
                os << arr[i];
            }
            return os;
        }

      
    };

    //verload the insertion operator to insert the content of a Collection object into an ostream object. 
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
        collection.display(os);
        return os;
    }







}

#endif
