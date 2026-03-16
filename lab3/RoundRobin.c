#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n], BT[n], RT[n];
    int CT[n], TAT[n], WT[n];

    int ganttP[100];
    int ganttT[100];
    int gIndex = 0;

    printf("Enter Arrival Time and Burst Time:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d AT BT: ", i+1);
        scanf("%d %d", &AT[i], &BT[i]);
        RT[i] = BT[i];
        CT[i] = WT[i] = TAT[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;

    while(completed < n) {
        int executed = 0;

        for(int i = 0; i < n; i++) {

            if(AT[i] <= time && RT[i] > 0) {

                executed = 1;

                ganttP[gIndex] = i;
                ganttT[gIndex] = time;
                gIndex++;

                if(RT[i] > tq) {
                    time += tq;
                    RT[i] -= tq;
                } else {
                    time += RT[i];
                    RT[i] = 0;
                    CT[i] = time;
                    completed++;
                }
            }
        }

        if(executed == 0)
            time++;
    }

    ganttT[gIndex] = time;

    for(int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    printf("\nGantt Chart:\n|");

    for(int i = 0; i < gIndex; i++) {
        printf(" P%d |", ganttP[i] + 1);
    }

    printf("\n%d", ganttT[0]);

    for(int i = 1; i <= gIndex; i++) {
        printf("    %d", ganttT[i]);
    }

    printf("\n");

    return 0;
}
