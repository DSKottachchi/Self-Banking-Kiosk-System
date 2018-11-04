#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <sstream>  
#include <cstdio>

using namespace std;

struct user // store user details
{
	string userName;
	string pinNo;
	int userType;
};
user person;

void welcomeScreen(); 
void accountLogin(); // login into the system
void diplayCustomerChoice(); 
void displayAdminChoice();
int getBalance(string); //gets the balance stored in the file
void balanceInquiry(); //Displays the customers balance 
int amountSufficient(); //Check whether intial deposit is sufficient to open an account
int generateAccNo(); //random account number is generated
void openAccount(); //customer is able to open a new account
void depoAcc(string, int); //balance updated in the file
void cashDeposit(); //cash is deposited in the account
void withdrawAcc(string, int); //balance is deducted in the file
void cashWithdrawal(); //cash is withdrawn from the account 
void transferFunds(); //cash in account transferred to 3rd party account holder
void payBill(); //payment of bills
void manageUser(); //admin is able to select from: add/modify/delete user
void addUser(); //new user is added
void modifyUser(); //user is modified
void deleteUser(); //user is deleted
void adminBack(); //admin return to menu screen
void returnMenu(); //customer return to menu screen
void quit(); //exit from system
void userlog(string, int); //generating reports
string getdate(); //generate the current date
string gettime(); //generate the current time

int main()
{
	welcomeScreen();
	system("pause");
	return 0;
}

void welcomeScreen()
{
	int user;
	cout << "---------------------------------" << endl;
	cout << "      Kiosk Banking System      " << endl;
	cout << "---------------------------------" << endl;

	cout << "Select type of User: (Customer: Press 1) (Admin: Press 2) (Exit: Press 3)" << endl;
	cin >> user;

	if (user >= 1 && user <= 3)
	{
		switch (user)
		{
		case 1:
			accountLogin();
			break;
		case 2:
			accountLogin();
			break;
		case 3:
			exit(3);
		default:
			cout << "Error";
			exit(0);
			break;
		}
	}
	else
	{
		system("CLS");
		cout << "\nWrong selection type.\nPlease Enter selection once again" << endl;
		welcomeScreen(); //Directs User Back To Main Menu
	}

}

void accountLogin()
{
	string line = " ";
	string _pin, pin, _username;
	int _userType, choice;
	bool found = false;
	cout << "Enter username: ";
	cin >> person.userName;
	cout << "Enter 4 digit Pin number: ";
	cin >> person.pinNo;

	ifstream infile("PinNumbers.txt");
	if (infile.is_open())
	{
		while (getline(infile, line)) 
		{
			infile >> _username >> _pin >> _userType;

			if (person.userName == _username && person.pinNo == _pin && _userType == 1)
			{
				cout << "Login successful \n" << endl;
				found = true; //whem entered details equal to the ones stored in the file for the customer
				system("CLS");
				diplayCustomerChoice();
				break;
			}
			else if (person.userName == _username && person.pinNo == _pin && _userType == 2)
			{
				cout << "Login successful \n" << endl;
				found = true; //whem entered details equal to the ones stored in the file for the admin
				system("CLS");
				displayAdminChoice();
				break;
			}
		}
	}
	if (!found) //if the details do not equal the stored data
	{
		cout << "Wrong Pin number (Press 1 to Try Again) (Press 2 to go back)" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			accountLogin();
			break;
		case 2:
			system("CLS");
			welcomeScreen();
			break;
		default:
			cout << "Error";
			break;
		}
	}
	infile.close();
}


