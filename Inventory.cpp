// Mirza Kazim Husain
// 12-3-21
// Purpose: To show the inventory of replacements parts of this electronic company.
// Input: User inputs name of the file he wants to open. User also selects which report he wants, or if he wants to end reviewing reports.
// Process: User puts in the name of the file. The information in file is also converted to alphabetical order. File doesnt contain all the information. 
// Information in the file is manipulated to find reorder report and inventory report.
// Inventory report give present information and Reorder report gives information for future orders.
// Output: An inventory list that give the name, manufacturer, quantity, cost of 
// each and then value. It then shows number of items, the total quantity and total value. Reorder Report shows how many orders are left.
 
 
 #include <iostream>
 #include <fstream>
 #include <iomanip>
 using namespace std;
 struct User // the struct contains the varibales from the file
 {
    string name;
    string manu;
    int quantity;
    int minimum;
    double price;
 };
 void report (struct User[], int i); // establishing function
 void inventory (struct User[], int i);
 int main()
 {
    string filename;
    cout << endl;
    cout << "Welcome I will show your inventory information." << endl;
    cout << endl;
    cout << "Please enter file name: ";
    cin >> filename;
    cout << endl;
    ifstream thefile;
    thefile.open(filename);
    if (thefile) // if file exists
    {
        int SIZE = 150;
        User arr[SIZE]; // establishing struct array
        int num = 0;
        char choice;
        while (thefile >> arr[num].name >> arr[num].manu >> arr[num].quantity >> 
        arr[num].minimum >> arr[num].price)
        {
            num++;
        }
        for (int a = 0; a < num; a ++)
       {
         for (int j = a + 1; j < num; j ++)  // making file in alphabetical order.
        {
            if (arr[a].name > arr[j].name)
            {
                User temp = arr[a];
                arr[a] = arr[j];
                arr[j] = temp;
            }
        }
       }
      do{
       cout << "Press 'I' to see the inventory report " << endl;
       cout << "Press 'R' to see the Reorder Report" << endl;
       cout << "OR press 'Q' to quit: ";
       cin >> choice;
       if (choice == 'I' || choice == 'i')
        {
           inventory (arr,num);
        }
       if (choice == 'R' || choice == 'r')
        {
            report (arr,num);
        }
       if (choice == 'q' || choice == 'Q')
        {
            cout << endl;
            cout << "Thank you. Goodbye" << endl;
            cout << endl;
        }
       }while (choice == 'I' || choice == 'i' || choice == 'R' || choice == 'r');
        thefile.close(); // closing the file
     }
       else
       cout << "File not found" << endl;
    return 0;
 }
 void inventory (struct User arr[] , int i) // This is the inventory report. Parameters is the struct array and the number of lines the file has.
 {
        double exact;
        int order;
        double totalprice;
        double arr6[i];
        for (int a = 0; a < i; a++)
          {
              arr6[a] = arr[a].price * arr[a].quantity;
          }
        cout << endl;
        cout << setw (30) << "Inventory Report" << endl;
        cout << endl;
        cout << "Item " << "   " << setw(10) << "Manufacturer" << "   " << setw(10)
        << "Quantity" << "   " << setw(10) << "Cost each($) " << "   " << setw(10) << "Total Value($)" << endl;
        cout << endl;
        for (int a = 0; a < i; a ++)
        {
            cout << arr[a].name << "   " << setw(10) << arr[a].manu << "   " <<  
            setw(10) << arr[a].quantity << "   " << setw(10) << arr[a].price << "   " << 
            setw(10) << arr6[a] << endl;
            cout << endl;
            exact += arr[a].quantity;
            totalprice += arr6[a];
        }
        order = i;
        cout << "Number of different items: " << order << endl;
        cout << "Total quantity: " << exact << endl;
        cout << "Total value of all items: $" << totalprice << endl;
        cout << endl;
 }
 void report (struct User arr[], int i) // This show the reorder report. Parameters are the struct array and number of lines the files has.
 {
        double exact;
        int order;
        double totalprice;
        int arr5[i];
        double arr7[i];
        for (int a = 0; a < i; a++)
         {
            arr5[a] = arr[a].minimum - arr[a].quantity;
         }
         for (int a = 0; a < i; a++)
         {
            arr7[a] = arr5[a] * arr[a].price;
         }
        cout << endl;
        cout << endl;
        cout << setw (30) << "Reorder Report" << endl;
        cout << endl;
        cout << "Item " << "   " << setw(10) << "Manufacturer" << "   " << setw(10)
        << "Quantity" << "   " << setw(10) << "Minimum" << "   " << setw(10) << "Order" << 
        "   " << setw(15) << "Cost($)" << endl;

        cout << endl;
        for (int a = 0; a < i; a ++)
        {
          if (arr[a].quantity < arr[a].minimum) // checking if quantity is less than minimum required
            {
              cout << arr[a].name << "   " << setw(10) << arr[a].manu << "   " << 
              setw(10) << arr[a].quantity << "   " << setw(10) << arr[a].minimum << "   " << 
              setw(10) << arr5[a] << "   " << setw(10) << arr7[a] << endl;
              cout << endl;
              exact += arr5[a];
              totalprice += arr7[a];
            }
          order = a;
        }
        cout << endl;
        cout << "Number of different items to order: " << order << endl;
        cout << "Total number to order: " << exact << endl;
        cout << "Total cost: $" << totalprice << endl;
        cout << endl;
 }
