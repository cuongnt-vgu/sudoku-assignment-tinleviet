#pragma once

#include "sudoku.h"

int naked_pairs(SudokuBoard *p_board);
void find_naked_pairs(Cell **p_cells, int *p_counter);