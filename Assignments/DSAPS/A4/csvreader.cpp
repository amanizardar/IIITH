#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void readCSV(istream &input, vector< vector<string> > &output)
{
   string csvLine;
    // read every line from the stream
    while( getline(input, csvLine) )
    {
            istringstream csvStream(csvLine);
           vector<string> csvColumn;
            string csvElement;
            // read every element from the line that is seperated by commas
            // and put it into the vector or strings
            while( getline(csvStream, csvElement, ',') )
            {
                    csvColumn.push_back(csvElement);
            }
            output.push_back(csvColumn);
    }
}

int main()
{
    ofstream myfile;
    myfile.open ("ab.txt");
    string a;
    fstream file("input.txt", ios::in);
   
    if(!file.is_open())
    {
           cout << "File not found!\n";
            return 1;
    }
    // typedef to save typing for the following object
    typedef vector< vector<string> > csvVector;
    csvVector csvData;

    readCSV(file, csvData);
    // print out read data to prove reading worked
    for(csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
    {
            for(vector<string>::iterator j = i->begin(); j != i->end(); ++j)
            {
          a=*j;
                  
        //   myfile <<a<<",";
          myfile <<a<<" ";


 }
 myfile <<"\n";
 cout << "\n";
 }
 myfile.close();


}