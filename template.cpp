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

    bool makeMove(int row, int col, char symbol)
    {
        if (!isValidMove(row, col))
            return false;
        grid[row][col] = symbol;
        return true;
    }
     // in Board class, public:
    void setCell(int row, int col, char symbol)
    {
        if (row >= 0 && row < size && col >= 0 && col < size)
            grid[row][col] = symbol;
    }
    void clearCell(int row, int col)
    {
        setCell(row, col, ' ');
    }

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

    bool checkWin(char symbol) const
    {
        // Check rows
        for (int i = 0; i < size; ++i)
        {
            bool win = true;
            for (int j = 0; j < size; ++j)
            {
                if (grid[i][j] != symbol)
                {
                    win = false;
                    break;
                }
            }
            if (win)
                return true;
        }
        // Check columns
        for (int j = 0; j < size; ++j)
        {
            bool win = true;
            for (int i = 0; i < size; ++i)
            {
                if (grid[i][j] != symbol)
                {
                    win = false;
                    break;
                }
            }
            if (win)
                return true;
        }

        // Main diagonal
        bool win = true;
        for (int i = 0; i < size; ++i)
        {
            if (grid[i][i] != symbol)
            {
                win = false;
                break;
            }
        }
        if (win)
            return true;

        // Anti-diagonal
        win = true;
        for (int i = 0; i < size; ++i)
        {
            if (grid[i][size - 1 - i] != symbol)
            {
                win = false;
                break;
            }
        }
        if (win)
            return true;

        return false;
    }

    bool isFull() const
    {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (grid[i][j] == ' ')
                    return false;
        return true;
    }

    char getCell(int row, int col) const
    {
        if (row < 0 || row >= size || col < 0 || col >= size)
            return ' ';
        return grid[row][col];
    }

    void reset()
    {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                grid[i][j] = ' ';
    }

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
    Player()
    {
        this->name = "";
        this->symbol = ' ';
    }

    Player(const string &name, char symbol)
    {
        this->name = name;
        this->symbol = symbol;
    }

    virtual void getMove(int &row, int &col, const Board &board) = 0;

    string getName() const
    {
        return name;
    }

    char getSymbol() const
    {
        return symbol;
    }

    void setName(const string &n)
    {
        name = n;
    }
};

// ================== Human Player ==================
class HumanPlayer : public Player
{
public:
    HumanPlayer(const string &name, char symbol)
    {
        this->name = name;
        this->symbol = symbol;
    }

