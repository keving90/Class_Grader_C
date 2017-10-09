//"utility_KevinGeiszler.h" by Kevin Geiszler

//This utility_KevinGeiszler.h file is a header file that should be included in the
//"testlettergrader_KevinGeiszler.c" file.

//Header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _UTILITY_KEVINGEISZLER__H
#define _UTILITY_KEVINGEISZLER__H

#define MAX 40
#define MAXLINE 256

//Need to have the structures declared before the function prototypes since they use this
//information for their formal parameters
//Create a structure that holds information for each student
struct info {
	char name[MAX];
	int quiz1;
	int quiz2;
	int quiz3;
	int quiz4;
	int mid1;
	int mid2;
	int final;
	int classScore;
	char letterGrade;
};

//Create a structure to hold overall records for the class
struct data {
	int quiz1;
	int quiz2;
	int quiz3;
	int quiz4;
	int mid1;
	int mid2;
	int final;
};

//Function prototypes
int gatherInput(FILE *fp, struct info *pStruct);
void calculateClassStats(int numStudents, struct data *pTotal, struct data *pMax, struct data *pMin, struct info *pStudents);
void calculateGrades(int numStudents, struct info *pStudents);
void printToOutputFile(FILE *pOut, int numStudents, struct info *pStudents);
void showClassData(int numStudents, const struct data *pTotal, struct data *pMax, struct data *pMin);
int myComp(const void *p1, const void *p2);

#endif


