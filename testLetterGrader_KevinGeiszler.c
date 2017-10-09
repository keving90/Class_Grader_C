/*****************************************************************************************

Program name: testLetterGrader_KevinGeiszler.c
By: Kevin Geiszler

Description: This program is designed to read an input file, and write to an output file.
The program reads an input file containing student information for a class. This
information includes names and grades for quizzes and tests, separated by a comma. The
program will gather this information from the input file, calculate the overall grade for
each student in the class, sort each student's name alphabetically, and write their name
and letter grade to the output file. The program will also display class averages, the
minimum scores, and the maximum scores for each quiz/test to the console. The user will
choose which input and output files they would like to use by inputting arguments to the
command line. There should be only one input file and one output file, otherwise the
program will terminate and display an error message.

*****************************************************************************************/

//Header file
//All other libraries included inside this header
#include "utility_KevinGeiszler.h"

/*****************************************************************************************

Function: main

Description: The main function uses several other functions defined in
"utility_KevinGeiszler.c". It pieces everything together, and allows the program to work
as described in the program description found at the beginning of this file.

Input: The main function takes in three command line arguments. One for the executable
file, one for the input file, and one for the output file. The code for opening the input
file can be found below. The gatherInput() function is used to collect information from
the input file. This function's definition and description can be found in
"utility_KevinGeiszler.c".

Output: The main function uses the showClassData() function to display output to the
console. It uses printToOutputFile() function to write output to the text file
provided in the command line arguments. These function definition and descriptions can be
found in "utility_KevinGeiszler.c".

Return: int

*****************************************************************************************/

int main(int argc, char *argv[])
{
	//Create an array of structures
	//Initialize every member of every structure as zero
	struct info studentInfo[100] = {0};
	
	//Create a structure to hold the total scores of each quiz/test
	//These totals will later be used to calculate the average for each quiz/test
	//Initialize the total for each quiz/test as zero
	struct data total = {0};
	
	//Create a structure to hold the max scores of each quiz/test
	//Initialize the each max as the minimum score so they can be beaten
	struct data max = {0};
	
	//Create a structure to hold the min scores of each quiz/test
	//Initialize the each min as the maximum score so there are likely lower scores
	struct data min = {100, 100, 100, 100, 100, 100, 100};

	FILE *pClassInfo; //File pointer for input file
	FILE *pOutput; //File pointer for output file
	int count = 0; //Create a counter to account for the amount of records taken from input

	//If the command line does not have three arguments (one for the main file, one for
	//input, and one for output), then an error message is displayed. The message will
	//tell the user how the command line arguments should be organized.
	//Otherwise, the program will tell you which files will be used for input and output.
	if (argc != 3)
	{
		printf("\nError, need the following file usage: %s inputFileName outputFileName\n\n", argv[0]);
		exit(1);
	}
	else
	{
		printf("\nInput will be read from: %s\n", argv[1]);
		printf("Output will be written into: %s\n\n", argv[2]);
	}
	
	//Open the input file.
	//If the file cannot be opened, then display an error message.
	if ((pClassInfo = fopen(argv[1], "r")) == NULL)
	{
		printf("Can't open %s.\n", argv[1]);
		exit(1);
	}
	
	//studentInfo does not need the & operator because it is an array (of structures)
	//gatherInput() returns the number of students in the class
	count = gatherInput(pClassInfo, studentInfo);
	calculateClassStats(count, &total, &max, &min, studentInfo);
	
	//Open the output file
	//If the file cannot be opened, then display an error message.
	if ((pOutput = fopen(argv[2], "w")) == NULL)
	{
		printf("Can't open %s.\n", argv[2]);
		exit(1);
	}
	
	//Sort the class results that will be printed to the output file.
	//Here, qsort uses a function called "myComp" to compare the names of each student
	//and sort them alphabetically.
	qsort(studentInfo, count, sizeof(struct info), myComp);
	
	calculateGrades(count, studentInfo);
	printToOutputFile(pOutput, count, studentInfo);
	showClassData(count, &total, &max, &min);
	
	//Close the files
	fclose(pClassInfo);
	fclose(pOutput);	
	
	return 0;
}







