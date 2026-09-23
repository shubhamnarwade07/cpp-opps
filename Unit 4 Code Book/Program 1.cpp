/*
 * Unit 4 Code Book
 * Concept 1: Write Text to a File
 * Aim: To create a text file and write data into it using std::ofstream.
 */

#include <fstream>
#include <iostream>

int main() {
    std::ofstream outputFile("message.txt");
    if (!outputFile) {
        std::cerr << "Error: Could not create message.txt\n";
        return 1;
    }

    outputFile << "Welcome to C++ File Handling\n";
    outputFile << "This is the first line written to a file.\n";
    outputFile << "Files store data permanently.\n";
    outputFile.close();

    std::cout << "Data written successfully to message.txt\n";
    return 0;
}
