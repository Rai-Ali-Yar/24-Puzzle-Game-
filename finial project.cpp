#include <iostream>//input output
#include <ctime>//time for srand
#include<conio.h>//for _gech
#include <windows.h>//color function
#include <fstream>//file handling
using namespace std;
int chk_legal[4] = { 1,1,1,1 };
int goal[25];
void initial_state(int initial[]);
void goal_state(int goal[]);
bool Is_Solvable(int goal[], int initial[]);//inversion
bool Is_Goal(int initial[], int goal[]);
void Display_goal(int goal[]);
void Display_initial(int initial[]);
void legal_moves(int initial[]);

void path(int move);
void initial_path(int initial[]);
void initial_goal(int goal[]);
void open_initial(int initial[]);
void open_goal(int goal[]);
void open_path();
void color(int color);
//void move_path(char move);
void initial_state(int initial[])//passing initial array to get randomly arranged 
{
	int  temp1, x;
	for (int i = 0; i < 25; i++)//filling array with 1-25 numbers
	{
		initial[i] = i + 1;
	}
	for (int i = 0; i < 12; i++)
	{
		temp1 = (rand() % 12) + 1;    //creating 12 random numbers and swap that value with the current index
		for (int j = 0; j < 25; j++)
		{
			x = initial[j];
			initial[j] = initial[temp1];
			initial[temp1] = x;
		}
	}
}
void goal_state(int goal[])
{
	int  temp1, x;
	for (int i = 0; i < 25; i++)
	{
		goal[i] = i + 1;
	}
	for (int i = 0; i < 12; i++)
	{
		temp1 = (rand() % 12) + 1;
		for (int j = 0; j < 25; j++)
		{
			x = goal[j];
			goal[j] = goal[temp1];
			goal[temp1] = x;
		}
	}
}
void loading()
{
	system("color 0a");
	cout << "\n\n\n\t\t\t\tPlease wait while loading\n\n";
	char a = 177, b = 219;
	cout << "\t\t\t\t";
	for (int i = 0; i <= 15; i++)
		cout << a;
	cout << "\r";
	cout << "\t\t\t\t";
	for (int i = 0; i <= 15; i++)
	{
		cout << b;
		for (int j = 0; j <= 1e8; j++);
	}

	system("CLS");
}
void Display_goal(int goal[])//display goal state in the mid of console
{
	system("color 3C");
	
	color(10);
	cout << "\t\t\t\t\t | GOAL STATE | ";
	for (int i = 0; i < 25; i++)
	{
		if (i % 5 == 0)
		{
			cout << endl;
			cout << "\t\t\t\t\t ------------------------- ";
			cout << endl << "\t\t\t\t\t |";
		}
		if (goal[i] != 25)
		{
			int temp;
			int count = 0;
			temp = goal[i];
			while (temp != 0)//Checks if number is 1 digit or 2 digit 
			{
				temp /= 10;//this will help in display
				count++;
			}
			if (count == 1)
			{
				cout << goal[i] << "  | ";//these space will be one more as a 1 digit number is there
			}
			else
			{
				cout << goal[i] << " | ";//these space will be one less as a 2 digit number is there
			}
		}
		else
		{

			cout << "   | ";
		}
	}
	cout << endl;
	cout << "\t\t\t\t\t ------------------------- ";
	cout << endl;

}
void Display_initial(int initial[])
{
	system("color 33");
	color(4);
	cout << "\n\t\t\t\t\t      | INITIAL STATE |    ";
	for (int i = 0; i < 25; i++)
	{
		if (i % 5 == 0)
		{
			cout << endl;
			cout << "\t\t\t\t\t ------------------------- ";
			cout << endl<<"\t\t\t\t\t |";
		}

		if (initial[i] != 25)
		{
			int temp;
			int count = 0;
			temp = initial[i];
			while (temp != 0)
			{
				temp /= 10;
				count++;
			}
			if (count == 1)
			{
					cout << initial[i] << "  | ";
			}
			else
			{
					cout << initial[i] << " | ";		
			}
		}
		else
		{
			cout << "   | ";
		}
	}
	cout << endl;
	cout << "\t\t\t\t\t ------------------------- ";
	cout << endl;
}
bool Is_Solvable(int goal[], int initial[])
{
	
	int count = 0;
	int sum_initial = 0, sum_goal = 0;

	for (int i = 1; i <= 24; i++)
	{
		for (int j = 0; j < 24; j++)//this will check every number next to it
		{
			if (initial[j] == i)//this is the condition on which code checks
			{
				for (int inver_temp = j; inver_temp < 24; inver_temp++)//this checks all the number ahead them 
				{
					if (initial[inver_temp] < i)//main inversion is check here
					{							//if the condition is true
						count = count + 1;     //counter will be increment
					}
				}
				sum_initial = sum_initial + count;//each individual count will be added
				count = 0;// again counter will be zero so next value counts proper
			}
		}
	}
	count = 0;
	for (int i = 1; i <= 24; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (goal[j] == i)
			{
				for (int n = j; n < 24; ++n)
				{
					if (goal[n] < i)
					{
						count = count + 1;
					}
				}
				sum_goal = sum_goal + count;
				count = 0;
			}
		}
	}

	if ((sum_goal % 2 == 0 && sum_initial % 2 == 0) || (sum_goal % 2 != 0 && sum_initial % 2 != 0))
	{

		return 1;
	}
	else
	{
		return 0;

	}
}
bool Is_Goal(int initial[], int goal[])
{
	int counter = 0;
	for (int i = 0; i < 25; i++)
	{
		if (initial[i] == goal[i])//checks each value of goal with initial
		{
			counter++;//each value which is equal is added to counter
		}
	}
	if (counter == 25)//if all values would be same counter is 25 
	{
		system("color 35");
		color(10);
		Display_goal(goal);
		Display_initial(initial);

		cout << "\tThe path which led you to victory\n\t";
		open_path();//this functions prints the whole path which led to victory
	    return 1;
	}
	else
	{
		return 0;
	}
}
/* ---------- | LEGAL MOVES | -----------------
 In  this function we  have taken  all  the edge
 or the boundry indexes if the space (25 index).
 if the current positionn at that loop is on the
 boundry points of 5x5 array then we would output
 you cannot move on that side.
  */
