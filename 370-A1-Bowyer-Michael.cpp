#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <locale>
#include <cctype>
#include <string.h>

using namespace std;

struct personInfo
{
    string fullName;
    int idNumber;
    string adress;
};

void printPersonData(personInfo person) //Prints single data structure
{
    cout  << "\n" << person.fullName << endl;
    cout  << person.idNumber << endl;
    cout  << person.adress  <<endl;
}
void printPeopleData(personInfo person[], int n) // prints multiple data structures
{
    int i;
    for(i=0; i<n ; i++)
    {
        cout  << person[i].fullName << endl;
        cout  << person[i].idNumber << endl;
        cout  << person[i].adress  << "\n" <<endl;
    }
}

void enterNewPerson(personInfo &newPerson) // called when new data structures are asked to be entered
{
    string newFirst, newLast, newAdress; // temporary strings to pass into sturcture
    //Entering new name
    cout << "\nEnter the first name of the new person: " << endl;
    cin >> newFirst;
    cout << "\nEnter the last name of the new person: "<< endl;
    cin >> newLast;
    newPerson.fullName= newLast + ", " + newFirst;
    //Entering new ID
    cout << "\nEnter the ID number of the new person(Numbers only): "<< endl;
    int idNum;
    cin >> idNum;
    newPerson.idNumber=idNum;
    //Entering New adress
    cout << "\nEnter the Address of the new person: "<< endl;
    cin.ignore(); // needed to forget previous cin function or else number will be stored twice
    getline(cin, newAdress);
    newPerson.adress=newAdress;
}

int userChoice() //Returns 1 if User inputs yes, and 0 if the user inputs no
{
    cout << "\n[Y] - Yes\t [N] - no" << endl;
    char input;
    cin >> input;// Copying other char sllows for new input if Y or N is not input after incorrect format message appears.
    int returnVar=2;// is 1 for Yes, an 0 for no
    while(returnVar==2)
    {
         if (input == 'Y') // if user inputs this then the new contact can be entered
        {
            returnVar=1;
        }
        else
        {
            if (input == 'N')
            {
                returnVar=0;
            }
            else // when input is not Y or N
            {
                cout << "\nInput is in an incorrect format.\nEnter 'Y' for yes, or 'N' for no." << endl;
                cin >> input;
            }
        }
    }
    return returnVar;
}

void sortPeople(personInfo people[], int numPeople) // sorts all data structures by ID number
{
    int i, j;//second variable is so that only the needed amount of iterations is made
    for(i=0; i< numPeople; i++)
    {
        for(j=0; j<numPeople-i; j++)
        {
            if(people[j].idNumber > people[j+1].idNumber) // puts structures in ascending order
            {
                swap(people[j], people[j+1]);
            }
        }
    }
}

int main ()
{
    //Opening text file named a1.
    fstream textfile;
    textfile.open("a1.txt");

    //Necassary variables & arrays to store data
    personInfo people[20]; // data structure maximum of 20 people
    int tempID; // used to temporarily store the read in ID number
    string temp;// also used to temporarily store the read in name & adress
    int openfail= 0; // used to decide if the file is opened up
    //Making sure a1 is properly opened
    while (openfail= textfile.fail() != 0) // If file is not in directory while loop runs, once file is in directory the while loop ends.
    {
        cout << "\n File cannot be found. Please place a1.txt in proper directory.\n" <<
         "\nOnce file a1.txt is in directory press enter." << endl;
        getline(cin, temp); // Waits for user to press enter to search for .txt file again.
        textfile.open("a1.txt");//Open text file to read in
    }
    system("cls");

    // reading in data from the text fil

    int personCounter=0;//counts amount of people read into structure array.
    while(getline(textfile, temp))//loop reads in all data and places it into structures, and ends once it reads in end of file.
    {
        people[personCounter].fullName=temp;
        textfile >> tempID; // used to retrieve the Integer value for ID
        people[personCounter].idNumber=tempID;
        getline(textfile, temp);
        getline(textfile, temp);// needed in order to properly read in, because without it the structure skips reading in the adress
        people[personCounter].adress=temp;
        getline(textfile, temp);
        personCounter++;
    }
    textfile.close(); // after reading in all people the text file is closed.

    sortPeople(people, personCounter-1);// Sorts each data structure, -1 because
    //personCounter is 1 larger than amount of structures stored
    cout << "Stored people displayed in ascending order by ID number:\n" << endl;
    printPeopleData(people, personCounter);

    //
    // USER INPUTS NEW PERSON INFORMATION
    //

    cout << "End of people in text file. \n\n---------Menu----------\n\n" <<
    "Would you like to enter a new person to the list?" << endl;
    while(userChoice()) // asks for Yes or No from user each iteration. If yes the loop begins.
    {
        system("cls");
        printPeopleData(people, personCounter);
        cout << "\n\n ---------Menu----------\n" << endl;
        enterNewPerson(people[personCounter]); // function to enter new person into struct
        printPersonData(people[personCounter]); //immediatly prints off new person
        personCounter++; // added so that if another person is added they will be placed into next slot of structure array
        cout << "\n Would you like to Enter another Person?" << endl;
    }

    system("cls");
    cout << "All read in people and any newly entered people are displayed below:\n" << endl;
    sortPeople(people, personCounter-1);
    printPeopleData(people, personCounter); // prints all read in data and newly entered data

    //
    // Searching for Searching for stored People
    //

    cout << "\n\n ---------Menu----------\n\nWould you like to search for someone in the list?" << endl;
    personInfo searchedPeople[personCounter]; // new structure array to store all searched for data.
    int printSearched=0; // this enters if statement outside of while loop to print off all searched results.
    // If variable stays 0 then program ends. If it is 1 then program prints all results from search.
    int searchResult=0;// keeps track of how many people are searched and found. declared here in order to print out all
    //search results which is outside of the while loop.
    int searchFound=0; //Triggered to 1 if a match is found, if not triggers if statement that outputs no results found.
    while(userChoice())
    {
        system("cls");
        cout << "\n\n ---------Menu----------\nEnter the last name of the person you would like to"
        << "\nsearch for (Enter first letter as a capital letter): " << endl;
        string searchedName;
        cin >> searchedName;
        int i;
        searchFound=0; // triggered if search is found, resets for each iteration or else if a search comes back positive
        // then another search is made but comes back negative the "No matches Found" will not be displayed.
        for(i=0; i< personCounter; i++)
        {
            if (people[i].fullName.find(searchedName) != string::npos)// if search result is positive, then the new
                // person info is stored into a new aray of people. Also keeps track of how many people match the searchs.
            {
                searchedPeople[searchResult].fullName=people[i].fullName;
                searchedPeople[searchResult].idNumber=people[i].idNumber;
                searchedPeople[searchResult].adress=people[i].adress;
                printPersonData(searchedPeople[searchResult]);
                searchResult++; // add one for each positive search result
                searchFound=1; // set to 1 so that if statement after for loop (which says "no results found") is not triggered
                // Also triggers the if statement outside of the while loop to print out found results
            }
        }
        if (searchFound==0) // prints if no results match any data
        {
            cout << "\nNo matches found." << endl;
        }
        cout << "\nWould you like to search for another person?" << endl;
    }
    if(searchFound==1) // prints all found search results
    {
        system("cls");
        cout << " ---------Menu----------\n"
        << "Here are all of your search results:\n" <<endl;
        printPeopleData(searchedPeople, searchResult);
    }
  return 0;
}
