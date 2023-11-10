#include "8q.h"

int main(int argc, char* argv[])
{
	test();
	int length;
	bool print = false;

	if (strcmp(argv[1], "-verbose") == 0) {
		length = argv[2][0] + char2num;
		print = true;
	}
	else {
		length = argv[1][0] + char2num;
	}
	if (length < 0 || length>10) {
		fprintf(stderr, "Invalid board size\n");
		exit(EXIT_FAILURE);
	}

	boardData boardList[ARRAY_SIZE];
	int boardCount = 1;
	boardList[0]=new_boardData(length);
	
	solve(length, boardList, boardCount);
	summary(length, true, boardList);
	return EXIT_SUCCESS;
}

void test()
{
	boardData boardList[3];
	int boardCount = 1;
	int length = 4;
	boardData testBoard = new_boardData(length);
	assert(testBoard.board[0][1] == 0);
	assert(testBoard.board[1][1] == 0);
	assert(testBoard.queen_number==0);
	assert(strcmp(testBoard.state,"0000")==0);

	testBoard = change_check(length, testBoard, 0, 0);
	assert(testBoard.board[0][1]==1);
	assert(testBoard.board[1][0]==1);
	assert(testBoard.board[1][1]==1);
	assert(testBoard.board[1][2]==0);

	boardList[1] = testBoard;

	boardData testBoard2 = same_board(length, testBoard);
	assert(testBoard2.board[0][1] == 1);
	assert(testBoard2.board[1][0] == 1);
	assert(testBoard2.board[1][1] == 1);
	assert(testBoard2.board[1][2] == 0);

	assert(!duplicate(length, 2, boardList, "1000"));
}

void summary(int length, bool print, boardData* boardList)
{
	int solution = 0;
	int f = 0;
	while (!END_LIST(f, length)) {
		if (boardList[f].queen_number == length) {
			if (print) {
				printf("%s\n", boardList[f].state);
			}
			solution++;
		}
		f++;
	}
	printf("%i solutions\n", solution);
}

boardData new_boardData(int length)
{
	boardData new_boardData;
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			new_boardData.board[y][x] = 0;
		}
	}
	new_boardData.queen_number = 0;
	for (int i = 0; i < length; i++) {
		new_boardData.state[i] = '0';
	}
	new_boardData.state[length] = '\0';
	return new_boardData;
}

void solve(int length, boardData* boardList,int boardCount)
{
	int f = 0;
	while (!END_LIST(f, length)) {
		boardCount=find_children(length,f,boardList,boardCount);
		f++;
	}
}

int find_children(int length, int f, boardData* boardList, int boardCount)
{
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			if (!boardList[f].board[y][x]) {
				boardData newBoard = same_board(length,boardList[f]);
				newBoard.board[y][x] = QUEEN;
				newBoard.queen_number += 1;
				newBoard.state[x] = y + 1 + num2char;
				newBoard = change_check(length, newBoard, y, x);
				if (!duplicate(length, boardCount, boardList, newBoard.state)) {
					boardList[boardCount++]=newBoard;
				}
			}
		}
	}
	return boardCount;
}

boardData same_board(int length,boardData oldBoard) 
{
	boardData new_boardData;
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			new_boardData.board[y][x] = oldBoard.board[y][x];
		}
	}
	new_boardData.queen_number = oldBoard.queen_number;
	for (int i = 0; i < length; i++) {
		new_boardData.state[i] = oldBoard.state[i];
	}
	new_boardData.state[length] = '\0';
	return new_boardData;
}

bool duplicate(int length, int boardCount,boardData* boardList,char* state)
{
	for (int i = 0; i < boardCount;i++) {
		if (strcmp(boardList[i].state, state) == 0) {
			return true;
		}
	}
	return false;
}

boardData change_check(int length, boardData oldBoard,int y,int x)
{
	// column check
	for (int j = 0; j < length; j++) {
		if (j == y) {
			j++;
		}
		oldBoard.board[j][x] = CHECK;
	}

	// row check
	for (int i = 0; i < length; i++) {
		if (i == x) {
			i++;
		}
		oldBoard.board[y][i] = CHECK;
	}

	// left diagonal
	int n = y + 1;
	int m = x + 1;
	while (n < length && m < length) {
		oldBoard.board[n][m] = CHECK;
		n++;
		m++;
	}
	n = y - 1;
	m = x - 1;
	while (n >= 0 && m >= 0) {
		oldBoard.board[n][m] = CHECK;
		n--;
		m--;
	}

	// right diagonal
	n = y - 1;
	m = x + 1;
	while (n >= 0 && m < length) {
		oldBoard.board[n][m] = CHECK;
		n--;
		m++;
	}
	n = y + 1;
	m = x - 1;
	while (n < length && m >= 0) {
		oldBoard.board[n][m] = CHECK;
		n++;
		m--;
	}
	return oldBoard;
}


