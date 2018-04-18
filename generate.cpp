/*
 * Mike Verdicchio
 * Thread Synchronization
 * generate.ccp
 * 
 * Generates an input file of length argv[1]
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <num_points>" << endl;
        return 1;
    }

    int num = stoi(argv[1]);
    int random;
    string input;

    remove("input.txt");
    ofstream file("input.txt");

    for (int i = 0; i < num; i++)
    {
        random = rand() % 32000;
        file << random << endl;
    }

    file.close();

    return 0;
}