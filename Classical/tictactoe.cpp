#include <bits/stdc++.h>
using namespace std;
int pos;
map <int, int> vis;
vector <int> mainBoard;
vector< vector<int> > game[100000];
map <vector<int>, int> id;
map <vector<int>, int>:: iterator it;  
void assignBoardPosition(vector <int> v, int k) {
	if(k == 9) {
		id[v] = pos++;
		return;
	}
	v[k] = 0;
	assignBoardPosition(v, k+1);
	v[k] = 1;
	assignBoardPosition(v, k+1);
	v[k] = 2;
	assignBoardPosition(v, k+1);
} 
int checkWinner(vector <int> board) {
	if((board[0] != 0 && board[3] != 0 && board[6] != 0 && (board[0] == board[3]) && (board[3] == board[6]))) {
		return board[0];
	} 
	if(board[1] != 0 && board[4] != 0 && board[7] != 0 && (board[1] == board[4]) && (board[4] == board[7])) {
		return board[1];
	}
	if(board[2] != 0 && board[5] != 0 && board[8] != 0 && (board[2] == board[5]) && (board[5] == board[8])) {
		return board[2];
	}
	if(board[0] != 0 && board[1] != 0 && board[2] != 0 && (board[0] == board[1]) && (board[1] == board[2])) {
		return board[0];
	} 
	if(board[3] != 0 && board[4] != 0 && board[5] != 0 && (board[3] == board[4]) && (board[4] == board[5])) {
		return board[3];
	}
	if(board[6] != 0 && board[7] != 0 && board[8] != 0 && (board[6] == board[7]) && (board[7] == board[8])) {
		return board[6];
	} 
	if(board[0] != 0 && board[4] != 0 && board[8] != 0 && (board[0] == board[4]) && (board[4] == board[8])) {
		return board[0];
	}
	if(board[2] != 0 && board[4] != 0 && board[6] != 0 && (board[2] == board[4]) && (board[4] == board[6])) {
		return board[2];
	} 
	return 0; 
}
int countVal = 0;
void createGamePlay(vector <int>& board, int depth) {
	int pos = id[board];
	if(vis[pos])
		return;
	vis[pos] = 1;
	if(depth > 8 || checkWinner(board) != 0)
		return;
	if(depth%2 == 0) {
		for(int i = 0; i < board.size(); i++) {
			if(board[i] == 0) {
				board[i] = 1;
				game[pos].push_back(board);
				createGamePlay(board, depth+1);
				board[i] = 0;
			}
		}
	} else {
		for(int i = 0; i < board.size(); i++) {
			if(board[i] == 0) {
				board[i] = 2;
				game[pos].push_back(board);
				createGamePlay(board, depth+1);
				board[i] = 0;
			}
		}
	}
}
bool correctPosition(int pos) {
	if(pos < 1 || pos > 9 || mainBoard[pos-1] != 0)
		return false;
	return true;
}
bool noBlanks(vector <int> board) {
	for(int i = 0; i < board.size(); i++) {
		if(board[i] == 0)
			return false;
	}
	return true;
}
int findVal(vector <int> board, int miniMax) {
	int pos = id[board];
	if(game[pos].size() == 0) {
		if(checkWinner(board) == 1)
			return -10;
		else if(checkWinner(board) == 2)
			return 10;
		else
			return 0;
	}
	if(miniMax%2) {
		int res = INT_MAX;
		for(int i = 0; i < game[pos].size(); i++) {
			res = min(res, findVal(game[pos][i], miniMax+1));
		}
		return res;
	} else {
		int res = INT_MIN;
		for(int i = 0; i < game[pos].size(); i++) {
			res = max(res, findVal(game[pos][i], miniMax+1));
		}
		return res;
	}
}
vector <int> computeNextMove() {
	int pos = id[mainBoard];
	int finalPos = 0, res = INT_MIN;
	for(int i = 0; i < game[pos].size(); i++) {
		int newVal = findVal(game[pos][i], 1);
		if(newVal > res) {
			res = newVal;
			finalPos = i;
		} 
	}
	return game[pos][finalPos];
}
void printBoard(vector <int> board, int player) {
	if(player%2) {
		cout<<"\n\nThe computer's move is\n\n";
	} else {
		cout<<"\n\nThe board after your move is\n\n";
	}
	for(int i = 0; i < board.size(); i++) {
		if(board[i] == 1)
			cout<<"O   ";
		else if(board[i] == 2)
			cout<<"X   ";
		else
			cout<<"-   ";
		if((i+1)%3 == 0)
			cout<<endl;
	}
}
int main()
{
	vector <int> v;
	int k = 9;
	pos = 0;
	while(k--) {
		mainBoard.push_back(0);
		v.push_back(0);
	}
	assignBoardPosition(v, 0);
	createGamePlay(mainBoard, 0);
	k = 0;
	int position;
	while(1) {
		if(checkWinner(mainBoard) == 1) {
			cout<<"\n\nCONGRATULATIONS YOU WON!!!\n\n";
			break;
		} else if(checkWinner(mainBoard) == 2) {
			cout<<"\n\nSORRY YOU LOSE\n\n";
			break;
		}
		if(k == 9) {
			cout<<"\n\nIT'S A DRAW!!\n\n";
			break;
		}
		if(k%2 == 0) {
			cout<<"Enter the position of the board for your move[1-9] ";
			cin>>position;
			while(!correctPosition(position)) {
				cout<<"Thats an invalid move!!. Enter a legal position ";
				cin>>position;
			}
			mainBoard[position-1] = 1;
			printBoard(mainBoard, k);
			k++;
		} else {
			mainBoard = computeNextMove();
			printBoard(mainBoard, k);
			k++;
		}
	}
	return 0;
}