void diplayCustomerChoice()
{
	int option = 0;

	cout << "Select from options below: " << endl;
	cout << "Press 1: Balance Inquiry \nPress 2: Open Account \nPress 3: Cash Withdrawal \nPress 4: Cash Deposit \nPress 5: Fund Transfer \nPress 6: Bill Payment \nPress 7: Quit " << endl;
	cin >> option;
	if (option >= 1 & option <= 7)
	{
		switch (option)
		{
		case 1:
			system("CLS");
			balanceInquiry();
			break;
		case 2:
			system("CLS");
			openAccount();
			break;
		case 3:
			system("CLS");
			cashWithdrawal();
			break;
		case 4:
			system("CLS");
			cashDeposit();
			break;
		case 5:
			system("CLS");
			transferFunds();
			break;
		case 6:
			system("CLS");
			payBill();
			break;
		case 7:
			quit();
			break;
		default:
			break;
		}
	}
	else
	{
		cout << "Invalid choice. Please select choice once again " << endl;
	}
}

void displayAdminChoice()
{

	int choice;
	cout << "Select from options below: " << endl;
	cout << "Press 1: Generate Reports \nPress 2: Modify User \nPress 3: Quit" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		break;
	case 2:
		system("CLS");
		manageUser();
		break;
	case 3:
		quit();
		break;
	}
}

int getBalance(string accountNo)
{
	string _accountNum, _username;
	int balance;
	bool found = false;
	string line = " ";
	ifstream infile("Balance.txt");
	if (infile.is_open())
	{

		while (getline(infile, line))
		{
			infile >> _accountNum >> _username >> balance;

			if (person.userName == _username && accountNo == _accountNum)
			{
				found = true; //When acount number entered are equal to the stored ones
				return balance; 
			}

		}
		if (!found)
		{
			int choice;
			cout << "Account number does not exist: (Press 1 to Try Again) (Press 2 to Go Back to menu)" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				balanceInquiry();
				break;
			case 2:
				diplayCustomerChoice();
				break;
			}
		}
	}
	infile.close();
}

void balanceInquiry()
{
	string accountNumber;
	cout << "Enter 6 digit Account number: ";
	cin >> accountNumber;
	int balance = getBalance(accountNumber); //balance called from get balance function
	cout << "Your account balance is: $" << balance << endl << endl;
	returnMenu();
}

int amountSufficient()
{
	int amount;
	int option;
	system("CLS");
	cout << "*Note: You must make an initial deposit of $100 in order to open an account*" << endl;
	cout << "Enter amount you want to deposit: $";
	cin >> amount;
	if (amount >= 100)
	{
		return amount; //if the deposit is greater than $100 then an account can be opened
	}
	else
	{
		cout << "Amount entered is insufficient \n Unable to open a account" << endl;
		cout << "Press 1: Try Again/ Press 2: Go Back" << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			system("CLS");
			amountSufficient();
			break;
		case 2:
			system("CLS");
			openAccount();
			break;
		default:
			cout << "Error";
			break;
		}
	}
}

int generateAccNo()
{
	srand(time(NULL)); //the random account number does not get repeated
	int i = 10000 + rand() % 90000; //random account numbers generated

	return i;
}

void openAccount()
{

	ofstream outfile;
	outfile.open("Balance.txt", ios::app | ios::out);

	int accNo, bal;
	stringstream convert;
	string n, account;
	int accountType, depositType;

	cout << "Enter the type of account you want to open: (Press 1: Current Account/ Press 2: Savings Account)" << endl;
	cin >> accountType;
	cout << "Do you want to make a cash deposit/ fund transfer? (Press 1: Cash Deposit/ Press 2: Fund transfer)" << endl;
	cin >> depositType;

	if (accountType >= 1 && accountType <= 2)
	{
		//check the deposit type
		if (accountType == 1)
		{
			bal = amountSufficient();
			accNo = generateAccNo();
			convert << accNo;
			n = convert.str();
			account = n + 'C';

			if (outfile.is_open())
			{
				outfile << '\n' << account << " " << person.userName << " " << bal;
				cout << "Account number: " << account << endl;
				cout << "Account added sucessfully" << endl;
			}
		}

		else if (accountType == 2)
		{
			bal = amountSufficient();
			accNo = generateAccNo();
			convert << accNo;
			n = convert.str();
			account = n + 'S';

			if (outfile.is_open())
			{
				outfile << '\n' << account << " " << person.userName << " " << bal;
				cout << "Account number: " << account << endl;
				cout << "Account added sucessfully" << endl;
			}
		}
	}
	else
	{
		system("CLS");
		cout << "Wrong Account Type Selection" << endl;
		openAccount();
	}
	returnMenu();
	outfile.close();

	//check the type of account
}

