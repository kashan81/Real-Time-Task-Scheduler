#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
public:
    int id;
    int priority;
    int burstTime;
    int remainingTime;

    Task(int i, int p, int b) {
        id = i;
        priority = p;
        burstTime = b;
        remainingTime = b;
    }
};

class RTOS {
private:
    vector<Task> tasks;
    vector<int> ganttChart;   // stores executed task IDs
    vector<int> timeLine;     // stores time steps
    int time;

public:
    RTOS() {
        time = 0;
    }

    void addTask(Task t) {
        tasks.push_back(t);
    }

    void sortByPriority() {
        sort(tasks.begin(), tasks.end(),
            [](Task &a, Task &b) {
                return a.priority > b.priority;
            });
    }

    void runPriorityScheduling() {

        cout << "\n===== PRIORITY SCHEDULING STARTED =====\n";

        while (true) {

            sortByPriority();

            bool allDone = true;

            for (auto &task : tasks) {

                if (task.remainingTime > 0) {

                    cout << "\nTime: " << time;
                    cout << "\nRunning Task: T" << task.id;
                    cout << " | Priority: " << task.priority << endl;

                    task.remainingTime -= 1;

                    // GANTT CHART LOG
                    ganttChart.push_back(task.id);
                    timeLine.push_back(time);

                    time++;

                    cout << "Remaining Time: " << task.remainingTime << endl;

                    allDone = false;
                    break;
                }
            }

            if (allDone) break;
        }

        cout << "\n===== ALL TASKS COMPLETED =====\n";

        printGanttChart();
    }

    void runRoundRobin(int quantum) {

        cout << "\n===== ROUND ROBIN STARTED =====\n";

        bool done = false;

        while (!done) {
            done = true;

            for (auto &task : tasks) {

                if (task.remainingTime > 0) {

                    done = false;

                    cout << "\nTime: " << time;
                    cout << "\nRunning Task: T" << task.id << endl;

                    int execTime = min(quantum, task.remainingTime);

                    for (int i = 0; i < execTime; i++) {
                        ganttChart.push_back(task.id);
                        timeLine.push_back(time);
                        time++;
                    }

                    task.remainingTime -= execTime;

                    cout << "Executed for: " << execTime << endl;
                    cout << "Remaining: " << task.remainingTime << endl;
                }
            }
        }

        cout << "\n===== ROUND ROBIN COMPLETED =====\n";

        printGanttChart();
    }

    void printGanttChart() {

        cout << "\n================ GANTT CHART ================\n";

        cout << "Timeline: \n| ";

        for (int i = 0; i < ganttChart.size(); i++) {
            cout << "T" << ganttChart[i] << " | ";
        }

        cout << "\n0";

        for (int i = 0; i < timeLine.size(); i++) {
            cout << "   " << timeLine[i] + 1;
        }

        cout << "\n=============================================\n";
    }
};

int main() {

    RTOS system;

    system.addTask(Task(1, 3, 5));
    system.addTask(Task(2, 5, 3));
    system.addTask(Task(3, 1, 7));
    system.addTask(Task(4, 4, 4));

    cout << "Choose Scheduling Algorithm:\n";
    cout << "1. Priority Scheduling\n";
    cout << "2. Round Robin\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        system.runPriorityScheduling();
    }
    else if (choice == 2) {
        system.runRoundRobin(2);
    }
    else {
        cout << "Invalid choice\n";
    }

    return 0;
}