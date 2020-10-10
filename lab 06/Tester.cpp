//Main Program to test Binary Search Tree functions
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "myBinarySearchTree_z870z666.hpp"
using namespace std;
int main(int argc, char* argv[]) 
{ 
if(argc != 3)
    {
        std::cout << "You have to provide one test instance file and output file name to run the test main!\n";
        return 0;
    }

//File Intiallization for input and output files
ifstream inFile;
ifstream inFile1;
inFile.open(argv[1]);
ofstream outfile (argv[2]);

//Open input and out file and sstart with hash table methods
if(inFile.is_open() and outfile.is_open())

  {
    int num;
//Binary search tree object with <int> as templete type
    myBinarySearchTree<int> BST;
    while(!inFile.eof())
    {
         inFile >> num;
/**
*  @Pre  A new instance has been read from input file
*  @Post Add the input instance from input file into BST using insert
*/
         BST.insert(num);
    }
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints all the elements of BST in InOrder to output file
*/  
   cout<<"----------------nmd1----------------------\n";

   BST.printTreeInorder(outfile);
   cout<<"----------------nmd2----------------------\n";
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints minimum element of BST to output file
*/ 
  cout<<"----------------nmd3----------------------\n";
   outfile <<BST.findMin() <<"\n";
   cout<<"----------------nmd4----------------------\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints maximum element of BST to output file
*/
cout<<"----------------nmd5----------------------\n";
   outfile<<BST.findMax() <<"\n";
   cout<<"----------------nmd6----------------------\n";
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints all the elements of BST in PostOrder to output file
*/ 
cout<<"----------------nmd7----------------------\n";
   BST.printTreePostorder(outfile);
   cout<<"----------------nmd8----------------------\n";
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Prints all the elements of BST in PreOrder to output file
*/
cout<<"----------------nmd9----------------------\n";
   BST.printTreePreorder(outfile);
   cout<<"----------------nmd10----------------------\n";
   outfile <<"\n";
/**
*  @Pre  The current BST as inpu and write to output file
*  @Post Check if BST is empty or not
*/
cout<<"----------------nmd11----------------------\n";
   outfile <<BST.isEmpty( )<<"\n";
   cout<<"----------------nmd12----------------------\n";
   outfile <<"\n";

//OPen a new file to get some elements from same instance file
  /**
  *  @Pre  Current BST as input
  *  @Post check if first 10 elements from input files are present in BST
  */
  inFile1.open(argv[1]);
  int count=0;
  num=0;
    while(!inFile1.eof() and (count !=10))
    {   
         inFile1 >> num;
         if(BST.contains(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
  inFile1.close(); 
  /**
  *  @Pre  Current BST as input
  *  @Post Remove first 10 elements from input files from BST
  */
 cout<<"----------------nmd13----------------------\n";
  inFile1.open(argv[1]);
  count=0;
  num=0;
    while(!inFile1.eof() and (count !=10))
    {   
         inFile1 >> num;
  
         BST.remove(num);
         count=count+1;
    }
    inFile1.close(); 
  /**
  *  @Pre  Current BST as input
  *  @Post check if first 10 elements from input files are present in BST
  */
 cout<<"----------------nmd14----------------------\n";
  inFile1.open(argv[1]);
  count=0;
  num=0;
    while(!inFile1.eof() and (count !=10))
    {   
         inFile1 >> num;
         if(BST.contains(num))
            outfile <<"1"<<"\n";
          else
            outfile<<"0"<<"\n";
         count=count+1;
    }
    inFile1.close(); 
  }
else
  {
      cout << "The instance.txt file cannot be opened";
  }
inFile.close();
outfile.close();
cout<<"ending\n";
}