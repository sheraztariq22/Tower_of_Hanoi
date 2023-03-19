//Sheraz Tariq //
//i211188 //
//SE-Q //
//Towers of Hanoi //
// I have designed this project in the form of game //

#include <iostream>
#include <conio.h>
#include <dos.h> // is for handling interrupts,producing sound,time,date stuff. It is old now though and due to security issues it is not used.Dos was a thing when Dos was the OS.Now there are Windows 7,8 10 so carrying out Dos operations on these is not correct.
#include <windows.h>   //Windows.h is used when you want to carry out operations that will carry out operations on Windows OS programs. More like new DOS (Asked later). This contains functions for Windows API
#include <time.h>  //Contains function prototypes and types for manipulating the time and date. This header file replaces header file



#define WIN_WIDTH 70

#define T1POSITION 15
#define T2POSITION 30
#define T3POSITION 45
#define DISKS 5

using namespace std;

typedef enum {black,
              blue,
              green,
              cyan,
              red,
              magenta,
              yellow,
              white,
              gray,
              lightblue,
              lightgreen,
              lightcyan,
              lightred,
              lightmagenta,
              lightyellow,
              lightwhite} ;


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int towers[3][DISKS];
int towersTop[3] = {DISKS-1,-1,-1};

int tries = 0;
int score = 0;

void gotoxy(int x, int y)
{
    CursorPosition.X = x; //set values of x coordinate of screen
    CursorPosition.Y = y;// set value of y coordinate of screen
    SetConsoleCursorPosition(console, CursorPosition); //sets the position of the cursor

}

void setColor(int textColor, int bgColor)
{
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
         size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);

}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);
    cout<<"Tries:"<<tries<<endl;
}

void instructions()
{
    system("cls");
    cout <<"Instructions";
    cout <<"\n----------------";
    cout <<"\n Shifts Disks from Tower 1 to Tower 3.";
    cout <<"\n You cannot place large disk on small disk";
    cout << "\n Towers are numbered as 1,2, and 3";
    cout << "\n\nPress any key to go back to menu";
    getch();

}

//function for drawing tiles
void drawTile(int tower, int tileNo, int y)
{
     int x;
     if (tower == 1)
        x= T1POSITION;
     else if (tower == 2)
        x= T2POSITION;
     else if (tower == 3)
        x= T3POSITION;

    x -= tileNo;

    for (int j = 0; j< ((tileNo)*2)-1; j++)
    {
        gotoxy (x,y);
        cout<< "*";
        x++;
    }
}

//function to build towers
void drawTower(int tower)
{
     int x;
     int y = 9;

     gotoxy(10,10);
     setColor(red, lightcyan);
      cout<<"==========";
     gotoxy(25,10);
      setColor(red, lightcyan);
      cout<<"==========";
     gotoxy(40,10);
      setColor(red, lightcyan);
      cout<<"==========";

     gotoxy(15,11);
      cout<<"1";
     gotoxy(30,11);
      cout<<"2";
     gotoxy(45,11);
      cout<<"3";

     for (int i =0; i<5; i++)
     {
         drawTile(tower, towers[tower-1][i], y);
         y--;
     }
}

//function to show the number of towers are empty to fill
int isEmpty(int towerNo)
{
    for (int i = 0; i<DISKS; i++)
         if (towers[towerNo][i] != 0)
              return 0;
    return 1;
}

//function to validate the tower from to tower to if possible
int validate(int from, int to){
    if (! isEmpty(to)){
        if (towers[from][towersTop[from]] < towers[to][towersTop[to]])
            return 1;
        else
            return 0;
    }
    return 1;
}

//function shows that how the towers got moved
int move(int from, int to)
{
    if (isEmpty(from))
        return 0;
    if (validate (from, to))
        {
        if (towers[from][towersTop[from]] != 0)
        {
            towersTop[to]++;
            towers[to][towersTop[to]] = towers[from][towersTop[from]];
            towers[from][towersTop[from]] = 0;
            towersTop[from]--;
            return 1;
        }
    }
    return 0;
}

//function that how user wins
int win()
{
    for (int i =0; i<DISKS; i++)
        {
        if (towers[2][i] != DISKS-i)
            return 0;
    return 1;
}
}

//fuctions shows that how does the game starts
void play()
{
     int from, to;
    for (int i =0; i<DISKS; i++)
         towers[0][i]= DISKS-i;
    for (int i =0; i<DISKS; i++)
         towers[1][i] = 0;
    for (int i =0; i<DISKS; i++)
         towers[2][i] = 0;
    do{
        system("cls");

        cout <<"==================================================="<<endl;
        cout <<"                    TOWER OF HANOI                 "<<endl;
        cout <<"==================================================="<<endl;

        drawTower(1);
        drawTower(2);
        drawTower(3);

        if (win()){
            system("cls");
            cout <<"=================================================="<<endl;
            cout <<"                    YOU WIN                       "<<endl;
            cout <<"=================================================="<<endl;
            cout <<endl<<endl<<endl;
            cout <<"Press any key to go back to menu. . . ";
            getch();
            break;
        }
        gotoxy(10, 15);
        cout <<"From (Values: 1,2,3):";
        cin>>from;
        gotoxy(10,16);
        cout <<"To (Values: 1,2,3):";
        cin>>to;

        if(to < 1 || to > 3)
            continue;
        if(from < 1 || from > 3)
            continue;
        if(from == to)
             continue;

        from--;
        to--;

        move(from, to);

        if (kbhit())
        {
            char ch = getch();
            if (ch == 'a' || ch=='A'){
            }
            if (ch == 'd' || ch=='D'){
            }
            if (ch == 27){
                break;
            }
        }

    }while(1);
}
int main()
{
    setcursor(0,0);
    srand((unsigned)time(NULL));

    do{
        system("cls");
        setColor(red, lightcyan);
        gotoxy(10,5);
        cout<<" -------------------- ";
        gotoxy(10,6);
        setColor(red, lightcyan);
        cout<<" |  Tower of Hanoi  | ";
        gotoxy(10,7);
        cout<<" -------------------- ";
        gotoxy(10,9);
        setColor(red, lightcyan);
        cout<<"1. Start Game";
        gotoxy(10,10);
        cout<<"2. Instructions";
        setColor(red, lightcyan);
        gotoxy(10,11);
        setColor(red, lightcyan);
        cout<<"3. Quit";
        gotoxy(10,13);
        cout<<"Select Option: ";
        char op = getche();

        if(op == '1')
        {
            play();
        }

        else if( op == '2')
        {
        instructions();
        }
        else if (op == '3')
        {
             exit(0);
        }


    }while(1);
    return 0;
}
