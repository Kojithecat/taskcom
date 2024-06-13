#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <CLI/CLI.hpp>

const std::string TASK_FILE = "/home/raul/Documentos/taskcom/build/tasks.txt";

struct Task {
    int id;
    std::string description;
    int urgency;
};

std::vector<Task> load_tasks() {
    std::vector<Task> tasks;
    std::ifstream file(TASK_FILE);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('|');
	    //std::cout << pos << std::endl;
            if (pos != std::string::npos) {
                int id = std::stoi(line.substr(0, pos));
		line = line.substr(pos + 1);
		pos = line.find('|');
	        //std::cout << pos << std::endl;
		if(pos != std::string::npos){
                    std::string description = line.substr(0, pos);
		    int urgency = std::stoi(line.substr(pos + 1));
		    //std::cout << id << " " << description << " " << urgency << std::endl;  
                    tasks.push_back({id, description, urgency});
            	}
	    }
        }
        file.close();
    }
    return tasks;
}

void save_tasks(const std::vector<Task>& tasks) {
    std::ofstream file(TASK_FILE);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.id << "|" << task.description << "|" << task.urgency << "\n";
        }
        file.close();
	//std::cout << "SAVED" << std::endl;
    }
}

void taskColor(std::string & colorInit, std::string & colorEnd, const int &  urgency){
    switch(urgency){
   
  	case 3:
	    colorInit = "\033[33m";
	    colorEnd = "\033[0m";
	    break;	
	    
	case 4:
	    colorInit = "\033[31m";
	    colorEnd = "\033[0m";
	    break;	
	    	
	case 5:	
	    colorInit = "\033[1;31m";
	    colorEnd = "\033[0m";
	    break;	    
    }
}

void list_tasks() {
    
    std::string colorInit = "";
    std::string colorEnd = "";
    std::vector<Task> tasks = load_tasks();
    
    if (tasks.empty()) {
       //std::cout << "No tasks available.\n";
    } else {
        for (const auto& task : tasks) {
	    int urg = task.urgency;
	    taskColor(colorInit, colorEnd, urg);
            std::cout << colorInit << "ID: " << task.id << ", Description: " << task.description << ", Urgency: " << urg << colorEnd << "\n";
        }
    }
}

void add_task(const std::string& description, int& urgency) {
    std::vector<Task> tasks = load_tasks();
    int new_id = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.push_back({new_id, description, urgency});
    //std::cout << "DESC pushed" << std::endl;
    save_tasks(tasks);
    std::cout << "Task added with ID " << new_id << ".\n";
}


void remove_task(int id) {
    std::vector<Task> tasks = load_tasks();
    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        save_tasks(tasks);
        std::cout << "Task with ID " << id << " has been completed.\n";
    } else {
        std::cout << "No task found with ID " << id << ".\n";
    }
}

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

