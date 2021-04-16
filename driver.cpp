#include "miniGit.hpp"
#include <iostream>
//lets go
using namespace std;

int main(){

    miniGit git = miniGit();


    //initial menu for adding a new (empty) repository
    cout << "Would you like to initialize an empty repository in this directory? (y or n)" << endl;

    bool check = true;
    while(check){

        char input;
        cin >> input;

        switch(input){
            case 'y': 
                git.newRepository();
                check = false;
                break;

            case 'n':
                cout << "Quitting" << endl;
                return 0;

            default:
                continue;
        }
    }

    
    while(true){
        cout << "What would you like to do?" << endl;
        cout << "(1) Add a file" << endl;
        cout << "(2) Remove a file" << endl;
        cout << "(3) Commit Changes" << endl;
        cout << "(4) Check out a previous version of the repository" << endl;
        cout << "(5) Quit" << endl;
        cout << "(6) Print" << endl;

        int input;
        cin >> input;

        switch(input){
            case 1:
                git.add();
                break;
            case 2:
                git.remove();
                break;
            case 3:
                git.commitChanges();
                break;
            case 4:
                git.checkOut();
                break;
            case 5:
                cout << "Quitting" << endl;
                return 0;
            case 6:
                git.printGit();
                break;
            default:
                cout << "Invalid input, try agagin" << endl;
                continue;
        }
    }


}