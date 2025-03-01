#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>

using namespace std;

class Puzzle {
   public:
      Puzzle();
      Puzzle(char t_l, char t_m, char t_r, char m_l, char m_m, char m_r, char b_l, char b_m, char b_r);
      Puzzle(vector<char> top_row, vector<char> mid_row, vector<char> bot_row);

      bool compare(Puzzle* p1);
      bool compare(Puzzle p1);
      vector<Puzzle> getChild(Puzzle puzzle);
      void display();
      int calculate_misplaced();
      int calculate_eucledian();

      void setTL(char in);
      void setTM(char in);
      void setTR(char in);
      void setML(char in);
      void setMM(char in);
      void setMR(char in);
      void setBL(char in);
      void setBM(char in);
      void setBR(char in);
      void setG(int n);

      char getTL();
      char getTM();
      char getTR();
      char getML();
      char getMM();
      char getMR();
      char getBL();
      char getBM();
      char getBR();

      int getG();
   private:
      int g;
      char top_left, top_mid, top_right;
      char mid_left, mid_mid, mid_right;
      char bot_left, bot_mid, bot_right;
};

/* Default Contructor, produces a default puzzle */
Puzzle::Puzzle() {
   this->top_left = '1';
   this->top_mid = '2';
   this->top_right = '3';
   this->mid_left = '4';
   this->mid_mid = '8';
   this->mid_right = 'b';
   this->bot_left = '7';
   this->bot_mid = '6';
   this->bot_right = '5';
}

/* Accepts literal char as arguments */
Puzzle::Puzzle(char t_l, char t_m, char t_r, char m_l, char m_m, char m_r, char b_l, char b_m, char b_r) {
   this->top_left = t_l;
   this->top_mid = t_m;
   this->top_right = t_r;
   this->mid_left = m_l;
   this->mid_mid = m_m;
   this->mid_right = m_r;
   this->bot_left = b_l;
   this->bot_mid = b_m;
   this->bot_right = b_r;
}

/* Accepts three rows in vectors and converts them into a puzzle object */
Puzzle::Puzzle(vector<char> top_row, vector<char> mid_row, vector<char> bot_row) {
   this->top_left = top_row[0];
   this->top_mid = top_row[1];
   this->top_right = top_row[2];
   this->mid_left = mid_row[0];
   this->mid_mid = mid_row[1];
   this->mid_right = mid_row[2];
   this->bot_left = bot_row[0];
   this->bot_mid = bot_row[1];
   this->bot_right = bot_row[2];
}

void Puzzle::display() {
   cout << top_left << " " << top_mid << " " << top_right << endl;
   cout << mid_left << " " << mid_mid << " " << mid_right << endl;
   cout << bot_left << " " << bot_mid << " " << bot_right << endl;
}

bool Puzzle::compare(Puzzle* p1) {
   if (this->getTL() == p1->getTL() &&
       this->getTM() == p1->getTM() &&
       this->getTR() == p1->getTR() &&
       this->getML() == p1->getML() &&
       this->getMM() == p1->getMM() &&
       this->getMR() == p1->getMR() &&
       this->getBL() == p1->getBL() &&
       this->getBM() == p1->getBM() &&
       this->getBR() == p1->getBR()) {
      return true;
   }
   return false;
}

bool Puzzle::compare(Puzzle p1) {
   if (this->getTL() == p1.getTL() &&
       this->getTM() == p1.getTM() &&
       this->getTR() == p1.getTR() &&
       this->getML() == p1.getML() &&
       this->getMM() == p1.getMM() &&
       this->getMR() == p1.getMR() &&
       this->getBL() == p1.getBL() &&
       this->getBM() == p1.getBM() &&
       this->getBR() == p1.getBR()) {
      return true;
   }
   return false;
}

