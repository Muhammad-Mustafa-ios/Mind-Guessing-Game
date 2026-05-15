#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

// ================= BASE CLASS =================
class Game {
protected:
    string playerName;
    int gamesPlayed;

    void setColor(int);
    void clearScreen();
    void slowPrint(string, int = 15);
    int menuChoice(int, int);
    void pauseScreen();
    void loadingBar(string);

public:
    Game();
    virtual void run() = 0;
};

// ================= DERIVED CLASS =================
class MindGame : public Game {

private:
    string password;

    void title();
    void rules();
    int playRound();
    void showPrize(int);
    void showScore();

    // Login System
    bool signUp();
    bool signIn();

    // File Handling
    void loadPlayerData();
    void savePlayerData();
    void writeSessionLog(int);

public:
    void run();
};

// ================= BASE CLASS DEFINITIONS =================

Game::Game() {
    gamesPlayed = 0;
}

void Game::setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Game::clearScreen() {
    system("cls");
}

void Game::slowPrint(string text, int delay) {

    for (char c : text)
    {
        cout << c;
        Sleep(delay);
    }
}

void Game::pauseScreen() {

    setColor(8);
    cout << "\nPress any key to continue...";
    _getch();
    setColor(7);
}

int Game::menuChoice(int start, int end) {

    int choice;

    cout << "\nEnter Choice: ";
    cin >> choice;

    while (cin.fail() || choice < start || choice > end)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        setColor(12);
        cout << "Invalid Choice! Try Again: ";
        setColor(7);

        cin >> choice;
    }

    cin.ignore();

    return choice;
}

void Game::loadingBar(string msg) {

    slowPrint(msg + "\n", 10);

    cout << "[";

    for (int i = 0; i < 30; i++)
    {
        cout << char(219);
        Sleep(40);
    }

    cout << "]\n";
}

// ================= LOGIN SYSTEM =================

bool MindGame::signUp() {

    clearScreen();
    title();

    setColor(11);
    cout << "\n============== SIGN UP ==============\n\n";
    setColor(7);

    cout << "Create Username : ";
    getline(cin, playerName);

    cout << "Create Password : ";
    getline(cin, password);

    ofstream file("players.txt");

    if (file.is_open())
    {
        file << playerName << endl;
        file << password << endl;
        file << gamesPlayed << endl;

        file.close();

        setColor(10);
        cout << "\nAccount Created Successfully!\n";
        setColor(7);

        pauseScreen();
        return true;
    }

    return false;
}

bool MindGame::signIn() {

    clearScreen();
    title();

    string user, pass;
    string storedUser, storedPass;

    setColor(11);
    cout << "\n============== SIGN IN ==============\n\n";
    setColor(7);

    cout << "Username : ";
    getline(cin, user);

    cout << "Password : ";
    getline(cin, pass);

    ifstream file("players.txt");

    if (file.is_open())
    {
        getline(file, storedUser);
        getline(file, storedPass);
        file >> gamesPlayed;

        file.close();

        if (user == storedUser && pass == storedPass)
        {
            playerName = user;

            setColor(10);
            cout << "\nLogin Successful!\n";
            setColor(7);

            pauseScreen();
            return true;
        }
    }

    setColor(12);
    cout << "\nInvalid Username or Password!\n";
    setColor(7);

    pauseScreen();
    return false;
}

// ================= FILE HANDLING =================

void MindGame::loadPlayerData() {

    ifstream file("players.txt");

    if (file.is_open())
    {
        getline(file, playerName);
        getline(file, password);
        file >> gamesPlayed;

        file.close();
    }
}

void MindGame::savePlayerData() {

    ofstream file("players.txt");

    if (file.is_open())
    {
        file << playerName << endl;
        file << password << endl;
        file << gamesPlayed << endl;

        file.close();
    }
}

