#include <Python.h>
#include <iostream>		// Used for console input and output
#include <iomanip>		// Used for console output formatting
#include <fstream>		// Used for reading files
#include <string>

using namespace std;

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
// ADDED: Debugging and exception handling statements to help me understand what went wrong as I programmed and how this function operates and prevent the program from crashing suddenly
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");

	if (!pName) {
		cout << "pName: " << pName << endl;
		throw runtime_error("Error: pName is NULL!");
	}

	// Load the module object
	pModule = PyImport_Import(pName);

	if (!pModule) {
		cout << "pModule: " << pModule << endl;
		throw runtime_error("Error: pModule is NULL! This is likely because of a syntax error in the function being called.");
	}

	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);

	if (!pDict) {
		throw runtime_error("Error: pDict is NULL!");
	}


	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);

	if (!pFunc) {
		throw runtime_error("Error: pFunc is NULL!");
	}

	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	// Debugging
	if (!presult) {
		cout << "pFunc: " << pFunc << endl;
		cout << "pValue: " << pValue << endl;

		throw runtime_error("Error calling Python function with string parameter!");
	}

	return _PyLong_AsInt(presult);
}

// Display a menu to the console
void DisplayMenu() {
	cout << "---------------------------------------------------" << endl;
	cout << "1: Print the quantity of all items purchased" << endl;
	cout << "2: Print the quantity of a specific item purchased" << endl;
	cout << "3: Create an item quantity histogram as a file" << endl;
	cout << "4: Exit" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Enter a menu option (1, 2, 3, or 4): ";
}

// Get an item to lookup from user
string GetItemToLookup() {
	string itemToLookup = "";

	cout << "Enter the item to lookup: ";
	cin >> itemToLookup;
	cout << endl;

	return itemToLookup;
}

// Read from frequency.dat and print a histogram based on the file's data
void PrintItemHistogramFromFile() {
	int LIST_WIDTH = 25;						// Used for output formatting
	ifstream readFile;						// File to read from
	string itemName = "";					// Temporary read for the item's name
	int itemQuantity = 0;					// Temproary read for the item's quantity

	// Open the file
	readFile.open("frequency.dat");

	// Check to make sure the file was opened properly
	if (!readFile.is_open()) {
		throw runtime_error("Failed to open frequency.dat");
	}

	// Print the header
	cout << setfill('-') << setw(LIST_WIDTH) << "" << endl;
	cout << "Item(s) Sold:" << endl;
	cout << setw(LIST_WIDTH) << "" << setfill(' ') << endl;

	// Read file and print results to console
	while (!readFile.eof()) {
		readFile >> itemName >> itemQuantity;

		cout << left << setw(12) << itemName << "|";
		cout << setfill('*') << setw(itemQuantity) << "" << endl;
		cout << setfill(' ');
	}

	// Print the footer
	cout << setfill('-') << setw(LIST_WIDTH) << "" << setfill(' ') << endl;
}

// Main program entry point
int main()
{
	const int EXIT_PROGRAM = 4;			// Exit condition for the while loop
	int menuSelection = -1;					// Menu option from the user
	string itemToLookup = "";				// Item lookup from the user
	int itemCount = -1;						// Number of times a given item was sold

	// Color console
	system("color 9F");

	// Main program while loop
	// Loop until exit code is given by user
	while (menuSelection != EXIT_PROGRAM) {
		// Display the main menu to the user
		DisplayMenu();

		// Use exception handling
		try {
			// Get menu selection from user
			cin >> menuSelection;
			cout << endl;

			// Logic flow of menu input
			switch (menuSelection) {
				// Print the number of times every item was sold
				case 1:
					callIntFunc("PrintItemSaleFrequency", "");
					break;

				// Lookup a specific item and print the number of times it was sold
				case 2:
					// Get item to lookup from user
					itemToLookup = GetItemToLookup();
					// Lookup and return item count in Python
					// Returning and printing value in C++ because it is required in the guidelines/rubric
					// Otherwise, I would have printed directly in Python
					itemCount = callIntFunc("PrintItemSaleFrequency", itemToLookup);

					// Print item count
					cout << itemToLookup << ": " << itemCount << endl;
					break;

				// Create and print a histogram with the number of times of every item was sold
				case 3:
					callIntFunc("PrintItemSaleFrequency", "histogram");	// Function call to python
					PrintItemHistogramFromFile();									// Function call in C++
					break;

				// Exit the program
				case 4:
					// Go back to loop code condition check which will now be an exit code
					continue;

				// Any case unhandled was unexpected; Throw an error
				default:
					throw runtime_error("Error: Invalid menu input!");
			}

			// Allow for a pause to review the information selected
			// Then, clean up the screen
			cout << endl;
			system("pause");
			system("cls");
		}
		// Error catching
		catch (runtime_error exception) {
			string dump = "Not empty";				// Used to throw away garbage input

			// Bulletproofing! While the string keeps getting garbage results, keep dumping the input and reset the input stream to a good state.
			// This makes it so that even if multiple characters get input into the stream it gets cleaned properly
			while (dump != "") {
				cin.clear();
				getline(cin, dump);
				cout << '\n' << exception.what() << '\n' << endl;
			}
			system("pause");
			system("cls");
		}
		// Handle anything I missed or didn't expect
		catch (...) {
			cout << "Unknown error!" << endl;
		}
	}
	// Return program success
	return 0;
}