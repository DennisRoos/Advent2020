#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <map>

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
	~player() {
		card* t = first;
		card* t2;
		while (t != NULL) {
			t2 = t;
			t = t->next;
			delete t2;
		}
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
	int mult = decksize;
	card* t = first;
	while (t != NULL) {
		total += mult * t->num;
		t = t->next;
		mult--;
	}
	return total;
}

string gamestate(player* p1, player* p2) {
	string s = "";
	card* t = p1->first;
	while (t != NULL) {
		s.append(to_string(t->num));
		s.append(",");
		t = t->next;
	}
	s.append(" ");
	t = p2->first;
	while (t != NULL) {
		s.append(to_string(t->num));
		s.append(",");
		t = t->next;
	}
	return s;
}

bool combat(player* p1, player* p2) {//return true if player 1 won, return false if player 2 won
	map<string,bool> m;
	while (p1->first != NULL && p2->first != NULL) {
		bool winner;
		string g = gamestate(p1, p2);
		if (m.count(g) > 0) {//we saw this gamestate before in this game
			m.clear();
			return true;//player 1 wins to avoid infinite loop
		}
		else {
			m.insert(pair<string, bool>(g, false));//save the current gamestate in the map
		}
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
			t = t->next;
			d1->first = n;
			d1->last = n;
			for (int i = 1; i < c1->num; i++) {
				int number = t->num;
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
			for (int i = 1; i < c2->num; i++) {
				int number = t->num;
				n = new card(number);
				d2->last->next = n;
				d2->last = n;
				t = t->next;
			}
			winner = combat(d1, d2);
			delete d1;
			delete d2;
		}
		else {//basic combat
			if (c1->num > c2->num) {//player 1 wins basic combat
				winner = true;
			}
			else {//player 2 wins
				winner = false;
			}
		}
		if (winner) {//player 1 wins the round
			p1->addcards(c1, c2);
		}
		else {//player 2 wins
			p2->addcards(c2, c1);
		}
	}
	m.clear();
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

		bool winner = combat(p1, p2);
		card* t = p1->first;
		while (t != NULL) {
			cout << t->num << ",";
			t = t->next;
		}
		cout << endl;
		t = p2->first;
		while (t != NULL) {
			cout << t->num << ",";
			t = t->next;
		}
		cout << endl;
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
