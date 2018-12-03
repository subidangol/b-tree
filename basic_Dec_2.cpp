#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;


int main()
{
	char zipcode[5];
	char filename[20], outputfilename[20];
	std::vector <string> indexset;
	string data;
	char c;
	int index_count=0;
	bool index_set_flag=false; //index set already exist if false
	ifstream infile1; //to read data file
	ifstream infile2; //to read index set if exists
	ofstream outfile; //to write to index set
	
	cout<<"Enter the name of the data file: ";
	cin>>filename;
	infile1.open(filename);

	if(!infile1.fail()) //trying to read the bloody datafile
	{
		cout<<"Invalid !!!!!!!!"<<endl;
		cout<<"Enter the bloody filename with lots of data: ";
		cin>>filename;
		infile1.open(filename);
	}
	
	cout<<"Enter the name of the output file: ";
	cin>>outputfilename;
	infile2.open(outputfilename);
	
	if(!infile2.fail())	// checking if our index set exist
	{
		outfile.open(outputfilename);
		index_set_flag=true;	//we need to write index set to the output
	}
	
	if(index_set_flag)	//copying the index set to the file
	{
		while(!outfile.eof())	//reading the existed index set into a local vector indexset
		{
			for(int i=0; i<8; i++)	
			{
				infile2.get(c);
				data+=c;
			}
			indexset[index_count]=data;
			data="";
			index_count++;
		}
		for(int i=0; i<indexset.size(); i++)
		{
			outfile<<indexset[i];
		}
	}
		
	return 0;
}
