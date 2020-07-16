#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
void CustReserve();
int ReserveSeat();
int Payment(string);
void DisplaySeats();
void DisplayInfo();
void SetColor(int);
void ClearConsoleToColors(int, int);
int h;
struct SeatCode{
	string SeatCodes;
}NumSeats[100];
int main()
{
	system("cls");
	int choice;
	bool s = true;
	cout << "*****************************************************" << endl;
	cout << "**                                                 **" << endl;
	cout << "**                                                 **" << endl;
	cout << "**            CONCERT RESERVATION SYSTEM           **" << endl;
	cout << "**                                                 **" << endl;
	cout << "**                                                 **" << endl;
	cout << "*****************************************************" << endl << endl;
	cout << "What would you want to do?" << endl;
	cout << "1.) Reserve a seat / Buy tickets" << endl;
	cout << "2.) Display the reserved seats" << endl;
	cout << "3.) Display information on the program of the concert" << endl;
	cout << "4.) Exit" << endl;
	while (s){
	cout << "Enter your choice: ";
	cin >> choice;
	switch(choice){
		case 1:
			CustReserve();
			s=0;
			break;
		case 2:
			DisplaySeats();
			main();
			s=0;
			break;
		case 3:
			DisplayInfo();
			s=0;
			break;
		case 4:
			return 0;
			break;
		default:
			cout << "Please choose between 1 to 4"<< endl;
			system("pause");
			s=0;
			main();
			break;
	}
	}
}

void CustReserve()
{
	system("cls");
	string Fname, Lname, choice, Fname1, Lname1; 
	int seats, price, price1;
	bool s = true;
	cout << "Enter the required information: " << endl;
	cout << "First Name: ";
	cin >> Fname;
	cout << "Last Name: ";
	cin >> Lname;
	while (s){
		cout << "Would you like to view first the reserved seats? (y/n) ";
		cin >> choice;
		if (choice == "y" || choice == "Y") {
			DisplaySeats();
		} else if (choice == "n" || choice =="N"){
			s = 0;
		} else {
			cout << "Please enter 'y' or 'n' " << endl; 
		}
	}
	s= true;
	while (s){
		cout << "Would you like to reserved a seat? (y/n) ";
		cin >> choice;
		cout << endl;	
		if (choice == "y" || choice == "Y") {
			 price = ReserveSeat();
		}else if (choice == "n" || choice =="N"){
			system("pause");
			s=0;
			main();
		} else {
			cout << "Please enter 'y' or 'n' " << endl; 
		}
	}
	int Number, Number1;
	ifstream Icust;
	Icust.open("Customer.txt", ios::app);
	while (Icust >> Number >> Fname1 >> Lname1 >> price1){
		Number1 = Number;
	}
	Icust.close();
	ofstream Ocust;
	Ocust.open("Customer.txt", ios::app);
	Ocust << Number1 + 1 << " " << Fname << " " << Lname << " " << price << endl;
	Ocust.close();
	cout << "First Name: " << Fname <<endl;
	cout << "Last Name: " << Lname << endl;
	cout << "Total Price: P" << price << endl;
	int choice1;
	string CC;
	char sign;
	cout << "Payments: " << endl 
		 << "Would you like to pay in Cash or Credit Card ?" << endl
		 << "Press 1 for Cash and 2 for Credit Card: ";
		cin >> choice1;
	switch (choice1){
		case 1: 
			cout <<"Please pay your ticket at the gate" << endl;
			break;
		case 2:
			cout<< "Please input your Credit Card no.: " ; 
			cin >> CC;
			cout<< "Enter your full name (This will be your electronic signiture.): "; 
			cin >> sign;
			break;
			}
	system("cls");
	cout << "Please print your ticket: " << endl << endl;
	cout << "----------Concert Reservation Ticket----------" << endl << endl
		 << "Customer Information: " << endl
		 << "Name: " << Fname << " " << Lname << endl
		 << "Reservation Number: " << Number1 + 1 << endl << endl
		 << "Seat Reservation Information: " << endl
		 << "Number of seats reserved: " << h << endl
		 << "Seat/s Reserved: " << endl;
	for (int q=0; q<h; q++){
		cout << NumSeats[q].SeatCodes << " ";
	}		 
	cout << endl << "Total Price: P" << price << endl;
	cout << "Status: ";
	if (choice1 == 1){
		cout << "Unpaid, please pay balance at the concert arena" << endl << endl;
	} else if (choice1 == 2){
		cout << "Paid, Via Credit Card" << endl <<endl;
	}
	cout << "--------This will serve as your ticket--------" << endl
		 << "--------Please present this upon entry--------" << endl;
	return;
}

