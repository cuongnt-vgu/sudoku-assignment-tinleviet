#include "naked_pairs.h"

int naked_pairs(SudokuBoard *p_board)
{
    // int changes = 0;

    // for (int i = 0; i < BOARD_SIZE; i++)
    // {
    //     for (int j = 0; j < BOARD_SIZE; j++)
    //     {
    //         Cell *cell = &p_board->data[i][j];
    //         if (cell->num_candidates == 2)
    //         {
    //             for (int k = 0; k < BOARD_SIZE; k++)
    //             {
    //                 if (k != j)
    //                 {
    //                     Cell *other_cell = &p_board->data[i][k];
    //                     if (other_cell->num_candidates == 2 && 
    //                         is_candidate(cell, other_cell->candidates[0]) && 
    //                         is_candidate(cell, other_cell->candidates[1]))
    //                     {
    //                         for (int l = 0; l < BOARD_SIZE; l++)
    //                         {
    //                             if (l != j && l != k)
    //                             {
    //                                 Cell *remove_cell = &p_board->data[i][l];
    //                                 if (is_candidate(remove_cell, cell->candidates[0]))
    //                                 {
    //                                     unset_candidate(remove_cell, cell->candidates[0]);
    //                                     changes++;
    //                                 }
    //                                 if (is_candidate(remove_cell, cell->candidates[1]))
    //                                 {
    //                                     unset_candidate(remove_cell, cell->candidates[1]);
    //                                     changes++;
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // return changes;
    return 0;
}