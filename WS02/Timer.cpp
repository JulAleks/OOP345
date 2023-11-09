/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #2 (PART 2)
Timer Module
File	Timer.h
Student Name: Julia Alekseev
Student ID#:  051292134
Email      :  jalekseev@myseneca.ca
Section    :  NFF
Date       :  Sep 23, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/


#include <chrono>
#include "Timer.h"

using namespace std;

namespace sdds
{   
    void Timer::start()
    {
        t_start = chrono::steady_clock::now();
    }

    long long Timer::stop()
    {
        t_end = chrono::steady_clock::now();
        chrono::nanoseconds elapsed_time = (t_end - t_start);
        return elapsed_time.count();
    }

}