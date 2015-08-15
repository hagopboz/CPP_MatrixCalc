#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

void displayMenu();
void displayMatrix(int**, int, int);//Matrix
void fillMatrix(int**, int, int);
void deleteMatrix(int**, int);
int **createMatrix(int, int);//Row, Col
int **multiplyMatricies(int**, int**, int, int, int, int);//M1, M2
int **addMatricies(int**, int**, int, int, int, int);//M1, M2
int **scalarMultiply(int**, int, int, int);
int **subtractMatricies(int**, int**, int, int, int, int);//M1, M2

int main()
{
	//Choice for the beginning
	int beginning = 0;
	do
	{
		cout << "-----WELCOME TO MATRIX CALCULATOR-----" << endl;
		cout << "(1) Manual input" << endl;
		cout << "(2) File input" << endl;
		cin >> beginning;
	}	while(beginning != 1 && beginning != 2);


	int **matrixOne;
	int **matrixTwo;
	int rowMatrix1 = 0, rowMatrix2 = 0, colMatrix1 = 0, colMatrix2 = 0;
	
	if(beginning == 1)			//User defined matrix
	{


		cout << "Enter Matrix 1 row size: ";
		cin >> rowMatrix1;
		cout<< "Enter Matrix 1 column size: ";
		cin >> colMatrix1;

		cout << "Enter Matrix 2 row size: ";
		cin >> rowMatrix2;
		cout << "Enter Matrix 2 column size: ";
		cin >> colMatrix2;

		matrixOne = createMatrix(rowMatrix1, colMatrix1);
		matrixTwo = createMatrix(rowMatrix2, colMatrix2);
	
		fillMatrix(matrixOne, rowMatrix1, colMatrix1);
		cout << endl;
		fillMatrix(matrixTwo, rowMatrix2, colMatrix2);
	}
	
	if(beginning == 2)			//Matrix read from file
	{
		//Clear cin
		cin.sync();
		cin.clear();
		
		system("cls");
		//Tell user how file should be formatted
		cout << "File format: " << endl;
		cout << "[rows]x[columns]" << endl;
		cout << "element element element" << endl;
		cout << "element element element" << endl;
		cout << "[rows]x[columns]" << endl;
		cout << "element element element" << endl;
		cout << "element element element" << endl;

		string filename;
		cout << "What is the filename: ";
		getline(cin, filename);
		ifstream inputFile(filename);
		if(inputFile.fail())
		{
			cout << "File not found" << endl;
			system("pause");
			return 0;
		}
		
		string line;
		do
		{
			getline(inputFile, line);
			if(line == "")
				continue;
			if(line.find('x') && line.find('X'))	//Check if dimension line
			{
				if(rowMatrix1 == 0)					//Set up matrixOne
				{
					rowMatrix1 = atoi(line.substr(0, 1).c_str());			//Take the first number
					colMatrix1 = atoi(line.substr(2, 3).c_str());			//Take the second number
					matrixOne = createMatrix(rowMatrix1, colMatrix1);

					for(int ndx = 0; ndx < rowMatrix1; ndx++)
					{
						getline(inputFile, line);
						for(int mdx = 0; mdx < colMatrix1; mdx++)
						{
							*(*(matrixOne + ndx) + mdx) = atoi(line.substr(0, 1).c_str());		//Add number to matrix
							if(mdx == colMatrix1 - 1)
							{
								continue;
							}
							else
							{
								line = line.substr(2, line.length());		//Alter line for next iteration
							}
						}
					}
				}
				else
				{
					rowMatrix2 = atoi(line.substr(0, 1).c_str());			//Take first number
					colMatrix2 = atoi(line.substr(2, 3).c_str());			//Take next number
					matrixTwo = createMatrix(rowMatrix2, colMatrix2);

					for(int ndx = 0; ndx < rowMatrix2; ndx++)
					{
						getline(inputFile, line);
						for(int mdx = 0; mdx < colMatrix2; mdx++)
						{
							*(*(matrixTwo + ndx) + mdx) = atoi(line.substr(0, 1).c_str());		//Add number to matrix
							if(mdx == colMatrix2 - 1)
								continue;
							else
								line = line.substr(2, line.length());		//Alter line for next iteration
						}
					}
				}
			}
		}	while(!inputFile.eof());

		inputFile.close();
	}
	
	system("cls");
	
	//Show users the matricies
	cout << "Matrix 1:\n";
	displayMatrix(matrixOne, rowMatrix1, colMatrix1);
	cout << "Matrix 2:\n";
	displayMatrix(matrixTwo, rowMatrix2, colMatrix2);

	//Get ready for newly created matrix from operations
	int **matrixThree = NULL;

	int choice = 5;
	do
	{
		displayMenu();
		cin >> choice;
		switch(choice)
		{
		case 0:
			break;
		case 1:
			system("cls");
			matrixThree = addMatricies(matrixOne, matrixTwo, rowMatrix1, rowMatrix2, colMatrix1, colMatrix2);
			cout << "Result:\n";
			displayMatrix(matrixThree, rowMatrix1, colMatrix2);
			break;
		case 2:
			system("cls");
			matrixThree = subtractMatricies(matrixOne, matrixTwo, rowMatrix1, rowMatrix2, colMatrix1, colMatrix2);
			cout << "Result:\n";
			displayMatrix(matrixThree, rowMatrix1, colMatrix2);
			break;
		case 3:
			system("cls");
			matrixThree = multiplyMatricies(matrixOne, matrixTwo, rowMatrix1, rowMatrix2, colMatrix1, colMatrix2);
			cout << "Result:\n";
			displayMatrix(matrixThree, rowMatrix1, colMatrix2);
			break;
		case 4:
			system("cls");
			int quotient;
			cout << "Input scalar: ";
			cin >> quotient;
			int which;
			cout << "Matrix 1 or 2: ";
			cin >> which;
			if(which == 1)
			{
				matrixThree = scalarMultiply(matrixOne, rowMatrix1, colMatrix1, quotient);
				cout << "Result:\n";
				displayMatrix(matrixThree, rowMatrix1, colMatrix1);
			}
			else if(which == 2)
			{
				matrixThree = scalarMultiply(matrixTwo, rowMatrix2, colMatrix2, quotient);
				cout << "Result:\n";
				displayMatrix(matrixThree, rowMatrix2, colMatrix2);
			}
			else
				cout << "Invalid selection, please try again." << endl;
			break;
		case 5:
			system("cls");
			int ch;
			cout << "Display which matrix?(1, 2, 3, 4 for all)" << endl;
			cin >> ch;
			switch(ch)
			{
			case 1:
				cout << "Matrix 1: " << endl;
				displayMatrix(matrixOne, rowMatrix1, colMatrix1);
				system("pause");
				break;
			case 2:
				cout << "Matrix 2: " << endl;
				displayMatrix(matrixTwo, rowMatrix2, colMatrix2);
				system("pause");
				break;
			case 3:
				if(matrixThree == NULL)
					break;
				cout << "Matrix 3: " << endl;
				displayMatrix(matrixThree, rowMatrix1, colMatrix2);
				system("pause");
				break;
			case 4:
				displayMatrix(matrixOne, rowMatrix1, colMatrix1);
				displayMatrix(matrixTwo, rowMatrix2, colMatrix2);
				if(matrixThree == NULL)
				{
					system("pause");
					break;
				}
				else
				{
					displayMatrix(matrixThree, rowMatrix1, colMatrix2);
					system("pause");
				}
				break;
			default:
				break;
			}
		default:
			system("cls");
			break;
		}
	}	while(choice != 0);

	

	deleteMatrix(matrixOne, rowMatrix1);
	deleteMatrix(matrixTwo, rowMatrix2);
	if(matrixThree != NULL)
		deleteMatrix(matrixThree, rowMatrix1);
	
	if(matrixOne != NULL)
		return 1;
	if(matrixTwo != NULL)
		return 1;
	return 0;
}

