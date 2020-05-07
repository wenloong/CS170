#ifndef OPERATOR_H
#define OPERATOR_H

#include "puzzle.h"

using namespace std;

class Operator {
   public:
      Operator(Puzzle puzzle) {
         this->puzzle.setTL(puzzle.getTL());
         this->puzzle.setTM(puzzle.getTM());
         this->puzzle.setTR(puzzle.getTR());
         this->puzzle.setML(puzzle.getML());
         this->puzzle.setMM(puzzle.getMM());
         this->puzzle.setMR(puzzle.getMR());
         this->puzzle.setBL(puzzle.getBL());
         this->puzzle.setBM(puzzle.getBM());
         this->puzzle.setBR(puzzle.getBR());
      }

      bool move_up() {
         if (puzzle.getTL() == 'b' || puzzle.getTM() == 'b' || puzzle.getTR() == 'b') {
            return false;
         } else {
            if (puzzle.getML() == 'b') {
               char temp = puzzle.getTL();
               puzzle.setTL('b');
               puzzle.setML(temp);
            } else if (puzzle.getMM() == 'b') {
               char temp = puzzle.getTM();
               puzzle.setTM('b');
               puzzle.setMM(temp);
            } else if (puzzle.getMR() == 'b') {
               char temp = puzzle.getTR();
               puzzle.setTR('b');
               puzzle.setMR(temp);
            } else if (puzzle.getBL() == 'b') {
               char temp = puzzle.getML();
               puzzle.setML('b');
               puzzle.setBL(temp);
            } else if (puzzle.getML() == 'b') {
               char temp = puzzle.getMM();
               puzzle.setMM('b');
               puzzle.setBM(temp);
            } else if (puzzle.getMR() == 'b') {
               char temp = puzzle.getMR();
               puzzle.setMR('b');
               puzzle.setBR(temp);
            }
         }
         return true;
      }

      bool move_down() {
         if (puzzle.getBL() == 'b' || puzzle.getBM() == 'b' || puzzle.getMR() == 'b') {
            return false;
         } else {
            if (puzzle.getTL() == 'b') {
               char temp = puzzle.getML();
               puzzle.setML('b');
               puzzle.setTL(temp);
            } else if (puzzle.getTM() == 'b') {
               char temp = puzzle.getMM();
               puzzle.setMM('b');
               puzzle.setTM(temp);
            } else if (puzzle.getTR() == 'b') {
               char temp = puzzle.getMR();
               puzzle.setMR('b');
               puzzle.setTR(temp);
            } else if (puzzle.getML() == 'b') {
               char temp = puzzle.getBL();
               puzzle.setBL('b');
               puzzle.setML(temp);
            } else if (puzzle.getMM() == 'b') {
               char temp = puzzle.getBM();
               puzzle.setBM('b');
               puzzle.setMM(temp);
            } else if (puzzle.getMR() == 'b') {
               char temp = puzzle.getBR();
               puzzle.setBR('b');
               puzzle.setMR(temp);
            } 
         }
         return true;
      }

      bool move_left() {
         if (puzzle.getTL() == 'b' || puzzle.getML() == 'b' || puzzle.getBL() == 'b') {
            return false;
         } else {
            if (puzzle.getTM() == 'b') {
               char temp = puzzle.getTL();
               puzzle.setTL('b');
               puzzle.setTM(temp);
            } else if (puzzle.getMM() == 'b') {
               char temp = puzzle.getML();
               puzzle.setML('b');
               puzzle.setMM(temp);
            } else if (puzzle.getBM() == 'b') {
               char temp = puzzle.getBL();
               puzzle.setBL('b');
               puzzle.setBM(temp);
            } else if (puzzle.getTR() == 'b') {
               char temp = puzzle.getTM();
               puzzle.setTM('b');
               puzzle.setTR(temp);
            } else if (puzzle.getMR() == 'b') {
               char temp = puzzle.getMM();
               puzzle.setMM('b');
               puzzle.setMR(temp);
            } else if (puzzle.getBR() == 'b') {
               char temp = puzzle.getBM();
               puzzle.setBM('b');
               puzzle.setBR(temp);
            } 
         }
         return true;
      }

      bool move_right() {
         if (puzzle.getTR() == 'b' || puzzle.getMR() == 'b' || puzzle.getBR() == 'b') {
            return false;
         } else {
            if (puzzle.getTM() == 'b') {
               char temp = puzzle.getTR();
               puzzle.setTR('b');
               puzzle.setTM(temp);
            } else if (puzzle.getMM() == 'b') {
               char temp = puzzle.getMR();
               puzzle.setMR('b');
               puzzle.setMM(temp);
            } else if (puzzle.getMR() == 'b') {
               char temp = puzzle.getBR();
               puzzle.setBR('b');
               puzzle.setMR(temp);
            } else if (puzzle.getTL() == 'b') {
               char temp = puzzle.getTM();
               puzzle.setTM('b');
               puzzle.setTL(temp);
            } else if (puzzle.getML() == 'b') {
               char temp = puzzle.getMM();
               puzzle.setMM('b');
               puzzle.setML(temp);
            } else if (puzzle.getBL() == 'b') {
               char temp = puzzle.getBM();
               puzzle.setBM('b');
               puzzle.setBL(temp);
            } 
         }
         return true;
      }

      void display() {
         return this->puzzle.display();
      }

   private:
      Puzzle puzzle;
      
};

#endif