int ReserveSeat()
{
    int nseats;
    int counter = 0;
    int price = 0;
	string seat, seats;
	cout << "RESERVING SECTION" << endl;
	cout << "-----------------"<< endl;
	cout << "No. of Seat/s: ";
	cin >> nseats;
	h = nseats;
	for(int x=0; x<nseats; x++){
		ifstream asd;
		asd.open("SeatPlan.txt");
		ofstream temp("temp.txt");
		cout << "Seat Code: ";
		bool check = true;
		while (check){
			cin >> seats;
			if (seats == "sta"){
				cout << "Error 'sta' represents stage" << endl;
				cout << "Seat Code: ";
			}else if (Payment(seats) == 0){
				cout << "Error: Seat may be reserved or may not exist, please enter another seat code: " << endl;
				cout << "Seat Code: ";
			} else if(Payment(seats) > 0){
				check = 0;
			}
		}
		price = price + Payment(seats);
		NumSeats[x].SeatCodes = seats;
		while(asd >> seat){
			if(seat == seats){
				temp << "RES ";
				counter = counter + 1;
				if (counter == 34){
					temp << endl;
					counter = 0;
				}
			}else{
				temp << seat << " ";
				counter = counter + 1;
				if (counter == 34){
					temp << endl;
					counter =0;
				}
			}
		}
		asd.close();
		temp.close();
		remove("SeatPlan.txt");
		rename("temp.txt", "SeatPlan.txt");
	}
	cout << "Total price is: P" << price << endl;
	cout << "YOUR SEAT/S HAS BEEN RESERVED." << endl;
	system("pause");
	system("cls");
	return price;
}

int Payment(string code)
{
	int counter1 = 0;
	int counter2 = 0;
	int value = 0;
	string seat;
	ifstream asd;
	asd.open("SeatPlan.txt");
	while(asd >> seat){
		if (seat == code){
		if (counter1 < 3){
			value = 500;
		}
		if (counter1 > 30){
			value = 500;
		}
		if (counter1 > 2 && counter1 < 31 && counter2 > 15){
			value = 500;
		}
		if (counter1 > 2 && counter1 <6 && counter2 <16){
			value = 2500;
		}
		if (counter1 > 5 && counter1 < 28 && counter2 > 12 && counter2 < 16){
			value = 2500;
		}
		
		if (counter1 > 5 && counter1 <9 && counter2 <10){
			value = 5000;
		}
		if (counter1 > 5 && counter1 < 28 && counter2 > 9 && counter2 < 13){
			value = 5000;
		}
		if (counter1 > 8 && counter1 <12 && counter2 <10){
			value = 7500;
		}
		if (counter1 > 11 && counter1 < 22 && counter2 > 6 && counter2 < 10){
			value = 7500;
		}
		if (counter1 == 12 && counter2 <6){
			value = 10000;
		}
		if (counter1 == 21 && counter2 <6){
			value = 10000;
		}
		if (counter1 > 21 && counter1 <25 && counter2 <10){
			value = 7500;
		}
		if (counter1 > 24 && counter1 <28 && counter2 <10){
			value = 5000;
		}
		if (counter1 > 27 && counter1 <31 && counter2 <16){
			value = 2500;
		}
		if (counter2 ==6 && counter1 >11 && counter1 < 22){
			value = 10000;
		}
		
		}
		counter1= counter1 + 1;
		if (counter1 == 34){
			counter1 = 0;
			counter2= counter2 + 1;
		}
	}
	asd.close();
	return value;
}

