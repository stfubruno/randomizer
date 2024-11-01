#include <iostream>
#include <string>
#include <thread>
#include <random>

#define NOMINMAX
#include <windows.h>

void cls(void)
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, TEXT(' '),
        dwConSize, coordScreen, &cCharsWritten);

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    FillConsoleOutputAttribute(hConsole, csbi.wAttributes
}

void loadingHoleAnimation() {
    cls()

        std::cout << "Loading... ";
    std::cout.flush();

    std::chrono::milliseconds delay(3000);

    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - startTime < delay) {
        static const std::string animation = "|/-\\";
        for (char frame : animation) {
            std::cout << '\r' << frame << " Loading... ";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    cls()
}

void shuffleNames(std::vector<std::string>& names) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(names.begin(), names.end(), generator);
}

int getValidTeamSize() {
    int teamSize;

    while (true) {
        std::cout << "Enter the team size (between 2 and 5): ";
        if (std::cin >> teamSize && teamSize > 1 && teamSize <= 5) {
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid team size. Team size must be an integer between 2 and 5.\n";
        }
    }

    return teamSize;
}

std::string getRandomTeamRole() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 1);

    std::random_device seed;
    generator.seed(seed());

    int role = distribution(generator);
    return (role == 0) ? "Attacker" : "Defender";
}

void hideConsoleCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

int main() {
    int teamSize = getValidTeamSize();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the newline character from the input stream

    cls()

        int totalPlayers = teamSize * 2;
    std::vector<std::string> names(totalPlayers);

    for (int i = 0; i < totalPlayers; i++) {
        std::cout << "Player " << (i + 1) << ": ";
        std::getline(std::cin, names[i]);
    }

    shuffleNames(names);
    loadingHoleAnimation();

    std::string teamARole = getRandomTeamRole();
    std::string teamBRole = (teamARole == "Attacker") ? "Defender" : "Attacker";

    std::cout << "Team A (" << teamARole << "):\n";
    for (int i = 0; i < teamSize; i++) {
        std::cout << names[i] << std::endl;
    }

    std::cout << "\nTeam B (" << teamBRole << "):\n";
    for (int i = teamSize; i < totalPlayers; i++) {
        std::cout << names[i] << std::endl;
    }

    hideConsoleCursor();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}