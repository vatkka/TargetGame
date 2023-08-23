#include <iostream>
#include<stack>
#include <cstdlib>
#include<ctime>

/*Class*/
class Move {
public:
	int row;
	int	col;
	Move(int, int);
};

using namespace std;
/*Const*/
const int MAX_SIZE = 3;

/*prototype function*/
int setDifficulty();
void gridInitialize();
void gridDisplay();
bool gridWin();
void gridReady(int);
void gridUndo(int, int);
void gridRedo(int, int);
void mainMenu(stack<Move>&, stack<Move>&, int&, int);
void mainMenuTxt(stack<Move>&, stack<Move>&);
int mainMenuChoice();
void mainMenuAct(stack<Move>&, stack<Move>&, int&, int);
void mainMemuMoveBar(int, int);
bool playAgain();

/*Global variables*/
int grid[MAX_SIZE][MAX_SIZE];

int main() {
	stack<Move> undoStack;					
	stack<Move> redoStack;
	do {
		system("cls");
		gridInitialize();
		int difficulty = setDifficulty();
		gridReady(difficulty);
		int count = 0;
		do {
			mainMenu(undoStack, redoStack, count, difficulty);
		} while (!gridWin() && count != difficulty);
		if (gridWin()) {
			system("cls");
			gridDisplay();
			cout << "\nCongrat you won!!!\n";
			system("pause");
		}
		else {
			system("cls");
			gridDisplay();
			cout << "Your moves are over, you've lost((\n";
			system("pause");
		}
		system("cls");
	} while (playAgain());


}

Move::Move(int r, int c) {  //constructor of  the class
	row = r;
	col = c;
}

void gridInitialize() {    // function to set all numbers in the grid to 9
	for (int i = 0; i <= MAX_SIZE-1; i++) {
		for (int j = 0; j <= MAX_SIZE-1; j++) {
			grid[i][j] = 9;
		}
	}

}

void gridDisplay() {   //function to show grid
	cout << "=============\n";
	for (int i = 0; i <= MAX_SIZE-1; i++) {
		for (int j = 0; j <= MAX_SIZE-1; j++) {
			cout <<"| " << grid[i][j] << " ";
		}
		cout << "|\n";
		cout << "=============\n";
	}
}

bool gridWin() {   //check if all numbers in the grid == 9
	int count = 0;
	for (int i = 0; i <= MAX_SIZE - 1; i++) {
		for (int j = 0; j <= MAX_SIZE - 1; j++) {
			if (grid[i][j] != 9) {
				count++;
			}
		}
	}
	if (count == 0) {
		return true;
	}
	return false;
}

void gridReady(int difficulty){  //prepering grid before game using difficulty level
	srand(time(0));
	int row;
	int col;
	for (int i = 0; i < difficulty; i++) {
		row = rand() % 3;
		col = rand() % 3;
		gridUndo(row, col);
	}
}

int setDifficulty() {  // asks user what difficulty he wants
	int x;
	cout << "\nChoose difficulty 1-9: ";
	do {
		cin >> x;
		if (x < 1 || x > 9) {
			cout << "\nIncorrect input, try again";
		}
	} while (x < 1 || x > 9);
	return x;
}

void mainMenu(stack<Move>& undoStack, stack<Move>& redoStack, int& count, int difficulty) { // using all menu functions in correct order
	system("cls");
	mainMemuMoveBar(count, difficulty);
	gridDisplay();
	mainMenuTxt(undoStack, redoStack);
	mainMenuAct(undoStack, redoStack, count, mainMenuChoice());
}

void mainMenuTxt(stack<Move>& undoStack, stack<Move>& redoStack) {  //displays what options user have
	cout << "\n1. Play";
	cout << "\n2. Undo choice";
	if (undoStack.empty()) {		
		cout << " (Not available)";
	}
	else {
		cout << " [" << undoStack.top().row << "][" << undoStack.top().col << "]";
	}
	cout << "\n3. Redo choice";
	if (redoStack.empty()) {
		cout << " (Not available)" << endl;
	}
	else {
		cout << " [" << redoStack.top().row << "][" << redoStack.top().col << "]" << endl;
	}
}

int mainMenuChoice() { //asks user what he want to do
	int choice;
	do {
		cout << "Enter your choice 1-3: ";
		cin >> choice;
		if (choice != 1 && choice != 2 && choice != 3) {
			cout << "\nIncorrect input, try again";
		}
	} while (choice != 1 && choice != 2 && choice != 3);

	return choice;
}

void mainMenuAct(stack<Move>& undoStack, stack<Move>& redoStack, int& count, int choice) { //function to use undo and redo in correct way
	int row;
	int col;
	switch (choice) {
	case 1: 
		cout << "\nEnter your move[Row][Column]: ";
		cin >> row >> col;
		gridRedo(row, col);
		undoStack.push(Move(row, col));
		while (!redoStack.empty()) {
			redoStack.pop();
		}
		count++;
		break;
	case 2: 
		if (undoStack.empty()) {
			cout << "You dont have move to undo\n";
			system("pause");
			break;
		}
		gridUndo(undoStack.top().row, undoStack.top().col);
		redoStack.push(undoStack.top());
		undoStack.pop();
		count--;
		break;
	case 3:
		if (redoStack.empty()) {
			cout << "You dont have move to redo\n";
			system("pause");
			break;
		}
		gridRedo(redoStack.top().row, redoStack.top().col);
		undoStack.push(redoStack.top());
		redoStack.pop();
		count++;
		break;
	default:
		break;
	}
}

void mainMemuMoveBar(int count, int difficulty) { //just text (in separete function because I deside to make it later and didn't want to touch other functions)
	cout << "\n Max moves: " << difficulty << " Number of moves: " << count<<"\n";
}

bool playAgain(){ //to ask restart game or not
	cout << "\nDo you want to play again? (Y/N): ";
	char ch;
	do {
		cin >> ch;
		if (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N') {
			cout << "\nIncorrect input, try again: ";;
		}
	} while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');
	if (ch != 'y' || ch != 'Y') {
		return true;
	}
	return false;
}

void gridUndo(int row, int col) {
	grid[row][col] = (grid[row][col] + 1) % 10;

	for (int i = 0; i < MAX_SIZE; i++) {
		grid[row][i] = (grid[row][i] + 9) % 10;
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		grid[i][col] = (grid[i][col] + 9) % 10;
	}
}

void gridRedo(int row,  int col) {
	grid[row][col] = (grid[row][col] + 9) % 10;

	for (int i = 0; i < MAX_SIZE; i++) {
		grid[row][i] = (grid[row][i] + 1) % 10;
	}
	for (int i = 0; i < MAX_SIZE; i++) {
			grid[i][col] = (grid[i][col] + 1) % 10;
	}
}