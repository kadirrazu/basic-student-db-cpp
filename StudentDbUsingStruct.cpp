#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <fstream>

#define AVAILABLE_SPACE 100

using namespace std;

struct students{
    int stdId;
    string firstName;
    string lastName;
    int age;
    string department;
    float cgpa;
};

students student[AVAILABLE_SPACE];

int totalEntries, currentTask;

void readStudentsData();
void printStudentsData();
void writeRecordsIntoFile();
void choiseTaskFromList();
void addNewRecord();
void updateSingleRecord();
void searchSingleRecord();
void deleteSingleRecord();

int main()
{
    readStudentsData();

    choiseTaskFromList();

    return 0;
}

void choiseTaskFromList()
{
    cout << "Please select a task from below: " << endl << endl;

    cout << "1. Print Records" << endl;
    cout << "2. Add New" << endl;
    cout << "3. Update Record" << endl;
    cout << "4. Search Record" << endl;
    cout << "5. Delete Record" << endl;
    cout << "6. Exit" << endl << endl;

    cout << "Choice: ";
    cin >> currentTask;
    cout << endl;

    switch( currentTask )
    {
        case 1:
            printStudentsData();
            choiseTaskFromList();
            break;

        case 2:
            addNewRecord();
            break;

        case 3:
            updateSingleRecord();
            break;

        case 4:
            searchSingleRecord();
            break;

        case 5:
            deleteSingleRecord();
            break;

        case 6:
            break;
    }

}

void readStudentsData()
{
    ifstream inputFile;

    inputFile.open("06-StudentDbUsingStructInput.txt");

    if( inputFile.is_open() )
    {
        inputFile >> totalEntries;

        for( int i=0; i<totalEntries; i++ )
        {
            inputFile >> student[i].stdId;
            inputFile >> student[i].firstName;
            inputFile >> student[i].lastName;
            inputFile >> student[i].age;
            inputFile >> student[i].department;
            inputFile >> student[i].cgpa;
        }
    }
    else
    {
        cout << "Can not open file to read inputs!" << endl;
    }

    inputFile.close();
}

void printStudentsData()
{
    cout << "************* STUDENTS INFORMATION *************" << endl << endl;

    for( int i=0; i<totalEntries; i++ )
    {
        cout << "Serial No.: " << i + 1 << endl;
        cout << "ID: " << student[i].stdId << endl;
        cout << "Name: " << student[i].firstName << " " << student[i].lastName << endl;
        cout << "Age: " << student[i].age << endl;
        cout << "Department: " << student[i].department << endl;
        cout << "CGPA: " << student[i].cgpa << endl << endl;
    }

    cout << endl;
}

void writeRecordsIntoFile()
{
    ofstream ouputFile;

    ouputFile.open("06-StudentDbUsingStructInput.txt");

    if( ouputFile.is_open() )
    {
        ouputFile << totalEntries << endl;

        for( int i=0; i<totalEntries; i++ )
        {
            ouputFile << student[i].stdId << " ";
            ouputFile << student[i].firstName << " ";
            ouputFile << student[i].lastName << " ";
            ouputFile << student[i].age << " ";
            ouputFile << student[i].department << " ";
            ouputFile << student[i].cgpa;
            ouputFile << endl;
        }
    }
    else
    {
        cout << "Error, Can not open output file!" << endl;
        return;
    }

    ouputFile.close();
}

void addNewRecord()
{
    int currentIndex = totalEntries;
    char decision;

    cout << "Please Enter New Record: " << endl << endl;

    cout << "Student ID: ";
    cin >> student[currentIndex].stdId;
    cout << endl;

    cout << "First Name: ";
    cin >> student[currentIndex].firstName;
    cout << endl;

    cout << "Last Name: ";
    cin >> student[currentIndex].lastName;
    cout << endl;

    cout << "Age: ";
    cin >> student[currentIndex].age;
    cout << endl;

    cout << "Department: ";
    cin >> student[currentIndex].department;
    cout << endl;

    cout << "CGPA: ";
    cin >> student[currentIndex].cgpa;
    cout << endl;

    cout << "Do you want to save this record permanently? (y/n) : ";
    cin >> decision;

    if( (decision == 'y') || (decision == 'Y') )
    {
        totalEntries += 1;

        writeRecordsIntoFile();

        readStudentsData();

        cout << endl << "New record was added successfully!" << endl << endl;

        choiseTaskFromList();

    }
    else if( (decision == 'n') || (decision == 'N') )
    {
        cout << endl << "New record flushed!" << endl << endl;

        readStudentsData();

        choiseTaskFromList();

    }
    else
    {
        cout << endl << "Invalid choice. Record was flushed without saving to file!" << endl << endl;

        readStudentsData();

        choiseTaskFromList();

    }

}

