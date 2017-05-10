/**********************************************************\
* Project Type  : Win32 Console Application                *
* Project Name  : C_Lab2                                   *
* File Name     : Source.cpp                               *
* Programmer(s) : Азеева Е.Р. & Князев А.С.                *
* Created       : 11/04/17                                 *
* Last Revision : 08/05/17                                 *
* Comment(s)    :                                          *
*----------------------------------------------------------*
*  Кафедра 302            Курс: ИНФОРМАТИКА   II семестр   *
*  Задание 4     Двумерные массивы                         *
*----------------------------------------------------------*
*                      ВАРИАНТ № 8                         *
*   Дана целочисленная «квадратная матрица. Определить     *
*   1. Произведение положительных элементов матрицы,       *
* которые расположены над побочной диагональю              *
*   2. Максимум среди сумм по строкам нечетных элементов   *
* матрицы Используя универсальные для различных наборов    *
* исходных данных подпрограммы реализовать данный алгоритм *
* для заданных матриц. A(N,N), В(М,М). В качестве одного   *
* из вариантов исходных данных принять- N=7, М=9 Чтение    *
* данных их файла производить с использованием функций     *
* ввода/вывода языка C++ Алгоритм должен быть              *
* параметризован, обмен данными с подпрограммой должен     *
* осуществляться только через параметры, каждый из наборов *
* исходных данных хранится в отдельном файле. Реализовать  *
* программу в двух вариантах в первом - при обращении к    *
* элементам массива использовать индексы, во втором -      *
* работать с массивом через указатели                      *
\**********************************************************/

#include <iostream>	
#include <fstream>

using namespace std;

// ------------ Constants ------------ //
const int N_MAX = 10;  // Maximal length of row or column.
const char INPUT_FILE_NAME[] = "KTest1.txt";  // Input file name.

// ------------ Prototypes ------------ //
// Inputs matrix. Returns error code.
int InputMatrix(
	const char *INPUT_FILE_NAME, // File name.   Input.
	int matrix[][N_MAX],         // Matrix.      Output.
	int *n                       // Matrix size. Output.
);

// Prints matrix.
void PrintMatrix(
	int matrix[][N_MAX], // Matrix.      Input.
	int n                // Matrix size. Input.
);

// Prints error message.
void PrintMessage(
	int errorCode,       // Error code. Input.
	const char* fileName // File name.  Input.
);

// Returns product of positive elements above side diagonal of matrix.
int GetProduct(
	int matrix[][N_MAX], // Matrix.      Input.
	int n                // Matrix size. Input.
);

// Returns maximum of sums of odd elements in rows.
int GetMaxSumsOddEementsInRows(
	int matrix[][N_MAX], // Matrix.      Input.
	int n                // Matrix size. Input.
);

// Returns sum of odd elements in row.
int GetSumOddEementsInRow(
	int matrix[][N_MAX], // Matrix.               Input.
	int n,               // Matrix size.          Input.
	int row              // Number of row to sum. Input.
);

// ------------ Implementations ------------ //
// Entry point.
int main()
{
	//----- VARIABLES ------
	int n;        // Matrix size.
	int errorCode;// Error code.
	int product;  // Product of positive elements above side diagonal.
	int matrix[N_MAX][N_MAX];	// Initial matrix.

	//----- PROGRAMM ------
	// Read matrix from file.
	errorCode = InputMatrix(INPUT_FILE_NAME, matrix, &n);

	// If error.
	if (errorCode != 0)
	{
		PrintMessage(errorCode, INPUT_FILE_NAME);

		cin.clear(); 
		cin.get();

		return errorCode;
	} // end if

	// Print matrix.
	cout << "INITIAL MATRIX:" << endl << endl;
	PrintMatrix(matrix, n);
	cout << endl;

	cout << "MATRIX SIZE: " << n << "x" << n << endl << endl;

	// Part 1 :
	// Find product of positive elements above side diagonal of matrix.
	product = GetProduct(matrix, n);

	if (product != 0)
	{
		cout << "Product of positive elements above side diagonal = "
			<< product << endl << endl;
	}
	else {
		cout << "There are no positive elements above side diagonal." << endl << endl;
	} // end if

	// Part 2 :
	// Find maximum of sums of odd elements.
	cout << "Max sum odd elements from row = "
		<< GetMaxSumsOddEementsInRows(matrix, n)
		<< endl;

	cin.clear();
	cin.get();

	return 0;

} //end main()

