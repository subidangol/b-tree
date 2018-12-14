/*Team Supreme
  Main Program */

#include<iostream>
#include<fstream>
#include<string>
#include "BPlusTree.h"
#include "BPlusTree.cpp"

using namespace std;

char choice;

int main()
{
	int i, n;
	bool j;
	float t;
	BPlusTree b;
	char ch;
	string filename;

	ifstream infile;
	ofstream outfile;

	do
	{
		cout << "Enter the name of the input file: ";
		cin >> filename;
		infile.open(filename.c_str());
		if (!infile)				//If file doesn't exist, it exits the
								//program.
		{
			j=false;
			cout << "Error, could not open input file\n" << endl;
		}
		else
			j = true;
	} while (!j);

	infile.get(ch);     //to get int from the input file
	infile.get(ch);		//gets '|' and ignores it.


	while (!infile.eof())		//Reads until the end of file.
	{
		infile.get(ch);
		while (ch != '|')		//Unless '|' is found
		{
			infile.get(ch);
		}

		infile >> t;	//Gets any integer from the file.


		cout << t << endl;
		cout << "Inserting the value " << t << endl;
		b.Insert(t);

	}

	while (choice != 4)
	{
		cout << "Choose from the Menu Options" << endl;
		cout << " 1) Traverse \n 2) Insert \n 3) Delete \n 4) Exit" << endl;
		cin >> choice;
		switch (choice)
		{
			case'1':
				cout << "traversal of constructed tree\n";
				b.Display(b, cout);	//traverses the B+ Tree
				break;
			case'2':
				cout << "Insert new value \n";
				cin >> t;
				b.Insert(t);
				cout << t <<" inserted";
				break;
			case'3': /*delete*/
				printf("enter the value to be deleted");
				cin >> t;
				b.Delete(t);
				break;
			//case'4': /*Exit*/break;
			case'4': printf("Exit"); return 0; break;
			default: break;
		}
	}


	system("PAUSE");

	infile.close();		//Closes the input file

	system("PAUSE");

	return 0;
}
