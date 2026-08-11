#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;
};

/* Function declarations */
void addStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayStudents();

int main() {
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Search Student\n");
        printf("5. Display All Students\n");
        printf("6. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                displayStudents();
                break;

            case 6:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

/* Add a new student */
void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

/* Delete a student */
void deleteStudent() {
    struct Student s;
    FILE *fp, *temp;
    int rollNo, found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent with Roll Number %d not found!\n", rollNo);
}

/* Update student details */
void updateStudent() {
    struct Student s;
    FILE *fp;
    int rollNo, found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {
            found = 1;

            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            /* Move file pointer back to the beginning of current record */
            fseek(fp, -sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            printf("\nStudent updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent with Roll Number %d not found!\n", rollNo);
}

/* Search for a student */
void searchStudent() {
    struct Student s;
    FILE *fp;
    int rollNo, found = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == rollNo) {
            found = 1;

            printf("\n---------- Student Details ----------\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Age         : %d\n", s.age);
            printf("Course      : %s\n", s.course);
            printf("Marks       : %.2f\n", s.marks);
            printf("-------------------------------------\n");

            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent with Roll Number %d not found!\n", rollNo);
}

/* Display all students */
void displayStudents() {
    struct Student s;
    FILE *fp;
    int count = 0;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n================ ALL STUDENTS ================\n");
    printf("%-10s %-20s %-5s %-20s %-10s\n",
           "Roll No", "Name", "Age", "Course", "Marks");
    printf("---------------------------------------------------------------\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%-10d %-20s %-5d %-20s %-10.2f\n",
               s.rollNo, s.name, s.age, s.course, s.marks);
        count++;
    }

    fclose(fp);

    if (count == 0)
        printf("No student records available.\n");

    printf("===============================================================\n");
}
