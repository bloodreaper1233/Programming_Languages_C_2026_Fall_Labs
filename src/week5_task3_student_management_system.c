
// week5_task3_student_management_system.c
// Name: Joyal  Surname: Joshy  Student ID: 251ADB018
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

int read_line(char *buf, size_t size) {
    size_t len;
    int ch;

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    len = strcspn(buf, "\r\n");

    if (buf[len] == '\0' && len == size - 1) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    buf[len] = '\0';
    return 0;
}

int load_students(Student arr[], int max) {
    FILE *fp;
    char line[256];
    int count = 0;

    if (arr == NULL || max <= 0) {
        return 0;
    }

    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;
    }

    while (count < max && fgets(line, sizeof(line), fp) != NULL) {
        Student s;
        char extra;

        if (sscanf(line, " %49[^,],%d,%f %c",
                   s.name, &s.id, &s.gpa, &extra) != 3) {
            continue;
        }

        if (s.name[0] == '\0' || s.gpa < 0.0f || s.gpa > 4.0f) {
            continue;
        }

        arr[count++] = s;
    }

    fclose(fp);
    return count;
}

int save_students(const Student arr[], int count) {
    FILE *fp;
    int i;

    fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (fprintf(fp, "%s,%d,%.2f\n",
                    arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            fclose(fp);
            return -1;
        }
    }

    if (fclose(fp) == EOF) {
        return -1;
    }

    return 0;
}

void add_student(Student arr[], int *count) {
    char name[256];
    char id_text[64];
    char gpa_text[64];
    char *end;
    long id_value;
    float gpa_value;

    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    printf("Enter name: ");
    if (read_line(name, sizeof(name)) != 0) {
        return;
    }

    printf("Enter ID: ");
    if (read_line(id_text, sizeof(id_text)) != 0) {
        return;
    }

    printf("Enter GPA: ");
    if (read_line(gpa_text, sizeof(gpa_text)) != 0) {
        return;
    }

    if (name[0] == '\0' || strchr(name, ',') != NULL ||
        strlen(name) >= NAME_LEN) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    errno = 0;
    id_value = strtol(id_text, &end, 10);
    if (id_text[0] == '\0' || *end != '\0' ||
        errno == ERANGE || id_value < INT_MIN || id_value > INT_MAX) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    errno = 0;
    gpa_value = strtof(gpa_text, &end);
    if (gpa_text[0] == '\0' || *end != '\0' ||
        errno == ERANGE || !(gpa_value >= 0.0f && gpa_value <= 4.0f)) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id_value;
    arr[*count].gpa = gpa_value;
    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    int i;

    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("Name: %s, ID: %d, GPA: %.2f\n",
               arr[i].name, arr[i].id, arr[i].gpa);
    }
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    char input[32];
    int choice;

    while (1) {
        printf("\n1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and exit\n");
        printf("Choose an option: ");

        if (read_line(input, sizeof(input)) != 0) {
            choice = 3;
        } else {
            char *end;
            long value;

            errno = 0;
            value = strtol(input, &end, 10);

            if (input[0] == '\0' || *end != '\0' ||
                errno == ERANGE || value < 1 || value > 3) {
                choice = 0;
            } else {
                choice = (int)value;
            }
        }

        if (choice == 1) {
            list_students(students, count);
        } else if (choice == 2) {
            add_student(students, &count);
        } else if (choice == 3) {
            if (save_students(students, count) != 0) {
                perror(DATA_FILE);
                return EXIT_FAILURE;
            }

            printf("Data saved. Goodbye!\n");
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

