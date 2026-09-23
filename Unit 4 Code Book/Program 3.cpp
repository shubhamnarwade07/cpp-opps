/*
 * Unit 4 Code Book
 * Concept 3: Append Data to a File
 * Aim: To add new content at the end of an existing file.
 */

#include <fstream>
#include <iostream>

int main() {
    std::ofstream outputFile("message.txt", std::ios::app);
    if (!outputFile) {
        std::cerr << "Error: Could not open message.txt for appending\n";
        return 1;
    }

    outputFile << "This line was added using append mode.\n";
    outputFile.close();

    std::cout << "New line appended successfully.\n";
    return 0;
}
