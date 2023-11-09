/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #6 (PART 2)
Fielsystem Module
File	Filesystem.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  2023-11-04
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H


#include <iostream>
#include "Directory.h"
#include "File.h"
namespace sdds
{
    class Filesystem : public Directory, File{
        
        Directory* m_root{nullptr}; //m_root: a pointer to the root directory of the filesystem.
        Directory* m_current{nullptr}; //m_current: a pointer to the current working directory in the filesystem from where operations are performed.

    public:
        Filesystem(){}//default 
        Filesystem(std::string f_name, std::string r_name = "");
        ~Filesystem();

     

        //this module does not allow copy operations. Make sure they are deleted.
        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        //this module supports move operations.
        Filesystem(Filesystem&&) noexcept;
        Filesystem& operator=(Filesystem&&) noexcept;

        Filesystem& operator+=(Resource*); //adds a resource to the current directory

        Directory* change_directory(const std::string& str= "");  //changes the current directory to the directory(located in the current directory) whose name matches argument.

        Directory* get_current_directory() const; // a query that returns the current directory.

      

    };
    std::string trimSpace(const std::string& str);
}

#endif
