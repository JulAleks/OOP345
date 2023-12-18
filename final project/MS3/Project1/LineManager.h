/*************** MS 3 - Line Manager Module - LineManager.h ********************
 Name: Julia Alekseev
 Seneca Student ID: 051292134
 Seneca email: jalekseev@myseneca.ca
  Date of completion: 2023-11-21

 I confirm that I am the only author of this file
 and the content was created entirely by me.
*************************************************************************/
/*
The LineManager class manages an assembly line of active stations 
*/
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Workstation.h"
#include "Utilities.h"
namespace sdds {
    class LineManager : public Utilities {
        // Instance Variables
        std::vector<Workstation*> m_activeLine; //the collection of workstations for the current assembly line.
        size_t m_cntCustomerOrder{0}; //the total number of CustomerOrder objects
        Workstation* m_firstStation{ nullptr }; //points to the first active station on the current line

    public:
        LineManager() {}; //default

        //this constructor receives the name of the file that identifies the active stations on the assembly line 
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        //this modifier reorders the workstations present in the instance variable m_activeLine (loaded by the constructor) and stores the reordered collection in the same instance variable. 
        void reorderStations();

        //this modifier performs one iteration of operations on all of the workstations in the current assembly line
        bool run(std::ostream& os);

        //this query displays all active stations on the assembly line in their current order
        void display(std::ostream& os) const;
    };


}

#endif 

