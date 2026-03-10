#include <stdio.h>

void fcfs(int n, int at[], int bt[]) {
    int ct[20], tat[20], wt[20];
    float avg_tat = 0, avg_wt = 0;

    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp;

                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
            }
        }
    }

    ct[0] = at[0] + bt[0];

    for(int i = 1; i < n; i++) {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\n--- FCFS Scheduling ---\n");
    printf("AT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Turnaround Time = %.2f\n", avg_tat/n);
    printf("Average Waiting Time = %.2f\n", avg_wt/n);
}


void sjf(int n, int at[], int bt[]) {
    int ct[20], tat[20], wt[20], done[20] = {0};
    int completed = 0, time = 0;
    float avg_tat = 0, avg_wt = 0;

    while(completed < n) {
        int min = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && done[i] == 0) {
                if(min == -1 || bt[i] < bt[min])
                    min = i;
            }
        }

        if(min == -1) {
            time++;
        } else {
            ct[min] = time + bt[min];
            tat[min] = ct[min] - at[min];
            wt[min] = tat[min] - bt[min];

            avg_tat += tat[min];
            avg_wt += wt[min];

            time = ct[min];
            done[min] = 1;
            completed++;
        }
    }

    printf("\n--- SJF (Non-Preemptive) ---\n");
    printf("AT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Turnaround Time = %.2f\n", avg_tat/n);
    printf("Average Waiting Time = %.2f\n", avg_wt/n);
}


int main() {
    int n;
    int at[20], bt[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    fcfs(n, at, bt);
    sjf(n, at, bt);

    return 0;
}
