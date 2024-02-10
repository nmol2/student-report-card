/*////Shri Gneshayeh Namah/////
******with the name of god*********
*Project on Management the record or Student Marks for a Institute
* contains two class 1.student 2.admin
**student class relate to the all task perform on to generate marksheet and management of data
**admin class relate to provide authenticity to the user of this app
WORK ON PROGRESS, there in now continous modification,updation and maintinance is required*/

#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <process.h>
#include <stdlib.h>
#include <dos.h>

#include <windows.h>

using namespace std;
void gotoxy(short x, short y);
void m_gets(char *str);
void credits();
void mainmenu();
void menu1();

void secureLogin();
//void signup();

class student
{
public:
	long roll;		  //Roll Number or the Student
	char name[20];	  //Full Name
	char subj[6][20]; //List of the subjects Student have
	int mks[6];		  //Array for total marks per subject
	int th[6];		  //Arrray for marks obtain in Theory papers
	int pr[6];		  //Array for marks obtain in Practicles
	//int i;
	int tot;	  //Grand Total of the Student
	float per;	  //Pecentage
	char g[6][2]; //Grades according to marks per subject
	char re[4];	  //Remark for student: FAIL/PASS

	void writes();	//Writes all data collected in a file
	void calc();	//Calculates the Pecentage,Grades,Total,GrandTotal and necessary data
	void subject(); //Help to selection of subjects
	void input();	//Takes all input by USER
	void reads();	//Reads previous saved data from file
	void output();	//Displays the data on screen in a Marksheet formate
	void failed();	//Diplays the list of all failed students
	void lin()		//Print line contain Dots(.)
	{
		cout << "\n------------";
		cout << "--------------";
		cout << "--------------";
		cout << "--------------";
		cout << "--------------";
		cout << "------------\n";
	}
	void star() //Print line contain Stars(*)
	{
		cout << "\n************";
		cout << "**************";
		cout << "**************";
		cout << "**************";
		cout << "**************";
		cout << "************\n";
	}
	void count(); //Shows the total number of students whose data entered
} s;

void student::input()
{
	//clrscr();
	int n;
	gotoxy(1, 5);
	cout << "\n\n\tENTER ROLL NUMBER OF STUDENT:";
	cin >> roll;

	cout << "\tENTER NAME OF THE STUDENT:";
	m_gets(name);

	cin.getline(name, sizeof(name) / sizeof(name[0]));

	cout << "\tENTER SUBJECTS OF THE STUDENT:";
	subject();

	cout << "\tENTER THE MARKS:-";
	cout << "\n(of the following Subjects & there Practicals)";
	cout << "\n(if subject has no practical then enter '55')\n";
	for (int i = 0; i < 6; i++)
	{
		cout << subj[i] << " -> Theory:";
		cin >> th[i];
		cout << "\t\tPractical:";
		cin >> pr[i];
	}
}

void student::subject()
{
	int cod;
	cout << "\nSUBJECT MENU:-";
	cout << "\n\t1.English"
		 << "\n\t2.Physics"
		 << "\n\t3.Chemistry"
		 << "\n\t4.Maths"
		 << "\n\t5.Bio"
		 << "\n\t6.Hindi"
		 << "\n\t7.Computer Science"
		 << "\n\t8.Physical Education";
	cout << "\nEnter the Subjects Code\n";
	for (int i = 0; i < 6; i++)
	{
	back:
		cout << i + 1 << ":";
		cin >> cod;
		switch (cod)
		{
		case 1:
			strcpy(subj[i], "English");
			break;
		case 2:
			strcpy(subj[i], "Physics");
			break;
		case 3:
			strcpy(subj[i], "Chemisry");
			break;
		case 4:
			strcpy(subj[i], "Maths");
			break;
		case 5:
			strcpy(subj[i], "Bio");
			break;
		case 6:
			strcpy(subj[i], "Hindi");
			break;
		case 7:
			strcpy(subj[i], "Computer Science");
			break;
		case 8:
			strcpy(subj[i], "Physical Education");
			break;
		default:
			cout << "\nWRONG CHOICE............";
			cout << "\nSUBJECT NOT AVAILABLE";
			cout << "\nPLEASE TRY AGAIN\n";
			goto back;
		}
	}
}

