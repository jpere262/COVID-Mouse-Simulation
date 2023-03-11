#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
    if (x >= 0 && y >= 0) {

        COORD kursor;
        kursor.X = x;
        kursor.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
    }
}