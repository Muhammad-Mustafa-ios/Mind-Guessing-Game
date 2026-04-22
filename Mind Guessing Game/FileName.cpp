#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <string>

using namespace std;

// ================= BASE CLASS =================
class Game
{
protected:
    string playerName;
    int gamesPlayed;

    void setColor(int);
    void clearScreen();
    void slowPrint(string, int = 20);
    char getChoice();
    void exitIfNo();
    void loadingBar(string);

public:
    Game();                // Constructor
    virtual void run() = 0;  // Pure Virtual Function (Polymorphism)
};

// ================= DERIVED CLASS =================
class MindGame : public Game
{
private:
    void title();
    void rules();
    int playRound();
    void showPrize(int);
    void showScore();

public:
    void run();   // Override Base Class Function
};

// ================= BASE CLASS DEFINITIONS =================

Game::Game()
{
    gamesPlayed = 0;
}

void Game::setColor(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Game::clearScreen()
{
    system("cls");
}

void Game::slowPrint(string text, int delay)
{
    for (char c : text)
    {
        cout << c;
        Sleep(delay);
    }
}

char Game::getChoice()
{
    cout << " (Y/N): ";
    char c = _getch();
    cout << c << endl;

    if (c == 'Y' || c == 'y') return 'Y';
    if (c == 'N' || c == 'n') return 'N';

    cout << "Invalid input!\n";
    return getChoice();
}

void Game::exitIfNo()
{
    if (getChoice() == 'N')
    {
        slowPrint("\nThank you for playing!\n");
        exit(0);
    }
}

void Game::loadingBar(string msg)
{
    slowPrint(msg + "\n", 10);
    cout << "[";
    for (int i = 0; i < 25; i++)
    {
        cout << "#";
        Sleep(60);
    }
    cout << "]\n\n";
}

// ================= DERIVED CLASS DEFINITIONS =================

void MindGame::title()
{
    setColor(11);
    cout << "=============================================\n";
    cout << "           MIND GUESSING GAME PLUS           \n";
    cout << "=============================================\n";
    setColor(7);
}

void MindGame::rules()
{
    setColor(10);
    cout << "\n=========== GAME RULES ===========\n";
    cout << "1. Think of a number (1-9)\n";
    cout << "2. Follow instructions\n";
    cout << "3. Magic reveals final number\n";
    cout << "=================================\n\n";
    setColor(7);
}

int MindGame::playRound()
{
    int num = (rand() % 10 + 1) * 2;

    slowPrint("Think of a Number (1 to 9)\n");
    exitIfNo();

    slowPrint("Add same number again.\n");
    exitIfNo();

    slowPrint("Now add my number: " + to_string(num) + "\n");
    exitIfNo();

    slowPrint("Donate half to charity.\n");
    exitIfNo();

    slowPrint("Return number to friend.\n");

    num = num / 2;

    slowPrint("You are left with: ");
    setColor(10);
    cout << num << endl;
    setColor(7);

    return num;
}

void MindGame::showPrize(int value)
{
    slowPrint("\nSpinning prize wheel...\n");
    loadingBar("Please wait");

    setColor(14);
    cout << "Your Prize:\n";
    setColor(10);

    switch (value)
    {
    case 1:  cout << "Chocolate\n"; break;
    case 2:  cout << "Banana\n"; break;
    case 3:  cout << "Gift Voucher\n"; break;
    case 4:  cout << "Movie Ticket\n"; break;
    case 5:  cout << "Ice Cream\n"; break;
    case 6:  cout << "Surprise Box\n"; break;
    case 7:  cout << "Pepsi\n"; break;
    case 8:  cout << "Burger\n"; break;
    case 9:  cout << "Candy\n"; break;
    case 10: cout << "Mystery Gift\n"; break;
    default: cout << "Better luck next time!\n";
    }

    setColor(7);
}

void MindGame::showScore()
{
    setColor(11);
    cout << "\n================ SCOREBOARD ================\n";
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "============================================\n";
    setColor(7);
}

void MindGame::run()
{
    srand(time(0));

    clearScreen();
    title();
    rules();

    slowPrint("Enter your name: ");
    setColor(9);
    getline(cin, playerName);
    setColor(7);

    slowPrint("\nWelcome " + playerName + "!\n");

    char again = 'Y';

    while (again == 'Y')
    {
        clearScreen();
        title();
        gamesPlayed++;

        int result = playRound();

        slowPrint("\nCheck your prize?");
        exitIfNo();

        showPrize(result);

        cout << "\nPlay again?";
        again = getChoice();

        clearScreen();
    }

    title();
    slowPrint("\nThanks for playing, " + playerName + "!\n");
    showScore();
    slowPrint("Goodbye!\n");
}

// ================= MAIN =================
int main()
{
    Game* game = new MindGame();  // Polymorphism
    game->run();                  // Base pointer calling derived function
    delete game;

    return 0;
}