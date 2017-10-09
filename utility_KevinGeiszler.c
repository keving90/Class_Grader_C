//"utility_KevinGeiszler.c" by Kevin Geiszler

//This source code is used with main() in "testLetterGrader_KevinGeiszler.c"
//It include a custom header file.

#include "utility_KevinGeiszler.h"

/*****************************************************************************************

Function: gatherInput

Description: This function gathers each student's information from the input file, places
the info into a string, and assigns the info to the corresponding variables. First, the
function places the file position pointer at the start of the file so no records are
missed. The function then works on one record at a time, and uses a counter to keep track
of how many records are inputted. One individual row in the inputfile is considered to be
one record. The sscanf function uses %[^,\n] which says, "read every character in the
string until ',' or '\n' is found." This function will also test for invalid scores
(scores greater than 100 or lower than 0).

Input: The function takes in information from the input file provided in the second
command line argument.

Output: The file input is placed into a structure of type "info"

Return: int

*****************************************************************************************/

int gatherInput(FILE *fp, struct info *pStruct)
{
	int i = 0;
	char pInBuffer[MAXLINE];

	//Place the file position pointer at the start of the file.
	rewind(fp);
	
	while (i < 100 && (fgets(pInBuffer, MAXLINE, fp)) != NULL)
	{	
		//%[^,\n] means read every character in the string until ',' or '\n' is found
		sscanf(pInBuffer, "%[^,\n], %d, %d, %d, %d, %d, %d, %d", pStruct[i].name,
					&pStruct[i].quiz1, &pStruct[i].quiz2, &pStruct[i].quiz3,
					&pStruct[i].quiz4, &pStruct[i].mid1, &pStruct[i].mid2,
					&pStruct[i].final);
		
		//Check for invalid scores
		if ((pStruct[i].quiz1 > 100 || pStruct[i].quiz1 < 0) ||
		    (pStruct[i].quiz2 > 100 || pStruct[i].quiz2 < 0) ||
		    (pStruct[i].quiz3 > 100 || pStruct[i].quiz3 < 0) ||
		    (pStruct[i].quiz4 > 100 || pStruct[i].quiz4 < 0) ||
		    (pStruct[i].mid1  > 100 || pStruct[i].mid1 < 0)  ||
		    (pStruct[i].mid2  > 100 || pStruct[i].mid2 < 0)  ||
		    (pStruct[i].final > 100 || pStruct[i].final < 0))
		{
			printf("Invalid score in row %d for %s.\n\n", i+1, pStruct[i].name);
			exit(1);
		}
			
		//Each loop cycle is recorded to calculate the number of students in the class
		i++;
	}
	
	//Return the number of students in the class
	return i;
}

/*****************************************************************************************

Function: calculateClassStats

Description: This function calculates the total score for each quiz/test so the average
of each one can later be displayed to the console. It also finds the maximum score and
minimum score for each quiz/test.

Input: None

Output: None

Return: void

*****************************************************************************************/

void calculateClassStats(int numStudents, struct data *pTotal, struct data *pMax, struct data *pMin, struct info *pStudents)
{
	int i = 0;

	//Calculate total for each quiz/test
	//This will be used to print the average to the console
	for (i = 0; i < numStudents; i++)
	{
		pTotal->quiz1 += pStudents[i].quiz1;
		pTotal->quiz2 += pStudents[i].quiz2;
		pTotal->quiz3 += pStudents[i].quiz3;
		pTotal->quiz4 += pStudents[i].quiz4;
		pTotal->mid1  += pStudents[i].mid1;
		pTotal->mid2  += pStudents[i].mid2;
		pTotal->final += pStudents[i].final;
	}

	//Calculate the max for each quiz/test
	//This will be used to print the maximum scores to the console
	for (i = 0; i < numStudents; i++)
	{
		if(pStudents[i].quiz1 > pMax->quiz1)
			pMax->quiz1 = pStudents[i].quiz1;
			
		if(pStudents[i].quiz2 > pMax->quiz2)
			pMax->quiz2 = pStudents[i].quiz2;
			
		if(pStudents[i].quiz3 > pMax->quiz3)
			pMax->quiz3 = pStudents[i].quiz3;
			
		if(pStudents[i].quiz4 > pMax->quiz4)
			pMax->quiz4 = pStudents[i].quiz4;
			
		if(pStudents[i].mid1 > pMax->mid1)
			pMax->mid1 = pStudents[i].mid1;
			
		if(pStudents[i].mid2 > pMax->mid2)
			pMax->mid2 = pStudents[i].mid2;
			
		if(pStudents[i].final > pMax->final)
			pMax->final = pStudents[i].final;
	}
	
	//Calculate the min for each quiz/test
	//This will be used to print the minimum scores to the console
	for (i = 0; i < numStudents; i++)
	{
		if(pStudents[i].quiz1 < pMin->quiz1)
			pMin->quiz1 = pStudents[i].quiz1;
			
		if(pStudents[i].quiz2 < pMin->quiz2)
			pMin->quiz2 = pStudents[i].quiz2;
			
		if(pStudents[i].quiz3 < pMin->quiz3)
			pMin->quiz3 = pStudents[i].quiz3;
			
		if(pStudents[i].quiz4 < pMin->quiz4)
			pMin->quiz4 = pStudents[i].quiz4;
			
		if(pStudents[i].mid1 < pMin->mid1)
			pMin->mid1 = pStudents[i].mid1;
			
		if(pStudents[i].mid2 < pMin->mid2)
			pMin->mid2 = pStudents[i].mid2;
			
		if(pStudents[i].final < pMin->final)
			pMin->final = pStudents[i].final;
	}
}



