#include <stdio.h>
#include <omp.h>

#define N 100
#define NUM_PROCESS 4
 
int main()
{
    int arr[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = sizeof(int) * (i);
    }
    int sum = 0;
    int part_process[NUM_PROCESS];
#pragma omp parallel num_threads(NUM_PROCESS)
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * (N / NUM_PROCESS);
        int end = (thread_id + 1) * (N / NUM_PROCESS);

        part_process[thread_id] = 0;

        for (int i = start; i < end; i++)
        {
            part_process[thread_id] += arr[i];
        }
    }
    for (int i = 0; i < NUM_PROCESS; i++)
    {
        sum += part_process[i];
        printf("Partial Process Sum %d is %d \n", i, part_process[i]);
    }

    printf("Sum is = %d", sum);

    return 0;
}