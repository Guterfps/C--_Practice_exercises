
#include <iostream>
#include <vector>

void GameOfLife(std::vector<std::vector<int>>& board);
void PrintBoard(std::vector<std::vector<int>>& board);

static constexpr short NUM_OF_NIB = 8;

int main(void) {
    std::vector<std::vector<int>> board = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};

    std::cout << "before:\n";
    PrintBoard(board);
    
    GameOfLife(board);

    std::cout << "after:\n";
    PrintBoard(board);

    return 0;
}

void GameOfLife(std::vector<std::vector<int>>& board) {
    static constexpr short r_nib[NUM_OF_NIB] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static constexpr short c_nib[NUM_OF_NIB] = {-1, 0, 1, -1, 1, -1, 0, 1};

    size_t rows = board.size();
    size_t cols = board[0].size();

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            size_t num_of_nib = 0;
            
            for (size_t t = 0; t < NUM_OF_NIB; ++t) {
                if (((i + r_nib[t]) < rows) && ((j + c_nib[t]) < cols)) {
                    num_of_nib += board[i + r_nib[t]][j + c_nib[t]] & 1;
                }
            }

            if (board[i][j] == 1) {
                if ((num_of_nib == 2) || (num_of_nib == 3)) {
                    board[i][j] += 2;
                }
            }
            else if (num_of_nib == 3) {
                board[i][j] += 2;
            }
        }
    }


    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            board[i][j] = (board[i][j] > 1) ? 1 : 0;
        }
    }

}

void PrintBoard(std::vector<std::vector<int>>& board) {
    for (auto row : board) {
        for (int cell : row) {
            std::cout << cell << ", ";
        }

        std::cout << '\n';
    }

    std::cout << std::endl;
}