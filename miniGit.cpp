#include "miniGit.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;



/**
 * Constructor for miniGit
*/
miniGit::miniGit(){
    head = new doublyNode;
    head->commitNumber = 1;
    head->head = NULL;
    head->next = NULL;
    head->previous = NULL;
};

/**
 * Destructor for miniGit
*/
miniGit::~miniGit(){
    //temporary doublyNode for traversal
    doublyNode* dTemp = head;

    //temporary singlyNode for traversal
    singlyNode* sTemp;

    //traverse entire doubly linked list, 
    while(dTemp != NULL){

        sTemp = dTemp->head;

        while(sTemp != NULL){
            cout << "Deleting File: "<< sTemp->fileName << endl;

            singlyNode* delTemp = sTemp->next;
            delete sTemp;

            sTemp = delTemp;
        }
        cout << "Deleting Commit: " << dTemp->commitNumber  << endl;

        doublyNode* delComTemp = dTemp->next;
        delete dTemp;

        dTemp = delComTemp;
    }
}

/**
 * Helper function to change the name of a file put into the .minigit directory
*/
string changeFileName(string s, int n){

    string out = "";

    for(int i = 0; i < s.length(); i++){

        if(s[i] == '.'){

            out += s.substr(0,i);

            if(n < 10){
                out += "0" + to_string(n);
            }
            else{
                out += to_string(n);
            }

            out += s.substr(i,s.length()-i);
        }
    }

    return out;
}

/**
 * Helper function to print the current file structure
*/
void miniGit::printGit(){
    //temporary doublyNode for traversal
    doublyNode* dTemp = head;

    //temporary singlyNode for traversal
    singlyNode* sTemp;

    //traverse entire doubly linked list, printing the appropriate commitNumbers and fileNames
    while(dTemp != NULL){

        cout << "Commit Number: " << dTemp->commitNumber << " -> ";
        sTemp = dTemp->head;

        while(sTemp != NULL){
            cout << sTemp->fileVersion << " -> ";
            sTemp = sTemp->next;
        }
        cout << endl;
        dTemp = dTemp->next;
    }
}

/**
 * Helper function to copy files from the working directory into .minigit
*/
void copyFileIntoGit(string fileName, string fileVersion){
    string temp;

    ifstream inFile;
    inFile.open(fileName);

    ofstream outFile;
    outFile.open(".minigit/" + fileVersion);

    while(getline(inFile,temp)){
        outFile << temp << endl;
    }
}

/**
 * Helper function to copy files from .minigit into the working directory
*/
void copyFileFromGit(string fileName, string fileVersion){
    string temp;

    ifstream inFile;
    inFile.open(".minigit/" + fileVersion);

    ofstream outFile;
    outFile.open(fileName,ofstream::trunc);

    while(getline(inFile,temp)){
        outFile << temp << endl;
    }
}

int miniGit::getVersion(){
    return head->commitNumber;
}

