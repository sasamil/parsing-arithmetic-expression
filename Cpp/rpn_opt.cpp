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
#include <stack>
#include <cstring>

#include <ctime>

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
                                       make_pair(precedence_0_operators, false)
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
const char* findLRBOperatorIn(const Operators& ops, const char* start, const char* _end)
{
   int iRParentheses = 0; // Number of encountered right parentheses.
   while (start < _end--) {
      const char ch = *_end;
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

   return 0; // No operator has been found.
}

//--------------------------------------------------------------
// Find a free right2left operator belonging to given operators-array.
// (for a RLB operators, it is the most left one, not embraced with parentheses)
const char* findRLBOperatorIn(const Operators& ops, const char* start, const char* _end)
{
   int iLParentheses = 0; // Number of encountered left parentheses.
   while (start < _end) {
      const char ch = *start;
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

   return 0; // No operator has been found.
}

//--------------------------------------------------------------
// A bit optimized version - prevents searching for the same operator twice (or more)
// (indexops - index of precedence level the search begins with)
void rpn(const char* str, const char* _end, int indexops, char* result, int* resultit)
{
   if (str + 1 == _end) { // if one-token expression only...
      result[(*resultit)++]=*str; // ...place it into the resulting string
      return;
   }

   auto fnp = [](bool b){return b ? findLRBOperatorIn : findRLBOperatorIn;}; // lambda to choose the right function

   // Traverse the arrays of operators (with different precedence) and do reordering for the matching one
   for (int jj = indexops; jj < NUM_PRECEDENCES; jj++) {
      auto const& ops = operators_arrays[jj];
      const char* position = fnp(ops.second)(ops.first, str, _end);
      if (position != 0) {
         rpn(str, position, ops.second ? jj : jj+1, result, resultit);
         rpn(position + 1, _end, ops.second ? jj+1 : jj, result, resultit);
         result[(*resultit)++]=*position;
         return;
      }
   }

   rpn(str+1, _end-1, 0, result, resultit); // ignore the enclosing parentheses
}

//--------------------------------------------------------------
// External, introducing function
void rpn_make(const char* str, char* result)
{
   int resultit = 0;

   // Parsing and reordering the expression:
   rpn(str, str + strlen(str), 0, result, &resultit); // optimized version

   result[resultit]=0;
}


//==============================================================
int main(/*int argc, char* argv[]*/)
{
   // few examples
   const char* input_expression1 = "1*(2+3-4*5)+(6-7*8)";
   const char* input_expression2 = "8*(1*(2+3*(4-5)+6)-7)+5";
   const char* input_expression3 = "(1+2*8-3)^(3-4-5)*(6-7*8/3+0)";
   const char* input_expression4 = "1+2*3=4*6^5+7*8/9>0";

   char postfix[LSTR];

   rpn_make(input_expression1, postfix);
   cout << input_expression1 << endl << postfix << endl << endl;

   rpn_make(input_expression2, postfix);
   cout << input_expression2 << endl << postfix << endl << endl;

   rpn_make(input_expression3, postfix);
   cout << input_expression3 << endl << postfix << endl << endl;

   rpn_make(input_expression4, postfix);
   cout << input_expression4 << endl << postfix << endl << endl;

   return 0;
}