void legal_moves(int initial[])
{
	int temperory;
	color(13);
	for (int i = 0; i < 25; i++)
	{
		if (initial[i] == 25)
		{
			temperory = i;
		}
	}
	if ((temperory == 20) || (temperory == 21) || (temperory == 22) || (temperory == 23) || (temperory == 24))//boundry indexs where space cannot move down 
	{
		cout << "\n\t\t\t\t\tyou cannot move up" << endl;
		chk_legal[0] = 0;
	}
	if ((temperory == 4) || (temperory == 9) || (temperory == 14) || (temperory == 19) || (temperory == 24))//boundry indexs where space cannot move right
	{
		cout << "\n\t\t\t\t\tyou cannot move left" << endl;
		chk_legal[1] = 0;
	}
	if ((temperory == 0) || (temperory == 1) || (temperory == 2) || (temperory == 3) || (temperory == 4))//boundry indexs where space cannot move up
	{
		cout << "\n\t\t\t\t\tyou cannot move down" << endl;
		chk_legal[2] = 0;
	}
	if ((temperory == 0) || (temperory == 5) || (temperory == 10) || (temperory == 15) || (temperory == 20))//boundry indexs where space cannot move left
	{
		cout << "\n\t\t\t\t\tyou cannot move right" << endl;
		chk_legal[3] = 0;
	}
}

