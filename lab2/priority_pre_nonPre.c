#include <stdio.h>
#include <limits.h>

int main()
{
    int n,i,j,ch;
    int bt[20],priority[20],wt[20],tat[20],p[20];
    int rt[20];
    int temp;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter your choice\n1. Non Pre-emptive\n2. Pre-emptive\n");
    scanf("%d",&ch);

    switch(ch)
    {

    case 1:
        for(i=0;i<n;i++)
        {
            printf("\nProcess %d\n",i+1);
            printf("Burst Time: ");
            scanf("%d",&bt[i]);
            printf("Priority: ");
            scanf("%d",&priority[i]);
            p[i]=i+1;
        }

        for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(priority[i] > priority[j])
                {
                    temp=priority[i];
                    priority[i]=priority[j];
                    priority[j]=temp;

                    temp=bt[i];
                    bt[i]=bt[j];
                    bt[j]=temp;

                    temp=p[i];
                    p[i]=p[j];
                    p[j]=temp;
                }
            }
        }

        wt[0]=0;

        for(i=1;i<n;i++)
            wt[i]=wt[i-1]+bt[i-1];
        for(i=0;i<n;i++)
            tat[i]=wt[i]+bt[i];
        float avgwt1=0,avgtat1=0;

        printf("\nPID\tBT\tPriority\tWT\tTAT\n");

        for(i=0;i<n;i++)
        {
            printf("P%d\t%d\t%d\t\t%d\t%d\n",p[i],bt[i],priority[i],wt[i],tat[i]);
            avgwt1+=wt[i];
            avgtat1+=tat[i];
        }

        printf("\nAverage Waiting Time = %.2f",avgwt1/n);
        printf("\nAverage Turnaround Time = %.2f\n",avgtat1/n);

        break;


    case 2:
    {
        int time=0,completed=0;

        for(i=0;i<n;i++)
        {
            printf("\nProcess %d\n",i+1);
            printf("Burst Time: ");
            scanf("%d",&bt[i]);
            printf("Priority: ");
            scanf("%d",&priority[i]);
            rt[i]=bt[i];
        }

        while(completed<n)
        {
            int highest=-1;
            int min_priority=INT_MAX;

            for(i=0;i<n;i++)
            {
                if(rt[i]>0 && priority[i]<min_priority)
                {
                    min_priority=priority[i];
                    highest=i;
                }
            }

            rt[highest]--;
            time++;

            if(rt[highest]==0)
            {
                completed++;
                tat[highest]=time;
                wt[highest]=tat[highest]-bt[highest];
            }
        }

        float avgwt2=0,avgtat2=0;
        printf("\nPID\tBT\tPriority\tWT\tTAT\n");
        for(i=0;i<n;i++)
        {
            printf("P%d\t%d\t%d\t\t%d\t%d\n",i+1,bt[i],priority[i],wt[i],tat[i]);
            avgwt2+=wt[i];
            avgtat2+=tat[i];
        }

        printf("\nAverage Waiting Time = %.2f",avgwt2/n);
        printf("\nAverage Turnaround Time = %.2f\n",avgtat2/n);

        break;
    }

    default:
        printf("Invalid Choice");

    }

    return 0;
}
