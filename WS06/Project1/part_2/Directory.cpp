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
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "Directory.h"
#include "Flags.h"
namespace sdds
{
    // custom constructor that receives the name of the directory as a string and uses it to initialize the Directory object.
     //Note: assume all directory names end with a /
    Directory::Directory(std::string name)
    {
        m_name = name;
    }

    //a destructor that deallocates memory for each resource that this directory holds.
    Directory::~Directory()
    {
        for (Resource* res : m_contents) {  //deleting all ptrs 
            delete res;
        }
        m_contents.clear();  //clearing the vector
    }


    
    void Directory::update_parent_path(const std::string& path)
    {   //sets the parent path to the parameter.
        m_parent_path = path;
        // For each resource that this directory holds, this member should also set their absolute path locations to the full absolute path of this directory.
        for (auto res : m_contents) {
            if (res != nullptr)
            {
                res->update_parent_path(path + m_name);
            }
           
        }
    }

    //a query that returns Flags::DIR
    NodeType Directory::type() const
    {
        return NodeType::DIR;
    }

    //a query that returns the name of the directory.
    std::string Directory::name() const
    {
        return m_name;
    }

    //a query that returns the full absolute path of the directory (a concatenation of the absolute path location and the directory name).
    std::string Directory::path() const
    {
        return m_parent_path + m_name;
    }

    //a query that returns the number of resources that this directory holds.
    int Directory::count() const
    {
        return static_cast<int>(m_contents.size());
      
    }

    // a query that returns the size of the directory in bytes. 
    size_t Directory::size() const
    {
        size_t tot = 0u;
        if (!m_contents.empty()) { //if not empty
            //The size of the directory is the sum of the individual sizes of each resource that this directory holds. 
            for (const auto res : m_contents) {
                if (res != nullptr) {
                    tot += res->size();
                }
           
            }
        }
        return tot; //This member returns 0u if the directory is empty.
    }

    //adds a resource to the directory and returns a reference to the current directory. 
    Directory& Directory::operator+=(Resource* src) {
        bool found = false;
       //This member should check for existing resources in the directory with the same name:
        for (Resource* res : m_contents) {
            if (res != nullptr) {
                if (res->name() == src->name()) {
                    found = true;
                    break;
                }
            }
         
        }
        // if a match is found, throwand exceptionand do nothing else
        if (found) {
            // Throw an exception if a resource with the same name already exists
            throw "**EXPECTED EXCEPTION:"+ src->name () + "image already exists in the root";
        }
        //if no match is found, add the resourceand update the absolute path location of the added resource with the directory's full absolute path.
        else {
            m_contents.push_back(src); //push at the end
            src->update_parent_path(m_parent_path + m_name); //update path
            return *this;  //return curr obj
        }
    }

    //finds and returns the address of a resource in the directory whose name matches the given string or nullptr if a match is not found.
    Resource* Directory::find(const std::string& str, const std::vector<OpFlags>& src) {
        Resource* temp{ nullptr }; //temp resource assign to nullptr, if nothing found return nullptr if found assign to temp and return

        //if the RECURSIVE flag is in the second parameter, this member will also attempt to recursively find a match in each directory that is in the m_contents vector
        bool found = false;
        for (OpFlags flag : src) {
            if (flag == sdds::OpFlags::RECURSIVE) {
                found = true;
            }
        }
        //if recursive is found
        for (Resource* resource : m_contents) {
            if (resource) {  
                if (resource->name() == str) {
                    temp = resource; // NOTE: If the current directory holds another directory named src which contains a file named sample.txt and we want to find sample.txt, this member will only return the sample.txt resource if the RECURSIVE flag is set, nullptr otherwise.
                    break; //if found stop
                }
                if (found) {
                    Directory* dir = dynamic_cast<Directory*>(resource); //casting a dir to crearte a recursive search of a directory withing a directory 
                    if (dir) {
                        temp = dir->find(str, src);  //HINT: If an element in m_contents is a directory, use its find() member function to find a match.
                        if (temp) {
                            break; //if found stop
                        }
                        
                    }
                }
            }
        }
        return temp;
    }

    //deletes a resource from the directory whose name matches the first argument (removing it from its contents and deallocating memory for it).
    void Directory::remove(const std::string& str, const std::vector<OpFlags>& src) {
        Resource* toDel = find(str, src);

        if (toDel) {
            //if it is a dir
            if (toDel->type() == NodeType::DIR) {
                //if the matched resource is a directory, the RECURSIVE flag must be set otherwise this member reports an std::invalid_argument exception with the message NAME is a directory. Pass the recursive flag to delete directories.".
                if (std::find(src.begin(), src.end(), sdds::OpFlags::RECURSIVE) == src.end()) {
                    throw std::invalid_argument(str + " is a directory. Pass the recursive flag to delete directories.");
                }
                //removal if recursive was set using lambda 
                m_contents.erase(std::remove_if(m_contents.begin(), m_contents.end(), [toDel](Resource* r)  {
                    return r == toDel;}), 
                    m_contents.end());

                // del found resource
                delete toDel;
            }
        }
        else { //if no matching resource is found, report an exception of type std::string with the message NAME does not exist in DIRECTORY_NAME.
            throw std::string(str + " does not exist in " + this->name());
        }
    }

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& src) const
    {
     

        //checking if long 
        bool f_long = false;
        for (FormatFlags flag : src) {
            if (flag == sdds::FormatFlags::LONG) {
                f_long = true;
            }
        }
        //printing header
        os << "Total size: " << size() << " bytes" << std::endl;


        for (Resource* resource : m_contents) {
            if (resource) {
                //if long print with bytes
                if (f_long) {
                    //if dir
                    if (resource->type() == NodeType::DIR) {
                        os << "D | " << std::setw(15) << std::left << resource->name() << " | " << std::setw(2) << std::right << (resource->count()-1) << " | " << std::setw(4) << std::right << resource->size() << " bytes | " << std::endl;
                    }//if file
                    else {
                        os << "F | " << std::setw(15) << std::left << resource->name() << " |    | " << std::setw(4) << std::right << resource->size();
                        os<< " bytes | " << std::endl;
                    }
                }
                //if regular priont without bytes
                else {
                    (resource->type() == NodeType::DIR) ? os << "D" : os << "F";
                    os << " | " << std::setw(15) << std::left << resource->name() << " |" << std::endl;
                }
               
            }
        }
    }

}