// Inputs matrix. Returns error code.
int InputMatrix(
	const char *INPUT_FILE_NAME, // File name.   Input.
	int matrix[][N_MAX],         // Matrix.      Output.
	int *n                       // Matrix size. Output.
) {

	//----- VARIABLES ------
	int i, j;  // For loops.
	ifstream fin(INPUT_FILE_NAME);  // Open file.

	//----- PROGRAMM ------
	// If file not exists.
	if (!fin)
	{
		fin.close();
		return 1;
	}// end if
	// If file is empty.
	if (fin.peek() == EOF) 
	{
		fin.close();
		return 2;
	}// end if

	// Read size of matrix.
	fin >> *n;

	// If matrix size more than N_MAX.
	if (*n > N_MAX)
	{
		return 3;
	}// end if
	// If matrix size less or equal.
	if (*n <= 0)
	{
		return 4;
	}// end if

	// Read matrix.
	// Read rows.
	for (i = 0; i < *n; i++)
	{
		// Read elements in row.
		for (j = 0; j < *n; j++)
		{
			//#    fin >> *(*(matrix +i)+j);
			/*#*/	fin >> matrix[i][j];
		}// end for j
	}// end for i

	return 0;
}//end InputMatrix()

 // Prints matrix.
void PrintMatrix(
	int matrix[][N_MAX], // Matrix.      Input.
	int n                // Matrix size. Input.
) {
	//----- VARIABLES ------
	int i, j;  // For loops.

	//----- PROGRAMM ------
	// Rows loop.
	for (i = 0; i < n; i++)
	{
		// Elements of row loop.
		for (j = 0; j < n; j++)
		{
			//#cout << *(*(matrix +i)+j) << "  ";
			/*#*/	cout << matrix[i][j] << "  ";
		}//for j

		cout << endl;
	}//for i

}  //end PrintMatrix()

// Prints error message.
void PrintMessage(
	int errorCode,       // Error code. Input.
	const char* fileName // File name.  Input.
) {
	switch (errorCode)
	{
	case 1:
		cout << "Input file: " << fileName << " not exist.";
		break;
	case 2:
		cout << "Input file: " << fileName << " is empty.";
		break;
	case 3:
		cout << "Matrix size couldn't be more than " << N_MAX << ".";
		break;
	case 4:
		cout << "Matrix size couldn't negative or equal zero.";
		break;
	default:
		cout << "Unknown error code: " << errorCode << " .";
	}
} // end PrintMessage()

// Returns product of positive elements above side diagonal of matrix.
int GetProduct(
	int matrix[][N_MAX], // Matrix.      Input.
	int n                // Matrix size. Input.
) {
	//----- VARIABLES ------
	int result = 1; // Result of multiplication.
	int i, j;       // For loops.
	int HasPositive = 0; // Matrix has positive elements? 1 - Has. 0 - Has not.

	//----- PROGRAMM ------
	// Rows loop. 
	for (i = 0; i < n - 1; i++)
	{
		// Elements of row loop.
		for (j = 0; j < n - i - 1; j++)
		{
			// If element is positive.
			//#if (*(*(matrix +i)+j) > 0)
			/*#*/ if (matrix[i][j] > 0)
			{
				HasPositive = 1;
				//#result *= *(*(matrix +i)+j);
				/*#*/	result *= matrix[i][j];
			}// end if
		}// end for j
	}// end for i

	// Returns [result] if matrix has positive elements 
	// otherwise returns 0.
	return HasPositive*result;

} //end GetProduct()

 // Returns maximum of sums of odd elements in rows.
int GetMaxSumsOddEementsInRows(
	int matrix[][N_MAX], // Matrix.      Input.
	int n                // Matrix size. Input.
) {
	//----- VARIABLES ------
	int i;   // For loop.
	int sum; // For sum.
	int maxSum; // Maximal sum.

	//----- PROGRAMM ------
	// Find sum in first row.
	maxSum = GetSumOddEementsInRow(matrix, n, 0);

	// Rows loop. 
	for (i = 1; i < n; i++)
	{
		// Find sum in i-ish row.
		sum = GetSumOddEementsInRow(matrix, n, i);

		// If current sum bigger than saved - save current sum.
		if (sum > maxSum)
		{
			maxSum = sum;
		} // end if
	} // end for i

	return maxSum;
}//end GetMaxSumsOddEementsInRows()

 // Returns sum of odd elements in row.
int GetSumOddEementsInRow(
	int matrix[][N_MAX], // Matrix.               Input.
	int n,               // Matrix size.          Input.
	int row              // Number of row to sum. Input.
) {
	//----- VARIABLES ------
	int j; // For loop.
	int sum = 0; // For sum.

	//----- PROGRAMM ------
	// Elements in row loop.
	for (j = 0; j < n; j++)
	{
		// If element is odd.
		//# if (1 == *(*(matrix +row)+j) % 2)
		/*#*/ if (1 == matrix[row][j] % 2)
		{
			//#sum += *(*(matrix +row)+j);
			/*#*/		sum += matrix[row][j];
		} // end if
	} // end for j

	return sum;
} // end GetSumOddEementsInRow()
