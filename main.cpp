#include <iostream>
#include <vector>
#include <memory>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

char getChar() {
    #ifdef _WIN32
        return _getch();
    #else
        #include <termios.h>
        #include <unistd.h>
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        char c = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return c;
    #endif
}

#include "MapFactory.h"

struct LevelInfo {
    std::string type;
    std::string file;
};

int main() {
    std::vector<LevelInfo> levels = {
        {"garden", "garden_1.txt"},
        {"garden", "garden_2.txt"},
        {"garden", "garden_3.txt"},
        {"garden", "garden_4.txt"},
        {"garden", "garden_5.txt"},
        {"garden", "garden_6.txt"},
        {"ocean", "ocean_1.txt"},
        {"ocean", "ocean_2.txt"},
        {"ocean", "ocean_3.txt"},
        {"ocean", "ocean_4.txt"}
    };

    for (const auto& level : levels) {
    next_level:
        std::unique_ptr<BaseMap> game = MapFactory::create(level.type);
        if (!game) {
            std::cerr << "Invalid map type: " << level.type << "\n";
            continue;
        }

    restart_level:
        game->loadFromFile(level.file);

        while (true) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            game->render();

            if (game->isVictory()) {
                std::cout << "\nVictory! Press [any key] to continue: \n";
                char C = getChar();
                std::cout << C << '\n';
                break;
            }

            if (game->hasFailed()) {
                std::cout << "\nPress R to restart, [any key] to quit game: ";
                char c = getch();
                std::cout << c << '\n';
                if (tolower(c) == 'r') goto restart_level;
                else {
                    std::cout << "Game exited.\n";
                    return 0;
                }
            }

            std::cout << "\nMove (WASD), R = Retry, U = Undo, E = Redo, Q = Quit: ";
            char input = getChar();
            std::cout << input << '\n';

            switch (tolower(input)) {
                case 'w': case 'a': case 's': case 'd':
                    game->movePlayer(input);
                    break;
                case 'r':
                    goto restart_level;
                case 'u':
                    game->undo();
                    break;
                case 'e':
                    game->redo();
                    break;
                case 'q':
                    std::cout << "Game exited.\n";
                    return 0;
                default:
                    break;
            }
        }
    }

    std::cout << "\nAll levels complete!\n";
    return 0;
}
