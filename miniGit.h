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
        miniGit();
        ~miniGit();
        void add(std::string filename);
        void remove(std::string filename);
        void commitChanges();
        void checkOut(int version);
    private:
        doublyNode head;
};