/**
 * Creates a new miniGit repository
*/
void miniGit::newRepository(){
    //make a new directory in current folder called .minigit
    system("mkdir .minigit");

}
/**
 * Function to add a new file to the current miniGit instance
*/ 
void miniGit::add(){

    string input;
    while(true){
        //prompt user to enter a file name
        cout << "Enter a filename: " << endl;
        
        cin >> input;

        //search directory for file. If it exists prompt the user to enter a valid file name
        ifstream fileIn = ifstream(input);

        if(fileIn.fail() == true){
            cout << "The file name provided does not exist within the directory. Please enter a valid file name: " << endl;
            continue;
        }
        else{
            break;
        }
    }

    //search the SLL for if the file has already been added, a file by the same name cannot be added twice
    singlyNode* temp = head->head;
    while(temp != NULL){
        if(temp->fileName == input){
            cout << "this file has already been added" << endl;
            return;
        }
        temp = temp->next;
    }

    //Add a new SSL node containing the name of the input file, name of repository file, and a pointer to the next node.

    singlyNode* newNode = new singlyNode();
    newNode->fileName = input;
    newNode->fileVersion = changeFileName(input,0);
    newNode->version = 0;
    
     
    //add new node to list
    newNode->next = head->head;
    head->head = newNode;

    //reposiroty name is a combination of the original file and file number and saved in the .minigit repo


}
/**
 * Removes a file from the current miniGit instance 
*/ 
void miniGit::remove(){
    //prompt user to enter a file name
    cout << "Please enter a file name" << endl;
    string input;
    cin >> input;

    //Check SSL for whether the file exists in the current version of the repository

    singlyNode* temp = head->head;
    singlyNode* prev = NULL;

    while(temp != NULL){
        if(temp->fileName == input){
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    //If found, delete the SSL Node
    if(temp != NULL){
        //if the node to be deleted is the first node in the list
        if(head->head == temp){
            head->head = temp->next;
            delete temp;
            return;
        }

        //if the node to be deleted is in the middle or at the end of the list
        prev->next = temp->next;
        delete temp;
        return;

    }
    return;
}
/**
 * Commits changes to the repository and logs said changes
*/
void miniGit::commitChanges(){
    //Traverse SSL and for every node 

    singlyNode* temp = head->head;

    while(temp != NULL){

        ifstream fileChecker = ifstream(".minigit/" + temp->fileVersion);
        //check  whether the corresponding fileVersion exists in .minigit
        
        
        //If the fileVersion does not exist, copy the file from the current directory into the minigit.
        //The newly copied file should get the same name from the node's fileVersion Number (only when added to a repo for the first time)
        if(fileChecker.fail() == true){
            //copy file over
            copyFileIntoGit(temp->fileName,temp->fileVersion);
        }
        //If the fileVersion does exist in .minigit, check whether the current directory file  has been changed
        //with respect to the fileVersion file 
        else{
            // (read file from current directory into one string and read file from .minigit into another)
            // (Check for equality)

            string comp1;
            string comp2;
            string tempString;
             
            while(getline(fileChecker,tempString)){
                comp1 += tempString;
            }

            fileChecker.close();
            fileChecker.open(temp->fileName);

            while(getline(fileChecker,tempString)){
                comp2 += tempString;
            }
            
            // If file is unchanged, do nothing
            if(comp1 == comp2){
                return;
            }
            // If file is changed, copy the file from the current directory to the .minigit directory and give it a name
            // with the incramented version number. Also update SLL node memeber fileVersion to the incramented name
            else{
                temp->version++;
                temp->fileVersion = changeFileName(temp->fileName,temp->version);

                //copy file over
                copyFileIntoGit(temp->fileName,temp->fileVersion);

                //update SSL node member fileVersion
                
            }
        }
            temp = temp->next;
    }

    //Once all files have been scanned, create a new DLL node of the repository 
    //An exact (deep) copy of the SLL from the previous node shall be copied into the new DLL node.
    //The commit number of the new DLL node will be the previous nodes commit number incramented by one 

    //
    doublyNode* newNode = new doublyNode;
    newNode->next = head;
    head->previous = newNode;
    newNode->commitNumber = head->commitNumber+1;
    newNode->previous = NULL;

    singlyNode* newFiles = new singlyNode;
    newNode->head = newFiles;

    singlyNode* traverse = head->head;
    singlyNode* tempCreate;

    while(traverse != NULL){

        newFiles->fileName = traverse->fileName;
        newFiles->fileVersion = traverse->fileVersion;
        newFiles->version = traverse->version;

        if(traverse->next != NULL){
            tempCreate = new singlyNode;
            newFiles->next = tempCreate;
        }
        else{
            newFiles->next = NULL;
        }

        newFiles = newFiles->next;
        traverse = traverse->next;
    }

    head = newNode;
}

/**
 * Allows the user to check out previous versions of the code
*/
void miniGit::checkOut(int version){
    //prompt user to enter a commit number
    cout << "enter a commit number" << endl;
    int num;


    //For a valid commit number, the files in the current directory should be overwritten by the corresponding files in the 
    //.minigit directory 
    //Issue warning that their changes will not be saved 
    
    //get input from user
    while(true){
        cin >> num;
        if(num > head->next->commitNumber){
            cout << "invalid commit number, try again" << endl; 
            continue;
        }
    }

    //find the node that corresponds to the user input
    doublyNode* traverse = head->next;
    while(traverse != NULL){
        if(num == traverse->commitNumber){
            break;
        }
        traverse = traverse->next;
    }

    singlyNode* fileTrav = traverse->head;

    while(fileTrav != NULL){
        copyFileFromGit(fileTrav->fileName,fileTrav->fileVersion);
    }
    
    //Must disallow add, remove and commit operations when the current version is different from the most recent commit

}
