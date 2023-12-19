#include <stdio.h>
#include <stdlib.h>
typedef struct Student{
    char grades;

}Student;
typedef struct Person{
    Student *grades;
} Person;

Person *p1;
int initializeValues();
int updateValues();
int main(int argc, char *argv[]){
    initializeValues();
    printf("Person1 grades: %c\n", (*p1).grades[1].grades);
    updateValues();
    free(p1);
    return 0;
}


int initializeValues(){
    p1 = malloc(sizeof(Person));
   
    if(p1 == NULL){
        printf("Couldnt init pointer");
    }
    (*p1).grades = malloc(2 * sizeof(Student));
    if((*p1).grades == NULL){
        printf("Couldnt initialize pointer");
    }

    (*p1).grades[0] = (Student){'A'};
    (*p1).grades[1] = (Student){'B'}; 
    return 0;
}

int updateValues(){
    if(p1 != NULL){
        printf("Llegue aqui lol");
        free((*p1).grades);
        free(p1);
        p1 = NULL; 
        if(p1 == NULL){
            printf("P1 is NULL now");        
       }

    }      
    return 0;
}


