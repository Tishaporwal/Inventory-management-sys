#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<conio.h>  
#include<stdlib.h>

using namespace std;

class mall {
	
    int pno;
    char name[30];
    float price, dis;
    int st;


public:
	
    void getdata();
    void showdata();
    int retpno();
    float retprice();
    char* retname();
    int retdis();
    int retst();
    void updateStock(int quantity);
    
};

fstream f;
mall m;


void mall::getdata() 
{
    char ch;
    // Change console color
    system("color e4");
    cout << "\n\tEnter the details of the product...";
    cout << "\n\tProduct No: ";
    cin >> pno;
    // Clear input buffer
    cin.get(ch);   
    cout << "\n\tProduct Name: ";
    cin.getline(name, 30);
    cout << "\n\tProduct Price: "; 
	cin >> price;
    cout << "\n\tProduct Discount(%): "; 
	cin >> dis;
    cout << "\n\tStock: "; 
	cin >> st;
}


void mall::showdata() 
{
    cout << setw(4) << pno << setw(20) << name << setw(8) << price << setw(10) << st << setw(10) << dis << "%" << "\n\t";
}


int mall::retpno()
{ 
 return pno;
}


float mall::retprice()
{ 
 return price;
}


char* mall::retname()
{ 
 return name; 
}



int mall::retdis()
{ 
 return dis; 
}

int mall::retst() 
{
 return st;
}

void mall::updateStock(int quantity) 
{
    st -= quantity;
}

// Function to display menu
void menu()
 {
    cout << "\n\t";
    system("color e4");
    
    cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(8) << "Price" << setw(8) << "Stock" << setw(15) << "Discount";
    cout << "\n\t--------------------------------------------------------\n\t";
}

// Function to create a new product
void enter()
{
	// Clear screen
	system("cls");
	system("color e4");
	// Open file in append mode
	f.open("mall.txt",ios::out|ios::app);
	m.getdata();
	// Write data to file
	f.write((char*)&m,sizeof(mall));
	f.close();
	
	cout<<"\n\n\tProduct has been created...!!! ";
	getch();
}

// Function to display all products
void display()
{
	system("color e4");
	cout<<"\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";

	f.open("mall.txt",ios::in);
	menu();

	while(f.peek() != EOF) 
	{
		f.read((char*)&m,sizeof(mall));
		m.showdata();
	}
	f.close();
	getch();
}

// Function to search for a product
void search()
 {
    int no, flag = 0;
    system("cls");
    system("color e4");
    
    cout << "\n\n\tEnter the Product No. of the Product to be searched: ";
    cin >> no;
    f.open("mall.txt", ios::in);
    menu();
    
    while (f.read((char*)&m, sizeof(mall))) 
	{
        if (m.retpno() == no) 
		{
            m.showdata();
            flag = 1;
        }
    }
    f.close();
    if (flag == 0)
        cout << "\n\n\tRecord does not exist...!!!";
    cin.ignore();
    cin.get();
}

// Function to update product details
void update() 
{
    int no, found = 0;
    system("cls");
    system("color e4");
    cout << "\n\n\tTo Update...Enter The Product No: ";
    cin >> no;
    f.open("mall.txt", ios::in | ios::out);
    menu();
    while (f.read((char*)&m, sizeof(mall)) && found == 0) 
	{
        if (m.retpno() == no)
		 {
            m.showdata();
            m.getdata();
            int pos = -1 * static_cast<int>(sizeof(m));
            f.seekp(pos, ios::cur);
            f.write((char*)&m, sizeof(mall));
            cout << "\n\n\t Record has been Updated...!!!";
            found = 1;
        }
    }
    f.close();
    if (found == 0)
        cout << "\n\n\tRecord Not Found ";
    cin.ignore();
    cin.get();
}

// Function to delete a product
void erase() 
{
    int no;
    system("cls");
    system("color e4");
    cout << "\n\n\n\tTo Delete...Enter The product No: ";
    cin >> no;
    f.open("mall.txt", ios::in | ios::out);
    fstream ft;
    ft.open("temp.txt", ios::out);
    f.seekg(0, ios::beg);
    while (f.read((char*)&m, sizeof(mall))) 
	{
        if (m.retpno() != no) 
		{
            ft.write((char*)&m, sizeof(mall));
        }
    }
    ft.close();
    f.close();
    remove("mall.txt");
    rename("temp.txt", "mall.txt");
    cout << "\n\n\tRecord has been Deleted...!!!";
    cin.ignore();
    cin.get();
}

