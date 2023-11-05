#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <conio.h>

const std::string DEFAULT = "\033[0m";
const std::string BLACK = "\033[38;2;0;0;0m";
const std::string COLUMNS = "\033[38;2;0;255;255m";
const std::string ROWS = "\033[38;2;0;255;0m";
std::string BACKGROUND_COLOR = "";
std::vector<std::vector<std::string>> board;
int rows;
int cols;
int inARow;
int numPlayers;
std::vector<std::string> playerRGBs;

void printBoard() {
    std::cout << "\n";
    for (int i = 0; i < rows; i++) {
        if (i < 9) {
            std::cout << DEFAULT + ROWS + " " << (i + 1) << " ";
        } else {
            std::cout << DEFAULT + ROWS << (i + 1) << " ";
        }
        for (int z = 0; z < cols; z++) {
            std::string color = playerRGBs[std::stoi(board[i][z])];
            std::cout << BACKGROUND_COLOR + BLACK << color + board[i][z] << BLACK + " " + DEFAULT;
        }
        std::cout << "\n";
    }
    std::cout << "   ";
    for (int i = 0; i < cols; i++) {
        if (i < 9) {
            std::cout << DEFAULT + COLUMNS + " " << (i + 1) << " ";
        } else {
            std::cout << DEFAULT + COLUMNS << (i + 1) << " ";
        }
    }
    std::cout << DEFAULT << "\n";
}

bool checkSpace(int col) {
    for (int i = 0; i < rows; i++) {
        if (board[i][col] == "00") {
            return true;
        }
    }
    return false;
}

bool checkFullBoard() {
    for (int i = 0; i < cols; i++) {
        if (checkSpace(i) == true) {
            return false;
        }
    }
    return true;
}

int dropPiece(int col, int player) {
    int row = -1;
    for (int i = (rows - 1); i >= 0; i--) {
        if (board[i][col] == "00") {
            row = i;
            if (player < 10) {
                board[i][col] = std::format("{}{}", "", std::format("{}{}", "0", player));
            } else {
                board[i][col] = std::format("{}{}", "", player);
            }
            
            break;
        }
    }
    return row;
}

bool checkWin(int row, int col) {
    std::vector<int> playerInARow = { 0,1 };
    for (int i = 0; i < cols; i++) {
        if (playerInARow[0] != 0 && playerInARow[0] == std::stoi(board[row][i])) {
            playerInARow[1]++;
        } else {
            playerInARow[0] = std::stoi(board[row][i]);
            playerInARow[1] = 1;
        }
        if (playerInARow[0] != 0 && playerInARow[1] == inARow) {
            return true;
        }
    }
    playerInARow[0] = 0;
    playerInARow[1] = 1;
    for (int i = 0; i < rows; i++) {
        if (playerInARow[0] != 0 && playerInARow[0] == std::stoi(board[i][col])) {
            playerInARow[1]++;
        } else {
            playerInARow[0] = std::stoi(board[i][col]);
            playerInARow[1] = 1;
        }
        if (playerInARow[0] != 0 && playerInARow[1] == inARow) {
            return true;
        }
    }
    playerInARow[0] = 0;
    playerInARow[1] = 1;
    int startRow = row;
    int startCol = col;
    int maxIterations = fmin(rows, cols);
    for (int i = 0; i < maxIterations; i++) {
        if (startRow != 0 && startCol != 0) {
            startRow--;
            startCol--;
        } else {
            break;
        }
    }
    for (int i = 0; i < maxIterations; i++) {
        if (playerInARow[0] != 0 && playerInARow[0] == std::stoi(board[startRow][startCol])) {
            playerInARow[1]++;
        } else {
            playerInARow[0] = std::stoi(board[startRow][startCol]);
            playerInARow[1] = 1;
        }
        if (playerInARow[0] != 0 && playerInARow[1] == inARow) {
            return true;
        }
        if (startRow != (rows - 1) && startCol != (cols - 1)) {
            startRow++;
            startCol++;
        } else {
            break;
        }
    }
    playerInARow[0] = 0;
    playerInARow[1] = 1;
    startRow = row;
    startCol = col;
    for (int i = 0; i < maxIterations; i++) {
        if (startRow != 0 && startCol != (cols-1)) {
            startRow--;
            startCol++;
        } else {
            break;
        }
    }
    for (int i = 0; i < maxIterations; i++) {
        if (playerInARow[0] != 0 && playerInARow[0] == std::stoi(board[startRow][startCol])) {
            playerInARow[1]++;
        } else {
            playerInARow[0] = std::stoi(board[startRow][startCol]);
            playerInARow[1] = 1;
        }
        if (playerInARow[0] != 0 && playerInARow[1] == inARow) {
            return true;
        }
        if (startRow != (rows - 1) && startCol != 0) {
            startRow++;
            startCol--;
        } else {
            break;
        }
    }
    return false;
}

