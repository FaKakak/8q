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
#define END_LIST(INDEX,LENGTH) (boardList[INDEX].state[LENGTH]!='\0')
#define ARRAY_SIZE 10000

struct boardData {
	int board[MAX_LENGTH][MAX_LENGTH];
	int queen_number;
	char state[MAX_LENGTH + 1];
};
typedef struct boardData boardData;

void test();
void summary(int length, bool print, boardData* boardList);
boardData new_boardData(int length);
void solve(int length, boardData* boardList, int boardCount);
int find_children(int length, int f, boardData* boardList, int boardCount);
boardData same_board(int length, boardData oldBoard);
bool duplicate(int length, int boardCount, boardData* boardList, char* state);
boardData change_check(int length, boardData oldBoard, int y, int x);