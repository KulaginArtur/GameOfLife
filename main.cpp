#include <iostream>
#include <vector>
#include <unistd.h>

const int ROWS = 40; // Height
const int COLS = 70; // Width

void printBoard(std::vector<std::vector<bool> > board) {
  system("clear"); // clear the terminal
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board[i][j]) {
        std::cout << "*"; // print alive cells as *
      } else {
        std::cout << " "; // print dead cells as space
      }
    }
    std::cout << std::endl;
  }
}

bool getCell(std::vector<std::vector<bool> > board, int row, int col) {
  // handle out-of-bounds cells by wrapping around the board
  int r = (row + ROWS) % ROWS;
  int c = (col + COLS) % COLS;
  return board[r][c];
}

void updateBoard(std::vector<std::vector<bool> >& board) {
  std::vector<std::vector<bool> > newBoard(ROWS, std::vector<bool>(COLS, false));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int neighbors = 0;
      for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
          if (di == 0 && dj == 0) {
            continue; // skip the cell itself
          }
          if (getCell(board, i + di, j + dj)) {
            neighbors++;
          }
        }
      }
      if (board[i][j]) { // cell is alive
        if (neighbors < 2 || neighbors > 3) {
          newBoard[i][j] = false; // cell dies
        } else {
          newBoard[i][j] = true; // cell survives
        }
      } else { // cell is dead
        if (neighbors == 3) {
          newBoard[i][j] = true; // cell comes to life
        }
      }
    }
  }
  board = newBoard; // update the board
}

int main() {
  // initialize the board randomly
  std::vector<std::vector<bool> > board(ROWS, std::vector<bool>(COLS, false));
  for (int i = 0; i < ROWS * COLS / 4; i++) {
    int row = rand() % ROWS;
    int col = rand() % COLS;
    board[row][col] = true;
  }

  while (true) {
    printBoard(board);
    updateBoard(board);
    usleep(100000); // sleep for 100ms
  }

  return 0;
}
