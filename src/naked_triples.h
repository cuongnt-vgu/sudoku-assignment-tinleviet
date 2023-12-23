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

bool is_in_list_naked_triples(NakedTriple *p_array, Cell *p1, Cell *p2, Cell *p3);
bool is_in_stored_candidates(int *p_stored_candidates, int candidate);
void find_naked_triples(Cell **p_cells, int *p_counter, int *p_unset, UnsetInfo_NakedTriple *p_unset_array, NakedTriple *p_naked_triples);
int naked_triples(SudokuBoard *p_board);
int naked_triples(SudokuBoard *p_board);