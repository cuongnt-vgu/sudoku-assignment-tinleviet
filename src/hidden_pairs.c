#include "hidden_pairs.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool is_in_list_hidden_pairs(HiddenPair *p_array, Cell *p_1, Cell *p_2, int *p_counter)
{
    for (int i = 0; i < *p_counter; i++)
    {
        if ((p_array[i].cell1 == p_1) && (p_array[i].cell2 == p_2))
        {
            return true;
        }
    }
    return false;
}

void find_hidden_pairs(Cell **cells, HiddenPair *p_hidden_pairs, int *p_counter)
{
    int candidates_count[BOARD_SIZE] = {0};
    int p_candidate[BOARD_SIZE*BOARD_SIZE] = {0};
    int set_count = 0;
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
        if (candidates_count[i] == 2)
        {
            p_candidate[set_count++] = i + 1;
        }
    }
    // for (int i = 0; i < set_count; i++)
    // {
    //     printf("%d ", p_candidate[i]);
    // }
    if (set_count < 2) return;
    for (int a = 0; a < set_count-1; a++)
    {
        for (int b = a + 1; b < set_count; b++)
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                if (cells[i]->num_candidates > 2)
                {
                    if ((is_candidate(cells[i], p_candidate[a])) && (is_candidate(cells[i], p_candidate[b])))
                    {
                        for (int j = i + 1; j < BOARD_SIZE; j++)
                        {
                            if (cells[j]->num_candidates > 2)
                            {
                                if ((is_candidate(cells[j], p_candidate[a])) && (is_candidate(cells[j], p_candidate[b])))
                                {
                                    if (!is_in_list_hidden_pairs(p_hidden_pairs, cells[i], cells[j], p_counter))
                                    {
                                        p_hidden_pairs[*p_counter].cell1 = cells[i];
                                        p_hidden_pairs[*p_counter].cell2 = cells[j];
                                        p_hidden_pairs[*p_counter].num_1 = p_candidate[a];
                                        p_hidden_pairs[*p_counter].num_2 = p_candidate[b];
                                        (*p_counter)++;
                                    }
                                }
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
        // printf("i: %d\n", i);
        // printf("row: \n");
        find_hidden_pairs(p_board->p_rows[i], hidden_pairs, &num_hidden_pairs);
        // printf("col: \n");
        find_hidden_pairs(p_board->p_cols[i], hidden_pairs, &num_hidden_pairs);
        // printf("box: \n");
        find_hidden_pairs(p_board->p_boxes[i], hidden_pairs, &num_hidden_pairs);
    }
    printf("Hidden pairs: %d\n", num_hidden_pairs);
    for (int i = 0; i < num_hidden_pairs; i++)
    {
        // printf("Hidden pairs location: (%d, %d), (%d, %d)\n", hidden_pairs[i].cell1->row_index, hidden_pairs[i].cell1->col_index, hidden_pairs[i].cell2->row_index, hidden_pairs[i].cell2->col_index);
        // printf("Hidden pairs: %d %d\n", hidden_pairs[i].num_1, hidden_pairs[i].num_2);
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