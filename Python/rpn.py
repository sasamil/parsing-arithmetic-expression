#***************************************************************************
#*   Copyright (C) 2018 by Саша Миленковић                                 *
#*   sasa.milenkovic.xyz@gmail.com                                         *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU General Public License as published by  *
#*   the Free Software Foundation; either version 3 of the License, or     *
#*   (at your option) any later version.                                   *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU General Public License for more details.                          *
#*   ( http://www.gnu.org/licenses/gpl-3.0.en.html )                       *
#*   You should have received a copy of the GNU General Public License     *
#*   along with this program; if not, write to the                         *
#*   Free Software Foundation, Inc.,                                       *
#*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#***************************************************************************
 
import sys

operators = [
            (['>', '<', '='], False),  
            (['+', '-'], True),  
            (['*', '/', '%'], True),
            (['^'], False)
            ]

NUM_PRECEDENCES = len(operators)

#-------------------------------------------------------------------------------
def isOperatorFrom(ops, ch):
  for op in ops:
    if ch == op:
      return True
  
  return False

#-------------------------------------------------------------------------------
def findLRBOperatorIn(ops, expr):
   iRParentheses = 0; # Number of encountered right parentheses.
   end = len(expr)
   while (0 < end):
      end -= 1
      ch = expr[end]
      if ch == ')':
         iRParentheses += 1
      elif ch == '(':
         iRParentheses -= 1
         # if iRParentheses < 0 raise ("invalid parentheses structure")
      elif iRParentheses == 0 and isOperatorFrom(ops, ch):
         return end

   return -1 # No operator found.

#-------------------------------------------------------------------------------
def findRLBOperatorIn(ops, expr):
   iLParentheses = 0; # Number of encountered left parentheses.
   start = 0
   end = len(expr)
   while (start < end):
      ch = expr[start]
      if ch == '(':
         iLParentheses += 1
      elif ch == ')':
         iLParentheses -= 1
         # if iRParentheses < 0 raise ("invalid parentheses structure")
      elif iLParentheses == 0 and isOperatorFrom(ops, ch):
         return start;
         
      start += 1

   return -1 # No operator found.

#-------------------------------------------------------------------------------
def rpn(expr):
   length = len(expr)
   if length == 1: # one-token expression
      return expr

   # Traverse the arrays of operators (with different precedence)
   for oprtrs in operators:
      ops = oprtrs[0]
      assoc = oprtrs[1]
      pos = 0
      if assoc:
         pos = findLRBOperatorIn(ops, expr)
      else:
         pos = findRLBOperatorIn(ops, expr)
         
      if pos != -1:
         return rpn(expr[0:pos]) + rpn(expr[pos+1:length]) + expr[pos] # The essence of the reverse-recursive algorithm. The essential idea.

   return rpn(expr[start+1:end-1]) # ignore/trim the enclosing parentheses

#-------------------------------------------------------------------------------
def main():

  while (True):
     expr = raw_input()
  	
     if expr == 'q' or expr == 'Q':
        sys.exit(1)
  	  
     print rpn(expr)

# -------------------------------------------------------------------------------
if __name__ == '__main__':
  main()
  
