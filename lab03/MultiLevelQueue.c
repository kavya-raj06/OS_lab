#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int pid[n], at[n], bt[n], type[n];
    int ct[n], tat[n], wt[n];
    int systemQ[n], userQ[n];
    int sysCount=0, userCount=0;

    for(int i=0;i<n;i++){
        printf("Enter PID AT BT TYPE(0-System,1-User): ");
        scanf("%d %d %d %d",&pid[i],&at[i],&bt[i],&type[i]);
        if(type[i]==0)
            systemQ[sysCount++]=i;
        else
            userQ[userCount++]=i;
    }

    int time=0;
    printf("\nGantt Chart:\n|");
    for(int i=0;i<sysCount;i++){
        int p=systemQ[i];
        if(time < at[p])
            time = at[p];
        printf(" P%d |",pid[p]);
        time += bt[p];
        ct[p] = time;
        tat[p] = ct[p] - at[p];
        wt[p] = tat[p] - bt[p];
    }

    for(int i=0;i<userCount;i++){
        int p=userQ[i];
        if(time < at[p])
            time = at[p];
        printf(" P%d |",pid[p]);
        time += bt[p];
        ct[p] = time;
        tat[p] = ct[p] - at[p];
        wt[p] = tat[p] - bt[p];
    }

    printf("\n");
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],type[i],ct[i],tat[i],wt[i]);
    }
    return 0;
}
