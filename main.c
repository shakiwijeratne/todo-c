/*To Do List App */
/*Features:
        Add tasks
        List tasks
        Edit tasks
        Delete tasks
        Mark as complete
*/

/*What we learn:
        Struct
        Input/Output
        Functions
        Pointers
        Loops
        Conditional statements
        Manual memory management
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *task;
    int completed; // 1 represents true 0 represents false
} Task;

Task *tasks = NULL;
int length = 0;

//Functions

void addTask(const char *task){
    tasks = (Task *)realloc(tasks, (length + 1) * sizeof(Task));
    tasks[length].task = (char *)malloc(strlen(task) + 1);
    tasks[length].completed = 0;

    strcpy(tasks[length].task, task);
    length++;
    printf("task added!\n");
}

void listTasks(){
    char status;

    for(int i= 0; i<length; i++){
        if(tasks[i].completed == 1){
            status = 'd';
        }else{
            status = 'n';
        }
        printf("%d. %s [%c]\n", i+1, tasks[i].task, status);
    }
}

void editTask(int index, const char *task){
    if(index <= length && index > 0){
        index = index - 1;

        char *editedTask = (char *)realloc(tasks[index].task, (strlen(task) + 1));

        if(editedTask != NULL){
            tasks[index].task = editedTask;
            strcpy(tasks[index].task, task);
            printf("task updated successfully!\n");
        }else{
            printf("memory allocation failed!\n");
        }
    }else{
        printf("Invalid index!\n");
    }
}

void deleteTask(int index){
    if(index <= length && index > 0){
        index = index - 1;

        free(tasks[index].task);

        for(int i = index; i < length - 1; i++){
            tasks[i] = tasks[i + 1];
        }

        length--;

        tasks = (Task *)realloc(tasks, (length * sizeof(Task)));
        printf("task deleted!\n");
    }else{
        printf("Invalid index!\n");
    }
}

void markCompleted(int index){
    if(index <= length && index > 0){
        tasks[index - 1].completed = 1;
        printf("task marked as completed!\n");
    }else{
        printf("Invalid index!\n");
    }
}

int main(){
    int running = 1;
    int choice;
    int indexInput;

    char taskInput[100];

    printf("\nOptions\n");
    printf("1.Add a task\n");
    printf("2.List all tasks\n");
    printf("3.Mark as complete\n");
    printf("4.Edit task\n");
    printf("5.Delete task\n");
    printf("6.Exit\n");

    while(running){
        printf("Enter choice (1,2,3,4,5,6): ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            printf("Enter Task: ");
            getchar();
            fgets(taskInput, sizeof(taskInput),stdin);
            taskInput[strcspn(taskInput, "\n")] = 0;
            addTask(taskInput);
            break;

        case 2:
            listTasks();
            break;

        case 3:
            printf("Enter index: ");
            scanf("%d", &indexInput);

            markCompleted(indexInput);
            break;

        case 4:
            printf("Enter index: ");
            scanf("%d", &indexInput);

            printf("Enter edited task: ");
            fgets(taskInput, sizeof(taskInput),stdin);
            taskInput[strcspn(taskInput, "\n")] = 0;

            editTask(indexInput, taskInput);
            break;

        case 5:
            printf("Enter index: ");
            scanf("%d", &indexInput);

            deleteTask(indexInput);
            break;

        case 6:
            running = 0;
            break;

        default:
            printf("Invalid choice!");
            break;
        }
    }

    free(tasks);
    return 0;
}


