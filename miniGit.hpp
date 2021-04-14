#ifndef miniGit_H
#define miniGit_H

#include <iostream>


struct doublyNode{
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};

struct singlyNode{
    std::string fileName;    // Name of local file
    std::string fileVersion; // Name of file in .minigit folder
    singlyNode * next;
};

class miniGit{

    public:
        void newRepository();
        void add();
        void remove();
        void commitChanges();
        void checkOut(int version);

    private:
        doublyNode head;
};

#endif