void MindGame::writeSessionLog(int result) {

    ofstream logFile("session_log.txt", ios::app);

    if (logFile.is_open())
    {
        time_t now = time(nullptr);

        // Buffer large enough for ctime output (26 chars including newline and null)
        char timeBuf[26] = { 0 };
        bool time_ok = false;

#if defined(_MSC_VER)
        // MSVC: use ctime_s
        if (ctime_s(timeBuf, sizeof(timeBuf), &now) == 0)
        {
            time_ok = true;
        }
#else
        // POSIX: use ctime_r
        if (ctime_r(&now, timeBuf) != nullptr)
        {
            time_ok = true;
        }
#endif

        logFile << "Player Name : " << playerName << endl;
        logFile << "Games Played: " << gamesPlayed << endl;
        logFile << "Magic Number: " << result << endl;

        if (time_ok)
        {
            // ctime output already contains a trailing newline
            logFile << "Session Time: " << timeBuf;
        }
        else
        {
            logFile << "Session Time: Unknown\n";
        }

        logFile << "----------------------------------\n";

        logFile.close();
    }
}

// ================= GAME FUNCTIONS =================

void MindGame::title() {

    setColor(11);

    cout << "====================================================\n";
    cout << "               MIND GUESSING GAME PLUS              \n";
    cout << "====================================================\n";

    setColor(7);
}

void MindGame::rules() {

    clearScreen();

    title();

    setColor(14);

    cout << "\n================== GAME RULES ==================\n\n";

    setColor(10);

    cout << "1. Think of ANY number from 1 to 9.\n\n";
    cout << "2. Follow all instructions carefully.\n\n";
    cout << "3. Perform calculations in your mind.\n\n";
    cout << "4. At the end, game will guess your answer.\n\n";
    cout << "5. You will also receive a mystery prize.\n\n";

    setColor(14);

    cout << "================================================\n";

    setColor(7);

    pauseScreen();
}

int MindGame::playRound() {

    clearScreen();

    title();

    int num = (rand() % 10 + 1) * 2;

    setColor(11);

    slowPrint("\nStep 1 -> Think of a number from 1 to 9\n");
    pauseScreen();

    slowPrint("\nStep 2 -> Add the same number of your Friend\n");
    pauseScreen();

    slowPrint("\nStep 3 -> Add my number: " + to_string(num) + "\n");
    pauseScreen();

    slowPrint("\nStep 4 -> Divide total by 2\n");
    pauseScreen();

    slowPrint("\nStep 5 -> Subtract your Friends number\n");
    pauseScreen();

    num = num / 2;

    setColor(10);

    slowPrint("\nYour Final Number Is : ");
    cout << num << endl;

    setColor(7);

    return num;
}

void MindGame::showPrize(int value) {

    cout << endl;

    loadingBar("Spinning Prize Wheel...");

    setColor(14);

    cout << "\n============= YOUR PRIZE =============\n\n";

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

    default:
        cout << "Better Luck Next Time!\n";
    }

    setColor(14);

    cout << "\n======================================\n";

    setColor(7);
}

void MindGame::showScore() {

    setColor(11);

    cout << "\n================ SCOREBOARD ================\n\n";

    setColor(10);

    cout << "Player Name  : " << playerName << endl;
    cout << "Games Played : " << gamesPlayed << endl;

    setColor(11);

    cout << "\n============================================\n";

    setColor(7);
}

// ================= MAIN GAME LOOP =================

void MindGame::run() {

    srand(time(0));

    int choice;

    while (true)
    {
        clearScreen();

        title();

        setColor(14);

        cout << "\n================ MAIN MENU ================\n\n";

        setColor(10);

        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Exit\n";

        setColor(14);

        cout << "\n===========================================\n";

        setColor(7);

        choice = menuChoice(1, 3);

        if (choice == 1)
        {
            signUp();
        }

        else if (choice == 2)
        {
            if (signIn())
                break;
        }

        else
        {
            slowPrint("\nThank You For Playing!\n");
            return;
        }
    }

    rules();

    char again = 'Y';

    while (again == 'Y' || again == 'y')
    {
        gamesPlayed++;

        int result = playRound();

        showPrize(result);

        savePlayerData();
        writeSessionLog(result);

        setColor(11);

        cout << "\n\n1. Play Again\n";
        cout << "2. Exit Game\n";

        setColor(7);

        int option = menuChoice(1, 2);

        if (option == 1)
            again = 'Y';
        else
            again = 'N';
    }

    clearScreen();

    title();

    showScore();

    slowPrint("\nThanks For Playing, " + playerName + "!\n");

    pauseScreen();
}

// ================= MAIN FUNCTION =================

int main() {

    Game* game = new MindGame();

    game->run();

    delete game;

    return 0;
}