#include <iostream>
using namespace std;
struct move{
	int r,c,score;
};

struct TicTacToe{
	char player, computer,grid[3][3];
	TicTacToe() {
		for (int i=0; i< 3; i++){
			for (int j=0; j< 3; j++){
				grid[i][j]=' ';
			}
		}
	}

	bool win(){
		int win_states[8][3]={{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0, 4,8}, {2, 4,6}};
		for (int i=0; i<8; i++){
			bool win = true;
			int first_r=win_states[i][0]/3,first_c=win_states[i][0] % 3;
			for (int j=0; j< 3; j++){
				int r = win_states[i][j]/3, c = win_states[i][j] % 3;
				if (grid[first_r][first_c] == ' ' || grid[first_r][first_c] != grid[r][c]){
					win=false;
				}
			}
			if (win == true){
				return true;
      }
		}
		return false;
	}

	bool tie(){
		if (win() == true){
			return false;
    }
		for (int i=0; i< 3; i++){
			for (int j=0; j< 3; j++){
				if (grid[i][j] == ' '){
					return false;
				}
			}
		}
		return true;
	}

	void player_move(){
		while (true){
			cout << "Enter an empty cell (1 - 9): ";
			int cell;
			cin >> cell;
			int r = (cell -1)/3, c =(cell-1)%3;
			if (cell >= 1 && cell <=9 && grid[r][c] == ' '){
				grid[r][c]=player;
				break;
			}
		}
	}

	void computer_move(){
		move best_move=minimax();
		grid[best_move.r][best_move.c]=computer;
	}

	move minimax(bool maximizing_player=true){
		move best_move;
		if (win() == true){
			if (maximizing_player){
				best_move.score = -1;
			} else{
				best_move.score = 1;
			}
			return best_move;
		} else if (tie() == true){
			best_move.score = 0;
			return best_move;
		}
		
		best_move.score=maximizing_player ? -2 : 2;
		for (int i =0; i<3; i++){
			for (int j = 0; j < 3; j++){
				if (grid[i][j] == ' '){
					grid[i][j] = maximizing_player ? computer : player;
					move board_state = minimax(!maximizing_player);
					if (maximizing_player){
						if (board_state.score > best_move.score){
							best_move.score = board_state.score;
							best_move.r = i;
							best_move.c = j;
						}
					} else{
						if (board_state.score < best_move.score){
							best_move.score = board_state.score;
							best_move.r = i;
							best_move.c = j;
						}
					}
					grid[i][j] = ' ';
				}
			}
		}
		return best_move;
	}

	void play(){
		while (true) {
			cout << "Which symbol (X or O, X goes first)? ";
			cin >> player;
			if (player == 'X' || player == 'O'){
				break;
			}
		}
		computer = player == 'X' ? 'O' : 'X';
		if (player == 'O'){
			computer_move();
		}
		print();
		while (true) {
			player_move();
			print();
			if (win()==true){
				cout << "Player win\n";
				return;
			} else if (tie()){
				cout << "Tie\n";
				return;
			}
			cout << "Computer is making move\n";
			computer_move();
			print();
			if (win()==true){
				cout << "Computer win\n";
				return;
			} else if (tie()){
				cout << "Tie\n";
				return;
			}
		}
	}

	void print() {
		cout << '\n';
		for (int i=0; i <3; i++){
			if (i){
				cout << "-----------\n";
			}
			for (int j =0; j< 3; j++){
				if (j){
					cout << "|";
				}
				cout << ' ';
				if (grid[i][j] == ' '){
					cout << 3*i+j+1;
				} else{
					cout << grid[i][j];
				}
				cout << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
};

int main(){
	TicTacToe game;
	game.play();
}
