#include "hidden_pairs.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool is_in_list_hidden_pairs(HiddenPair *p_array, Cell *p)
{
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
    {
        if ((p_array[i].cell1 == p) || (p_array[i].cell2 == p))
        {
            return true;
        }
    }
    return false;
}

void find_hidden_pairs(Cell **cells, HiddenPair *p_hidden_pairs, int *p_counter)
{
    int candidates_count[BOARD_SIZE] = {0};
    int p_candidate[2] = {0};
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (cells[i]->num_candidates > 1)
        {
            int *candidates = get_candidates(cells[i]);
            for (int j = 0; j < cells[i]->num_candidates; j++)
            {
                candidates_count[candidates[j] - 1]++;
            }
            free(candidates);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = i + 1; j < BOARD_SIZE; j++){
            if (candidates_count[i] == 2 && candidates_count[j] == 2)
            {
                p_candidate[0] = i + 1;
                p_candidate[1] = j + 1;
                break;
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (cells[i]->num_candidates > 2)
        {
            if ((is_candidate(cells[i], p_candidate[0])) && (is_candidate(cells[i], p_candidate[1])))
            {
                for (int j = i + 1; j < BOARD_SIZE; j++)
                {
                    if (cells[j]->num_candidates > 2)
                    {
                        if ((is_candidate(cells[j], p_candidate[0])) && (is_candidate(cells[j], p_candidate[1])))
                        {
                            if (!is_in_list_hidden_pairs(p_hidden_pairs, cells[i]) && !is_in_list_hidden_pairs(p_hidden_pairs, cells[j]))
                            {
                                p_hidden_pairs[*p_counter].cell1 = cells[i];
                                p_hidden_pairs[*p_counter].cell2 = cells[j];
                                p_hidden_pairs[*p_counter].num_1 = p_candidate[0];
                                p_hidden_pairs[*p_counter].num_2 = p_candidate[1];
                                (*p_counter)++;
                            }
                        }
                    }
                }
            }
        }
    }
}

int hidden_pairs(SudokuBoard *p_board)
{
    HiddenPair hidden_pairs[BOARD_SIZE*BOARD_SIZE];
    int num_hidden_pairs = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pairs(p_board->p_rows[i], hidden_pairs, &num_hidden_pairs);
        find_hidden_pairs(p_board->p_cols[i], hidden_pairs, &num_hidden_pairs);
        find_hidden_pairs(p_board->p_boxes[i], hidden_pairs, &num_hidden_pairs);
    }

    for (int i = 0; i < num_hidden_pairs; i++)
    {
        printf("Hidden pairs location: (%d, %d), (%d, %d)\n", hidden_pairs[i].cell1->row_index, hidden_pairs[i].cell1->col_index, hidden_pairs[i].cell2->row_index, hidden_pairs[i].cell2->col_index);
        for (int j = 0; j < BOARD_SIZE; j++){
            if (is_candidate(hidden_pairs[i].cell1, j + 1) && (j != hidden_pairs[i].num_1 - 1) && (j != hidden_pairs[i].num_2 - 1))
            {
                unset_candidate(hidden_pairs[i].cell1, j + 1);
            }
            if (is_candidate(hidden_pairs[i].cell2, j + 1) && (j != hidden_pairs[i].num_1 - 1) && (j != hidden_pairs[i].num_2 - 1))
            {
                unset_candidate(hidden_pairs[i].cell2, j + 1);
            }
        }
    }


    return num_hidden_pairs;
}