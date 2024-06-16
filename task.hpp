#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

const std::string TASK_FILE = "/home/raul/Documentos/taskcom/build/tasks.txt";

struct Task {
    int id;
    std::string description;
    int urgency;
};

std::vector<Task> load_tasks(); 

void save_tasks(const std::vector<Task>& tasks); 

void taskColor(std::string & colorInit, std::string & colorEnd, const int &  urgency);
 
void list_tasks();

void add_task(const std::string& description, int& urgency); 

void remove_task(int id);

#endif
