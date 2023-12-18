#pragma once

#include "sudoku.h"

typedef struct {
    Cell *cell1;
    Cell *cell2;
    Cell *cell3;
    int num_1;
    int num_2;
    int num_3;
} HiddenTriples;

int check_cell_in_hidden_triples(int triples[3], Cell* p_cell);
int check_hidden_triples(Cell **p_cells, int possible_triples[], int *indices);
void find_hidden_triples(Cell **p_cells, HiddenTriples *p_hidden_triples, int *p_counter);
int hidden_triples(SudokuBoard *p_board);