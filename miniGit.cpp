#include "miniGit.hpp"

miniGit::miniGit(){
    
};

miniGit::~miniGit(){

}


void miniGit::add(){
    //prompt user to enter a file name

    //search directory for file. If it exists prompt the user to enter a valid file name

    //search the SLL for if the file has already been added, a file by the same name cannot be added twice

    //Add a new SSL node containing the name of the input file, name of repository file, and a pointer to the next node.
    //reposiroty name is a combination of the original file and file number and saved in the .minigit repo

}

void miniGit::remove(){
    //prompt user to enter a file name

    //Check SSL for whether the file exists in the current version of the repository

    //If found, delete the SSL Node



}

void miniGit::commitChanges(){
    //Traverse SSL and for every node 

        //check  whether the corresponding fileVersion exists in .minigit

        //If the fileVersion does not exist, copy the file from the current directory into the minigit.
        //The newly copied file should get the same name from the node's fileVersion Number (only when added to a repo for the first time)

        //If the fileVersion does exist in .minigit, check whether the current directory file  has been changed
        //with respect to the fileVersion file 

            // (read file from current directory into one string and read file from .minigit into another)
            // (Check for equality)

            // If file is unchanged, do nothing

            // If file is changed, copy the file from the current directory to the .minigit directory and give it a name
            // with the incramented version number. Also update SLL node memeber fileVersion to the incramented name
    
    //Once all files have been scanned, create a new DLL node of the repository 
    //An exact (deep) copy of the SLL from the previous node shall be copied into the new DLL node.
    //The commit number of the new DLL node will be the previous nodes commit number incramented by one 

}

void miniGit::checkOut(int version){
    //prompt user to enter a commit number

    //For a valid commit number, the files in the current directory should be overwritten by the corresponding files in the 
    //.minigit directory 
    //Issue warning that their changes will not be saved 

    //Search through DLL for a node with matching commit number
    //Must disallow add, remove and commit operations when the current version is different from the most recent commit

}