bool takeTurn(int player) {
    bool invalid = true;
    int col = 0;
    std::cout << "Player " << player << ", enter a column (1-" << cols << ") to drop your piece: ";
    while (invalid) {
        std::cin >> col;
        col--;
        if (col >= 0 && col <= cols - 1) {
            if (checkSpace(col)) {
                invalid = false;
            } else {
                std::cout << "Ther is no more space in column " << (col + 1) << ". Please try another column: ";
            }
        } else {
            std::cout << "Column " << (col + 1) << " doesn't exist. Try again: ";
        }
    }
    int row = dropPiece(col, player);
    return checkWin(row, col);
}

int main() {
    int r;
    int g;
    int b;
    std::cout << "Enter the R value of an RGB code for the background color: ";
    while (true) {
        std::cin >> r;
        if (r >= 0 && r <= 255) {
            break;
        } else {
            std::cout << "\nSorry, invalid entry. Try again: ";
        }
    }
    std::cout << "\nEnter the G value of an RGB code for the background color: ";
    while (true) {
        std::cin >> g;
        if (g >= 0 && g <= 255) {
            break;
        } else {
            std::cout << "\nSorry, invalid entry. Try again: ";
        }
    }
    std::cout << "\nEnter the B value of an RGB code for the background color: ";
    while (true) {
        std::cin >> b;
        if (b >= 0 && b <= 255) {
            break;
        } else {
            std::cout << "\nSorry, invalid entry. Try again: ";
        }
    }
    BACKGROUND_COLOR = std::format("\033[1;48;2;{};{};{}m", r, g, b);
    std::cout << "\n\nHow many rows should the board have? (Minimum is 5): ";
    while (true) {
        std::cin >> rows;
        if (rows < 5) {
            std::cout << "\nSorry, there need to be at least 5 rows. Try again: ";
        } else {
            break;
        }
    }
    std::cout << "\nHow many columns should the board have? (Minimum is 5): ";
    while (true) {
        std::cin >> cols;
        if (cols < 5) {
            std::cout << "\nSorry, there need to be at least 5 columns. Try again: ";
        } else {
            break;
        }
    }
    board.resize(rows);
    for (int i = 0; i < rows; i++) {
        board[i].resize(cols);
    }
    for (int i = 0; i < rows; i++) {
        for (int z = 0; z < cols; z++) {
            board[i][z] = "00";
        }
    }
    std::cout << "\nHow many pieces in a row should be required to win? (Minimum is 3): ";
    while (true) {
        std::cin >> inARow;
        if (inARow < 3 || inARow >(fmin(rows, cols) - 1)) {
            std::cout << "Sorry, the number of pieces in a row to win must be at least 3 and\nat most the minimum between the number of rows and columns minus 1.\nTry again: ";
        } else {
            break;
        }
    }
    std::cout << "\n\nHow many people are playing? (Minimum is 2): ";
    while (true) {
        std::cin >> numPlayers;
        if (numPlayers < 2) {
            std::cout << "\nSorry, there need to be at least 2 players. Try again: ";
        } else {
            break;
        }
    }
    std::cout << "\033[H\033[2J\033[3J";
    playerRGBs.resize(1);
    playerRGBs[0] = BLACK;
    for (int i = 1; i <= numPlayers; i++) {
        std::cout << "\nPlayer " << i << ", enter the R value of an RGB code: ";
        while (true) {
            std::cin >> r;
            if (r >= 0 && r <= 255) {
                break;
            } else {
                std::cout << "\nSorry, invalid entry. Try again: ";
            }
        }
        std::cout << "\nPlayer " << i << ", enter the G value of an RGB code: ";
        while (true) {
            std::cin >> g;
            if (g >= 0 && g <= 255) {
                break;
            } else {
                std::cout << "\nSorry, invalid entry. Try again: ";
            }
        }
        std::cout << "\nPlayer " << i << ", enter the B value of an RGB code: ";
        while (true) {
            std::cin >> b;
            if (b >= 0 && b <= 255) {
                break;
            } else {
                std::cout << "\nSorry, invalid entry. Try again: ";
            }
        }
        playerRGBs.push_back(std::format("\033[38;2;{};{};{}m", r, g, b));
    }
    std::cout << "\033[H\033[2J\033[3J";
    printBoard();
    bool loop = true;
    while (loop) {
        for (int i = 1; i <= numPlayers; i++) {
            bool full = checkFullBoard();
            if (!full) {
                bool win = takeTurn(i);
                std::cout << "\033[H\033[2J\033[3J";
                printBoard();
                if (win) {
                    std::cout << "\n\n" << playerRGBs[i] << "Player " << i << " WON!" << DEFAULT << "\n\n";
                    loop = false;
                    break;
                }
            } else {
                std::cout << DEFAULT + "\n\nThe board is full! It's a TIE!\n\n";
                loop = false;
                break;
            }
        }
    }
    std::cout << "Press any key to close this window . . .";
    int w = _getch();
}