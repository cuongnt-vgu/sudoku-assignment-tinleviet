#include "naked_pairs.h"
#include <stdlib.h>


void find_naked_pairs(Cell **p_cells, int *p_counter)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates == 2)
        {
            for (int j = i + 1; j < BOARD_SIZE; j++)
            {
                if (p_cells[j]->num_candidates == 2)
                {
                    int *candidates_1 = get_candidates(p_cells[i]);
                    int *candidates_2 = get_candidates(p_cells[j]);
                    if ((candidates_1[0] == candidates_2[0]) && (candidates_1[1] == candidates_2[1]))
                    {
                        for (int k = 0; k < BOARD_SIZE; k++)
                        {
                            if ((k != i) && (k != j))
                            {
                                unset_candidate(p_cells[k], candidates_1[0]);
                                unset_candidate(p_cells[k], candidates_1[1]);
                            }
                        }
                        (*p_counter)++;
                    }
                    free(candidates_1);
                    free(candidates_2);
                
                }
            }
        }
    }
}

int naked_pairs(SudokuBoard *p_board)
{
    int naked_counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs(p_board->p_rows[i], &naked_counter);
        find_naked_pairs(p_board->p_cols[i], &naked_counter);
        find_naked_pairs(p_board->p_boxes[i], &naked_counter);
    }

    return naked_counter;
}