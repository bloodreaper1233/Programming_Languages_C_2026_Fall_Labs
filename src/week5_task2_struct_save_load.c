
// week5_task2_struct_save_load.c
// Name: Joyal  Surname: Joshy  Student ID: 251ADB018
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// TODO: Complete the function implementations and the file handling logic.
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int age;
    float gpa;
} Student;

int save_student(const Student *s, const char *filename) {
    FILE *fp;

    if (s == NULL || filename == NULL) {
        return -1;
    }

    fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    if (fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) == EOF) {
        return -1;
    }

    return 0;
}

int load_student(const char *filename, Student *out) {
    FILE *fp;
    int fields;

    if (filename == NULL || out == NULL) {
        return -1;
    }

    fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    fields = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);

    if (fclose(fp) == EOF || fields != 3) {
        return -1;
    }

    return 0;
}

int main(void) {
    Student original = {"Alice", 21, 3.75f};
    Student loaded = {0};

    if (save_student(&original, "student.txt") != 0) {
        perror("student.txt");
        return EXIT_FAILURE;
    }

    if (load_student("student.txt", &loaded) != 0) {
        perror("student.txt");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}
