#include <iostream>
#include <Windows.h> //for sleep
#include <conio.h> //for kbhit
#include <ctime>    // for time
#include "World.h"
#include <mmstream.h>

using namespace std;

// Function to move console output coordinates
void gotoxy2(int x, int y) {
    if (x >= 0 && y >= 0) {

        COORD kursor;
        kursor.X = x;
        kursor.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
    }
}

// Function to hide console cursor
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Play music in background while program is running, looped
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    // Creates main menu for simulation
    while (1)
    {
        system("cls");

        // Hide console cursor
        ShowConsoleCursor(false);

        // Displays title of program in ASCII
        SetConsoleTextAttribute(hConsole, 2);
        cout << R"(
     _____ _____  _   _ ___________  ___  ___                       _____ _                 _       _   _
    /  __ \  _  || | | |_   _|  _  \ |  \/  |                      /  ___(_)               | |     | | (_)
    | /  \/ | | || | | | | | | | | | | .  . | ___  _   _ ___  ___  \ `--. _ _ __ ___  _   _| | __ _| |_ _  ___  _ __
    | |   | | | || | | | | | | | | | | |\/| |/ _ \| | | / __|/ _ \  `--. \ | '_ ` _ \| | | | |/ _` | __| |/ _ \| '_ \
    | \__/\ \_/ /\ \_/ /_| |_| |/ /  | |  | | (_) | |_| \__ \  __/ /\__/ / | | | | | | |_| | | (_| | |_| | (_) | | | |
     \____/\___/  \___/ \___/|___/   \_|  |_/\___/ \__,_|___/\___| \____/|_|_| |_| |_|\__,_|_|\__,_|\__|_|\___/|_| |_|

                   )" << endl;

        // Colored Start Instructions
        gotoxy2(50, 10);
        SetConsoleTextAttribute(hConsole, 15);
        cout << "Press '"; 
        SetConsoleTextAttribute(hConsole, 11);
        cout << "Q";
        SetConsoleTextAttribute(hConsole, 15);
        cout << "' to start" << endl;
        
        // Instructions to exit program
        gotoxy2(45, 13);
        cout << "Press any other button to exit" << endl;

        // Starts simulation once "Q" is pressed
        if (_kbhit())
        {
            char ch2;

            ch2 = _getch();
            if (ch2 == 'q' || ch2 == 'Q')
            {
                World myWorld(time(0));
                myWorld.display();

                char ch;

                // Infinite loop until a keyboard input is pressed
                while (1)
                {   
                        system("cls"); // Clears the system so the terminal only shows one instance of world map at a time

                        // Displays ASCII title
                        SetConsoleTextAttribute(hConsole, 2); {
                            cout << R"(
   _____ _____  _   _ ___________  ___  ___                       _____ _                 _       _   _
  /  __ \  _  || | | |_   _|  _  \ |  \/  |                      /  ___(_)               | |     | | (_)
  | /  \/ | | || | | | | | | | | | | .  . | ___  _   _ ___  ___  \ `--. _ _ __ ___  _   _| | __ _| |_ _  ___  _ __
  | |   | | | || | | | | | | | | | | |\/| |/ _ \| | | / __|/ _ \  `--. \ | '_ ` _ \| | | | |/ _` | __| |/ _ \| '_ \
  | \__/\ \_/ /\ \_/ /_| |_| |/ /  | |  | | (_) | |_| \__ \  __/ /\__/ / | | | | | | |_| | | (_| | |_| | (_) | | | |
   \____/\___/  \___/ \___/|___/   \_|  |_/\___/ \__,_|___/\___| \____/|_|_| |_| |_|\__,_|_|\__,_|\__|_|\___/|_| |_|

                   )" << endl;
                        }

                        SetConsoleTextAttribute(hConsole, 15);
                        // Hide console cursor
                        ShowConsoleCursor(false);

                        // Creates top border for legend
                        {
                            gotoxy2(7, 10);
                            cout << char(201);
                            gotoxy2(8, 10);
                            for (int i = 0; i < 23; i++)
                            {
                                cout << char(205);
                            }
                            gotoxy2(31, 10);
                            cout << char(187);
                            for (int i = 0; i < 4; i++)
                            {
                                gotoxy2(7, 11 + i);
                                cout << char(186) << "                       " << char(186) << endl;
                            }
                            gotoxy2(7, 15);
                            cout << char(200);
                            gotoxy2(8, 15);
                            for (int i = 0; i < 23; i++)
                            {
                                cout << char(205);
                            }
                            gotoxy2(31, 15);
                            cout << char(188);
                        }
                        // Creates lower border for legend
                        {
                            gotoxy2(2, 17);
                                cout << char(201);
                            gotoxy2(3, 17);
                                for (int i = 0; i < 33; i++)
                                {
                                    cout << char(205);
                                }
                            gotoxy2(36, 17);
                                cout << char(187);
                                for (int i = 0; i < 2; i++)
                                {
                                    gotoxy2(2, 18 + i);
                                    cout << char(186) << "                                 " << char(186) << endl;
                                }
                            gotoxy2(2, 20);
                                cout << char(200);
                                gotoxy2(3, 20);
                                for (int i = 0; i < 33; i++)
                                {
                                    cout << char(205);
                                }
                            gotoxy2(36, 20);
                                cout << char(188);
                        }
                        // Creates legend for symbols and colors
                        {
                            gotoxy2(8, 11);
                            SetConsoleTextAttribute(hConsole, 14);
                            cout << "Yellow means uninfected" << endl;
                            gotoxy2(8, 12);
                            SetConsoleTextAttribute(hConsole, 12);
                            cout << "Red means infected" << endl;
                            gotoxy2(8, 13);
                            SetConsoleTextAttribute(hConsole, 11);
                            cout << "Blue means immune" << endl;
                            gotoxy2(8, 14);
                            SetConsoleTextAttribute(hConsole, 2);
                            cout << "Green means baby" << endl;
                            gotoxy2(3, 18);
                            SetConsoleTextAttribute(hConsole, 15);
                            cout << "'M' and 'p' stand for MALE mice" << endl;
                            gotoxy2(3, 19);
                            cout << "'F' and 'b' stand for FEMALE mice" << endl;
                        }
                        // Creates purple border for grid display
                        {
                            // Top of border
                            gotoxy2(39, 7);
                                SetConsoleTextAttribute(hConsole, 5);
                                for (int test = 0; test <= 81; test++)
                                {
                                    cout << char(220);
                                    test++;
                                }
                            // Sides of border
                                for (int test2 = 0; test2 <= 21; test2++)
                                {
                                    gotoxy2(39, 8 + test2);
                                    cout << char(186) << "                                       " << char(186) << endl;
                                }
                            // Cut-off in middle of border
                            gotoxy2(40, 27);
                                for (int test3 = 0; test3 <= 77; test3++)
                                {
                                    cout << char(220);
                                    test3++;
                                }
                            // Bottom of border
                            gotoxy2(39, 30);
                                for (int test4 = 0; test4 <= 81; test4++)
                                {
                                    cout << char(223);
                                    test4++;
                                }
                                SetConsoleTextAttribute(hConsole, 15);
                        }
                        // Creates another legend for instructions
                        {
                            gotoxy2(3, 30);
                            cout << "Press any other key to exit";
                            gotoxy2(98, 30);
                            cout << "made by Junior Perez";

                            gotoxy2(85, 10);
                            cout << "Press 'C' to infect 3 mice" << endl;
                            gotoxy2(85, 11);
                            cout << "with COVID-19" << endl;
                            gotoxy2(85, 16);
                            cout << "Press 'I' to make all non-infected" << endl;
                            gotoxy2(85, 17);
                            cout << "adult mice immune" << endl;
                        }

                    myWorld.simulateOneStep();
                    myWorld.display();
                    if (_kbhit()) //breaks loop if keyboard is pressed
                    {
                        // Randomly infects THREE adult mice if C is pressed
                        ch = _getch();
                        if (ch == 'c' || ch == 'C')
                        {
                            myWorld.InfectMice();
                        }
                        // Makes all uninfected adult mice immune to Covid
                        else if (ch == 'i' || ch == 'I')
                        {
                            myWorld.makeMiceImmune();
                        }
                        // Stops program if any key other than "C" or "I" is pressed
                        else
                        {
                            break;
                        }
                    }
                    Sleep(500); //500 ms delay between each loop
                }
                return 0;
            }
            else
            {
                break;
            }
        }
        Sleep(400);
    }
}
