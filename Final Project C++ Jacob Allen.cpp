//program designed for elementary teachers
//to enter in names of students and test scores
//and the names and scores stored into a seperate
//txt file, the teachers can then view, edit, or create new
//data to input into the file.
//created by Jacob Allen on November 21, 2016
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

//function prototypes

void enterNew();
void viewCurrent();
void editCurrent();

int main(int argc, char *argv[]) {
	//selection variable
	int choice = 0;
	
	cout << "Menu: Enter 1 to create a new class entry, enter 2 to view current class entries, enter 3 to edit current class entries, or enter -1 to end the program: ";
	cin >> choice;
	while (choice != -1) {
		if (choice == 1) 
		{
			enterNew();
		}//end if
		else if (choice == 2)
		{
			viewCurrent();
		}//end else if
		else if (choice == 3)
		{
			editCurrent();
		}//end else if
		else
			cout << "Invalid entry." << endl;
		cout << endl << "Menu: Enter 1 to create a new class entry, enter 2 to view current class entries, enter 3 to edit current class entries, or enter -1 to end the program: ";
		cin >> choice;
	}
}//end main

void enterNew()
{
	//declare variables for class input
	string names = " ";
	string cNum = " ";
	//declare file
	ofstream outFile;
	outFile.open("/Volumes/JSCHOOLDR/Final Project C++ Jacob Allen/Final Project C++.txt", ios::app);
	
	if (outFile.is_open() && cNum != "-1")
	{
		int x = 0;
		int y = 0;
		
		cout << "Please enter the name or number of this class. (-1 to return to menu): ";
		cin >> cNum;
		
		cout << "How many students are in the class? ";
		cin >> x;
		cin.ignore(); //ignores the /n character
		
		cout << "Please enter in each of the students names followed by their test score. (i.e. First Last 91): " << endl;
		string students[60] = {""};									//we store the students in an array and import the area to the txt file
		string name = "";
		string score = "";
		
		outFile << "Class " << cNum << endl << " " << endl;
			for (y = 1; y < x + 1; y += 1)
			{
				getline(cin, students[y]);
				outFile << students[y] << endl;
			}//end for
		outFile << " " << endl;
		outFile.close();
	}//end if
	else
		cout << "The file was not opened properly." << endl;
	
}//end enterNew

void viewCurrent()
{
	bool check = false;		//to verify the class name or number actually exists
	string num = "";
	string line = "";
	string classNum = "";
	
	//declare file
	ifstream inFile;
	
	cout << "Which class name or number would you like to view? (-1 to end): ";
	cin >> num;
	
	while (num != "-1")
	 {	
		inFile.open("/Volumes/JSCHOOLDR/Final Project C++ Jacob Allen/Final Project C++.txt");
		
		while (inFile.is_open() && num != "-1" && !inFile.eof()) 
		{
			getline (inFile, line, ' ');
			getline (inFile, classNum);
			
			if (line == "Class" && classNum == num) 
			{
				check = true;
				getline (inFile, line, ' ');
				getline (inFile, classNum);
				while (line != "Class" && !inFile.eof())
				{
					cout << line << " " << classNum << endl;
					getline (inFile, line, ' ');
					getline (inFile, classNum);
				}
			}
		}//end while
		inFile.close();
		
		if (check == false)
		{
			cout << "Invalid class selection. ";
		}//end if
		
		cout << endl << "Which class name or number would you like to view? (-1 to end): ";
		cin >> num;
		
	}//end while
	
}//end viewCurrent

void editCurrent() 
{
	string num = "";
	string line = "";
	string classNum = "";
	string edit = "";
	string file = "";
	//declare file
	ifstream inFile;
	
	cout << "Which class name or number would you like to edit? (-1 to end): ";
	cin >> num;
		
	while (num != "-1") 
	{	
		inFile.open("/Volumes/JSCHOOLDR/Final Project C++ Jacob Allen/Final Project C++.txt");
		
		while (inFile.is_open() && num != "-1" && !inFile.eof()) 
		{
			getline (inFile, line, ' ');
			getline (inFile, classNum);
			edit = "Class " + num + "\n \n";
			if (line == "Class" && classNum == num) 
			{
				getline (inFile, line, ' ');
				getline (inFile, classNum);
				while (line != "Class" && !inFile.eof())
				{
					if (line != "") {
						cout << line << " " << classNum << endl;
						
					}
					getline (inFile, line, ' ');
					getline (inFile, classNum);
				}
		}//end if
		}//end while
		inFile.close();
		inFile.open("/Volumes/JSCHOOLDR/Final Project C++ Jacob Allen/Final Project C++.txt");

		while (inFile.is_open() && !inFile.eof()) 
		{
			getline (inFile, line);
			file += line + "\n";		//stores every line of the txt file into a string (very big string)
		}//end while
		inFile.close();		//close file
		
		cin.ignore();
		cout << "What name would you like to edit: ";
		getline(cin, num);
		
		int index1 = file.find(num, 0);
		int index2 = file.find("\n", index1);
		string sub = file.substr(index1, index2-index1);
		
		cout << "What corrections would you like to make? Re-enter the name and score: ";			//corrections
		getline(cin, num);
		
		cout << "You want to change '" << sub << "' to '" << num << "', correct? (Y or N) " << endl;			//verification
		sub = num;
		cin >> num;
		
		if (num == "Y")
		{
			file.replace(index1, index2-index1, sub);
		}
		ofstream outFile;
		outFile.open("/Volumes/JSCHOOLDR/Final Project C++ Jacob Allen/Final Project C++.txt");
		outFile << file; 	//imports the "very big string" into the text file, replacing all current data
		
		cout << endl << "Which class name or number would you like to edit? (-1 to end): ";
		cin >> num;
		outFile.close()
		
	}//end while
}//end editCurrent