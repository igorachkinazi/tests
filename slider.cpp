#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 

using namespace std;

#define LUC "\u250f"
#define HBR "\u2501"
#define RUC "\u2513"
#define VBR "\u2503"
#define LLC "\u2517"
#define RLC "\u251b"

#define TIME_NOW chrono::steady_clock::now()

class SliderGame {
public:
    SliderGame(int size) : size(size), board(size * size) {
        reset();
    }

    void printBoard() const {
        cout << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j)
                cout << LUC << HBR << HBR << RUC;
            cout << endl;
            for (int j = 0; j < size; ++j) {
                int val = board[i * size + j];
                cout << VBR;
                if(val)
                   printf("%2d", val);
                else
                   cout << "  ";
                cout << VBR;
            }
            cout << endl;
            for (int j = 0; j < size; ++j) 
                cout << LLC << HBR << HBR << RLC;
            cout << endl;
        }
    }

    int move(int tile) {
        auto it = find(board.begin(), board.end(), tile);
        if (it == board.end()) return 0;

        int tileIndex = distance(board.begin(), it);
        int emptyIndex = find(board.begin(), board.end(), 0) - board.begin();

        if (isAdjacent(tileIndex, emptyIndex)) {
            swap(board[tileIndex], board[emptyIndex]);
            return 1;
        }
        return 0;
    }

    int moveUp() {
        int emptyIndex = find(board.begin(), board.end(), 0) - board.begin();
        int tileIndex = emptyIndex + size;
        if(tileIndex < size * size) {
            swap(board[tileIndex], board[emptyIndex]);
            return 1;
        }
        return 0;
    }

    int moveDown() {
        int emptyIndex = find(board.begin(), board.end(), 0) - board.begin();
        int tileIndex = emptyIndex - size;
        if(tileIndex >= 0) {
            swap(board[tileIndex], board[emptyIndex]);
            return 1;
        }
        return 0;
    }

    int moveLeft() {
        int emptyIndex = find(board.begin(), board.end(), 0) - board.begin();
        if(emptyIndex % size != size - 1) {
            swap(board[emptyIndex + 1], board[emptyIndex]);
            return 1;
        }
        return 0;
    }

    int moveRight() {
        int emptyIndex = find(board.begin(), board.end(), 0) - board.begin();
        if(emptyIndex % size) {
            swap(board[emptyIndex - 1], board[emptyIndex]);
            return 1;
        }
        return 0;
    }

    bool isSolved() const {
        for (int i = 0; i < size * size - 1; ++i) {
            if (board[i] != i + 1) return false;
        }
        return board[size * size - 1] == 0;
    }

    void reset() {
        for (int i = 0; i < size * size; ++i) {
            board[i] = i;
        }

        random_device rd; 
        auto g = default_random_engine { rd() };
        shuffle(board.begin(), board.end(), g);
    }

private:
    bool isAdjacent(int index1, int index2) const {
        int row1 = index1 / size;
        int col1 = index1 % size;
        int row2 = index2 / size;
        int col2 = index2 % size;

        return (abs(row1 - row2) + abs(col1 - col2)) == 1;
    }

    int size;
    vector<int> board;
};

bool is_number(string& str) {
    if (str.empty())
        return false;

    size_t pos = 0;
    try {
        std::stoi(str, &pos);
    } catch (const invalid_argument& ia) {
        return false;
    } catch (const out_of_range& oor) {
        return false;
    }

    return pos == str.length();
}

int main() {
    vector<int> bestScores;
    vector<double> bestTimes;

    int size;
    cout << " Enter size of the game board: ";
    cin >> size;

    SliderGame game(size);
    game.reset();
    int moves = 0;
    auto begin_t = TIME_NOW;

    while (true) {
        game.printBoard();

        string str;
        int tile = -2;
        cout << "Moves: " << moves << endl;
        cout << "Enter tile to move (or w - to move up, a - left, s - down, d - right),  0 to reset, -1 or ^C to exit: ";
        cin >> str;

        if(is_number(str)) {
            tile = stoi(str);
            if (tile == 0) {
                game.reset();
                moves = 0;
                begin_t = TIME_NOW;
            }
            else if (tile == -1)
                break;
            else
                moves += game.move(tile);
        }
        else {
            if(str == "w")
                moves += game.moveUp();
            else if(str == "s")
                moves += game.moveDown();
            else if(str == "a")
                moves += game.moveLeft();
            else if(str == "d")
                moves += game.moveRight();
        }
 
        if (game.isSolved()) {
            game.printBoard();
            auto elapsed_secs = chrono::duration_cast<chrono::seconds>(TIME_NOW - begin_t);
            cout << "You solved it in " << moves << " moves and " << elapsed_secs.count() << " seconds!" << endl;
            bestScores.push_back(moves);
            sort(bestScores.begin(), bestScores.end());
            cout << endl << "Best scores so far:" << endl;
            for (auto i : bestScores)
                cout << "Solved in " << i << " moves" << endl;
            bestTimes.push_back(elapsed_secs.count());
            sort(bestTimes.begin(), bestTimes.end());
            cout << endl << "Best times so far:" << endl;
            for (auto i : bestTimes)
                cout << "Solved in " << i << " seconds" << endl;
            cout << endl << "Enter p to play again or ^C to exit ";
            cin >> str;
            game.reset();
            moves = 0;
            begin_t = TIME_NOW;
        }
    }

    return 0;
}

