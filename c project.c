#include <stdio.h>

struct Student {
    int roll_no;
    char name[50];
    int marks[5];
    float average;
    char grade;
};

void calculateGrade(struct Student *s) {
    int total = 0;
    for (int i = 0; i < 5; i++)
        total += s->marks[i];

    s->average = total / 5.0;

    if (s->average >= 90) s->grade = 'A';
    else if (s->average >= 75) s->grade = 'B';
    else if (s->average >= 60) s->grade = 'C';
    else s->grade = 'D';
}

int readStudent(FILE *fp, struct Student *s) {
    if (fscanf(fp, "%d", &s->roll_no) != 1)
        return 0;

    if (fscanf(fp, " %49[^0-9]", s->name) != 1)
        return 0;

    for (int i = 0; i < 5; i++) {
        if (fscanf(fp, "%d", &s->marks[i]) != 1)
            return 0;
    }
    return 1;
}

void saveAndShowReport(FILE *out, struct Student s) {
    fprintf(out, "--------------------------------------------\n");
    fprintf(out, "Student Report: %s\n", s.name);
    fprintf(out, "Roll No: %d\n", s.roll_no);
    fprintf(out, "Marks: ");
    for (int i = 0; i < 5; i++)
        fprintf(out, "%d ", s.marks[i]);
    fprintf(out, "\nAverage: %.2f\nGrade: %c\n", s.average, s.grade);
    fprintf(out, "--------------------------------------------\n\n");

    printf("Processed record for: %s\n", s.name);
}

int main() {
    FILE *input = fopen("input_data.txt", "r");
    FILE *output = fopen("output_report.txt", "w");

    if (!input) {
        printf("Error: Could not open input_data.txt\n");
        return 1;
    }
    if (!output) {
        printf("Error: Could not create output_report.txt\n");
        fclose(input);
        return 1;
    }

    struct Student s;
    int count = 0;

    while (readStudent(input, &s)) {
        calculateGrade(&s);
        saveAndShowReport(output, s);
        count++;
    }

    fclose(input);
    fclose(output);

    printf("\nSuccess! %d records processed.\n", count);

    return 0;
}