void depoAcc(string accNo,int deposit)
{
	string line = " ";
	string  _accNo, _name;
	int  balance, newbal;

	ifstream infile;
	infile.open("Balance.txt");

	ofstream outfile;
	outfile.open("newbal.txt", ios::out | ios::app);

	balance = getBalance(accNo);
	newbal = balance + deposit;
	if (infile.fail())
	{
		cout << "Error loading file";
		exit(1);
	}
	else
	{
		while (getline(infile, line))
		{
			while (infile >> _accNo >> _name >> balance)
			{
				if (accNo == _accNo)
				{
					outfile << _accNo << " " << _name << " " << newbal << endl;
				}
				else
				{
					outfile << _accNo << " " << _name << " " << balance << endl;
				}
			}
		}
	}
	
	outfile.close();
	infile.close();
}

void cashDeposit()
{
	string accNo;
	int deposit;

	cout << "Enter your account number: ";
	cin >> accNo;
	cout << "Enter Amount: ";
	cin >> deposit;
	depoAcc(accNo, deposit);
	userlog(accNo, deposit);
	cout << "Cash deposited successfully" << endl;
	returnMenu();
}

void withdrawAcc(string accNo, int withdraw)
{
	string line = " ";
	string _accNo, _name;
	int balance, newbal;
	ifstream infile;
	infile.open("Balance.txt");

	ofstream outfile;
	outfile.open("newbal.txt", ios::out | ios::app);

	balance = getBalance(accNo);
	newbal = balance - withdraw;

	if (infile.fail())
	{
		cout << "Error loading file";
		exit(1);
	}
	else
	{
		if (newbal >= 100)
		{
			while (getline(infile, line))
			{
				while (infile >> _accNo >> _name >> balance)
				{
					if (accNo == _accNo)
					{
						outfile << _accNo << " " << _name << " " << newbal << endl;
					}
					else
					{
						outfile << _accNo << " " << _name << " " << balance << endl;
					}
				}
			}
			cout << "Cash withdrawn successfully" << endl;

		}
		else
		{
			cout << "Amount insufficient! " << endl;
		}
	}

	outfile.close();
	infile.close();
}

void cashWithdrawal()
{
	string accNo;
	int withdraw;

	cout << "Enter account number: ";
	cin >> accNo;
	cout << "Enter amount you want to withdraw: ";
	cin >> withdraw;

	withdrawAcc(accNo, withdraw);
	returnMenu();
}

void transferFunds()
{
	string line = " ";
	string name, accNo;
	string _accNo, _name, accountNumber;
	int transfer, _bal, option;

	ifstream infile;
	infile.open("fundTransferAcc.txt");

	ofstream outfile;
	outfile.open("newfundTrans.txt", ios::out | ios::app);

	if (infile.fail())
	{
		cout << "Error loading file";
		exit(1);
	}
	cout << "You will be charged an amount to $150 per transfer \n" << endl;
	cout << "Enter your account number: ";
	cin >> accountNumber;
	cout << "Enter 3rd party Account holder's Bank: " << endl;
	cin >> name;
	cout << "Enter 3rd party Account holder's Account No: " << endl;
	cin >> accNo;
	cout << "Enter amount you want to transfer: " << endl;
	cin >> transfer;

	while (getline(infile, line))
	{
		while (infile >> _accNo >> _name >> _bal)
		{

			if (transfer <= _bal)
			{
				int newTrans = _bal + transfer;
				if (name == _name && _accNo == accNo)
				{
					outfile << _accNo << " " << _name << " " << newTrans << endl;
				}
				else
				{
					outfile << _accNo << " " << _name << " " << _bal << endl;
				}

			}
			else
			{
				cout << "Amount insufficient to transfer funds" << endl;
				cout << "Press 1: To Try again \n Press 2: To go back";
				cin >> option;
				switch (option)
				{
				case 1:
					transferFunds();
					break;
				case 2:
					diplayCustomerChoice();
					break;
				}
			}
		}

	}
	withdrawAcc(accountNumber, transfer + 150);
	cout << "Funds transfered" << endl;
	returnMenu();
	infile.close();
	outfile.close();
}

