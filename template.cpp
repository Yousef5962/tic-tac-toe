#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================== Board Class ==================
class Board
{
private:
    vector<vector<char>> grid;
    int size;

public:
    Board(int s = 3)
    {
        size = s;
        grid.resize(size, vector<char>(size, ' '));
    }

    void display() const
    {
        cout << endl;

        // Print column headers
        cout << "   "; // offset
        for (int c = 0; c < size; c++)
        {
            cout << " " << c + 1 << "  ";
        }
        cout << endl;

        for (int r = 0; r < size; r++)
        {
            // Print row number
            cout << " " << r + 1 << " ";

            for (int c = 0; c < size; c++)
            {
                cout << " " << grid[r][c] << " ";
                if (c < size - 1)
                    cout << "|";
            }
            cout << endl;

            // Print row separator
            if (r < size - 1)
            {
                cout << "   "; // offset
                for (int c = 0; c < size; c++)
                {
                    cout << "---";
                    if (c < size - 1)
                        cout << "+";
                }
                cout << endl;
            }
        }

        cout << endl;
    }

    bool makeMove(int row, int col, char symbol);

    bool isValidMove(int row, int col) const
    {
        // Validate row is within range
        if (row < 0 || row >= size)
        {
            return false;
        }

        // Validate column is within range
        if (col < 0 || col >= size)
        {
            return false;
        }

        // Check if the cell is empty
        return (grid[row][col] == ' ');
    }

    bool checkWin(char symbol) const;

    bool isFull() const;

    char getCell(int row, int col) const;

    void reset();

    int getSize() const
    {
        return size;
    }
};

// ================== Player (Abstract) ==================
class Player
{
protected:
    string name;
    char symbol;

public:
    Player(const string &name, char symbol);

    virtual void getMove(int &row, int &col, const Board &board) = 0;

    string getName() const;

    char getSymbol() const;

    void setName(const string &n);
};

// ================== Human Player ==================
class HumanPlayer : public Player
{
public:
    HumanPlayer(const string &name, char symbol);

    void getMove(int &row, int &col, const Board &board) override;
};

// ================== AI Player ==================
class AIPlayer : public Player
{
private:
    int difficulty;

    void getRandomMove(const Board &board, int &row, int &col) const
    {
        vector<pair<int, int>> moves;

        for (int i = 0; i < board.getSize(); i++)
        {
            for (int j = 0; j < board.getSize(); j++)
            {
                if (board.isValidMove(i, j))
                    moves.push_back({i, j});
            }
        }

        int choice = rand() % moves.size();
        row = moves[choice].first;
        col = moves[choice].second;
    }

    int minimax(Board &board, bool isMax) const;

    void getBestMove(Board &board, int &row, int &col) const
    {
        int bestVal = -1000;
        row = col = -1;
        for (int i = 0; i < board.getSize(); i++)
        {
            for (int j = 0; j < board.getSize(); j++)
            {
                if (board.isValidMove(i, j))
                {
                    board.makeMove(i, j, symbol);
                    int moveVal = minimax(board, false);
                    board.makeMove(i, j, ' ');

                    if (moveVal > bestVal)
                    {
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
    }

public:
    AIPlayer(const string &name, char symbol, int diff) : Player(name, symbol)
    {
        difficulty = diff;
    }

    void setDifficulty(int d) { difficulty = d; }

    void getMove(int &row, int &col, const Board &board) override;
};

// ================== Game Class ==================
class Game
{
private:
    Board board;
    Player *player1;
    Player *player2;
    Player *current;

public:
    Game()
    {
        board.reset();
        player1 = nullptr;
        player2 = nullptr;
        current = nullptr;
    };

    void showMenu()
    {
        cout << "TIC-TAC-TOE GAME" << endl;
        cout << " ================== " << endl;
        cout << "1.Player vs Player" << endl;
        cout << "2.Player vs Computer(Easy)" << endl;
        cout << "3.Player vs Computer(Hard)" << endl;
        cout << "4.Exit" << endl;
        cout << "Select game mode:";
        int output;
        cin >> output;
        switch (output)
        {
        case 1:
            setupPvP();
            break;
        case 2:
            setupPVC(1);
            break;
        case 3:
            setupPVC(2);
            break;
        case 4:
            cout << "The game closed.";
        default:
            cout << "This number is incorrect , Try again.";
        }
    };

    void setupPvP()
    {
        string name1, name2;
        cout << "Hello Player 1 , Enter your name :";
        cin >> name1;
        cout << "Hello Player 2 , Enter your name :";
        cin >> name2;
        player1 = new HumanPlayer(name1, 'X');
        player2 = new HumanPlayer(name2, 'O');
        cout << "Player 1 :" << name1 << "(X)";
        cout << "Player 2 :" << name2 << "(O)";
        current = player1;
        board.reset();
        board.display();
    };

    void setupPVC(int diff)
    {
        string name1;
        cout << "Hello Player 1 , Enter your name :";
        cin >> name1;
        player1 = new HumanPlayer(name1, 'X');
        player2 = new AIPlayer("Computer", 'O', diff);
        cout << "Player 1 :" << name1 << "(X)";

        if (diff == 1)
        {
            cout << "Player 2 : Computer " << "(O , Difficulty = Easy)\n";
        }
        else
        {
            cout << "Player 2 : Computer " << "(O , Difficulty = Hard)\n";
        }

        current = player1;
        board.reset();
        board.display();
    };

    void switchPlayer()
    {
        if (current == player1)
            current = player2;
        else
            current = player1;
    };

    bool checkGameEnd()
    {
        if (board.checkWin('X'))
        {
            cout << "Congratulations! " << player1->getName() << " has won the game!\n";
            return true;
        }
        else if (board.checkWin('O'))
        {
            cout << "Congratulations! " << player2->getName() << " has won the game!\n";
            return true;
        }
        else if (board.isFull())
        {
            cout << "It's a draw!";
            return true;
        }

        return false;
    };

    void start()
    {
        showMenu();

        if (player1 == nullptr || player2 == nullptr)
        {
            return;
        }

        while (true)
        {
            int row, col;
            cout << current->getName() << "'s turn (" << current->getSymbol() << "):\n";
            board.display();
            current->getMove(row, col, board);
            board.isValidMove(row, col);
            board.makeMove(row, col, current->getSymbol());
            board.display();

            if (checkGameEnd())
                break;

            switchPlayer();
        }
    }
};

// ================== Main ==================
int main()
{
    Game g;
    g.start();
    // Board b(5);
    // b.display();
    return 0;
}
