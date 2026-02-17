/**
FROM CHAT-GPT
*/

#include <iostream>

int n_row, n_col;
char grid[30][30] = {'\0'};

int find_ground_row(int col) {
    int row = 0;
    while (
        grid[row][col] != 'O' &&
        grid[row][col] != '\0'
    ) row++;
    
    return row;
}

int main() {
    std::cin >> n_row >> n_col;

    for (int i = 0; i < n_row; i++) {
        std::cin >> grid[i];
    }

    for (int col = 0; col < n_col; col++) {
        int bricks;
        std::cin >> bricks;
        int ground_row = find_ground_row(col);
        while (--ground_row >= 0 && bricks-- > 0) { // fill brick from ground
            grid[ground_row][col] = '#';
        }
    }

    // แสดงผล
    for (int i = 0; i < n_row; i++) {
        std::cout << grid[i] << "\n";
    }

}