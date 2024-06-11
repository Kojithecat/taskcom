#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <CLI/CLI.hpp>

const std::string TASK_FILE = "tasks.txt";

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
	    std::cout << pos << std::endl;
            if (pos != std::string::npos) {
                int id = std::stoi(line.substr(0, pos));
		line = line.substr(pos + 1);
		pos = line.find('|');
	        std::cout << pos << std::endl;
		if(pos != std::string::npos){
                    std::string description = line.substr(0, pos);
		    int urgency = std::stoi(line.substr(pos + 1));
		    std::cout << id << " " << description << " " << urgency << std::endl;  
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

void list_tasks() {
    std::vector<Task> tasks = load_tasks();
    if (tasks.empty()) {
       //std::cout << "No tasks available.\n";
    } else {
        for (const auto& task : tasks) {
            std::cout << "ID: " << task.id << ", Description: " << task.description << ", Urgency: " << task.urgency << "\n";
        }
    }
}

void add_desc(const std::string& description, int& urgency) {
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
        std::cout << "Task with ID " << id << " removed.\n";
    } else {
        std::cout << "No task found with ID " << id << ".\n";
    }
}

int main(int argc, char** argv) {
    CLI::App app{"Personal Task Manager"};

    std::string description;
    int id = -1;
    bool list = false;
    bool add = false;
    bool remove = false;
    int urgency = 1;

    app.add_flag("-l,--list", list, "List all tasks");
    app.add_flag("-a,--add", add, "Add a new task");
    app.add_flag("-r,--remove", remove, "Remove a task by ID");
    app.add_option("-d,--description", description, "Description of the new task")->needs("-a");
    app.add_option("-i,--id", id, "ID of the task to remove")->needs("-r");
    app.add_option("-u,--urgency", urgency, "Urgency of the task 1-5")->needs("-d");
    //std::cout << "VALID ARGUMENTS" << std::endl;
    CLI11_PARSE(app, argc, argv);

    if (list) {
        list_tasks();
    } else if (add) {
        if (!description.empty()) {
            add_desc(description, urgency);
        } else {
            std::cerr << "Task description cannot be empty.\n";
        }
    } else if (remove) {
        if (id != -1) {
            remove_task(id);
        } else {
            std::cerr << "Task ID is required to remove a task.\n";
        }
    } else {
	    std::cout << app.help() << std::endl;
    }

    return 0;
}

