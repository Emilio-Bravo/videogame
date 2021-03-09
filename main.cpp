#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
/*!CONSTANTS!*/
#define UP 72
#define LEFT 75
#define RIGTH 77
#define DOWN 80
void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon,dwPos);
}
void hidden()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}
void limits()
{
    for (int i = 2; i < 78; i++)
    {
        gotoxy(i,3);
        printf("%c",205);
        gotoxy(i,33);
        printf("%c",205);
    }
    for (int i = 4; i < 33; i++)
    {
        gotoxy(2,i);
        printf("%c",186);
        gotoxy(77,i);
        printf("%c",186);
    }
    gotoxy(2,3);
    printf("%c",201);
    gotoxy(2,33);
    printf("%c",200);
    gotoxy(77,3);
    printf("%c",187);
    gotoxy(77,33);
    printf("%c",188);
}
class Ship
{
private:
    int x,y,hearts,lives;
public:
    Ship(int x, int y, int hearts, int lives):x(x),y(y),hearts(hearts),lives(lives) {}
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void make();
    void heartsDecrease()
    {
        hearts--;
    }
    void delete_remainings();
    void move_position();
    void showHealth();
    void exploit();
};

void Ship::make()
{
    gotoxy(x,y);
    printf("  %c",30);
    gotoxy(x,y+1);
    printf(" %c%c%c",40,207,41);
    gotoxy(x,y+2);
    printf("%c%c %c%c",30,190,190,30);
}
void Ship::delete_remainings()
{
    gotoxy(x,y);
    printf("     ");
    gotoxy(x,y+1);
    printf("     ");
    gotoxy(x,y+2);
    printf("     ");
}
void Ship::move_position()
{
    if (kbhit())
    {
        Ship::delete_remainings();
        char key = getch();
        if (key == LEFT && x > 3) x--;
        if (key == RIGTH && x + 6 < 77) x++;
        if (key == UP && y > 4) y--;
        if (key == DOWN && y + 3 < 33) y++;
        Ship::make();
    }
}
void Ship::showHealth()
{
    gotoxy(50,2);
    printf("lives %d",lives);
    gotoxy(64,2);
    printf("Health");
    printf("      ");
    gotoxy(70,2);
    for (int i = 0; i < hearts; i++)
    {
        gotoxy(70+i,2);
        printf("%c",3);
    }
}
void Ship::exploit()
{
    if (hearts == 0)
    {
        delete_remainings();
        gotoxy(x,y);
        printf("   **   ");
        gotoxy(x,y+1);
        printf("  ****  ");
        gotoxy(x,y+2);
        printf("   **   ");
        Sleep(200);
        delete_remainings();
        gotoxy(x,y);
        printf(" * ** * ");
        gotoxy(x,y+1);
        printf("  **** ");
        gotoxy(x,y+2);
        printf(" * ** *");
        Sleep(200);
        delete_remainings();
        lives--;
        hearts = 3;
        showHealth();
        delete_remainings();
        make();
    }
}
class Asteroid
{
    int x,y;
public:
    Asteroid(int x, int y)
    {
        x = x;
        y = y;
    }
    void make();
    void move_position();
    void colition(class Ship &s);
};
void Asteroid::make()
{
    gotoxy(x,y);
    printf("%c",184);
}
void Asteroid::move_position()
{
    gotoxy(x,y);
    printf(" ");
    y++;
    if (y > 32)
    {
        x = rand()%71 + 4;
        y = 4;
    }
    make();
}
void Asteroid::colition(class Ship &s)
{
    if (x >= s.getX() && x < s.getX() + 6 && y >= s.getY() && y <= s.getY() + 2)
    {
        s.heartsDecrease();
        s.make();
        s.showHealth();
        x = rand()%71 + 4;
        y = 4;
    }
}
int main()
{
    Asteroid asteroid(10,4), asteroid2(4,8), asteroid3(15,10), asteroid4(20,16);
    hidden();
    Ship ship(7,7,3,3);
    ship.make();
    limits();
    ship.showHealth();
    bool on_exit = false;
    while(!on_exit)
    {
        ship.exploit();
        asteroid.move_position();
        asteroid2.move_position();
        asteroid3.move_position();
        asteroid4.move_position();
        asteroid.colition(ship);
        asteroid2.colition(ship);
        asteroid3.colition(ship);
        asteroid4.colition(ship);
        ship.move_position();
        Sleep(30);
    }
    return 0;
}
