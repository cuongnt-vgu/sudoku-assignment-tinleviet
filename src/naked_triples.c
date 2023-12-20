#include "naked_triples.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool is_in_list_naked_triples(NakedTriple *p_array, Cell *p1, Cell *p2, Cell *p3)
{
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
        if ((p_array[i].cell1 == p1) && (p_array[i].cell2 == p2) && (p_array[i].cell3 == p3)){
            return true;
        }
    }
    return false;
}

bool is_in_stored_candidates(int *p_stored_candidates, int candidate)
{
    for (int i = 0; i < 3; i++){
        if (p_stored_candidates[i] == candidate){
            return true;
        }
    }
    return false;
}

void find_naked_triples(Cell **p_cells, int *p_counter, int *p_unset, UnsetInfo_NakedTriple *p_unset_array, NakedTriple *p_naked_triples)
{
    int stored_candidates[3] = {0};
    int diff_count = 0;
    for (int i = 1; i <= BOARD_SIZE - 2; i++){
        stored_candidates[0] = i;
        for (int j = i + 1; j <= BOARD_SIZE - 1; j++){
            stored_candidates[1] = j;
            for (int k = j + 1; k <= BOARD_SIZE; k++){
                stored_candidates[2] = k;
                for (int m = 0; m < BOARD_SIZE; m++){
                    if (p_cells[m]->num_candidates > 1){
                        int *candidates_1 = get_candidates(p_cells[m]);
                        for (int n = 0; n < p_cells[m]->num_candidates; n++){
                            if (!is_in_stored_candidates(stored_candidates, candidates_1[n])){
                                diff_count++;
                            }
                        }
                        free(candidates_1);
                        if (diff_count == 0){
                            for (int n = m + 1; n < BOARD_SIZE; n++){
                                if (p_cells[n]->num_candidates > 1){
                                int *candidates_2 = get_candidates(p_cells[n]);
                                for (int o = 0; o < p_cells[n]->num_candidates; o++){
                                    if (!is_in_stored_candidates(stored_candidates, candidates_2[o])){
                                        diff_count++;
                                    }
                                }
                                free(candidates_2);
                                if (diff_count == 0){
                                    for (int p = n + 1; p < BOARD_SIZE; p++){
                                        if (p_cells[p]->num_candidates > 1){
                                        int *candidates_3 = get_candidates(p_cells[p]);
                                        for (int q = 0; q < p_cells[p]->num_candidates; q++){
                                            if (!is_in_stored_candidates(stored_candidates, candidates_3[q])){
                                                diff_count++;
                                            }
                                        }
                                        free(candidates_3);
                                        if (diff_count == 0){
                                            if (!is_in_list_naked_triples(p_naked_triples, p_cells[m], p_cells[n], p_cells[p])){
                                                p_naked_triples[*p_counter].cell1 = p_cells[m];
                                                p_naked_triples[*p_counter].cell2 = p_cells[n];
                                                p_naked_triples[*p_counter].cell3 = p_cells[p];
                                                (*p_counter)++;
                                                // printf("stored_candidates: %d %d %d\n", stored_candidates[0], stored_candidates[1], stored_candidates[2]);
                                            }
                                            for (int r = 0; r < BOARD_SIZE; r++){
                                                if ((p_cells[r] != p_cells[m]) && (p_cells[r] != p_cells[n]) && (p_cells[r] != p_cells[p])){
                                                    // int *candidates_r = get_candidates(p_cells[r]);
                                                    // for (int s = 0; s < p_cells[r]->num_candidates; s++){
                                                    //     printf("candidates_r: %d\n", candidates_r[s]);
                                                    // }
                                                    // free(candidates_r);
                                                    if (is_candidate(p_cells[r], stored_candidates[0])){
                                                        p_unset_array[*p_unset].cell = p_cells[r];
                                                        p_unset_array[*p_unset].candidate1 = stored_candidates[0];
                                                        p_unset_array[*p_unset].candidate2 = 0;
                                                        p_unset_array[*p_unset].candidate3 = 0;
                                                        (*p_unset)++;
                                                    }
                                                    if (is_candidate(p_cells[r], stored_candidates[1])){
                                                        p_unset_array[*p_unset].cell = p_cells[r];
                                                        p_unset_array[*p_unset].candidate1 = 0;
                                                        p_unset_array[*p_unset].candidate2 = stored_candidates[1];
                                                        p_unset_array[*p_unset].candidate3 = 0;
                                                        (*p_unset)++;
                                                    }
                                                    if (is_candidate(p_cells[r], stored_candidates[2])){
                                                        p_unset_array[*p_unset].cell = p_cells[r];
                                                        p_unset_array[*p_unset].candidate1 = 0;
                                                        p_unset_array[*p_unset].candidate2 = 0;
                                                        p_unset_array[*p_unset].candidate3 = stored_candidates[2];
                                                        (*p_unset)++;
                                                    }
                                                }
                                            }
                                        }
                                        else {
                                            diff_count = 0;
                                        }
                                        }
                                    }
                                }
                                else {
                                    diff_count = 0;
                                }
                                }
                            }
                        }
                        else {
                            diff_count = 0;
                        }
                    }
                }
            }
        }
    }
}

int naked_triples(SudokuBoard *p_board)
{
    UnsetInfo_NakedTriple unset_array[BOARD_SIZE*BOARD_SIZE];
    int num_unset = 0;
    NakedTriple naked_triples[BOARD_SIZE*BOARD_SIZE];
    int num_naked_triples = 0;

    for (int i = 0; i < BOARD_SIZE; i++){
        find_naked_triples(p_board->p_rows[i], &num_naked_triples, &num_unset, unset_array, naked_triples);
        find_naked_triples(p_board->p_cols[i], &num_naked_triples, &num_unset, unset_array, naked_triples); 
        find_naked_triples(p_board->p_boxes[i], &num_naked_triples, &num_unset, unset_array, naked_triples);
    }

    // for (int i = 0; i < num_naked_triples; i++){
    //     printf("Location of naked triples: (%d, %d) (%d, %d) (%d, %d)\n", naked_triples[i].cell1->row_index, naked_triples[i].cell1->col_index, naked_triples[i].cell2->row_index, naked_triples[i].cell2->col_index, naked_triples[i].cell3->row_index, naked_triples[i].cell3->col_index);
    // }
    for (int i = 0; i < num_unset; i++){

        if (is_candidate(unset_array[i].cell, unset_array[i].candidate1))
        {
            unset_candidate(unset_array[i].cell, unset_array[i].candidate1);
        }
        if (is_candidate(unset_array[i].cell, unset_array[i].candidate2))
        {
            unset_candidate(unset_array[i].cell, unset_array[i].candidate2);
        }
        if (is_candidate(unset_array[i].cell, unset_array[i].candidate3))
        {
            unset_candidate(unset_array[i].cell, unset_array[i].candidate3);
        }
    }
    return num_naked_triples;
}