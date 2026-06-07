#include <stdio.h>
#define MAX_TASKS 10

typedef struct {
    int id;
    int C;
    int P;
    int remaining_time;
    int next_arrival;
} Task;

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int findLCM(Task tasks[], int n) {
    int result = tasks[0].P;
    for (int i = 1; i < n; i++) {
        result = lcm(result, tasks[i].P);
    }
    return result;
}

void sortByPeriod(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].P > tasks[j].P) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Task tasks[MAX_TASKS];
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter C and P for Process %d: ", tasks[i].id);
        scanf("%d %d", &tasks[i].C, &tasks[i].P);
        tasks[i].remaining_time = 0;
        tasks[i].next_arrival = 0;
    }

    sortByPeriod(tasks, n);
    int MAX_TIME = findLCM(tasks, n);
    int gantt[MAX_TIME];
    int time = 0;
    while (time < MAX_TIME) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].P;
            }
        }

        int current_task = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current_task = i;
                break;
            }
        }
        if (current_task != -1) {
            tasks[current_task].remaining_time -= 1;
            gantt[time] = tasks[current_task].id;
        } else {
            gantt[time] = 0;
        }
        for (int i = 0; i < n; i++) {
            if (time > tasks[i].next_arrival - tasks[i].P && tasks[i].remaining_time > 0) {
                printf("Deadline Miss at time %d for Process %d\n", time, tasks[i].id);
            }
        }
        time++;
    }

    printf("\nGantt Chart:\n");
    for (int i = 0; i < MAX_TIME; i++) {
        printf("|");
        if (gantt[i] == 0)
            printf("Idle\t");
        else
            printf("P%d\t", gantt[i]);
    }
    printf("|\n");

    for (int i = 0; i < MAX_TIME; i++) {
        printf("%d\t", i);
    }
    printf("%d\n", MAX_TIME);
    return 0;
}
