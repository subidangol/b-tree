#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main()
{
	BPlusTree b;
	char filename[20];           //for data file
	char indexfilename[20];      //for index file
	char newfilename[20];        //for new data file
	char choice;                 //stores the user commands
	char key[5];                 //stores the zipcode
	char ch;                     //get each character for new data file
	string record;               //get the line for the data file
	int count_data;
	int count = 100;
	long t;
	bool index_set_flag = false; //index set already exist if false
	fstream infile1;             //to read and update data file
	ifstream infile2;            //to read index set if exists
	ofstream outfile;            //to write to index set
	ifstream newrecord_file;
	ofstream newrecord_out;

	cout << "Enter the name of the record file: ";
	cin >> filename;
	infile1.open(filename);
	while (infile1.fail()) //trying to read the Record datafile
	{
		cout << "Invalid. Enter the name of the record file: ";
		cin >> filename;
		infile1.open(filename);
	}
	cout << "Enter the name of the index set file: ";
	cin >> indexfilename;
	infile2.open(indexfilename);

	if (infile2.fail())	//if indexset does not exist, create a new one
	{
		infile2.close();
		outfile.open(indexfilename); //new index set opened
		index_set_flag = true; //we need to write index set to the new indexset file
	}

	if (index_set_flag)
	{
		getline(infile1, record);
		outfile << "int";
		while (!infile1.eof())
		{
			getline(infile1, record);

			for (int i = 0; i < 5; i++) 
			{ 
				key[i] = record[i]; 
			}

			cout << key;
			outfile << "|" << key << count;
			count_data = 1;
			for (int j = 0; j < 4; j++)
			{
				getline(infile1, record);
				if (!infile1.eof())
					count_data++;
				else
					break;
			}

			if (!infile1.eof())
				count++;
		}
		outfile << "|" << endl;
		outfile.close();
		infile2.open(indexfilename);
	}


	infile2.get(ch);        //to get int from the input file
	infile2.get(ch);		//gets '|' and ignores it.

	while (!infile2.eof())		//Reads until the end of file.
	{
		infile2.get(ch);
		while (ch != '|')		//Unless '|' is found
		{
			infile2.get(ch);
		}

		infile2 >> t;	//Gets any integer from the file.
		cout << "Inserting the value " << t << endl;
		b.Insert(t);
	}

	while (choice != 4)
	{
		cout << "\nChoose from the Menu Options" << endl;
		cout << " d -- Display \n i v -- Insert \n d v -- Delete \n 4)e -- Exit\n" << endl;
		cin >> choice;
		switch (choice)
		{
			case'd':
				cout << "Displays the data by traversing the constructed tree\n";
				b.Display(b, cout);	//traverses the B+ Tree
				break;
			case'i':
				cout << "Enter a filename having new records \n";
				cin >> newfilename;
				newrecord_file.open(newfilename); //reading from the new record file

				while (!newrecord_file.eof())
				{
					getline(newrecord_file, record);
					infile1 << record;
					for (int i = 0; i < 5; i++) 
						key[i] = record[i]; 

					if (count_data == 5)
					{
						count++;
						t = atol(key) * 1000 + count;
						b.Insert(t);
					}
					else
						count_data++;
				}
				break;

			case'4': /*Delete after a value has been entered*/
				printf("Enter the value to be deleted");
				cin >> t;
				b.Delete(t);
				break;

			case'4': /*Exit from the program*/
				printf("Exit");  
				break;

			default: break;
		}
	}
	return 0;
}