/*
 * Shows the "main menu"
 */
void displayMenu()
{
	cout << "(0) Exit" << endl;
	cout << "(1) Add Matricies" << endl;
	cout << "(2) Subtract Matricies" << endl;
	cout << "(3) Multiply Matricies" << endl;
	cout << "(4) Scalar Multiplication" << endl;
	cout << "(5) Display Matrix" << endl;

	return;
}


/*
 * Display the matrix
 */
void displayMatrix(int **matrix, int row, int col)
{
	if(matrix == NULL)
		return;
	for(int ndx = 0; ndx < row; ndx++)
	{
		cout << "[\t";
		for(int mdx = 0; mdx < col; mdx++)
		{
			cout << *(*(matrix + ndx) + mdx) << "\t";
		}
		cout << "]" <<endl;
	}
	cout << endl;
	return;
}

/*
 * Gets user input to fill the matrix
 */
void fillMatrix(int **matrix, int row, int col)
{
	for(int ndx = 0; ndx < row; ndx++)
	{
		for(int mdx = 0; mdx < col; mdx++)
		{
			cout  << "Element for " << ndx + 1 << ", " << mdx + 1 << ": ";
			cin >> *(*(matrix + ndx) + mdx);
		}
	}
	return;
}


/*
 * Releases memory back to system
 */