// Function to place an order
void place_order() 
{
	
    int order[30], quan[30], i = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    system("cls");
    system("color e4");
    display();
    cout << "\n\n\t============================";
    cout << "\n\t      PLACE YOUR ORDER";
    cout << "\n\t============================\n";
    do {
        cout << "\n\n\tEnter The Product No: ";
        cin >> order[i];
        cout << "\tQuantity: ";
        cin >> quan[i];
        f.open("mall.txt", ios::in | ios::out);
        bool found = false;
        while (f.read((char*)&m, sizeof(mall))) 
		{
            if (m.retpno() == order[i])
			 {
                if (quan[i] > m.retst()) 
				{
                    cout << "\n\tOnly " << m.retst() << " items of " << m.retname() << " are available. Do you want to order " << m.retst() << " item(s)? (Y/N): ";
                    char choice;
                    cin >> choice;
                    if (choice == 'Y' || choice == 'y')
					{
                        quan[i] = m.retst();
                        found = true;
                    } else {
                        quan[i] = 0;
                    }
                }
				    else 
			     	{
                      found = true;
                    }
                break;
            }
        }
        f.close();
        if (!found) {
            cout << "\n\tProduct not found!";
            quan[i] = 0;
        }
        i++;
        cout << "\n\tDo you want to order another product ?(y/n): ";
        cin >> ch;
    } 
	while (ch == 'y' || ch == 'Y');

    for (int x = 0; x < i; x++) 
	{
        if (quan[x] != 0)
		 {
            if (quan[x] == m.retst()) 
			{
                cout << "\n\tLow stock alert for Product No: " << order[x] << " (" << m.retname() << ")";
            }
        }
    }

    cout << "\n\n\tThank You...!!!";
    cout << "\n\n\t\t************************BILL************************\n\n\t\t";
    cout << setw(4) << "P No" << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(8) << "Price" << setw(8) << "Amount" << setw(10) << "Discount" << endl;
    cout << "\t\t------------------------------------------------------------\n\t\t";
    f.open("mall.txt", ios::in | ios::out);
    for (int x = 0; x < i; x++)
	 {
        if (quan[x] != 0)
		 {
            while (f.read((char*)&m, sizeof(mall))) 
			{
                if (m.retpno() == order[x]) {
                    amt = m.retprice() * quan[x];
                    damt = amt - (amt * m.retdis() / 100);
                    cout << setw(4) << order[x] << setw(20) << m.retname() << setw(10) << quan[x] << setw(8) << m.retprice() << setw(8) << amt << setw(10) << damt << "\n\t\t";
                    total += damt;
                    int pos = -1 * static_cast<int>(sizeof(m));
                    f.seekp(pos, ios::cur);
                    m.updateStock(quan[x]);
                    f.write((char*)&m, sizeof(mall));
                    f.clear(); 
                    f.seekg(0, ios::beg); 
                    break;
                }
            }
        }
    }
    f.close();
    cout << "\n\t\t--------------------------------------------------------------";
    cout << "\n\t\tThank You...Visit Once Again...............TOTAL = " << "Rs." << total;
    cout << "\n\t\t--------------------------------------------------------------";
    cin.ignore();
    cin.get();
}

void intro()
 {
    system("color b4");
    cout << "\n\n\n\n\n\n\n\n\n\t\t\t\tINVENTORY MANAGEMENT SYSTEM\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cin.ignore();
    cin.get();
}

void welcome()
 {
    system("cls");
    system("color a4");
    cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\tWelcome to GROCIFY";
    cin.ignore();
    cin.get();
}

// Function to verify password for admin access
int password() 
{
    char a[20], b[20];
    int i, j, flag = 0;
    cout << "\n";
    for (i = 0; i < 30; i++)
        cout << "*~";
    cout << "\n\t\t\t\t\tENTER THE PASSWORD TO LOGIN ADMIN MODULE\n";
    for (j = 0; j < 30; j++)
        cout << "*~";
    cout << "\n\n\n\n";
    do 
	{
        cout << "\n\n\n\n\t\t\t\t\t\tEnter Password: ";
        cin >> a;
        ifstream pass("password.dat");
        pass >> b;
        if (strcmp(a, b) == 0)
            flag = 1;
        else {
            cout << "\n\n\t\t\t\t\tWRONG PASSWORD!!!";
            cout << "\n\n\t\t\tDo you want to try again? (Y/N): ";
            char choice;
            cin >> choice;
            if (choice != 'Y' && choice != 'y')
                break;
        }
        pass.close();
    } while (!flag);
    return flag;
}

// Function to display admin menu
void admin_menu() 
{
    char ch;
    do 
	{
        system("cls");
        system("color e4");
        cout << "\n\n\t1.Create Products";
        cout << "\n\n\t2.Display Products";
        cout << "\n\n\t3.Search Products ";
        cout << "\n\n\t4.Modify Products";
        cout << "\n\n\t5.Delete Products";
        cout << "\n\n\t6.Place an Order";
        cout << "\n\n\t7.EXIT";
        cout << "\n\n\tEnter Your Choice: ";
        ch=getche();
        
        switch (ch) 
		{
          case '1': 
		            enter();
		            break;
          case '2':
		            system("cls"); 
					display(); 
					break;
          case '3': 
		            search(); 
					break;
          case '4':
		            update();
				    break;
          case '5':
		            erase(); 
					break;
          case '6': 
		            place_order(); 
					break;
          case '7': 
		            exit(0);
		            
          default: cout << "\a";
        }
    } 
	while (ch != '7');
    getch();
}

// Main function
int main() 
{
    int opt, pass;
    
    intro();
    welcome();
    
    system("cls");
    cout << "\n\n\n\n\n";
    
    for (int i = 0; i < 30; i++)
        cout << "\a";
    cout << "\n\n\n\n\n\t\t\t\t\t---------------------:LOGIN AS:---------------------\n";
    cout << "\n\t\t\t\t1. CUSTOMER";
    cout << "\n\t\t\t\t2. ADMINISTRATOR";
    cout << "\n\n\n\n\n\t\t\t\t\t\tENTER YOUR OPTION: ";
    cin >> opt;
    
    switch (opt) 
	{
     case 1:
        place_order();
        break;
     case 2:
        pass = password();
        if (pass)
	    {
            admin_menu();
        } 
		else
	    {
            cout << "\n\n\t\t\t\t\tWRONG PASSWORD!!!";
        }
        break;
    default:
        cout << "\n\n\t\t\t\t\tWRONG OPTION!!!";
    }
    return 0;
}

