#include "task.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
    CLI::App app{"Personal Task Manager"};

    std::string description = "";
    bool list = false;
    int id = -1;
    int urgency = 1;

    app.add_flag("-l,--list", list, "List all tasks");
    app.add_option("-a,--add", description, "Add a new task");
    app.add_option("-c,--check", id, "Check the task with the given ID");
    app.add_option("-u,--urgency", urgency, "Urgency of the task 1-5")->needs("-a");
    //std::cout << "VALID ARGUMENTS" << std::endl;
    CLI11_PARSE(app, argc, argv);

    if (list) {
        list_tasks();
    } else if (!description.empty()) {
        add_task(description, urgency);
        }
      else if (id  != -1) {
            remove_task(id);
        }
      else {
	    std::cout << app.help() << std::endl;
    }

    return 0;
}

