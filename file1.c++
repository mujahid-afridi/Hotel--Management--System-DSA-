#include <iostream>
#include <algorithm>
#include <cctype>
#include <regex>
using namespace std;
class Hotel
{
public:
  int roomId;
  string name;
  string date;
  int days;
  string type;
  Hotel *next;
  Hotel(int id, string name, string date, int days, string type)
  {
    this->roomId = id;
    this->name = name;
    this->date = date;
    this->days = days;
    this->type = type;
    next = NULL;
  }
};
void allocateRoom(Hotel *&head, int id, string name, string date, int days, string type)
{
  Hotel *temp = head;
  Hotel *node = new Hotel(id, name, date, days, type);
  if (temp == NULL)
  {
    head = node;
    return;
  }
  else
  {
    node->next = temp;
    head = node;
    return;
  }
}
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
bool validateDateFormat(const string& date) {
    // Regular expression for DD/MM/YYYY format
    regex dateRegex(R"((0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4})");
    return regex_match(date, dateRegex);
}
bool checkRoom(Hotel *head, int id)
{
  Hotel *temp = head;
  while (temp != NULL)
  {
    if (temp->roomId == id)
    {
      return true;
    }
    temp = temp->next;
  }
  return false;
}
void searchRoom(Hotel *head, int id)
{
  Hotel *temp = head;
  if (head == NULL)
  {
    cout << "Sorry, the list is empty. Please first add then can search." << endl;
    return;
  }
  while (temp != NULL)
  {
    if (temp->roomId == id)
    {
      cout << "Room ID\t\tCustomer Name\t\tAllocation Date\t\tRoom Type" << endl;
      cout << temp->roomId << "\t\t" << temp->name << "\t\t" << temp->date << "\t\t" << temp->type << endl;
      return;
    }
    temp = temp->next;
  }
  cout << "No room found with id " << id << endl;
}
void updateRoom(Hotel *&head, int searchingID, int id, string name, string date, string type)
{
  Hotel *temp = head;
  if (head == NULL)
  {
    cout << "The list is empty and there is no something to update." << endl;
    return;
  }
  while (temp != NULL)
  {
    if (temp->roomId == searchingID)
    {
      temp->roomId = id;
      temp->name = name;
      temp->date = date;
      temp->type = type;
      cout << "The Record of Room with ID " << id << " has updated." << endl;
      return;
    }
    temp = temp->next;
  }
  cout << "The Room According To Your ID Does Not Found In The List" << endl;
}
void deleteRoom(Hotel *&head, int id)
{
  Hotel *temp = head;
  Hotel *preNode;
  if (head == NULL)
  {
    cout << "The Link List is empty." << endl;
    return;
  }
  if (temp->roomId == id)
  {
    head = temp->next;
    delete temp;
    cout << "The Room with ID " << id << " successfully deleted." << endl;
    return;
  }
  while (temp->roomId != id)
  {
    preNode = temp;
    temp = temp->next;
  }
  preNode->next = temp->next;
  delete temp;
  cout << "The Room with ID " << id << " successfully deleted." << endl;
}
void showRoomRecord(Hotel *head)
{
  if (head == NULL)
  {
    cout << "**********The Link List is empty**********" << endl;
  }
  else
  {
    cout << "Room ID\t\tCustomer Name\t\tAllocation Date\t\tDays\t\tRoom Type" << endl;
    Hotel *temp = head;
    while (temp != NULL)
    {
      cout << temp->roomId << "\t\t" << temp->name << "\t\t" << temp->date << "\t\t"<<temp->days<<"\t\t" << temp->type << endl;
      temp = temp->next;
    }
  }
}
int calculateRoomPrice(string type, int days)
{
  int pricePerDay = 0;
  if (type == "single")
  {
    pricePerDay = 1000;
  }
  else if (type == "double")
  {
    pricePerDay = 2000;
  }
  return pricePerDay * days;
}
void calculateBill(Hotel *head, int id)
{
  Hotel *temp = head;
  if (head == NULL)
  {
    cout << "The list is empty. No records found." << endl;
    return;
  }
  while (temp != NULL)
  {
    if (temp->roomId == id)
    {
      int totalCost = calculateRoomPrice(temp->type, temp->days);
      cout << "Bill for Room ID: " << temp->roomId << endl;
      cout << "Customer Name: " << temp->name << endl;
      cout << "Room Type: " << temp->type << endl;
      cout << "Number of Days: " << temp->days << endl;
      cout << "Total Cost: $" << totalCost << endl;
      return;
    }
    temp = temp->next;
  }
  cout << "Room with ID " << id << " not found." << endl;
}