void updateSingleRecord()
{
    int searchId, index = -1, tempAge;
    string tempFirstName, tempLastName, tempDepartment;
    float tempCgpa;

    cout << "Please Enter Student ID: ";
    cin >> searchId;

    int counter = 0;

    for( int i=0; i<totalEntries; i++)
    {
        if( student[i].stdId == searchId )
        {
            index = i;
            counter++;
        }
    }

    if( counter > 0 )
    {
       cout << endl <<"Please enter following details for student ID: " << searchId << endl << endl;

       cout << "First Name: ";
       cin >> tempFirstName;
       cout << endl;

       cout << "Last Name: ";
       cin >> tempLastName;
       cout << endl;

       cout << "Age: ";
       cin >> tempAge;
       cout << endl;

       cout << "Department: ";
       cin >> tempDepartment;
       cout << endl;

       cout << "CGPA: ";
       cin >> tempCgpa;
       cout << endl;

       char confirm;

       cout << endl <<"Pleae confirm update task (y/n): ";

       cin >> confirm;

       if( confirm == 'y' || confirm == 'Y')
       {
            student[index].firstName = tempFirstName;
            student[index].lastName = tempLastName;
            student[index].age = tempAge;
            student[index].department = tempDepartment;
            student[index].cgpa = tempCgpa;

            writeRecordsIntoFile();

            readStudentsData();

            cout << endl <<"Record was successfully updated for ID: " << searchId << endl << endl;

            choiseTaskFromList();
       }
       else
       {
           cout << endl << "Update task was aborted!" << endl << endl;

           choiseTaskFromList();
       }
    }
    else
    {
        cout << endl << "Error, Invalid Student ID!" << endl << endl;

        choiseTaskFromList();

    }
}

void searchSingleRecord()
{
    int searchId, index = -1;

    cout << "Please Enter Student ID: ";
    cin >> searchId;

    int counter = 0;

    for( int i=0; i<totalEntries; i++)
    {
        if( student[i].stdId == searchId )
        {
            index = i;
            counter++;
        }
    }

    if( counter > 0 )
    {
       cout << endl <<"Details Information for ID: " << searchId << endl << endl;

       cout << "First Name: " << student[index].firstName << endl;
       cout << "Last Name: " << student[index].lastName << endl;
       cout << "Age: " << student[index].age << endl;
       cout << "Department: " << student[index].department << endl;
       cout << "CGPA: " << student[index].cgpa << endl << endl;

       choiseTaskFromList();
    }
    else
    {
        cout << endl << "No result was found for Student ID: " << searchId << endl << endl;

        choiseTaskFromList();

    }
}

void deleteSingleRecord()
{
    int delId;

    cout << endl << endl << "Delete Record by Student ID" << endl << endl;
    cout << "Please enter Student ID to delete: ";

    cin >> delId;

    int counter = 0, index = -1;

    for( int i=0; i<totalEntries; i++ )
    {
        if( student[i].stdId == delId )
        {
            index = i;
            counter++;
        }
    }

    if( counter > 0 )
    {
       int positionToGrab = index+1;

       for(int i=index; i<totalEntries; i++)
       {
            student[i].stdId = student[positionToGrab].stdId;
            student[i].firstName = student[positionToGrab].firstName;
            student[i].lastName = student[positionToGrab].lastName;
            student[i].age = student[positionToGrab].age;
            student[i].department = student[positionToGrab].department;
            student[i].cgpa = student[positionToGrab].cgpa;

            positionToGrab++;
       }

       totalEntries = totalEntries - 1;

       writeRecordsIntoFile();

       cout << endl << "Record was deleted from system." << endl << endl;

       choiseTaskFromList();

    }
    else
    {
        cout << endl << "Invalid Student ID: " << delId << endl << endl;

        choiseTaskFromList();

    }

}
