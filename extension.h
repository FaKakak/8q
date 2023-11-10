#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "general.h"

#define char2num (0-'0')
#define num2char ('0'-0)
#define MAX_LENGTH 10
#define QUEEN 2
#define CHECK 1

struct boardData {
	int board[MAX_LENGTH][MAX_LENGTH];
	int queen_number;
	struct boardData* next;
	char state[MAX_LENGTH + 1];
};
typedef struct boardData boardData;

boardData* new_boardData();
void solve(int length, boardData* front, boardData** endPoint);
void find_children(int length, boardData* parent, boardData** endPoint);
bool duplicate(boardData* board, boardData* start);
boardData* same_board(int length, boardData* parent);
void change_check(int length, boardData* board, int y, int x);
void summary(int length, bool print, boardData* start);
void test();
void freeList(boardData* f);