void deleteMatrix(int **matrix, int row)
{
	for(int ndx = 0; ndx < row; ndx++)
		delete [] matrix[ndx];
	delete [] matrix;
	matrix = NULL;
	return;
}


/*
 * Initializes matrix
 */
int **createMatrix(int row, int col)
{
	int **matrix = new int*[row];
	for(int ndx = 0; ndx < row; ndx++)
		matrix[ndx] = new int[col];
	return matrix;
}

/*
 * Performs matrix addition
 */
int **addMatricies(int **matrixOne, int **matrixTwo, int rowMatrix1, int rowMatrix2, int colMatrix1, int colMatrix2)
{
	if(rowMatrix1 != rowMatrix2)
	{
		cout << "Matricies could not be added." << endl;
		cout << "Rows were not equal." << endl;
		return NULL;
	}
	else if(colMatrix1 != colMatrix2)
	{
		cout << "Matricies could not be added." << endl;
		cout << "Columns were not equal." << endl;
		return NULL;
	}
	int **returnMatrix = createMatrix(rowMatrix1, colMatrix2);

	for(int ndx = 0; ndx < rowMatrix1; ndx++)
	{
		for(int mdx = 0; mdx < colMatrix2; mdx++)
		{
			
			*(*(returnMatrix + ndx) + mdx) = *(*(matrixOne + ndx) + mdx) + *(*(matrixTwo + ndx) + mdx);
		}
	}
	return returnMatrix;
}

/*
 * Performs matrix multiplication
 */
int **multiplyMatricies(int** matrix1, int** matrix2, int rowM1, int rowM2, int colM1, int colM2)
{
	if(rowM1 != colM2)
	{
		cout << "Matricies could not be multiplied." << endl;
		cout << "Matrix 1 rows not equal to Matrix 2 columns." << endl;
		return NULL;
	}
	else if(rowM2 != colM1)
	{
		cout << "Matricies could not be multiplied." << endl;
		cout << "Matrix 1 columns not equal to Matrix 2 rows." << endl;
		return NULL;
	}

	int **returnMatrix = createMatrix(rowM1, colM2);
	
	for(int ndx = 0; ndx < rowM1; ndx++)
	{
		for(int mdx = 0; mdx < colM2; mdx++)
		{
			int tmp = 0, counter = 0;
			do
			{
				tmp += (*(*(matrix1 + ndx) + counter) * (*(*(matrix2 + counter) + mdx)));
				counter++;
			}	while(counter < colM2);

			*(*(returnMatrix + ndx) + mdx) = tmp;
		}
	}

	return returnMatrix;
}

/*
 * Performs scalar multiplication
 */
int  **scalarMultiply(int **matrix, int row, int col, int quotient)
{
	int **returnMatrix = createMatrix(row, col);

	for(int ndx = 0; ndx < row; ndx++)
	{
		for(int mdx = 0; mdx < col; mdx++)
		{
			
			*(*(returnMatrix + ndx) + mdx) = *(*(matrix + ndx) + mdx) * quotient;
		}
	}

	return returnMatrix;
}

/*
 * Performs matrix suhbtraction
 */
int **subtractMatricies(int **matrixOne, int **matrixTwo, int rowMatrix1, int rowMatrix2, int colMatrix1, int colMatrix2)
{
	if(rowMatrix1 != rowMatrix2)
	{
		cout << "Matricies could not be subtracted." << endl;
		cout << "Rows were not equal." << endl;
		return NULL;
	}
	else if(colMatrix1 != colMatrix2)
	{
		cout << "Matricies could not be subtracted." << endl;
		cout << "Columns were not equal." << endl;
		return NULL;
	}
	int **returnMatrix = createMatrix(rowMatrix1, colMatrix2);

	for(int ndx = 0; ndx < rowMatrix1; ndx++)
	{
		for(int mdx = 0; mdx < colMatrix2; mdx++)
		{
			
			*(*(returnMatrix + ndx) + mdx) = *(*(matrixOne + ndx) + mdx) - *(*(matrixTwo + ndx) + mdx);
		}
	}
	return returnMatrix;
}