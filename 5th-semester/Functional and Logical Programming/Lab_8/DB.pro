/*****************************************************************************

		Copyright (c) My Company

 Project:  DB
 FileName: DB.PRO
 Purpose: No description
 Written by: Visual Prolog
 Comments:
******************************************************************************/

include "db.inc"

domains
	TCountry = STRING
	TCapital = STRING
	TOneNeighbour = STRING
	TTwoNeighbour = STRING

facts
	item(TCountry, TCapital, TOneNeighbour, TTwoNeighbour)

predicates
	nondeterm switch(INTEGER)
	nondeterm repeat
	
clauses
	repeat.
	repeat:-repeat.
	
	switch(Case) :- Case = '0', write("The program is complited. Good Bye!"), nl.
	switch(Case) :- Case = '1',
		write('\10', "-[ ADD ]-------------------"),
		write('\10', "TCountry: "), readln(TCountry),
		write('\10', "TCapital: "), readln(TCapital),
		write('\10', "TOneNeighbour: "), readln(TOneNeighbour),
		write('\10', "TTwoNeighbour: "), readln(TTwoNeighbour),
		assert(item(TCountry, TCapital, TOneNeighbour, TTwoNeighbour)), fail.
	switch(Case) :- Case = '2',
		write('\10', "-[ DELETE ]-------------------"),
		write('\10', "TCountry: "), readln(TCountry),
		write('\10', "TCapital: "), readln(TCapital),
		write('\10', "TOneNeighbour: "), readln(TOneNeighbour),
		write('\10', "TTwoNeighbour: "), readln(TTwoNeighbour),
		retract(item(TCountry, TCapital, TOneNeighbour, TTwoNeighbour)), fail.
	switch(Case) :- Case = '3',
		write('\10', "-[ EDIT ]-------------------"),
		write('\10', "REPLACE ITEM: "),
		write('\10', "TCountry: "), readln(TCountry),
		write('\10', "TCapital: "), readln(TCapital),
		write('\10', "TOneNeighbour: "), readln(TOneNeighbour),
		write('\10', "TTwoNeighbour: "), readln(TTwoNeighbour),
		retract(item(TCountry, TCapital, TOneNeighbour, TTwoNeighbour)),
		write('\10', "NEW ITEM: "),
		write('\10', "TCountry: "), readln(TCountry1),
		write('\10', "TCapital: "), readln(TCapital1),
		write('\10', "TOneNeighbour: "), readln(TOneNeighbour1),
		write('\10', "TTwoNeighbour: "), readln(TTwoNeighbour1),
		assert(item(TCountry1, TCapital1, TOneNeighbour1, TTwoNeighbour1)), fail.
	switch(Case) :- Case = '4',
		write('\10', "-[ SAVING ]-------------------"),
		save("D:\\���\\Functional_and_Logical_Programming\\Labs\\Lab_8\\db.txt"),
		write('\10', "DB saved in file db.txt "), nl, fail.
	switch(Case) :- Case = '5',
		write('\10', "-[ LOADING ]-------------------"),
		retractall(item(_,_,_,_)),
		consult("D:\\���\\Functional_and_Logical_Programming\\Labs\\Lab_8\\db.txt"),
		write('\10', "DB loaded from file db.txt "), nl, fail.
	switch(Case) :- Case = '6',
		write('\10', "-[ PRINT ]-------------------"),
		item(TCountry, TCapital, TOneNeighbour, TTwoNeighbour),
		write('\10', "TCountry: ",TCountry),
		write('\10', "TCapital: ",TCapital),
		write('\10', "TOneNeighbour: ",TOneNeighbour),
		write('\10', "TTwoNeighbour: ", TTwoNeighbour),
		write('\10', "-----------------------------"), fail.
	
goal
	repeat,
	write('\10',"-[ MENU ]------------------"),
        write('\10',"[1]  ADD"),
        write('\10',"[2]  DELETE"),
        write('\10',"[3]  EDIT"),
        write('\10',"[4]  SAVE"),
        write('\10',"[5]  LOAD"),
        write('\10',"[6]  PRINT"),
        write('\10',"[0]  EXIT"),
        readchar(Case), nl, switch(Case),!.