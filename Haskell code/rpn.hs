{-
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
 *									   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 -}

-- New algorithm for parsing simple arythmetic expressions.

-- rpn - it is the crucial function

import Data.Char
import Data.List 

type Triplet = (String, Char, String)

--------------------------------------------------
-- Groups of possible operators.
-- The reversed precedence order (from lowest to highest precedence)
-- Second parameter is associativity ( True = left2right; False = right2left)
operators = [
            (['>', '<', '='], False),  
            (['+', '-'], True),  
            (['*', '/', '%'], True),
            (['^'], False)
            ]

--------------------------------------------------
first :: Triplet -> String
first (a,_,_) = a

second :: Triplet -> Char
second (_,a,_) = a

third :: Triplet -> String
third (_,_,a) = a

--------------------------------------------------
from_just :: Maybe a -> a
from_just Nothing = error "Maybe.from_just: Nothing"
from_just (Just x) = x

--------------------------------------------------
-- Number of left parenthises in string (counting from left to right)
-- (Number of right parentheses must not be greater in any moment - otherwise -1 returns)
left_prt_number :: String -> Int 
left_prt_number "" = 0
left_prt_number (x:[])
   | x == '('  =  1 
   | x == ')'  = -1
   | otherwise =  0
left_prt_number xs = foldl (\acc x -> if acc == -1 then -1 else acc + (left_prt_number $ x:[])) 0 xs

--------------------------------------------------
-- Breaks expression into the form [prefixString, char, suffixString] for the every character
-- e.g. "abcde" -> [("", a, "bcde"),  ("a", b, "cde"),  ("ab", c, "de"),  ("abc", d, "e"),  ("abcd", e, "")]
ledger :: String -> [Triplet]
ledger "" = []
ledger (x:[]) = ("", x, "") : []
ledger (x:xs) = ("", x, xs) : (trans $ ledger xs)
   where trans = map (\(a, b, c) -> (x:a, b, c))
   
--------------------------------------------------
-- The most important and the essential function.
-- find_node ops - curried function which takes a precedence-group of operators (together with association) and finds node in a ledger-string
-- found_ops - suitable precedence-group of operators (together with association) which has a node in a ledger-string
-- found_node - found suitable node in a ledger string
rpn :: String -> String
rpn "" = ""
rpn (x:[]) = x:[]
rpn xs 
   | found_ops /= Nothing = (rpn left) ++ (rpn right) ++ [op] -- The essence of this algorithm. The essential idea.
   | otherwise = rpn . init $ tail xs
   where rpnlist = ledger xs
         find_node ops = find (\x -> second x `elem` (fst ops) && left_prt_number (third x) == 0) (if snd ops then reverse rpnlist else rpnlist)
         found_ops = find (\ops -> find_node ops /= Nothing) operators
         found_node = from_just . find_node $ from_just found_ops
         left = first found_node 
         op = second found_node
         right = third found_node


-- usage: 
-- rpn "8*(1*(2+3*(4-5)+6)-7)+5"   ( = "812345-*+6+*7-*5+" )
-- rpn "(((1*(2+3-4*5))))+(6-7*8)"   ( = "0123+45*-*-678*-+" )
-- rpn "(1+2)/((3-4-5))*(6-7*8/3+0)"    ( = "12+34-5-/678*3/-0+*" )
-- rpn "(4+5*(7-3))-2"  ( = "4573-*+2-")
