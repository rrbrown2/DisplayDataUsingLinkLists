#if
/*
Prepares an inventory report stores the result into a linked list and displays the list data.
*/
#endif
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// start creating linked list
struct node
{
    int item_Number;
    string item_description;
    int cases_On_Hand;
    int case_Capacity;
    float price;
    int date_created_Year;
    int date_created_Month;
    int date_created_Day;
    int date_modified_Year;
    int date_modified_Month;
    int date_modified_Day;
    int minimum_Inventory;
    node *next;
};

string month[13] = {"Error", "Jan.", "Feb.", "March", "Apr.", "May", "June", "July", "Aug.", "Sep.", "Oct.", "Nov.", "Dec."};

//function prototypes
void read_data(string fileName); // for reading file inventory data
char menu(); // Show menu
void insertNode(node *current);
void insert();
void remove();
void modify();
void showlist();
//end of function prototypes

node *head;
int list_size;

int main() {
  head = NULL;
  list_size =  0;
  read_data("read.txt");
  char choice;
  int number;
  do{
    choice = menu();
    switch(toupper(choice))
    {
      case 'D':
        showlist();
        break;
      case 'E':
        cout << "Bye!!";
        break;
      default:
        cout << "Option not valid!" << endl;
        break;
    }
  } while(choice != 'E');
  return 0;
}

// reads inventory data from a file this data will be store into linked list
void read_data(string fileName)
{
  ifstream infile; // files read object
  infile.open(fileName.c_str());
  char *buffer = new char [20];
  node *current;
  while (!infile.eof()) {
      current = new node();
      infile >> current->item_Number;
      if (infile.eof()){
      	break;
	  }
      infile.read(buffer, 20);
      current->item_description = buffer;
      infile >> current->cases_On_Hand;
      infile >> current->case_Capacity;
      infile >> current->price;
      infile >> current->date_created_Year;
      infile >> current->date_created_Month;
      infile >> current->date_created_Day;
      infile >> current->date_modified_Year;
      infile >> current->date_modified_Month;
      infile >> current->date_modified_Day;
      infile >> current->minimum_Inventory;
      current->next = NULL;
      insertNode(current);
  }
  return;
}

char menu()
{
  string choice;
  cout << "D. Print Report " << endl;
  cout << "E. Quit " << endl;
  cin >> choice;
  return toupper(choice[0]);
}

void insertNode(node *newOne){
    if(head == NULL){
      list_size = 1;
      head = newOne;
      return;
    }

    node *current = head;
    node *previus = NULL;

    while(current != NULL){
      if (current->item_Number > newOne->item_Number){
        newOne->next = current;
        if (previus == NULL){
        	head = newOne;
		}
        else{
        	previus->next = newOne;
    	}
		list_size++;
        return;
      }
      previus = current;
      current = current->next;
    }

    list_size++;
    previus->next = newOne;

}

void showlist()
{
  if(head == NULL){
    cout << "The list is empty"  << endl;
    return;
  }

  cout << setw(60) << "Inventory Report" << endl;
  cout << setw(70) << "Items Printed in Ascending Order" << endl << endl;
  cout << left << setw(11) <<  "Item"   << setw(20) << "Item"        << setw(15) << "Cases"    << setw(10) << "Stock*" << setw(15) << "Date"    << setw(15) << "Date"     << setw(20) << "Min"         << endl;
  cout << left << setw(11) <<  "Number" << setw(20) << "Description" << setw(15) << "In stock" << setw(10) << "Value"  << setw(15) << "Created" << setw(15) << "Modified" << setw(20) << "Inv. Amount" << endl;
  node *current = head;
  double totalValue = 0;
  while(current != NULL)
  {
  	ostringstream date1, date2;
  	date1 << (current->date_created_Month > 0 && current->date_created_Month < 13 ? month[current->date_created_Month] : month[0]) << " " << current->date_created_Day << ", " << current->date_created_Year;
  	date2 << (current->date_modified_Month > 0 && current->date_modified_Month < 13 ? month[current->date_modified_Month] : month[0]) << " " << current->date_modified_Day << ", " << current->date_modified_Year;
    cout << setw(10) << left << current->item_Number
         << setw(21) << current->item_description

         << setw(15) << current->cases_On_Hand
         << setw(10) << (current->cases_On_Hand * current->case_Capacity * current->price)
         << setw(15) << date1.str()
         << setw(15) << date2.str()
         << setw(20) << current->minimum_Inventory << endl;
    totalValue += (current->cases_On_Hand * current->case_Capacity * current->price);
    current = current->next;
  }

  cout << "Total Value of Inventory ======== $" << totalValue << endl;
  cout << setw(50) << left << "END OF REPORT" << endl;

  return;
}