/*****************************************************************************************

Function: calculateGrades

Description: This function calculates each studen't overall grade in the class based on
the teacher's proposed grading structure. The function then assigns a letter grade to each
student's overall grade. The letter grade will later be printed to the output file along
with each corresponding student's name.

Input: None

Output: None

Return: void

*****************************************************************************************/

void calculateGrades(int numStudents, struct info *pStudents)
{
	int i = 0;
	
	//Determine each student's overall score in the class
	for (i = 0; i < numStudents; i++)
	{
		pStudents[i].classScore = (.10)*(pStudents[i].quiz1 + pStudents[i].quiz2 + pStudents[i].quiz3 + pStudents[i].quiz4)
					  + (.20)*pStudents[i].mid1 + (.15)*pStudents[i].mid2
					  + (.25)*pStudents[i].final;
	}
	
	//Determine letter grades
	for (i = 0; i < numStudents; i++)
	{
		if (pStudents[i].classScore >= 90)
			pStudents[i].letterGrade = 'A';
		else if (pStudents[i].classScore >= 80 && pStudents[i].classScore < 90)
			pStudents[i].letterGrade = 'B';
		else if (pStudents[i].classScore >= 70 && pStudents[i].classScore < 80)
			pStudents[i].letterGrade = 'C';
		else if (pStudents[i].classScore >= 60 && pStudents[i].classScore < 70)
			pStudents[i].letterGrade = 'D';
		else
			pStudents[i].letterGrade = 'F';
	}
}

/*****************************************************************************************

Function: printToOutputFile

Description: This function prints the name of each student in the class and their overall
letter grade for the class to the user's desired output file. The function also appends a
colon to the end of each name. This allows better formatting for the format specifer "%s"
in the fprintf() function.

Input: None

Output: This function writes output to the output file declared by the user in the third
command line argument.

Return: void

*****************************************************************************************/

void printToOutputFile(FILE *pOut, int numStudents, struct info *pStudents)
{
	int i = 0;
	
	//Append a colon to the end of each name
	for (i = 0; i < numStudents; i++)
	{
		int len = strlen(pStudents[i].name);
		pStudents[i].name[len] = ':';
		pStudents[i].name[len+1] = '\0';
	}
	
	//Place names and grades into output file
	for (i = 0; i < numStudents; i++)
	{
		fprintf(pOut, "%-25s %c\n", pStudents[i].name, pStudents[i].letterGrade);
	}
}

/*****************************************************************************************

Function: showClassData

Description: This function displays class data to the console. This data includes the
average score, the highest score (max), and the lowest score (min) of each quiz/test.

Input: None

Output: Overall class information is displayed to the console.

Return: void

*****************************************************************************************/

//Pass a pointer to the structure when displaying to console
//can use a const argument to prevent the structure from being altered
//Also need count as an argument
void showClassData(int numStudents, const struct data *pTotal, struct data *pMax, struct data *pMin)
{
	//Console class data output formatting
	printf("Here are the class averages:\n\n");
	printf("\t\tQ1\tQ2\tQ3\tQ4\tMid1\tMid2\tFinal\n");
	
	//Print average for each quiz or test
	printf("Average:\t%5.2lf\t%5.2lf\t%5.2lf\t%5.2lf\t%5.2lf\t%5.2lf\t%5.2lf\n",
				(double)pTotal->quiz1/numStudents, (double)pTotal->quiz2/numStudents, (double)pTotal->quiz3/numStudents,
				(double)pTotal->quiz4/numStudents, (double)pTotal->mid1/numStudents, (double)pTotal->mid2/numStudents,
				(double)pTotal->final/numStudents);
	
	//Print maximum scores
	printf("Maximum:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
				pMax->quiz1, pMax->quiz2, pMax->quiz3,
				pMax->quiz4, pMax->mid1, pMax->mid2,
				pMax->final);
	
	
	//Print minimum scores
	printf("Minimum:\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
				pMin->quiz1, pMin->quiz2, pMin->quiz3,
				pMin->quiz4, pMin->mid1, pMin->mid2,
				pMin->final);
	
	printf("\n\n");
}

/*****************************************************************************************

Function: myComp

Description: This function is used with qsort(). It compares two strings found in a
structure and sorts them alphabetically. The myComp function is actually using the strcmp
function to compare each string, but qsort requires a function that takes arguments of
type void.

Input: None

Output: None

Return: int

*****************************************************************************************/

int myComp(const void *p1, const void *p2)
{
	//Need to use pointer to type "struct info" to access values.
	//Since the arguments enter the function as type void, we need to typecast
	//the pointers to point to type "struct info".
	
	struct info *a1 = (struct info *) p1;
	struct info *a2 = (struct info *) p2;
	
	return strcmp(a1->name, a2->name);
}

/****************************************************************************************/


