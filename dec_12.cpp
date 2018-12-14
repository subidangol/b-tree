#include <cstdlib>

#include <fstream>

#include <vector>

#include <iostream>

#include <string>

#include "BPlusTree.h"

#include <stdlib.h>

using namespace std;



int main()

{


	char filename[20], outputfilename[20] ;

	BPlusTree b;

	string data;

	char c;
	
	
	char choice;

	int index_count=0;

	int count=100;

	string record;

	char key[5];
	
	char newrecord_filename[20];
	
	bool index_set_flag=false; //index set already exist if false

	fstream infile1; //to read data file

	ifstream infile2; //to read index set if exists

	ofstream outfile; //to write to index set

	ifstream newrecord_file;
	
	ofstream newrecord_out;
	

	cout<<"Enter the name of the Record file: ";

	cin>>filename;

	infile1.open(filename);

	while(infile1.fail()) //trying to read the Record datafile

	{

		cout<<"Invalid !!!!!!!!"<<endl;

		cout<<"Enter the bloody filename with lots of data: ";

		cin>>filename;

		infile1.open(filename);

	}

	cout<<"Enter the name of the index set file: ";

	cin>>outputfilename;

	infile2.open(outputfilename);



	if(infile2.fail())	// checking if our index set exist

	{

		infile2.close();
		outfile.open(outputfilename);

		index_set_flag=true;	//we need to write index set to the output

	}

	int count_data;	//counter variable to count the number of data skipped while building sequence set
	if(index_set_flag)
	{
			//building new sequence set or index set
		
		getline(infile1,record);
		outfile<<"int";

		while(!infile1.eof())

		{

			

			getline(infile1,record);
			//cout<<record<<endl;

			for(int i=0; i<5; i++) {key[i]=record[i];}
			
			cout<<key;

			outfile<<"|"<<key<<count;
			count_data=1;
			for(int j=0; j<4; j++)

			{
				
				getline(infile1,record);	
				if(!infile1.eof())
					count_data++;
				else
					break;
				
			}
			if(!infile1.eof())
					count++;
			

		}
		outfile<<"|"<<endl;
		outfile.close();
		infile2.open(outputfilename);
	}
	
	long i, n;

	bool j;

	long t;

	char ch;
	
	infile2.get(ch);     //to get int from the input file

	infile2.get(ch);		//gets '|' and ignores it.





		while (!infile2.eof())		//Reads until the end of file.

		{

			infile2.get(ch);

			while (ch != '|')		//Unless '|' is found

			{

				infile2.get(ch);

			}



			infile2 >> t;	//Gets any integer from the file.





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
					cout << "Enter a filename having new records \n";
					cin>>newrecord_filename;
					//cin >> t;	// it takes long values
					
					newrecord_file.open(newrecord_filename);//reading from the new record file actually opening the new record file to read from it
					//infile1.close();
					//infile1.open(filename); //was trying to open the previous record file to write on it
					while(!newrecord_file.eof())
					{
						getline(newrecord_file,record);
						
						infile1<<record;	//updating our record file
						
						for(int i=0; i<5; i++) {key[i]=record[i];}
						if(count_data==5)
						{	
							count++;
							t=atol(key);
							t=t*1000+count;
							b.Insert(t);
						}
						else
							count_data++;
					}
				
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
		


	return 0;

}