void DisplaySeats() 
{
	system("cls");
	string seat;
	string choice;
	ifstream asd;
	asd.open("SeatPlan.txt");
	int counter1 = 0, counter2 =0;
	while(asd >> seat){
		if (counter1 < 3){
			SetColor(1);
			cout << seat;
		}
		if (counter1 > 30){
			SetColor(1);
			cout << seat;
		}
		if (counter1 > 2 && counter1 < 31 && counter2 > 15){
			SetColor(1);
			cout << seat;
		}
		if (counter1 > 2 && counter1 <6 && counter2 <16){
			SetColor(2);
			cout << seat;
		}
		if (counter1 > 5 && counter1 < 28 && counter2 > 12 && counter2 < 16){
			SetColor(2);
			cout << seat;
		}
		
		if (counter1 > 5 && counter1 <9 && counter2 <10){
			SetColor(3);
			cout << seat;
		}
		if (counter1 > 5 && counter1 < 28 && counter2 > 9 && counter2 < 13){
			SetColor(3);
			cout << seat;
		}
		if (counter1 > 8 && counter1 <12 && counter2 <10){
			SetColor(4);
			cout << seat;
		}
		if (counter1 > 11 && counter1 < 22 && counter2 > 6 && counter2 < 10){
			SetColor(4);
			cout << seat;
		}
		if (counter1 == 12 && counter2 <6){
			SetColor(5);
			cout << seat;
		}
		if (counter1 == 21 && counter2 <6){
			SetColor(5);
			cout << seat;
		}
		if (counter1 > 12 && counter1 <21 && counter2 <6){
			SetColor(15);
			cout << seat;
		}
		if (counter1 > 21 && counter1 <25 && counter2 <10){
			SetColor(4);
			cout << seat;
		}
		if (counter1 > 24 && counter1 <28 && counter2 <10){
			SetColor(3);
			cout << seat;
		}
		if (counter1 > 27 && counter1 <31 && counter2 <16){
			SetColor(2);
			cout << seat;
		}
		if (counter2 ==6 && counter1 >11 && counter1 < 22){
			SetColor(5);
			cout << seat;
		}
		cout << " | ";
		counter1+=1;
		if (counter1 == 34){
			cout << endl;
			counter1 = 0;
			counter2+=1;
			cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	SetColor(15);
	asd.close();
	cout << "VIP/PINK - P10000" << endl;
	cout << "RED - P7500" << endl;
	cout << "CYAN - P5000" << endl;
	cout << "GREEN - P2500" << endl;
	cout << "BLUE - P500" << endl << endl;
	system("pause");
	return;
}

void DisplayInfo()
{
	system("cls");
	cout << endl;
	cout << "BRUNO MARS LIVE IN MANILA 2017" << endl;
	cout << "MALL OF ASIA ARENA" << endl;
	cout << "April 9, 2017 - 7pm" << endl;
	cout << endl;
	cout << "Ticket Prices:" << endl;
	cout << "VIP/PINK - P10000" << endl;
	cout << "RED - P7500" << endl;
	cout << "CYAN - P5000" << endl;
	cout << "GREEN - P2500" << endl;
	cout << "BLUE - P500" << endl << endl;
	system("pause");
	main();

}

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void ClearConsoleToColors(int ForgC, int BackC)
 {
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                     
 COORD coord = {0, 0};
 
  DWORD count;

               
 CONSOLE_SCREEN_BUFFER_INFO csbi;
                 
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                         
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                         
      SetConsoleCursorPosition(hStdOut, coord);
 }
 return;
}