int Puzzle::calculate_misplaced() {
   int count_misplaced;

   if (this->getTL() != '1' && this->getTL() != 'b')
      count_misplaced++;
   if (this->getTM() != '2' && this->getTM() != 'b')
      count_misplaced++;
   if (this->getTR() != '3' && this->getTR() != 'b')
      count_misplaced++;
   if (this->getML() != '4' && this->getML() != 'b')
      count_misplaced++;
   if (this->getMM() != '5' && this->getMM() != 'b')
      count_misplaced++;
   if (this->getMR() != '6' && this->getMR() != 'b')
      count_misplaced++;
   if (this->getBL() != '7' && this->getBL() != 'b')
      count_misplaced++;
   if (this->getBM() != '8' && this->getBM() != 'b')
      count_misplaced++;   
   if (this->getBR() != 'b' && this->getBR() != 'b')
      count_misplaced++;

   return count_misplaced;
}

int Puzzle::calculate_eucledian() {
   int count_eucledian;

   if (this->getTL() != '1' && this->getTL() != 'b')
      count_eucledian += abs((this->getTL() - 1) % 3 - (0 % 3)) + abs(floor((this->getTL() - 1) / 3) - floor(0/3));
   if (this->getTM() != '2' && this->getTM() != 'b')
      count_eucledian += abs((this->getTM() - 1) % 3 - (1 % 3)) + abs(floor((this->getTM() - 1) / 3) - floor(1/3)); 
   if (this->getTR() != '3' && this->getTR() != 'b')
      count_eucledian += abs((this->getTR() - 1) % 3 - (2 % 3)) + abs(floor((this->getTR() - 1) / 3) - floor(2/3)); 
   if (this->getML() != '4' && this->getML() != 'b')
      count_eucledian += abs((this->getML() - 1) % 3 - (3 % 3)) + abs(floor((this->getML() - 1) / 3) - floor(3/3)); 
   if (this->getMM() != '5' && this->getMM() != 'b')
      count_eucledian += abs((this->getMM() - 1) % 3 - (4 % 3)) + abs(floor((this->getMM() - 1) / 3) - floor(4/3)); 
   if (this->getMR() != '6' && this->getMR() != 'b')
      count_eucledian += abs((this->getMR() - 1) % 3 - (5 % 3)) + abs(floor((this->getMR() - 1) / 3) - floor(5/3)); 
   if (this->getBL() != '7' && this->getBL() != 'b')
      count_eucledian += abs((this->getBL() - 1) % 3 - (6 % 3)) + abs(floor((this->getBL() - 1) / 3) - floor(6/3)); 
   if (this->getBM() != '8' && this->getBM() != 'b')
      count_eucledian += abs((this->getBM() - 1) % 3 - (7 % 3)) + abs(floor((this->getBM() - 1) / 3) - floor(7/3));  
   if (this->getBR() != 'b' && this->getBR() != 'b')
      count_eucledian += abs((this->getBR() - 1) % 3 - (8 % 3)) + abs(floor((this->getBR() - 1) / 3) - floor(8/3)); 

   return count_eucledian;
}

char Puzzle::getTL() {
   return top_left;
}

char Puzzle::getTM() {
   return top_mid;
}

char Puzzle::getTR() {
   return top_right;
}

char Puzzle::getML() {
   return mid_left;
}

char Puzzle::getMM() {
   return mid_mid;
}

char Puzzle::getMR() {
   return mid_right;
}

char Puzzle::getBL() {
   return bot_left;
}

char Puzzle::getBM() {
   return bot_mid;
}

char Puzzle::getBR() {
   return bot_right;
}

void Puzzle::setTL(char in) {
   top_left = in;
}

void Puzzle::setTM(char in) {
   top_mid = in;
}

void Puzzle::setTR(char in) {
   top_right = in;
}

void Puzzle::setML(char in) {
   mid_left = in;
}

void Puzzle::setMM(char in) {
   mid_mid = in;
}

void Puzzle::setMR(char in) {
   mid_right = in;
}

void Puzzle::setBL(char in) {
   bot_left = in;
}

void Puzzle::setBM(char in) {
   bot_mid = in;
}

void Puzzle::setBR(char in) {
   bot_right = in;
}

void Puzzle::setG(int n) {
   g = n;
}

int Puzzle::getG() {
   return g;
}

#endif
