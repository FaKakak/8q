#include "extension.h";

int main(int argc, char* argv[])
{
	test();
	int length;
	bool print=false;

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

	boardData* f = new_boardData();
	boardData* end = f;

	for (int i = 0; i < length; i++) {
		f->state[i] = '0';
	}
	f->state[length] = '\0';

	solve(length, f, &end);
	summary(length, print, f);
	freeList(f);
	return EXIT_SUCCESS;
}

void freeList(boardData* f)
{
	while(f!=NULL) {
		boardData* temp = f->next;
		free(f);
		f = temp;
	}
}

void test()
{
	boardData* test1 = new_boardData();
	for (int i = 0; i < MAX_LENGTH; i++) {
		test1->state[i] = '1';
	}
	test1->state[MAX_LENGTH] = '\0';

	boardData* test2 = new_boardData();
	for (int i = 0; i < MAX_LENGTH; i++) {
		test2->state[i] = '0';
	}
	test2->state[MAX_LENGTH] = '\0';

	boardData* test3 = new_boardData();
	for (int i = 0; i < MAX_LENGTH; i++) {
		test3->state[i] = '0';
	}
	test3->state[MAX_LENGTH] = '\0';

	assert(duplicate(test1, test2) == false);
	assert(duplicate(test3, test2) == true);

	test1->next = test2;
	boardData* child_board = same_board(MAX_LENGTH, test1);
	assert(child_board->next != test2);

	change_check(MAX_LENGTH, test2, 0, 3);
	assert(test2->board[0][0] == 1);
	assert(test2->board[1][3] == 1);
	assert(test2->board[2][1] == 1);
	assert(test2->board[1][4] == 1);
}

void summary(int length,bool print, boardData* start)
{
	int solution = 0;
	for (boardData* board = start; board != NULL; board = board->next) {
		if (board->queen_number == length) {
			if (print) {
				printf("%s\n", board->state);
			}
			solution++;
		}
	}
	printf("%i solutions\n", solution);
}

boardData* new_boardData() 
{
	boardData* new_boardData = (boardData*) ncalloc(1,sizeof(boardData));
	return new_boardData;
}

void solve(int length, boardData* front,boardData** endPoint)
{
	do {
		find_children(length, front, endPoint);
		front = front->next;
	} while (front);
}

void find_children(int length, boardData* parent, boardData** endPoint)
{
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			if (!parent->board[y][x]) {
				boardData* child_board = same_board(length,parent);
				child_board->board[y][x] = QUEEN;
				child_board->queen_number +=1;
				change_check(length,child_board, y, x);
				child_board->state[x] = y+1+num2char;
				if (!duplicate(child_board, parent)) {
					(*endPoint)->next = child_board;
					*endPoint = child_board;
				}
				else {
					free(child_board);
				}
			}
		}
	}
}

bool duplicate(boardData* board, boardData* start)
{
	boardData* front;
	for (front = start; front != NULL; front = front->next) {
		if (strcmp(front->state, board->state) == 0) {
			return true;
		}
	}
	return false;
}

boardData* same_board(int length, boardData* parent)
{
	// Ó¦¸ÃdoneÁË
	boardData* board = new_boardData();
	board->queen_number = parent->queen_number;
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < length; x++) {
			board->board[y][x] = parent->board[y][x];
		}
	}
	for (int i = 0; i < length; i++) {
		board->state[i] = parent->state[i];
	}
	return board;
}

void change_check(int length,boardData* board, int y, int x)
{
	// column check
	for (int j = 0; j < length; j++) {
		if (j == y) {
			j++;
		}
		board->board[j][x] = CHECK;
	}

	// row check
	for (int i = 0; i < length; i++) {
		if (i==x) {
			i++;
		}
		board->board[y][i] = CHECK;
	}

	// left diagonal
	int n = y+1;
	int m = x+1;
	while (n < length && m < length) {
		board->board[n][m] = CHECK;
		n++;
		m++;
	}
	n = y - 1;
	m = x - 1;
	while (n >= 0 && m >= 0) {
		board->board[n][m] = CHECK;
		n--;
		m--;
	}

	// right diagonal
	n = y - 1;
	m = x + 1;
	while (n >= 0 && m < length) {
		board->board[n][m] = CHECK;
		n--;
		m++;
	}
	n = y + 1;
	m = x - 1;
	while (n < length && m >= 0) {
		board->board[n][m] = CHECK;
		n++;
		m--;
	}
}

