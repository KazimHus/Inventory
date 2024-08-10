#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

struct User // the struct contains the variables from the file
{
    string name;
    string manu;
    int quantity;
    int minimum;
    double price;
};

void report(const vector<User>& arr); // declaring function
void inventory(const vector<User>& arr);

int main()
{
    string filename;
    cout << endl;
    cout << "Welcome! I will show your inventory information." << endl;
    cout << endl;
    cout << "Please enter file name: ";
    cin >> filename;
    cout << endl;

    ifstream thefile;
    thefile.open(filename);

    if (thefile) // if file exists
    {
        vector<User> arr; // using vector instead of fixed-size array
        User tempUser;
        char choice;

        while (thefile >> tempUser.name >> tempUser.manu >> tempUser.quantity >>
               tempUser.minimum >> tempUser.price)
        {
            arr.push_back(tempUser); // add each user to the vector
        }

        // Sort the vector in alphabetical order.
        for (int a = 0; a < arr.size(); a++)
        {
            for (int j = a + 1; j < arr.size(); j++)
            {
                if (arr[a].name > arr[j].name)
                {
                    User temp = arr[a];
                    arr[a] = arr[j];
                    arr[j] = temp;
                }
            }
        }

        do
        {
            cout << "Press 'I' to see the inventory report " << endl;
            cout << "Press 'R' to see the Reorder Report" << endl;
            cout << "OR press 'Q' to quit: ";
            cin >> choice;

            if (choice == 'I' || choice == 'i')
            {
                inventory(arr);
            }
            else if (choice == 'R' || choice == 'r')
            {
                report(arr);
            }
            else if (choice == 'Q' || choice == 'q')
            {
                cout << endl;
                cout << "Thank you. Goodbye" << endl;
                cout << endl;
                break; // Exit the loop when 'Q' or 'q' is pressed
            }

        } while (choice == 'I' || choice == 'i' || choice == 'R' || choice == 'r');

        thefile.close(); // closing the file
    }
    else
    {
        cerr << "File not found" << endl; // using cerr for error reporting
    }

    return 0;
}

void inventory(const vector<User>& arr) // This is the inventory report.
{
    double exact = 0.0;
    int order = 0;
    double totalprice = 0.0;
    vector<double> arr6(arr.size());

    for (int a = 0; a < arr.size(); a++)
    {
        arr6[a] = arr[a].price * arr[a].quantity;
    }

    cout << endl;
    cout << setw(30) << "Inventory Report" << endl;
    cout << endl;
    cout << "Item " << "   " << setw(10) << "Manufacturer" << "   " << setw(10)
         << "Quantity" << "   " << setw(10) << "Cost each($) " << "   " << setw(10) << "Total Value($)" << endl;
    cout << endl;

    for (int a = 0; a < arr.size(); a++)
    {
        cout << arr[a].name << "   " << setw(10) << arr[a].manu << "   "
             << setw(10) << arr[a].quantity << "   " << setw(10) << arr[a].price << "   "
             << setw(10) << arr6[a] << endl;
        cout << endl;
        exact += arr[a].quantity;
        totalprice += arr6[a];
    }

    order = arr.size();
    cout << "Number of different items: " << order << endl;
    cout << "Total quantity: " << exact << endl;
    cout << "Total value of all items: $" << totalprice << endl;
    cout << endl;
}

void report(const vector<User>& arr) // This shows the reorder report.
{
    double exact = 0.0;
    int order = 0;
    double totalprice = 0.0;
    vector<int> arr5(arr.size());
    vector<double> arr7(arr.size());

    for (int a = 0; a < arr.size(); a++)
    {
        arr5[a] = arr[a].minimum - arr[a].quantity;
    }

    for (int a = 0; a < arr.size(); a++)
    {
        arr7[a] = arr5[a] * arr[a].price;
    }

    cout << endl;
    cout << setw(30) << "Reorder Report" << endl;
    cout << endl;
    cout << "Item " << "   " << setw(10) << "Manufacturer" << "   " << setw(10)
         << "Quantity" << "   " << setw(10) << "Minimum" << "   " << setw(10) << "Order"
         << "   " << setw(15) << "Cost($)" << endl;
    cout << endl;

    for (int a = 0; a < arr.size(); a++)
    {
        if (arr[a].quantity < arr[a].minimum) // checking if quantity is less than minimum required
        {
            cout << arr[a].name << "   " << setw(10) << arr[a].manu << "   "
                 << setw(10) << arr[a].quantity << "   " << setw(10) << arr[a].minimum << "   "
                 << setw(10) << arr5[a] << "   " << setw(10) << arr7[a] << endl;
            cout << endl;
            exact += arr5[a];
            totalprice += arr7[a];
            order++;
        }
    }

    cout << endl;
    cout << "Number of different items to order: " << order << endl;
    cout << "Total number to order: " << exact << endl;
    cout << "Total cost: $" << totalprice << endl;
    cout << endl;
}
