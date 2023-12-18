#pragma once

#include "sudoku.h"

typedef struct {
    Cell *cell;
    int candidate1;
    int candidate2;
    int candidate3;
    int num_candidates;
} UnsetInfo_NakedTriple;

typedef struct {
    Cell *cell1;
    Cell *cell2;
    Cell *cell3;
} NakedTriple;

int naked_triples(SudokuBoard *p_board);