void payBill()
{
	int option, amount, _bal;
	string payment, accNo, _payment;
	string line = " ";
	cout << "Select account you want to pay for: \nPress 1.Cable TV \nPress 2.Electricity \nPress 3.Telephone \nPress 4.Water \nPress 5.Internet \nPress 6. Insuarance \n";
	cin >> option;
	switch(option)
	{
	case 1: 
		payment = "CableTV";
		break;
	case 2: 
		payment = "Electricity";
		break;
	case 3:
		payment = "Telephone";
		break;
	case 4:
		payment = "Water";
		break;
	case 5:
		payment = "Internet";
		break;
	case 6:
		payment = "Insuarance";
		break;
	default:
		cout << "Error" << endl;
		break;
	}

	cout << "Enter your account number: ";
	cin >> accNo;
	cout << "Enter amount you want to pay: ";
	cin >> amount;
	withdrawAcc(accNo, amount);
	
	ifstream infile;
	infile.open("payeeDetails.txt");
	ofstream outfile;
	outfile.open("newpayee.txt", ios::out | ios::app);

	if (infile.fail())
	{
		cout << "Error loading file";
		exit(1);
	}

	while (getline(infile, line))
	{
		while (infile >> _payment >> _bal)
		{
			if (amount <= _bal)
			{
				int newpayeebal = _bal + amount;
				if (payment == _payment)
				{
					outfile << payment << " " << newpayeebal << endl;
				}
				else
				{
					outfile << _payment << " " << _bal << endl;
				}

			}
			else
			{
				cout << "Amount insufficient to Paybill funds" << endl;
				cout << "Press 1: To Try again \n Press 2: To go back";
				cin >> option;
				switch (option)
				{
				case 1:
					payBill();
					break;
				case 2:
					diplayCustomerChoice();
					break;
				}
			}
		}

	}

}
	
string getdate()
{
	char date[9];
	_strdate_s(date);
	string ctime = date;
	return date;
}

void userlog(string accountNo, int amount)
{
	ofstream outfile("log.txt", ios::app| ios::out);
	string date = getdate();
	string time = gettime();
	outfile << date << " " << time << " " << accountNo << " " << amount << endl;

    outfile.close();
}

string gettime()
{
	char time[9];
	_strtime_s(time);
	string ctime = time;
	return time;
}

void manageUser()
{
	int choice;
	system("CLS");
	cout << "Press 1. Add User" << endl << "Press 2. Modify User" << endl << "Press 3. Delete User" << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		system("CLS");
		addUser();
		break;
	case 2:
		system("CLS");
		modifyUser();
		break;
	case 3:
		system("CLS");
		deleteUser();
		break;
	}
}

void addUser()
{
	string accountNo, balance;
	ofstream outfile;
	outfile.open("PinNumbers.txt", ios::app | ios::out);
	if (!outfile)
	{
		cout << "Error in opening file" << endl;
	}

	cout << "Enter Username: ";
	cin >> person.userName;
	cout << "Enter pin number: ";
	cin >> person.pinNo;
	cout << "Enter User type (1.Customer / 2.Admin)" << endl;
	cin >> person.userType;

	outfile << person.userName << " " << person.pinNo << " " << person.userType << endl;
	
	if (person.userType == 1)
	{
		openAccount();
	}

	cout << "User added sucessfully" << endl;

	outfile.close();
	adminBack();
}


