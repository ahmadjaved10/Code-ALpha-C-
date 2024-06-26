//Ahmad Javed


#include <iostream>
#include <string>
using namespace std;

class Task {
private:
    string desc;
    bool complete;
    int duedate;
    int priority;
public:
    Task(string desc, bool comp, int due, int prior) {
        this->desc = desc;
        this->complete = comp;
        this->duedate = due;
        this->priority = prior;
    }

    Task() {
        desc = '/0';
        this->complete = false;
        duedate = 0;
        priority = 0;
    }

    void setdesc(string desc) {
        this->desc = desc;
    }

    void setcomp(bool comp) {
        this->complete = comp;
    }

    void setdue(int due) {
        this->duedate = due;
    }

    void setprior(int prior) {
        this->priority = prior;
    }

    string getdesc() {
        return desc;
    }

    bool comp() {
        return complete;
    }

    int due() {
        return duedate;
    }

    int prior() {
        return priority;
    }

    void displayTask() {
        cout << "Description: " << desc << endl;
        cout << "Complete: " << (complete ? "Yes" : "No") << endl;
        cout << "Due date: " << duedate << endl;
        cout << "Priority: " << priority << endl;
    }
};

class ToDolist {
private:
    Task** tasks;
    int capacity;
    int count;
public:
    ToDolist(int capacity) {
        this->capacity = capacity;
        this->count = 0;
        tasks = new Task * [capacity];
        for (int i = 0; i < capacity; i++) {
            tasks[i] = nullptr;
        }
    }

    void createtask(string desc, bool comp, int due, int prior) {
        if (count < capacity) {
            tasks[count] = new Task(desc, comp, due, prior);
            count++;
        }
        else {
            cout << "Tasks full" << endl;
        }
    }

    Task* getask(int index) {
        if (index < count && index >= 0) {
            return tasks[index];
        }
        else {
            cout << "Task not added or index out of range" << endl;
            return nullptr;
        }
    }

    void markAsCompleted(int index) {
        if (index < count && index >= 0) {
            tasks[index]->setcomp(true);
        }
        else {
            cout << "Task not added or index out of range" << endl;
        }
    }

    Task* updatetask() {
        cout << "Which task do you want to update? Please enter its index: ";
        int index;
        cin >> index;

        if (index >= 0 && index < count) {
            Task* t = tasks[index];

            cout << " Enter 1 to update description" << endl;
                cout<<" 2 to update completion status" << endl;
                cout<<" 3 to update due date" << endl;
                cout << " 4 to update priority : " << endl;
            int choice;
            cin >> choice;

            switch (choice) {
            case 1: {
                cout << "Enter new description: ";
                string newDesc;
                cin.ignore();
                getline(cin, newDesc);
                t->setdesc(newDesc);
                break;
            }
            case 2: {
                cout << "Enter new completion status (0 for incomplete, 1 for complete): ";
                bool newComp;
                cin >> newComp;
                t->setcomp(newComp);
                break;
            }
            case 3: {
                cout << "Enter new due date: ";
                int newDue;
                cin >> newDue;
                t->setdue(newDue);
                break;
            }
            case 4: {
                cout << "Enter new priority: ";
                int newPrior;
                cin >> newPrior;
                t->setprior(newPrior);
                break;
            }
            default: {
                cout << "Invalid choice." << endl;
                break;
            }
            }
            return t;
        }
        else {
            cout << "Task not added or index out of range" << endl;
            return nullptr;
        }
    }

    void displayTasks() {
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                cout << "Task " << i + 1 << ":" << endl;
                tasks[i]->displayTask();
                cout << endl;
            }
        }
        else {
            cout << "No tasks added yet" << endl<<endl<<endl;
        }
    }


    int getcount() {
        return count;
    }


    ~ToDolist() {
        for (int i = 0; i < capacity; i++) {
            delete tasks[i];
        }
        delete[] tasks;
    }


};

int main() {


    cout << "********************WELCOME to TO-DO-LiST application********************" << endl;

  
    cout << endl;

    int capacity;
    cout << "Please enter the maximum number of tasks: ";
    cin >> capacity;
    ToDolist myList(capacity);

    int choice;
    do {
        cout << "******************To-Do List Application******************" << endl;
        cout << "1. Add Task"<<endl;
        cout << "2. Mark Task as Completed"<<endl;
        cout << "3. Update Task"<<endl;
        cout << "4. View Tasks"<<endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: "<<endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            string desc;
            bool comp = false;
            int due, prior;

            cout << endl << endl;
            cout << "***************ADD Task*****************" << endl;
            cout << endl << endl;

            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, desc);
            cout << "Enter due date (YYYYMMDD): ";
            cin >> due;
            cout << "Enter priority (1-5): ";
            cin >> prior;
            
            myList.createtask(desc, comp, due, prior);
            break;
        }
        case 2: {
            cout << endl << endl;
            cout << "***************TASK COMPLETION*****************" << endl;
            cout << endl << endl;
            int index;
            cout << "Enter the index of the task to mark as completed: ";
            cin >> index;
            myList.markAsCompleted(index - 1);
            break;
        }
        case 3: {

            cout << endl << endl;
            cout << "***************UPDATE TASK SECTION*****************" << endl;
            cout << endl << endl;
            myList.updatetask();
            break;
        }
        case 4: {
            cout << endl << endl;
            cout << "***************DISPLAYING TASKS*****************" << endl;
            cout << endl << endl;

            myList.displayTasks();
            break;
        }
        case 5: {
            cout << "Exiting application..." << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    } while (choice != 5);

    return 0;
}
