## Student Details

- **Student Name:** Narwade Shubham Dilip

- **Roll No:** AD2363

- **Class / Division:** SY / C

- **Course Name:** Object Oriented Programming with C++ (OOPs with C++)



---



## List of Programs (Units 4)



### Unit 4: Files and Streams

1. `1_Student_Record_File_System.cpp` – Student Record File System

2. `2_Server_Log_Analyzer.cpp` – Server Log Analyzer

3. `3_Binary_File_for_Fixed_Size_Records.cpp` – Binary File for Fixed-Size Records

4. `Project_Library_Book_Management_System.cpp` – Library Book Management System (Mini Project)



---



## Program Descriptions



### Unit 4: Files and Streams



#### 1. Student Record File System (`1_Student_Record_File_System.cpp`)

- **Description:** Implements persistent text-based storage for student records using `std::ofstream` and `std::ifstream` in CSV format. Encapsulates roll number, student name, and academic marks, providing member functions `saveToFile()`, `loadFromLine()`, and `display()` along with `std::stringstream` parsing and error handling (`stoi`, `stod`).



#### 2. Server Log Analyzer (`2_Server_Log_Analyzer.cpp`)

- **Description:** Demonstrates sequential file parsing, string pattern matching, and file analysis. Creates sample server logs and processes them line-by-line using `std::ifstream` and `std::getline()`, filtering and extracting critical security and server failure events (`ERROR`, `CRITICAL`) into structured records.



#### 3. Binary File for Fixed-Size Records (`3_Binary_File_for_Fixed_Size_Records.cpp`)

- **Description:** Illustrates low-level binary file I/O operations using `std::ios::binary`, `write()`, and `read()` with `reinterpret_cast`. Stores and retrieves structured image metadata (`ImageMetadata`) using fixed-size byte buffers to achieve efficient serialization without text conversion overhead.



#### 4. Library Book Management System (`Project_Library_Book_Management_System.cpp`)

- **Description:** A mini-project implementing an object-oriented, persistent library book management application. Features complete CRUD capabilities including adding books, listing the library catalog, searching by ISBN, title, or author, and issuing or returning books with automatic CSV file synchronization.
