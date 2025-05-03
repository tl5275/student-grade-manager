#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_SUBJECTS 10

typedef struct {
    char name[50];
    int roll;
    float marks[MAX_SUBJECTS];
    float total;
    float percentage;
    float percentile;
} Student;

void inputSubjectNames(char subjectNames[][30], int subCount) {
    for (int i = 0; i < subCount; i++) {
        printf("Enter name of Subject %d: ", i + 1);
        scanf(" %[^\n]", subjectNames[i]);
    }
}

void inputStudents(Student s[], int n, int subCount, char subjectNames[][30]) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", s[i].name);
        printf("Roll Number: ");
        scanf("%d", &s[i].roll);
        s[i].total = 0;
        for (int j = 0; j < subCount; j++) {
            printf("Marks for %s: ", subjectNames[j]);
            scanf("%f", &s[i].marks[j]);
            s[i].total += s[i].marks[j];
        }
        s[i].percentage = s[i].total / subCount;
    }
}

void calculatePercentiles(Student s[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (s[j].total < s[i].total) {
                count++;
            }
        }
        s[i].percentile = ((float)count / (n - 1)) * 100;
    }
}

void sortByTotalDescending(Student s[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].total < s[j+1].total) {
                Student temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
}

void sortByRoll(Student s[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].roll > s[j+1].roll) {
                Student temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
}

int binarySearchByRoll(Student s[], int n, int keyRoll) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (s[mid].roll == keyRoll)
            return mid;
        else if (s[mid].roll < keyRoll)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

float calculateClassAverage(Student s[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += s[i].percentage;
    }
    return sum / n;
}

void findTopper(Student s[], int n) {
    printf("\nTopper:\n");
    printf("Name: %s\n", s[0].name);
    printf("Roll: %d\n", s[0].roll);
    printf("Total Marks: %.1f\n", s[0].total);
    printf("Percentage: %.1f\n", s[0].percentage);
}

void displayStudents(Student s[], int n, int subCount, char subjectNames[][30]) {
    printf("\n%-20s %-6s ", "Name", "Roll");
    for (int i = 0; i < subCount; i++) {
        printf("%-6s ", subjectNames[i]);
    }
    printf(" Total  %%age  Percentile\n");

    for (int i = 0; i < n; i++) {
        printf("%-20s %-6d ", s[i].name, s[i].roll);
        for (int j = 0; j < subCount; j++) {
            printf("%6.1f ", s[i].marks[j]);
        }
        printf("%6.1f %6.1f %9.2f\n", s[i].total, s[i].percentage, s[i].percentile);
    }

    float avg = calculateClassAverage(s, n);
    printf("\nClass Average Percentage: %.2f\n", avg);
}

void displayStudentDetails(Student s, int subCount, char subjectNames[][30]) {
    printf("\nStudent Details:\n");
    printf("Name: %s\n", s.name);
    printf("Roll: %d\n", s.roll);
    for (int i = 0; i < subCount; i++) {
        printf("%s: %.1f\n", subjectNames[i], s.marks[i]);
    }
    printf("Total: %.1f\n", s.total);
    printf("Percentage: %.1f\n", s.percentage);
    printf("Percentile: %.2f\n", s.percentile);
}

int main() {
    Student students[MAX];
    char subjectNames[MAX_SUBJECTS][30];
    int n, subCount;

    printf("Enter number of students: ");
    scanf("%d", &n);
    printf("Enter number of subjects: ");
    scanf("%d", &subCount);

    inputSubjectNames(subjectNames, subCount);
    inputStudents(students, n, subCount, subjectNames);

    calculatePercentiles(students, n);

    int choice;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Display Students Sorted by Total Marks (Descending)\n");
        printf("2. Display Students Sorted by Roll Number (Ascending)\n");
        printf("3. Show Class Average and Topper\n");
        printf("4. Search Student by Roll Number\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sortByTotalDescending(students, n);
                printf("\n--- Sorted by Total Marks (Descending) ---");
                displayStudents(students, n, subCount, subjectNames);
                break;
            case 2:
                sortByRoll(students, n);
                printf("\n--- Sorted by Roll Number (Ascending) ---");
                displayStudents(students, n, subCount, subjectNames);
                break;
            case 3:
                sortByTotalDescending(students, n);
                printf("\nClass Average: %.2f\n", calculateClassAverage(students, n));
                findTopper(students, n);
                break;
            case 4: {
                int keyRoll;
                sortByRoll(students, n); // sort before searching
                printf("Enter roll number to search: ");
                scanf("%d", &keyRoll);
                int index = binarySearchByRoll(students, n, keyRoll);
                if (index != -1)
                    displayStudentDetails(students[index], subCount, subjectNames);
                else
                    printf("Student with roll number %d not found.\n", keyRoll);
                break;
            }
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
