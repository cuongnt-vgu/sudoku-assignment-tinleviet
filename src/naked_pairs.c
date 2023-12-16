#include "naked_pairs.h"
#include <stdlib.h>
#include <stdio.h>


void find_naked_pairs(Cell **p_cells, int *p_counter, int *p_unset, UnsetInfo *p_unset_array)
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
                            int action = 0;
                            if ((k != i) && (k != j) && (p_cells[k]->num_candidates > 1))
                            {
                                if (is_candidate(p_cells[k], candidates_1[0]) || is_candidate(p_cells[k], candidates_1[1]))
                                {
                                    p_unset_array[*p_unset].cell = p_cells[k];
                                    p_unset_array[*p_unset].candidate1 = candidates_1[0];
                                    p_unset_array[*p_unset].candidate2 = candidates_1[1];
                                    (*p_unset)++;
                                    action++;
                                }
                            }
                            if (action > 0){
                                (*p_counter)++;

                            }
                        }
                        
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
    UnsetInfo unset_array[BOARD_SIZE * BOARD_SIZE];
    int unset_counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs(p_board->p_rows[i], &naked_counter, &unset_counter, unset_array);
        find_naked_pairs(p_board->p_cols[i], &naked_counter, &unset_counter, unset_array);
        find_naked_pairs(p_board->p_boxes[i], &naked_counter, &unset_counter, unset_array);
    }

    for (int i = 0; i < unset_counter; i++)
{
    if (is_candidate(unset_array[i].cell, unset_array[i].candidate1))
    {
        unset_candidate(unset_array[i].cell, unset_array[i].candidate1);
    }
    if (is_candidate(unset_array[i].cell, unset_array[i].candidate2))
    {
        unset_candidate(unset_array[i].cell, unset_array[i].candidate2);
    }
}
    printf("Naked pairs: %d\n", naked_counter);
    return naked_counter;
}