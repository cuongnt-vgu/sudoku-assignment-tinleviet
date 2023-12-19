#include "hidden_singles.h"

#include <stdlib.h>

int find_hidden_values(Cell **p_cells, int *hidden_values)
{
    int num_hidden = 0;
    int candidate_counter[BOARD_SIZE] = {0};

    for (Cell **p_cell = p_cells; p_cell < p_cells + BOARD_SIZE; p_cell++)
    {
        if ((*p_cell)->num_candidates > 1)
        {
            int *candidates = get_candidates(*p_cell);
            for (int *p_candidate = candidates; p_candidate < candidates + (*p_cell)->num_candidates; p_candidate++)
            {
                candidate_counter[*p_candidate - 1]++;
            }
            free(candidates);
        }
    }

    for (int *p_counter = candidate_counter; p_counter < candidate_counter + BOARD_SIZE; p_counter++)
    {
        if (*p_counter == 1)
        {
            hidden_values[num_hidden++] = (p_counter - candidate_counter) + 1;
        }
    }
    return num_hidden;
}

bool is_in_list_hidden_singles(HiddenSingle *p_array, int size, Cell *p)
{
    for (int i = 0; i < size; i++)
    {
        if (p_array[i].p_cell == p)
        {
            return true;
        }
    }
    return false;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles,
                        int *p_counter)
{
    int hidden_values[BOARD_SIZE];
    int num_values = find_hidden_values(p_cells, hidden_values);

    for (int i = 0; i < num_values; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates > 1)
            {
                int *candidates = get_candidates(p_cells[j]);
                for (int k = 0; k < p_cells[j]->num_candidates; k++)
                {
                    if ((candidates[k] == hidden_values[i]) && (!is_in_list_hidden_singles(p_hidden_singles, *p_counter, p_cells[j])))
                    {
                        p_hidden_singles[*p_counter].p_cell = p_cells[j];
                        p_hidden_singles[*p_counter].value = hidden_values[i];
                        (*p_counter)++;
                    }
                }
                free(candidates);
            }
        }
    }
}

int hidden_singles(SudokuBoard *p_board)
{
    int hidden_single_counter = 0;
    HiddenSingle hidden_single_cells[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_single(p_board->p_rows[i], hidden_single_cells, &hidden_single_counter);
        find_hidden_single(p_board->p_cols[i], hidden_single_cells, &hidden_single_counter);
        find_hidden_single(p_board->p_boxes[i], hidden_single_cells, &hidden_single_counter);
    }

    for (int i = 0; i < hidden_single_counter; i++)
    {
        set_candidates(hidden_single_cells[i].p_cell, (int *)(int[]){hidden_single_cells[i].value}, 1);
    }

    return hidden_single_counter;
}
