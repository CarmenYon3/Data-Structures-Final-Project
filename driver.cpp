#include "miniGit.hpp"
#include <iostream>

using namespace std;

int main(string args[]){

    //initial menu for adding a new (empty) repository
    cout << "Would you like to initialize an empty repository in this directory? (y or n)" << endl;

    while(true){

        char input;
        cin >> input;

        switch(input){
            case 'y': 

                break;

            case 'n':

                break;

            default:
                continue;
        }
    }


}