void  make_moves(int initial[], int move)//takes input and swaps
{
	int x, temp = 0;
	for (int i = 0; i < 25; i++)
	{
		if (initial[i] == 25)//checks where the space is at that time
		{
			temp = i;
		}
	}
	switch (move)
	{
	case 80:
	{
		if (chk_legal[2] == 0)
		{
			break;
		}
		x = initial[temp - 5];
		initial[temp - 5] = initial[temp];
		initial[temp] = x;
		Display_goal(goal);
		Display_initial(initial);
		break;
	}
	case 72:
	{
		if (chk_legal[0] == 0)
		{
			break;
		}
		x = initial[temp + 5];
		initial[temp + 5] = initial[temp];
		initial[temp] = x;
		Display_goal(goal);
		Display_initial(initial);
		break;

	}
	case 77:
	{
		if (chk_legal[3] == 0)
		{
			break;
		}
		x = initial[temp - 1];
		initial[temp - 1] = initial[temp];
		initial[temp] = x;
		Display_goal(goal);
		Display_initial(initial);
		break;

	}
	case 75:
	{
		if (chk_legal[1] == 0)
		{
			break;
		}
		x = initial[temp + 1];
		initial[temp + 1] = initial[temp];
		initial[temp] = x;
		Display_goal(goal);
		Display_initial(initial);
		break;
	}
	}
	chk_legal[0] = 1;
	chk_legal[1] = 1;
	chk_legal[2] = 1;
	chk_legal[3] = 1;
}



void clear_path()
{
	ofstream write;
	write.open("pathofmoves.txt");
		if (!write.is_open())
		{
			cout << "File Didn't opened" << endl;
		}
		while (write.eof())
		{
			write << " " << endl;
		}
		write.close();
}
void path(char move)
{
	fstream moves("pathofmoves.txt", ios::in | ios::app);
		if (!moves.is_open())
		{
			cout << "File Didn't opened"<<endl;
		}
	moves << move << endl;
	moves.close();
}