int main()
{
  cout << "\t\tWelcome to Hotel Management System Application\n"
       << endl
       << endl;
  cout << "\t\t\t_____Hotel Management System_____" << endl
       << endl;
  cout << "So.No\t\tFunctions\t\tDescriptions" << endl;
  cout << "1\t\tAllocate Room\t\tInsert New Room" << endl;
  cout << "2\t\tSearch Room\t\tSearch Room With ID" << endl;
  cout << "3\t\tUpdate Room\t\tUpdate Room Record With ID" << endl;
  cout << "4\t\tDelete Room\t\tDelete Room With ID" << endl;
  cout << "5\t\tShow Room Record\t\tShow Room Record That We Added" << endl;
  cout << "6\t\tCalculate Bill\t\tCalculate bill of each Room" << endl;
  cout << "7\t\tExit\n"
       << endl;

  Hotel *head = NULL;
  int choice;

  do
  {
    cout << "\nEnter You Choice: \t";
    cin >> choice;
    cout << endl;
    if (choice == 1)
    {
      int id, days;
      string name, date, type;
      cout << "Enter the id of Room :\t";
      cin >> id;
      if (checkRoom(head, id))
      {
        cout << "**********This room already exist***********" << endl;
      }
      else
      {
        cout << "Enter the name of Customer :\t";
        cin.ignore(); // Clear the buffer
        getline(cin, name); // Use getline to allow spaces in names
        cout << "Enter date in DD/MM/YYYY format :\t";
        cin >> date;
        if(!validateDateFormat(date)){
          cout<<"Invalid date format."<<endl;
          continue;
        }
        cout << "Enter the no of Day or Days :\t";
        cin >> days;
        cout << "Enter the type of Room (Single/Double):\t";
        cin >> type;
        type = toLowerCase(type);
        if (type != "single" && type != "double") {
            cout << "Invalid room type entered. Please enter 'Single' or 'Double'." <<endl;
        continue;
        }
        allocateRoom(head, id, name, date, days, type);
      }
    }
    else if (choice == 2)
    {
      int id;
      cout << "Enter ID for searching Room : ";
      cin >> id;
      searchRoom(head, id);
    }
    else if (choice == 3)
    {
      int searchingID, days;
      cout << "Enter ID for updating Room : ";
      cin >> searchingID;
      int id;
      string name, date, type;
      cout << "Enter the ID for updating previous ID of Room :\t";
      cin >> id;
      cout << "Enter the name for updating previous name of Customer :\t";
      cin >> name;
      cout << "Enter date in DD/MM/YYYY format :\t";
      cin >> date;
      if(!validateDateFormat(date)){
        cout<<"Invalid date format."<<endl;
        continue;
      }
      cout << "Enter the no of Day or Days :\t";
      cin >> days;
      cout << "Enter the type for updating previous type of Room(Single/Double) :\t";
      cin >> type;
      type = toLowerCase(type);
      if (type != "single" && type != "double") {
          cout << "Invalid room type entered. Please enter 'Single' or 'Double'." <<endl;
        continue;
      }
      updateRoom(head, searchingID, id, name, date, type);
    }
    else if (choice == 4)
    {
      int id;
      cout << "Enter ID : ";
      cin >> id;
      deleteRoom(head, id);
    }
    else if (choice == 5)
    {
      showRoomRecord(head);
    }
    else if (choice == 6)
    {
      int id;
      cout<<"Enter room ID to calculate Bill"<<endl;
      cin>>id;
      calculateBill(head,id);
    }
    else
    {
      cout << "Please choose correct So.No..." << endl;
    }
  } while (choice != 7);
}