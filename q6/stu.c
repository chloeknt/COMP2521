// COMP2521 21T2 Sample Final Exam Q6
// Read and sort student records

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Constants

#define MAXNAME 40
#define MAXSTU  20
#define MAXLINE 100

// Student records
typedef struct _stu_rec {
	int   zid;
	char  name[MAXNAME];
	int   program;
	float wam;
} Student;

// Possible sort fields
typedef enum { BY_ZID, BY_NAME } Ordering;

// Helper functions
int readStudents(FILE *, Student *);
void sortStudents(Student *, int, Ordering);
void showStudents(FILE *, Student *, int);
void sortName(Student *stu, int n);
void sortZid(Student *stu, int n);
void swap(Student *stu, int a, int b);

int main(int argc, char **argv)
{
	Student  students[MAXSTU]; // array of student records
	int      nstudes;          // # records filled in array
	Ordering order = BY_ZID;   // order by zid or name

	// handle optional command-line argument
	// default ordering is by zid
	if (argc > 1 && strcmp(argv[1],"name") == 0)
			order = BY_NAME;

	nstudes = readStudents(stdin, students);
	sortStudents(students, nstudes, order);
	showStudents(stdout, students, nstudes);
}

// Sort "n" records in the "stu" array by order
// Always in ascending order
// If order == BY_ZID, sort numerically on unique "zid" field
// If order == BY_NAME, sort lexicographically on "name" field
//    if names are equal, sort in ascending order on "zid" field
void sortStudents(Student *stu, int n, Ordering order)
{
	if (order == BY_NAME) {
	    sortName(stu, n);
	} else if (order == BY_ZID) {
	    sortZid(stu, n);
	}
}

void sortName(Student *stu, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            Student *s1 = &stu[j];
            Student *s2 = &stu[j + 1];
            if (strcmp(s1->name, s2->name) > 0) {
                swap(stu, j, j + 1);
            } else if (strcmp(s1->name, s2->name) == 0) {
                if (s1->zid > s2->zid) {
                    swap(stu, j, j + 1);
                } 
            }
        }
    }
} 

void sortZid(Student *stu, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1;  j++) {
            Student *s1 = &stu[j];
            Student *s2 = &stu[j + 1];
            if (s1->zid > s2->zid) {
                swap(stu, j, j + 1);
            }
        }
    }
}

void swap(Student *stu, int a, int b) {
    Student *s1 = &stu[a];
    Student *s2 = &stu[b];
    Student *temp = malloc(sizeof(Student));
    
    temp->zid = s1->zid;
    strcpy(temp->name, s1->name);
    temp->program = s1->program;
    temp->wam = s1->wam;
    
    s1->zid = s2->zid;
    strcpy(s1->name, s2->name);
    s1->program = s2->program;
    s1->wam = s2->wam;
    
    s2->zid = temp->zid;
    strcpy(s2->name, temp->name);
    s2->program = temp->program;
    s2->wam = temp->wam;
}

// Read student records from file "in"
// Read into array of student records "stu"
// Returns number of records read
int readStudents(FILE *in, Student *stu)
{
	char line[MAXLINE];
	int  n, nread = 0;

	while (fgets(line, MAXLINE, in) != NULL) {
		// pointer to current student record
		Student *s = &stu[nread];
		n = sscanf(line, "%d:%[^:]:%d:%f", 
		           &(s->zid), &(s->name[0]), &(s->program), &(s->wam));
		if (n != 4) {
			fprintf(stderr, "Bad input: %s", line);
			exit(1);
		}
		nread++;
	}
	return nread;
}

// Print student info on standard output
// Info comes from array "stu" of student records
//   which contains "n" entries
void showStudents(FILE *out, Student *stu, int n)
{
	for (int i = 0; i < n; i++) {
		// pointer to current student record
		Student *s = &stu[i];
			// should use MAXNAME, rather than 40
		fprintf(out, "%-7d %-40s %04d %0.1f\n",
		        s->zid, s->name, s->program, s->wam);
	}
}
