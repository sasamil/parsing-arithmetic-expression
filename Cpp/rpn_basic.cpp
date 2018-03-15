/***************************************************************************
 *   Copyright (C) 2018 by Саша Миленковић                                 *
 *   sasa.milenkovic.xyz@gmail.com                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *   ( http://www.gnu.org/licenses/gpl-3.0.en.html )                       *
 *									                                                *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<char> Operators;
typedef vector<pair<Operators, bool>> Operators2d;

const int LSTR = 256;

// Used operators. Four levels of precedence, in this example
const Operators precedence_0_operators = { '^' };              // right-to-left
const Operators precedence_1_operators = { '*', '/', '%'};     // left-to-right
const Operators precedence_2_operators = { '+', '-'};          // left-to-right
const Operators precedence_3_operators = { '<', '>', '='};     // right-to-left

// Here, the operator-arrays are deliberately put in reverse precedence order.
// In this algorithm, lower precedence operators should be handled/searched first
// so that the higher precedence operators should be applied before them.
const Operators2d operators_arrays = { make_pair(precedence_3_operators, false),
                                       make_pair(precedence_2_operators, true),
                                       make_pair(precedence_1_operators, true),
                                       make_pair(precedence_0_operators, true)
                                     };

const int NUM_PRECEDENCES = operators_arrays.size();

//--------------------------------------------------------------
inline bool isOperatorFrom(const Operators& ops, const char ch) {
   for (auto it=ops.begin(); it!=ops.end(); it++)
      if(ch == *it) return true;

   return false;
}

//--------------------------------------------------------------
// Find a free left2right operator belonging to given operators-array.
// (for a LRB operators, it is the most right one, not embraced with parentheses)
int findLRBOperatorIn(const Operators& ops, const string& str)
{
   int iRParentheses = 0; // Number of encountered right parentheses.
   int _end = str.size();
   while (0 < _end--) {
      const char ch = str[_end];
      switch (ch) {
      case ')':
         iRParentheses++;
         break;
      case '(':
         iRParentheses--;
         //if (iRParentheses < 0) throw "invalid parentheses structure";
         break;
      default:
         if (iRParentheses == 0 && isOperatorFrom(ops, ch)) return _end;
      }
   }

   return -1; // No operator has been found.
}

//--------------------------------------------------------------
// Find a free right2left operator belonging to given operators-array.
// (for a RLB operators, it is the most left one, not embraced with parentheses)
int findRLBOperatorIn(const Operators& ops, const string& str)
{
   int iLParentheses = 0; // Number of encountered left parentheses.
   int start = 0;
   int _end = str.size();
   while (start < _end) {
      const char ch = str[start];
      switch (ch) {
      case '(':
         iLParentheses++;
         break;
      case ')':
         iLParentheses--;
         //if (iLParentheses < 0) throw "invalid parentheses structure";
         break;
      default:
         if (iLParentheses == 0 && isOperatorFrom(ops, ch)) return start;
      }
      start++;
   }

   return -1; // No operator has been found.
}

//--------------------------------------------------------------
string rpn(const string& expr)
{
   int length = expr.size();
   if (length == 1) return expr;

   auto fnp = [](bool b){return b ? findLRBOperatorIn : findRLBOperatorIn;}; // lambda to choose the right function

   // Traverse the arrays of operators (with different precedence)
   for (int jj = 0; jj < NUM_PRECEDENCES; jj++) {
      auto const& ops = operators_arrays[jj];
      auto pos = fnp(ops.second)(ops.first, expr);
      if (pos != -1) return rpn(expr.substr(0, pos)) + rpn(expr.substr(pos+1, length-pos-1)) + expr[pos]; // The essential idea!
   }

   return rpn(expr.substr(1, length-2)); // ignore the enclosing parentheses
}


//==============================================================
int main(/*int argc, char* argv[]*/)
{
   // few expression examples
   string input_expr1("1*(2+3-4*5)+(6-7*8)");
   string input_expr2("1+2*3=4*6^5+7*8/9>0");

   cout << input_expr1 << endl << rpn(input_expr1) << endl << endl;
   cout << input_expr2 << endl << rpn(input_expr2) << endl << endl;

   return 0;
}

