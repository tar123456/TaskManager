#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<chrono>
#include<functional>
#include<memory>

struct task{
    std::string Title;
    std::string Description;
    std::chrono::year_month_day deadline_Date;
    unsigned int day, month;
    int year;
    bool isValid = true;

    task(std::string Title, std::string Descrip, std::string deadline)
    {
        this->Title = Title;
        this->Description = Descrip;
        std::istringstream input_stream(deadline);
        char hyp1, hyp2;
        input_stream>>year>>hyp1>>month>>hyp2>>day;
        if(input_stream.fail()||hyp1!='-'||hyp2!='-'||month<1||month>12||day<1||day>31||(month==2&&day>29))
        {
            std::cout<<"Invalid date format or invalid date entered";
            isValid=false;
            return;

        }
        try{
        deadline_Date=std::chrono::year{year}/std::chrono::month{month}/std::chrono::day{day};
        }
        catch (const std::exception&) {
            std::cout << "Invalid date value: " << deadline << std::endl;
            return;
        }
    
    }
    bool operator>(const task& other) const{
        return deadline_Date > other.deadline_Date;
    }
    void print() {
        if (isValid) {
            std::cout << "Task: " << Title << "\nDescription: " << Description << "\nDeadline: "
                      << (int)deadline_Date.year() << "-"
                      << (unsigned)deadline_Date.month() << "-"
                      << (unsigned)deadline_Date.day() << std::endl;
        } else {
            std::cout << "Task has invalid date.\n";
        }
    }
};
int main()
{
    std::priority_queue<task, std::vector<task>,  std::greater<task>> taskQueue;

    std::string Task, Descrip, deadline;
    int option;
    std::shared_ptr<task> newTask;

    std::cout<<"1: Add Task\n2:Complete Task\n3:Print Tasks \n0: Exit \n";
    std::cin>>option;
    std::cin.ignore();
    while(option != 0)
    {
        switch(option)
        {
            case 1: 
            {
               std::cout << "Enter task title: ";
               std::getline(std::cin, Task);
               std::cout << "Enter task description: ";
               std::getline(std::cin, Descrip);
               std::cout << "Enter task deadline (YYYY-MM-DD): ";
               std::getline(std::cin, deadline);
               newTask = std::make_shared<task>(Task, Descrip, deadline);
               taskQueue.push(*newTask);
               std::cout<<"New Task Added: \n";
               newTask->print();
               break;
            }
            case 2:
            {   
            if(!taskQueue.empty())
               {
                   taskQueue.pop();
                   std::cout<<"Task Completed!!! Good Job!!! \n";
               }
            else
               {
                   std::cout<<"You are top of the game!!! No Tasks at the moment to be completed\n";
               }
                break;
            }
            case 3:
            {
               std::cout<<"Following are the tasks that are pending: \n";
               int size = taskQueue.size();
               std::priority_queue<task, std::vector<task>,  std::greater<task>> temp = taskQueue;


               while (!temp.empty()) {
                   task currentTask = temp.top();
                   currentTask.print();
                   temp.pop();
                   
                } 
                
                std::cout<<"\n Please make sure you complete them timely. \n";
                break;
            }
            case 0:
            {
               std::cout<<"Exiting";
               break;
            }
            default:
            {
               std::cout<<"Please enter valid option to continue. \n";
               break;
            }

        };
        std::cout << "\n1: Add Task\n2: Complete Task\n3: Print Tasks\n0: Exit\n";
        std::cin >> option;
        std::cin.ignore();

    }



    return 0;
}