void initial_path(int initial[])
{
	ofstream initialpath;
	initialpath.open("initial_P.txt");
	if (!initialpath.is_open())
	{
		cout << "File Didn't opened" << endl;
	}
	for (int i = 0; i < 25; i++)
	{
		initialpath << initial[i]<<endl ;
	}
	initialpath.close();
}
void initial_goal(int goal[])
{
	ofstream goalpath;
	goalpath.open("goal_P.txt");
	if (!goalpath.is_open())
	{
		cout << "File Didn't opened" << endl;
	}
	for (int i = 0; i < 25; i++)
	{
		goalpath << goal[i] << endl;
	}
}
void open_initial(int initial[])
{
	int word;
	ifstream initialpath;
	initialpath.open("initial_P.txt");
	while (!initialpath.eof())
	{
		for(int i=0;i<25;i++)
		{
			initialpath >> initial[i];
		}
	}
	initialpath.close();
}
void open_goal(int goal[])
{
	int word;
	ifstream goalpath;
	goalpath.open("goal_P.txt");
	while (!goalpath.eof())
	{
		for (int i = 0; i < 25; i++)
		{

			goalpath >> goal[i];
		}
	}
	goalpath.close();
}
void open_path()
{
	char p;
	int h = 0;
	ifstream read;
	read.open("pathofmoves.txt");
	if (!read) {
		cout << "File Not Found!" << endl;
	}
	while (!read.eof())
	{
		read >> p;
		if(h%2!=0)
		{
			if (p == 72)
			{
				p += 13;
			}
			else if (p == 75)
			{
				p += 1;
			}
			else if (p == 77)
			{
				p += 5;
			}
			else if (p == 80)
			{
				p -= 12;
			}
			cout << "->" << p;
		}
		h++;
	}
	cout << endl;
	read.close();
}
///////////////////////////////////////////////////////
/////                                     ////////////
////                 MAIN                 ///////////
////                                    ////////////
///////////////////////////////////////////////////
int main()
{
	int o, v = 1;
	int initial[25];
	
	char move;
	
	system("color A0");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	color(10);
	cout << "\t\t\t\t\t WELCOME TO 24 Puzzle Game \n\n";
	color(9);
	cout << "\t\t\t\t\t\tPress any key\n";
	o = _getch();
	loading();

	
		system("cls");
		system("color 38");
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		color(10);
		cout << "\t\t\t\t\t 24 Puzzle Game\n\n";
		color(4);
		cout << "\t\t\t\t\t   MAIN MENU \n\n";
		color(6);
		cout << "\t\t\t\t\t1->Instructions.\n";
		cout << "\t\t\t\t\t2->NEW GAME.\n";
		cout << "\t\t\t\t\t3->Resume with previous game\n";
		cout << "\t\t\t\t\t4->Exit.\n";
		o = _getch();

		switch (o)
		{
		//instructions
		case 49:
		{
			system("cls");
			system("color 40");
			color(11);
			cout << "\n\n\n\n\n\n\n\n\n\n";
			cout << "\t\t\t\t\t Instructions of Game \n\n";
			cout << "\t\t\t\t\t1->Every time you play new game new initial state\n ";
			cout << "\t\t\t\t\t   and goal state will be generated.\n\n";
			cout << "\t\t\t\t\t2->You have 5X5 table and there is space on a random point\n\n";
			cout << "\t\t\t\t\t3->Once you reach goal state game will  be finished \n\n";
			cout << "\t\t\t\t\t4->Then you can start a new game at any point or resume game\n\n";
			cout << "\t\t\t\t\t5->Resume game will start where you have leave your game\n\n";
			cout << "\t\t\t\t\t6->To resume press escape key\n\n";
			system("pause");
			break;
		}
		//new game
		case 50:
		{
			clear_path();
			system("cls");
			srand(time(0));
			initial_state(initial);
			goal_state(goal);
			bool chk = Is_Solvable(goal, initial);
			while (chk == 0)
			{
				initial_state(initial);
				goal_state(goal);
				chk = Is_Solvable(goal, initial);
			}
			Display_goal(goal);
			Display_initial(initial);
			color(10);
			cout << "\n\t\t\t Enter down key to  move upwards";
			cout << "\tEnter upward key to move downwards\n";
			cout << "\t\t\t Enter right key to move leftwards";
			cout << "\t Enter left key to move rightwards\n";
			int q=0;
			while (true)
			{
				if(q%2!=0)
				{
					system("cls");
				}
				q++;
				move = _getch();
				if (move == 27)
				{
					cout << "YOUR GAME IS RESUMED ";
					break;
				}
				
				make_moves(initial, move);
				legal_moves(initial);
				path(move);
				initial_path(initial);
				initial_goal(goal);
				
				bool y = Is_Goal(initial, goal);//checks if goal = initial
				if (y == 1)
				{
					cout << "win";
					break;
				}
			}
			break;
		}
		//resume mode 
		case 51:
		{
			loading();
			int u;
			system("cls");
			system("color B1");
			color(10);
			cout << "\n\n\n\n\n\n\n\n\n\n\n";
			cout<<"\t\t\t\t\tRESUME GAME FROM PREVIOUS GAME\n\n";
			color(3);
			cout << "\t\t\t\t\tPress any key to continue";
			u = _getch();
			system("cls");
			open_initial(initial);

			open_goal(goal);
			Display_goal(goal);
			Display_initial(initial);
			color(10);
			cout << "\n\t\t\t Enter down key to  move upwards";
			cout << "\tEnter upward key to move downwards\n";
			cout << "\t\t\t Enter right key to move leftwards";
			cout << "\t Enter left key to move rightwards\n";
			int q = 0;
			while (true)
			{
				if (q % 2 != 0)
				{
					system("cls");
				}
				q++;
				move = _getch();
				if (move == 27)
				{
					break;
				}

				make_moves(initial, move);
				legal_moves(initial);

				path(move);
				initial_path(initial);
				initial_goal(goal);

				bool y = Is_Goal(initial, goal);

				if (y == 1)
				{
					cout << "win";
					break;
				}

			}
			break;

		}

		case 52:
		{
			system("cls");
			break;
		}
		default:
		{
			cout << "INVALID INPUT";
			break;

		}
		}
}





























void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);//
}