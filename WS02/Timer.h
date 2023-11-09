/*/////////////////////////////////////////////////////////////////////////
                       OOP345 Workshop - #2 (PART 2)
Timer Module
File	Timer.h
Student Name: Julia Alekseev
Student ID# :  051292134
Email       :  jalekseev@myseneca.ca
Section     :  NFF
Date        :  Sep 23, 2023
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <iostream>
#include <chrono>


namespace sdds
{
    class Timer {
        std::chrono::steady_clock::time_point t_start;
        std::chrono::steady_clock::time_point t_end;
    public:
        //a modifier that starts the timer (takes the current timestamp and stores it in an attribute).
        void start();

        //a modifier that stops the timer (takes the current timestamp) and returns how many nanoseconds passed since the timer has started as a long long value.
        long long stop();
    };
}

#endif // !SDDS_TIMER_H