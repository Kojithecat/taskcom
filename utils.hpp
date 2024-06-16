#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>


struct Task {
    int id;
    std::string description;
    int urgency;
};

void sortTasksUrgency(std::vector<Task> & taskVec);

void sortTasksDuedate(std::vector<Task> & taskVec);


 
#endif
