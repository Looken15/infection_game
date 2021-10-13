#include <iostream>
#include <string>

#include "board.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    board b = board();
    b.play();
}