    void getMove(int &row, int &col, const Board &board) override
    {
        cout << "\n"
             << this->name << " (" << this->symbol << "), it's your turn!\n";

        while (true)
        {
            cout << "Enter row (1-indexed): ";
            int size = board.getSize();
            while (!(cin >> row) || row < 1 || row > size)
            {
                cout << "Invalid input! Please enter a number between 1 and " << size << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Enter column (1-indexed): ";
            while (!(cin >> col) || col < 1 || col > size)
            {
                cout << "Invalid input! Please enter a number between 1 and " << size << ": ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            row--;
            col--;

            if (board.isValidMove(row, col))
            {
                break;
            }
            else
            {
                cout << "Invalid move! That cell is already occupied. Try again.\n";
            }
        }
    }
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

    int minimax(Board &board, bool isMax , int alpha , int beta , int depth) const
    {
        char opponent = (symbol == 'X') ? 'O' : 'X';

        if (board.checkWin(symbol))
            return 10 - depth ;
        if (board.checkWin(opponent))
            return depth -10;
        if (board.isFull())
            return 0;

        if (isMax)
        {
            int best = INT_MIN;
            for (int i = 0; i < board.getSize(); i++)
            {
                for (int j = 0; j < board.getSize(); j++)
                {
                    if (board.isValidMove(i, j))
                    {
                        board.makeMove(i, j, symbol);
                        best = max(best, minimax(board, false , alpha , beta, depth +1));
                        board.setCell(i, j, ' ');
                        alpha = max(alpha, best);
                        //Alpha-Beta pruning.
                        if(beta<= alpha)
                            return best;
                    }
                }
            }
            return best;
        }
        else
        {
            int best = INT_MAX;
            for (int i = 0; i < board.getSize(); i++)
            {
                for (int j = 0; j < board.getSize(); j++)
                {
                    if (board.isValidMove(i, j))
                    {
                        board.makeMove(i, j, opponent);
                        best = min(best, minimax(board, true , alpha , beta, depth +1));
                        board.setCell(i, j, ' ');

                        beta = min(beta , best);
                        // Alpha-Beta pruning
                        if(beta <= alpha)
                            return best;

                    }
                }
            }
            return best;
        }
    }

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
                    int moveVal = minimax(board, false ,INT_MIN , INT_MAX , 0);
                    board.setCell(i, j, ' ');

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

    void getMove(int &row, int &col, const Board &board) override
    {
        if (difficulty == 1)
            getRandomMove(board, row, col);
        else
        {
            Board temp = board;
            getBestMove(temp, row, col);
        }
    }
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

    Game(int size)
    {
        board = Board(size);
        player1 = nullptr;
        player2 = nullptr;
        current = nullptr;
    };

    void showMenu()
    {
        cout << endl
             << "TIC-TAC-TOE GAME" << endl;
        cout << " ================== " << endl;
        cout << "1.Player vs Player" << endl;
        cout << "2.Player vs Computer(Easy)" << endl;
        cout << "3.Player vs Computer(Hard)" << endl;
        cout << "4.Exit" << endl;
        cout << "Select game mode: ";
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
            return;
        default:
            cout << "This number is incorrect, Try again.";
            showMenu();
        }
    };

    void setupPvP()
    {
        string name1, name2;
        cout << "Hello Player 1 , Enter your name : ";
        cin >> name1;
        cout << "Hello Player 2 , Enter your name : ";
        cin >> name2;
        player1 = new HumanPlayer(name1, 'X');
        player2 = new HumanPlayer(name2, 'O');
        cout << "Player 1 : " << name1 << " (X)" << endl;
        cout << "Player 2 : " << name2 << " (O)" << endl;
        current = player1;
        board.reset();
        board.display();
    };

    void setupPVC(int diff)
    {
        string name1;
        cout << "Hello Player 1 , Enter your name : ";
        cin >> name1;
        player1 = new HumanPlayer(name1, 'X');
        player2 = new AIPlayer("Computer", 'O', diff);
        cout << "Player 1 : " << name1 << " (X)\n";

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

    bool checkGameEnd() const
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
        srand(time(0));

        showMenu();

        if (player1 == nullptr || player2 == nullptr)
        {
            return;
        }

        while (true)
        {
            int row, col;
            cout << current->getName() << "'s turn (" << current->getSymbol() << "):\n";
            current->getMove(row, col, board);
            board.makeMove(row, col, current->getSymbol());
            board.display();

            if (checkGameEnd())
                break;

            switchPlayer();
        }
    }

    ~Game()
    {
        delete player1;
        delete player2;
    }
};

// ================== Main ==================
int main()
{
    char again;

    do
    {
        //-------------- Board Size Selection ---------------
        int size;
        cout << "Select board size:\n"
             << "  - 0 for standard 3x3\n"
             << "  - (Choose a number) for custom n x n board\n"
             << "Your choice: ";

            while(true){
                if(!(cin >> size)){
                    cout<< "Invalid input! Please enter a number : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else if(size == 0){
                size = 3;
                break;
                } else if(size < 3){
                cout << "Board size must be 3 or greater! Try again: ";
                } else {
                break;
                }

            }
        //------------------------------------------------

        Game g(size);
        g.start();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max() , '\n');

    } while (again == 'y' || again == 'Y');

    cout << "Thanks for playing!\n";

    return 0;
}
