/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #6 (PART 2)
Directory Module 
File	Directory.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  2023-11-04
I have done all the coding by myself and only copied the code that my 
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include <iostream>
#include "Resource.h"

namespace sdds
{
    class Directory : public Resource {
        std::vector<Resource*> m_contents{nullptr};
    public:
        Directory() {};
        Directory(std:: string name);
        ~Directory();

        //this class should not allow copy/move operations.
        Directory(const Directory&) = delete;
        Directory(const Directory&&) = delete;
        Directory& operator=(Directory&) = delete;
        Directory& operator=(Directory&&) = delete;


        void update_parent_path(const std::string&);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count() const;
        size_t size() const;
        Directory& operator+=(Resource*);

        //This member also takes an optional vector of flags that determine how the find is performed (defaults to an empty collection). 
        Resource* find(const std::string&, const std::vector<OpFlags>& src = {});


        //part 2
        void remove(const std::string&, const std::vector<OpFlags>& src = {});
        void display(std::ostream&, const std::vector<FormatFlags>& src = {}) const;
    };
}

#endif