void student::calc()
{
	int k = 0;
	tot = 0;
	input();
	for (int i = 0; i < 6; i++)
	{
		if (pr[i] != 55)
			// break;
			mks[i] = th[i] + pr[i];
		else
			mks[i] = th[i];
	}
	for (int i = 0; i < 6; i++)
	{
		if (mks[i] >= 90)
			strcpy(g[i], "A+");
		else if ((mks[i] >= 80) && (mks[i] < 90))
			strcpy(g[i], "A");
		else if ((mks[i] >= 70) && (mks[i] < 80))
			strcpy(g[i], "B+");
		else if ((mks[i] >= 60) && (mks[i] < 70))
			strcpy(g[i], "B");
		else if ((mks[i] >= 50) && (mks[i] < 60))
			strcpy(g[i], "C+");
		else if ((mks[i] >= 40) && (mks[i] < 50))
			strcpy(g[i], "C");
		else if ((mks[i] >= 33) && (mks[i] < 40))
			strcpy(g[i], "D");
		else
		{
			strcpy(g[i], "E");
			k++;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (i < 5)
			tot += mks[i];
	}
	per = tot / 5;
	{
		if (k > 1)
			strcpy(re, "FAIL");
		else
			strcpy(re, "PASS");
	}
}

void student::writes()
{
	ofstream x;
	x.open("azo.dat", ios::app | ios::out);
	calc();
	x.write((char *)&s, sizeof(s));
	x.close();
	menu1();
}

void student::reads()
{
	ifstream x;
	x.open("azo.dat", ios::in);

	while (x)
	{
		x.read((char *)&s, sizeof(s));
		//if(x.eof())
		//break;
		output();
		getch();
		//cout<<"wait!!!......\n \n";
		////clrscr();
		system("cls");
	}
	x.close();
	menu1();
}

void student::output()
{
	//clrscr();
	system("cls");
	cout << endl;
	lin();
	cout << setw(50) << "CBSE XII BOARD RESULT" << endl;
	cout << endl;
	cout << setw(53) << "SGRR PUBLIC SCHOOL KOTDWARA" << endl;
	cout << endl;
	cout << "NAME: " << name << endl;
	cout << "ROLL NO: " << roll << endl;
	cout << endl;
	cout << "SUBJECT" << setw(15) << "THEORY" << setw(18) << "PRACTICAL" << setw(10) << "TOTAL"
		 << "\t "
		 << "GRADE" << endl;
	lin();

	for (int i = 0; i < 6; i++)
	{
		cout << subj[i] << setw(14) << th[i] << setw(15) << ((pr[i] == 55) ? "-" : "" + pr[i]) << setw(12) << mks[i] << "\t " << g[i] << endl;
	}

	// cout << subj[0] << setw(14) << th[0] << setw(15) << "-" << setw(12) << mks[0] << "\t " << g[0] << endl;

	// cout << subj[1] << setw(14) << th[1] << setw(15) << pr[1] << setw(12) << mks[1] << "   "
	// 	 << "\t " << g[1] << endl;
	// cout << "CHEMISTRY" << setw(12) << th[2] << setw(15) << pr[2] << setw(12) << mks[2] << "   "
	// 	 << "\t " << g[2] << endl;
	// cout << "MATHS" << setw(16) << th[3] << setw(15) << "-" << setw(12) << mks[3] << "   "
	// 	 << "\t " << g[3] << endl;
	// cout << "COMPUTER" << setw(13) << th[4] << setw(15) << pr[4] << setw(12) << mks[4] << "   "
	// 	 << "\t " << g[4] << endl;
	// cout << "PHYSICAL" << setw(13) << th[5] << setw(15) << pr[5] << setw(12) << mks[5] << "   "
	// 	 << "\t " << g[5] << endl;
	cout << endl;
	lin();
	cout << "TOTAL" << setw(46) << tot << endl;
	cout << "PERCENTAGE" << setw(41) << per << "%" << endl;
	if (per > 95)
		cout << "\t \t \tSCHOLARSHIP AWARDED" << endl;
	cout << re;
	lin();
	getch();
}

void student::failed()
{
	//clrscr();
	system("cls");
	int nos = 0;
	cout << "\n\t**----------------------------------------------------------**"
		 << "\n";
	cout << "\t|| THE LIST OF STUDENTS WHO FAILED IN MORE THAN ONE SUBJECT ||"
		 << "\n";
	cout << "\t**----------------------------------------------------------**\n\n";
	cout << " ROLL	NAME	NO. OF SUBJECTS		PERCENTAGE"
		 << "\n";
	lin();
	getch();
	ifstream x;
	x.open("azo.dat", ios::in);
	x.seekg(0);
	while (x)
	{
		x.read((char *)&s, sizeof(s));
		//if(x.eof())
		//break;
		if (strcmp(re, "FAIL") == 0)
			cout << roll << "\t" << name << "\t\t" << nos << "\t\t" << per << endl;
	}
	x.close();
}

void student::count()
{
	//clrscr();
	system("cls");
	int a = 0;
	ifstream gp("azo.dat", ios::binary);
	if (!gp)
	{
		cout << "File Error" << endl;
	}
	else
	{
		gp.seekg(0);
		while (gp.read((char *)&s, sizeof(s)))
		{
			a++;
		}
		cout << "\n\t\t\t\tSTATUS";
		cout << "\n\n\t\tTOTAL NUMBER OF STUDENTS(DATA) ENTERED = " << a;
		cout << "\n";
		gp.close();
		getch();
		mainmenu();
	}
}

void gotoxy(short x, short y) //definition of gotoxy function//
{
	cout << "";
	// COORD pos = {x, y};
	// SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void m_gets(char *str)
{
	cin.getline(str, sizeof(str) / sizeof(str[0]));
}

void credits()
{
	//clrscr();
	system("cls");
	gotoxy(33, 6);
	cout << "-:Created By:-";
	//lin();
	for (int i = 72; i > 24; i--)
	{
		gotoxy(i, 10);
		cout << "S.G.R.R. PUBLIC SCHOOL KOTDWAR ";
		//delay();
		Sleep(70);
	}
	for (int i = 62; i > 32; i--)
	{
		gotoxy(i, 13);
		cout << "ANMOL AGRAWAL ";
		//delay();
		Sleep(70);
	}
	for (int i = 58; i > 28; i--)
	{
		gotoxy(i, 16);
		cout << "CLASS-12 ROLLNO:XXXXXX ";
		//delay();
		Sleep(70);
	}
	gotoxy(28, 25);
	cout << "Press any key to exit...";
	getch();
	exit(0);
}

void menu1()
{
	//clrscr();
	system("cls");
	char cha;
back:
	cout << "\n\t**----------------------------------------------------------**\n";
	cout << "\t||                            MENU                          ||\n";
	cout << "\t**----------------------------------------------------------**\n\n";
	cout << "\n\n\t1.MAKE REPORT CARDS"
		 << "\n\t2.VIEW REPORT CARDS"
		 << "\n\t3.VIEW FAILURES LIST"
		 << "\n\t4.BACK TO MAIN MENU";
	cout << "\n\tPLEASE ENTER YOUR CHOICE:\n";
	cha = getch();
	/*switch(cha)
	{
	case '1':
		menu1();
		break;
	case '2':
		s.count();
		break;
	case '3':
		s.failed(); //SIFT TO MENU
		break;
	case '4':
		//clrscr();
system("cls");
		gotoxy(20,20);
		cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
		char yn;
		cin>>yn;
		if((yn=='Y')||(yn=='y'))
		{//credits();
		exit(0);}
		else{ mainmenu(); }
	default:cout<<"\n\n\t\tWrong Choice....Please Retry!";
		goto back;
		getch();*/
	switch (cha)
	{
	case '1':
		s.writes();
		goto back;
	case '2':
		s.reads();
		goto back;
	case '3':
		s.failed();
		goto back;
	case '4':
		menu1();
		goto back;
	case '5':
		menu1();
		goto back;
	default:
		mainmenu();
	}
	getch();
}

void mainmenu()
{
	char chc;
	cout << "\n\t**----------------------------------------------------------**"
		 << "\n";
	cout << "\t||                        MAIN MENU                         ||"
		 << "\n";
	cout << "\t**----------------------------------------------------------**\n\n";
	cout << "\n\n\t1.MENU"
		 << "\n\t2.STATS"
		 << "\n\t3.TUTORIAL"
		 << "\n\t4.EXIT";
	cout << "\n\tPLEASE ENTER YOUR CHOICE:\n";
	chc = getch();
	switch (chc)
	{
	case '1':
		menu1();
		break;
	case '2':
		s.count();
		break;
	case '3':
		s.failed(); //SIFT TO MENU
		break;
	case '4':
		//clrscr();
		system("cls");
		gotoxy(20, 20);
		cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
		char yn;
		cin >> yn;
		if ((yn == 'Y') || (yn == 'y'))
		{ //credits();
			exit(0);
		}
		else
		{
			mainmenu();
		}
	default:
		cout << "\n\n\t\tWrong Choice....Please Retry!";
		mainmenu();
		getch();
	}
}

class admin
{
public:
	char admins[20], usc[20]; //existed userName and secureCode
	void signup();
	void signin();
} a;

/*
void secureLogin()
{						  //char admin[20], usc[20];  //existed userName and secureCode
	int un = 0;			  //username existance flag
	char jalim[20];		  //gets the User's Security Code
	char na[20], key[20]; //userName and secureCode from keyBoard
	int attempts = 3;	  //number of attempts

	ifstream x;
	x.open("secusc.dat", ios::in);
	if (x == 0)
	{
		strcpy(a.admins, "anmol");
		strcpy(a.usc, "ultron");
		x.write((char *)&a, sizeof(a));
	}
	//clrscr();
	system("cls");
	cout << "\nDear user,Please enter your name:";
	m_gets(na);

	//ifstream x;
	//x.open("secusc.dat",ios::in);
	while (x)
	{
		x.read((char *)&a, sizeof(a));
		if (strcmp(a.admins, na) == 0)
		{
			un = 1;
			strcpy(jalim, a.usc);
			break;
		}
	}
	x.close();

	if (un == 1)
	{
		while (attempts > 0)
		{
			//clrscr();
			system("cls");
			cout << "Attempts Remaining" << attempts;
			gotoxy(28, 25);
			cout << "Dear " << na << ", now enter your security code(USC):";
			m_gets(key);
			if (strcmp(jalim, key) == 0)
				mainmenu();
			cout << "\nWRONG!!! " << attempts--;
			if (attempts == 1)
				cout << "Its your last chance bro, Be cool...";
			else
				cout << "Try Again...";
			getch();
		}
		cout << "You are in danger...\nError 209!\nNow contact ARA";
		getch();
		exit(0);
	}
	else
	{
		cout << "\nYou are not a Authorized user";
		getch();
		exit(0);
	}
}
*/

int main()
{
	//clrscr();
	system("cls");
	/*for(int i=35;i>10;i--)
	{
	//delay();
Sleep(180);
	//clrscr();
system("cls");
	gotoxy(30,i);
	cputs("**********A********");
	gotoxy(30,i+2);
	cputs("*****PROJECT ON*****");
	gotoxy(30,i+4);
	cputs("*REPORT CARD MAKING*");
	gotoxy(30,i+7);
	cputs("                    ");
	}*/
	for (int i = 72; i > 38; i--)
	{
		gotoxy(i, 10);
		cout << "A ";
		//delay();
		Sleep(70);
	}
	for (int i = 62; i > 34; i--)
	{
		gotoxy(i, 13);
		cout << "PROJECT ON ";
		//delay();
		Sleep(70);
	}
	for (int i = 58; i > 30; i--)
	{
		gotoxy(i, 16);
		cout << "REPORT CARD MAKING ";
		//delay();
		Sleep(70);
	}
	gotoxy(1, 21);
	/*cout<<"\n\t		               A";
	//delay();
Sleep(2000);
	cout<<"\n\t		           PROJECT ON";
	//delay();
Sleep(2000);
	cout<<"\n\t		      REPORT CARD MAKING\n";
	//delay();
Sleep(2000);*/
	mainmenu();
	// secureLogin();
	return 0;
}