void modifyUser()
{
	string pin1, _name, accNo, balance;
	string name, newPin, newName;
	string line = " ";
	int userType;

	ifstream infile;
	infile.open("PinNumbers.txt");

	ofstream outfile;
	outfile.open("newpin.txt", ios::out | ios::app);

	ifstream balfile;
	balfile.open("Balance.txt");

	ofstream newbalfile;
	newbalfile.open("newbal.txt", ios::out | ios::app);

	cout << "Enter name you want to update: ";
	cin >> name;
	cout << "Enter new name: ";
	cin >> newName;
	cout << "Enter new pin number: ";
	cin >> newPin;

	if (infile.fail())
	{
		cout << "Error loading file";
		exit(1);
	}

	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			while (infile >> _name >> pin1 >> userType)
			{
				if (name == _name && userType == 1)
				{
					outfile << newName << " " << newPin << " " << "1" << endl;
				}
				else if (name == _name && userType == 2)
				{
					outfile << newName << " " << newPin << " " << "2" << endl;
				}
				else
				{
					outfile << _name << " " << pin1 << " " << userType << endl;
				}
			}
		}
	}

	if (balfile.is_open())
	{
		//infile.read(reinterpret_cast<char*>(&person.userName), sizeof(person));
		while (getline(balfile, line))
		{
			while (balfile >> accNo >> _name >> balance)
			{
				if (name == _name && userType == 1)
				{
					newbalfile << accNo << " " << newName << " " << balance << endl;
				}
				else
				{
					newbalfile << accNo << " " << _name << " " << balance << endl;
				}
			}
		}
	}
	cout << "User data has been modified" << endl;

	balfile.close();
	newbalfile.close();
	infile.close();
	outfile.close();
	
	adminBack();
}

void deleteUser()
{
	string n, pin, name, accNo, balance;
	int userType;
	string line = " ";

	ifstream infile;
	infile.open("PinNumbers.txt");

	ofstream outfile;
	outfile.open("newpin.txt", ios::out | ios::app);

	ifstream balfile;
	balfile.open("Balance.txt");

	ofstream newbalfile;
	newbalfile.open("newbal.txt", ios::out | ios::app);

	cout << "Enter name you want to delete: ";
	cin >> n;

	if (infile.fail())
	{
		cout << "Error loading file";
		exit(1);
	}

	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			while (infile >> name >> pin >> userType)
			{
				if (n == name)
				{
					break;
				}
				else
				{
					outfile << name << " " << pin << " " << userType << endl;
				}
			}
		}
	}

	if (balfile.is_open())
	{
		//infile.read(reinterpret_cast<char*>(&person.userName), sizeof(person));
		while (getline(balfile, line))
		{
			while (balfile >> accNo >> name >> balance)
			{
				if (n == name)
				{
					break;
				}
				else
				{
					newbalfile << accNo << " " << name << " " << balance << endl;
				}
			}
		}
	}

	cout << "User data has been deleted!" << endl;

	balfile.close();
	newbalfile.close();
	infile.close();
	outfile.close();

	//remove("PinNumbers.txt");
	//rename("newpin.txt", "PinNumbers.txt");
	
	adminBack();
}

void adminBack()
{
	int goback;
	cout << "\nPress 1 to go back: ";
	cin >> goback;
	if (goback == 1)
	{
		system("CLS");
		displayAdminChoice();
	}
}

void returnMenu()
{
	int option;
	cout << endl;
	cout << "Press 1: To go Back" << endl << "Press 2: To Exit System" << endl;
	cin >> option;
	while (option >= 1 && option <= 2)
	{
		switch (option)
		{
		case 1:
			system("CLS");
			diplayCustomerChoice();
		case 2:
			system("CLS");
			cout << "Exiting System.......";
			exit(0);
		}
	}
	system("CLS");
	cout << " *** Wrong selection choice ***" << endl << "Please try again" << endl;
	returnMenu();
}

void quit()
{
	system("CLS");
	int choice;
	cout << "Are you sure you want to quit? (Press 1: Yes / Press 2: No) " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		exit(1);
		break;
	case 2:
		diplayCustomerChoice();
		break;
	}
}