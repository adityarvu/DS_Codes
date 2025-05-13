#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX 100
#define TASK_LEN 100

char stack[MAX][TASK_LEN];
time_t timestamps[MAX];
int top = -1;

// Start a new task
void startTask(const char *task) {
    if (top >= 0) {
        printf(" Interruption: %s\n", task);
    }
    if (top == MAX - 1) {
        printf(" Stack overflow! Too many tasks.\n");
        return;
    }
    ++top;
    strcpy(stack[top], task);
    timestamps[top] = time(NULL);
    printf(" Started task: %s\n", task);
}

// Finish the current task
void finishTask() {
    if (top == -1) {
        printf(" No task to finish.\n");
        return;
    }
    time_t now = time(NULL);
    double duration = difftime(now, timestamps[top]);
    printf(" Finished: %s\n", stack[top]);
    printf(" Time spent: %.0f seconds\n", duration);
    top--;

    if (top >= 0) {
        printf(" Resuming: %s\n", stack[top]);
    } else {
        printf(" No remaining tasks. You are free!\n");
    }
}

// Print the task stack
void showTaskStack() {
    printf("\n Task Stack:\n");
    if (top == -1) {
        printf("   [Empty]\n");
        return;
    }
    for (int i = top; i >= 0; i--) {
        printf("   %s%s\n", stack[i], i == top ? " (current)" : "");
    }
}

int main() {
    char command[10], task[TASK_LEN];

    printf(" Task Switching Simulation\n\n");
    printf("Commands:\n  start - to start a new task\n  done - to finish the current task\n  exit - to quit\n");

    while (1) {
        printf("\n>>> ");
        scanf("%s", command);
        getchar();  // Clear newline

        if (strcmp(command, "start") == 0) {
            printf("Enter task description: ");
            fgets(task, TASK_LEN, stdin);
            task[strcspn(task, "\n")] = '\0';  // Remove newline
            startTask(task);
        } else if (strcmp(command, "done") == 0) {
            finishTask();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf(" Unknown command. Use: start, done, exit\n");
        }
    }

    showTaskStack();
    return 0;
}