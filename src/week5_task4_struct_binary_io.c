// week5_task4_struct_binary_io.c   (BONUS)
// Name: Joyal  Surname: Joshy  Student ID: 251ADB018
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

int save_binary(const Student *s, const char *filename) {
    FILE *fp;

    if (s == NULL || filename == NULL) {
        return -1;
    }

    fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }

    if (fwrite(s, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) == EOF) {
        return -1;
    }

    return 0;
}

int load_binary(const char *filename, Student *out) {
    FILE *fp;

    if (filename == NULL || out == NULL) {
        return -1;
    }

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    if (fread(out, sizeof(Student), 1, fp) != 1) {
        fclose(fp);
        return -1;
    }

    if (fclose(fp) == EOF) {
        return -1;
    }

    return 0;
}

long file_size(const char *filename) {
    FILE *fp;
    long size;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    size = ftell(fp);

    if (fclose(fp) == EOF) {
        return -1;
    }

    return size;
}

int main(void) {
    Student original = {"Alice", 21, 3.75f};
    Student loaded = {0};
    FILE *fp;
    long binary_size;
    long text_size;

    if (save_binary(&original, "student.bin") != 0) {
        perror("student.bin");
        return EXIT_FAILURE;
    }

    if (load_binary("student.bin", &loaded) != 0) {
        perror("student.bin");
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n",
           loaded.name, loaded.age, loaded.gpa);

    binary_size = file_size("student.bin");
    if (binary_size < 0) {
        perror("student.bin");
        return EXIT_FAILURE;
    }

    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        perror("student.txt");
        return EXIT_FAILURE;
    }

    if (fprintf(fp, "%s %d %.2f\n",
                original.name, original.age, original.gpa) < 0) {
        perror("student.txt");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fclose(fp) == EOF) {
        perror("student.txt");
        return EXIT_FAILURE;
    }

    text_size = file_size("student.txt");
    if (text_size < 0) {
        perror("student.txt");
        return EXIT_FAILURE;
    }

    printf("Binary file size: %ld bytes\n", binary_size);
    printf("Text file size: %ld bytes\n", text_size);

    return EXIT_SUCCESS;
}
