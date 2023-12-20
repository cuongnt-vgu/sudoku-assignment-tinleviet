#include "hidden_triples.h"
#include <stdlib.h>
#include <stdio.h>

bool is_in_list_hidden_triples(HiddenTriples *p_array, int size, Cell *p1, Cell *p2, Cell *p3)
{
    for (int i = 0; i < size; i++)
    {
        if ((p_array[i].cell1 == p1) && (p_array[i].cell2 == p2) && (p_array[i].cell3 == p3))
        {
            return true;
        }
    }
    return false;
}

int is_hidden_triples(Cell **p_cells, int triple_sets[], int *indices)
{
    int cell_counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->num_candidates == 1) continue;
        else {
            for (int j = 0; j < 3; j++)
            {   
                if (is_candidate(p_cells[i], triple_sets[j])) {
                    indices[cell_counter++] = i;
                    break;
                }
            }
        }
    }
    if (cell_counter == 3) return 1;
    return 0;
}

void find_hidden_triples(Cell **p_cells, HiddenTriples *p_hidden_triples, int *p_counter)
{
    int candidate_counter[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        candidate_counter[i] = 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int* candidates = get_candidates(p_cells[i]);
        for (int j = 0; j < p_cells[i]->num_candidates; j++)
        {
            candidate_counter[candidates[j]-1] += 1;
        }
        free(candidates);
    }

    int triple_sets[BOARD_SIZE];
    int triple_sets_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (candidate_counter[i] == 2 || candidate_counter[i] == 3)
        {
            triple_sets[triple_sets_count++] = i+1;
        }
    }

    if (triple_sets_count < 3) return;

    for (int i = 0; i < triple_sets_count - 2; i++)
    {
        for (int j = i+1; j < triple_sets_count - 1; j++)
        {
            for (int k = j+1; k < triple_sets_count; k++)
            {
                int set[3] = {triple_sets[i], triple_sets[j], triple_sets[k]};
                int indices[BOARD_SIZE];
                if (is_hidden_triples(p_cells, set, indices))
                {
                    if (p_cells[indices[0]]->num_candidates <=3 && p_cells[indices[1]]->num_candidates <=3 && p_cells[indices[2]]->num_candidates <=3) continue;
                    if(!is_in_list_hidden_triples(p_hidden_triples, *p_counter, p_cells[indices[0]], p_cells[indices[1]], p_cells[indices[2]]))
                    {
                        p_hidden_triples[*p_counter].cell1 = p_cells[indices[0]];
                        p_hidden_triples[*p_counter].cell2 = p_cells[indices[1]];
                        p_hidden_triples[*p_counter].cell3 = p_cells[indices[2]];
                        p_hidden_triples[*p_counter].num_1 = set[0];
                        p_hidden_triples[*p_counter].num_2 = set[1];
                        p_hidden_triples[*p_counter].num_3 = set[2];
                        (*p_counter)++;
                    }
                }
            }
        }
    }
}

int hidden_triples(SudokuBoard *p_board)
{
    int counter = 0;

    HiddenTriples p_hidden_triples[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_triples(p_board->p_rows[i], p_hidden_triples, &counter);
        find_hidden_triples(p_board->p_cols[i], p_hidden_triples, &counter);
        find_hidden_triples(p_board->p_boxes[i], p_hidden_triples, &counter);
    }
    
    for (int i = 0; i < counter; i++)
    {
        int num_1 = p_hidden_triples[i].num_1;
        int num_2 = p_hidden_triples[i].num_2;
        int num_3 = p_hidden_triples[i].num_3;
        printf("Location of hidden triples: (%d, %d), (%d, %d), (%d, %d)\n", p_hidden_triples[i].cell1->row_index, p_hidden_triples[i].cell1->col_index, p_hidden_triples[i].cell2->row_index, p_hidden_triples[i].cell2->col_index, p_hidden_triples[i].cell3->row_index, p_hidden_triples[i].cell3->col_index);
        printf("Hidden Triple: %d %d %d\n", num_1, num_2, num_3);
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (j != num_1-1 && j != num_2-1 && j != num_3-1)
            {
                if (is_candidate(p_hidden_triples[i].cell1, j+1)){
                    unset_candidate(p_hidden_triples[i].cell1, j+1);
                }
            }     
            if (j != num_1-1 && j != num_2-1 && j != num_3-1)
            {
                if (is_candidate(p_hidden_triples[i].cell2, j+1)){
                    unset_candidate(p_hidden_triples[i].cell2, j+1);
                }
            }
            if (j != num_1-1 && j != num_2-1 && j != num_3-1)
            {
                if (is_candidate(p_hidden_triples[i].cell3, j+1)){
                    unset_candidate(p_hidden_triples[i].cell3, j+1);
                }
            }       
            
        }
    }

    return counter;
}