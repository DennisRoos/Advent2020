#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;
int startsize;

struct card {
	int num;
	card* next;
	card(int n) : num(n), next(NULL) {}
};

class player {
public:
	card* first;
	card* last;
	int decksize;
	void addcards(card* c1, card* c2);
	int score();
	player(int d) {
		decksize = d;
	}
};


void player::addcards(card* c1, card* c2) {
	c1->next = c2;
	c2->next = NULL;
	last->next = c1;
	last = c2;
	decksize += 2;
}

int player::score() {
	int total = 0;
	int mult = 2 * startsize;
	card* t = first;
	while (t != NULL) {
		total += mult * t->num;
		t = t->next;
		mult--;
	}
	return total;
}

struct gamestate {
	vector<int> d1;
	vector<int> d2;
	gamestate(player* p1, player* p2) {
		card* t = p1->first;
		while (t != NULL) {
			d1.push_back(t->num);
			t = t->next;
		}
		t = p2->first;
		while (t != NULL) {
			d2.push_back(t->num);
			t = t->next;
		}
	}
};


bool combat(player* p1, player* p2, int depth) {//return true if player 1 won, return false if player 2 won
	vector<gamestate> g;
	while (p1->first != NULL && p2->first != NULL) {
		bool winner;
		card* c1 = p1->first;
		card* c2 = p2->first;
		p1->decksize--;
		p2->decksize--;
		p1->first = p1->first->next;
		p2->first = p2->first->next;
		if (p1->decksize >= c1->num && p2->decksize >= c2->num) {//Recursive combat!
			player* d1 = new player(c1->num);
			player* d2 = new player(c2->num);
			card* t = p1->first;
			card* n = new card(t->num);
			int highest = t->num;
			t = t->next;
			d1->first = n;
			d1->last = n;
			for (int i = 1; i < c1->num; i++) {
				int number = t->num;
				if (number > highest) {
					highest = number;
				}
				n = new card(number);
				d1->last->next = n;
				d1->last = n;
				t = t->next;
			}
			t = p2->first;
			n = new card(t->num);
			t = t->next;
			d2->first = n;
			d2->last = n;
			bool p1HasHighest = true;
			for (int i = 1; i < c2->num; i++) {
				int number = t->num;
				if (number > highest) {
					p1HasHighest = false;
				}
				n = new card(number);
				d2->last->next = n;
				d2->last = n;
				t = t->next;
			}
			if (p1HasHighest) {//if Player 1 has the highest card of both subdecks, no need to play out the subgame, player 1 will always be the winner
				winner = true;
			}
			else {
				cout << "Recursive combat starts with decksizes " << c1->num << " and " << c2->num << endl;
				winner = combat(d1, d2, depth + 1);
				cout << "Recursive combat over, back to depth " << depth << endl;
			}
			delete d1;
			delete d2;
		}
		else {
			if (c1->num > c2->num) {//player 1 wins basic combat
				winner = true;
			}
			else {//player 2 wins
				winner = false;
			}
		}
		if (winner) {//player 1 wins the round
			//cout << "Player 1 wins the round between cards " << c1->num << " and " << c2->num << endl;
			p1->addcards(c1, c2);
		}
		else {//player 2 wins
			//cout << "Player 2 wins the round between cards " << c1->num << " and " << c2->num << endl;
			p2->addcards(c2, c1);
		}
		gamestate g2 = gamestate(p1, p2);
		for (int i = 0; i < g.size(); i++) {
			if (g[i].d1.size() == g2.d1.size() && g[i].d2.size() == g2.d2.size()) {//check all previous gamestates with same deck sizes
				bool b = true;
				for (int j = 0; j < g[i].d1.size(); j++) {
					if (g[i].d1[j] != g2.d1[j]) {
						b = false;
					}
				}
				
				for (int k = 0; k < g[i].d2.size(); k++) {
					if (g[i].d2[k] != g2.d2[k]) {
						b = false;
					}
				}
				if (b) {//we saw this gamestate before in this game

					cout << "INFINITE LOOP DETECTED!\n";
					return true;//player 1 wins to avoid infinite loop
				}
			}
		}
		g.push_back(g2);
	}
	if (p1->first == NULL) {
		return false;//player 2 won
	}
	else {
		return true;
	}
}

int main(int argc, char * argv[]) {

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		startsize = 25;//start size for one player's deck
		player* p1 = new player(startsize);
		player* p2 = new player(startsize);
		string s;
		int n;
		infile >> s;
		infile >> s;
		infile >> n;
		card* c1 = new card(n);
		p1->first = c1;
		p1->last = c1;
		for (int i = 1; i < startsize; i++) {
			infile >> n;
			card* c = new card(n);
			p1->last->next = c;
			p1->last = c;
		}
		infile >> s;
		infile >> s;
		infile >> n;
		c1 = new card(n);
		p2->first = c1;
		p2->last = c1;
		for (int i = 1; i < startsize; i++) {
			infile >> n;
			card* c = new card(n);
			p2->last->next = c;
			p2->last = c;
		}

		//part 1
		/*while (p1->first != NULL && p2->first != NULL) {
		card* c1 = p1->first;
		card* c2 = p2->first;
		p1->first = p1->first->next;
		p2->first = p2->first->next;
		if (c1->num > c2->num) {//player 1 wind the round
		p1->addcards(c1, c2);
		}
		else {//player 2 wins
		p2->addcards(c2, c1);
		}
		}*/

		/*player *t1 = new player(2);
		card* h1 = new card(43);
		card* h2 = new card(19);
		h1->next = h2;
		t1->first = h1;
		t1->last = h2;

		player *t2 = new player(3);
		card* h3 = new card(2);
		card* h4 = new card(29);
		card* h5 = new card(14);
		h3->next = h4;
		h4->next = h5;
		t2->first = h3;
		t2->last = h5;

		bool winner = combat(t1, t2);*/

		bool winner = combat(p1, p2,1);

		int score;
		if (winner) {//player 1 won
			score = p1->score();
		}
		else {
			score = p2->score();
		}
		cout << "Final score is " << score << endl;
	}
	return 0;
}