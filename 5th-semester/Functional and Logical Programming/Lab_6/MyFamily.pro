/*****************************************************************************

		Copyright (c) My Company

 Project:  MYFAMILY
 FileName: MYFAMILY.PRO
 Purpose: No description
 Written by: Visual Prolog
 Comments:
******************************************************************************/

include "myfamily.inc"

%Вариант 2. A2, A12, Б8, Б18, Б25, В2 

predicates
	%Базовые отношения, задаваемые в виде фактов.
	nondeterm parent(STRING, STRING)
	nondeterm woman(STRING)
	nondeterm man(STRING)
	nondeterm married_couple(STRING, STRING)
	
	%Вспомогательные отношения для производных отношений.
	nondeterm sibling(STRING, STRING)
	nondeterm grandparent(STRING, STRING)
	nondeterm sister(STRING, STRING)
	nondeterm check_any_cousin_sister(STRING, STRING, INTEGER)

	%Производные отношения, определяемые с помощью базовых отношений.
	%A) Близкие кровные родственники.
	%2. мать (mother);
	nondeterm mother(STRING, STRING)
	%12. дядя (uncle) - родной брат родителя ребенка.
	nondeterm uncle(STRING, STRING)
	%Б) Неблизкие кровные родственники.
	%8. троюродная сестра (second_cousin_sister) - внучка брата или сестры дедушки или бабушки;
	nondeterm second_cousin_sister(STRING, STRING)
	%18. двоюродная племянница (first_cousin_niece) - дочь двоюродного брата или сестры (сын или дочь дяди или тети соответственно);
	nondeterm first_cousin_niece(STRING, STRING)
	%25. N-юродная сестра (любого уровня) (any_cousin_sister).
	nondeterm any_cousin_sister(STRING, STRING, INTEGER)
	%В) Родственники по закону.
	%2. жена (wife)
	nondeterm wife(STRING, STRING)

clauses
	%Факты.
	parent("Ульрик", "Михаэль").
	parent("Ульрик", "Марта").
	parent("Ульрик", "Магнус").
	parent("Катарина", "Михаэль").
	parent("Катарина", "Марта").
	parent("Катарина", "Магнус").
	parent("Яна", "Мадс").
	parent("Яна", "Ульрик").
	parent("Тронте", "Мадс").
	parent("Тронте", "Ульрик").
	parent("Ной", "Тронте").
	parent("Агнес", "Тронте").
	parent("Адам", "Ной").
	parent("Ева", "Ной").
	parent("Ханна", "Йонас").
	parent("Михаэль", "Йонас").
	parent("Себастьян", "Ханна").
	parent("Даниэль", "Инес").
	parent("Хелена", "Катарина").
	parent("Герман", "Катарина").
	parent("Бартош", "Агнес").
	parent("Бартош", "Ханно").
	parent("Силья", "Агнес").
	parent("Силья", "Ханно").
	parent("Шарлотта", "Элизабет").
	parent("Шарлотта", "Франциска").
	parent("Петер", "Элизабет").
	parent("Петер", "Франциска").
	parent("Хельге", "Петер").
	parent("Гретта", "Хельге").
	parent("Бернд", "Хельге").
	parent("Бернд", "Регина").
	parent("Клавдия", "Регина").
	parent("Регина", "Бартош").
	parent("Борис", "Бартош").
	parent("Эгон", "Клавдия").
	parent("Дорис", "Клавдия").
	parent("Магнус", "Жанна").
	parent("Селена", "Жанна").
	parent("Хелена", "Дмитрий").
	parent("Герман", "Дмитрий").
	parent("Дмитрий", "Венера").
	parent("Хлоя", "Венера").
	parent("Венера", "Брэнд").
	parent("Уэйн", "Брэнд").
	
	man("Ульрик").
	man("Михаэль").
	man("Магнус").
	man("Мадс").
	man("Тронте").
	man("Ной").
	man("Адам").
	man("Йонас").
	man("Себастьян").
	man("Даниэль").
	man("Герман").
	man("Бартош").
	man("Ханно").
	man("Петер").
	man("Бернд").
	man("Борис").
	man("Эгон").
	man("Дмитрий").
	man("Уэйн").
	man("Брэнд").
	
	woman("Марта").
	woman("Катарина").
	woman("Яна").
	woman("Агнес").
	woman("Ева").
	woman("Ханна").
	woman("Инес").
	woman("Хелена").
	woman("Силья").
	woman("Шарлотта").
	woman("Элизабет").
	woman("Франциска").
	woman("Хельге").
	woman("Гретта").
	woman("Клавдия").
	woman("Регина").
	woman("Дорис").
	woman("Селена").
	woman("Жанна").
	woman("Хлоя").
	woman("Венера").
	
	married_couple("Михаэль", "Ханна").
	married_couple("Ульрик", "Катарина").
	married_couple("Герман", "Хелена").
	married_couple("Тронте", "Яна").
	married_couple("Бартош", "Силья").
	married_couple("Адам", "Ева").
	married_couple("Ной", "Агнес").
	married_couple("Борис", "Регина").
	married_couple("Бернд", "Гретта").
	married_couple("Бернд", "Клавдия").
	married_couple("Эгон", "Дорис").
	married_couple("Петер", "Шарлотта").
	married_couple("Магнус", "Селена").
	married_couple("Дмитрий","Хлоя").
	married_couple("Венера", "Уэйн").
	
	%Правила (вспомогательные).
	%X брат или сестра Y.
	sibling(X,Y) :- parent(Parent, X), parent(Parent, Y), not(X=Y), !.
	%X бабушка или дедушка Y.
	grandparent(X,Y) :- parent(Parent, Y), parent(X, Parent), not(parent(X, Y)).
	%X сестра Y.
	sister(X,Y) :- parent(Parent, X), parent(Parent, Y), not(X=Y), woman(X).
	%Проверочное правило перед выполнением рекурсивного правила any_cousin_sister(...).
	check_any_cousin_sister(Sister, Child, N) :-
					woman(Sister),
					any_cousin_sister(Sister, Child, N).
	
	%Правила (по заданию).
	mother(X,Y) :- parent(X,Y), woman(X).
	uncle(X,Y) :- parent(Parent, Y), sibling(X, Parent), man(X), not(parent(X, Y)).

	second_cousin_sister(Child1, Child2) :-
				grandparent(Y1, Child1),
				grandparent(Y2, Child2),
				not(Y1=Y2),
				sibling(Y1, Y2),
				woman(Child1).

	first_cousin_niece(Niece, UncleOrAunt) :-
				grandparent(GrandParent, Niece),
				sibling(GrandParent, UncleOrAunt),
				woman(Niece).
	
	any_cousin_sister(ParentSister, ParentChild, 1) :- sibling(ParentSister, ParentChild).
	any_cousin_sister(Sister, Child, N) :-
				N > 1,
				parent(ParentSister, Sister),
				parent(ParentChild, Child),
				not(ParentSister=ParentChild),
				M = N-1,
				any_cousin_sister(ParentSister, ParentChild, M).
				
	
	wife(X,Y):-
		married_couple(X,Y),
		man(X),
		woman(Y).
				
goal
	%Перечень вопросов, касающихся родственных отношений типа "Находится ли субъект a в отношении R с субъектом b? [тип: R(a,b)]".
	%Вопрос 1.
	%write("Является ли Ева матерью Ноя?"), nl,
	%parent("Ева", "Ной"), write("Ева является матерью Ноя."), nl.
	%Вопрос 2.
	%write("Является ли Магнус дядей Йонаса?"), nl,
	%uncle("Магнус", "Йонас"), write("Магнус является дядей Йонаса"), nl.
	%Вопрос 3.
	%write ("Является ли Шарлотта троюродной сестрой Бартошу?"), nl,
	%second_cousin_sister("Шарлотта", "Бартош"), write("Шарлотта является троюродной сестрой Бартошу."), nl.
	%Вопрос 4.
	%write ("Является ли Жанна троюродной сестрой Брэнду?"), nl,
	%second_cousin_sister("Жанна", "Брэнд"), write("Жанна является троюродной сестрой Брэнду."), nl.
	%Вопрос 5.
	%write("Является ли Жанна двоюродной племянницей Дмитрия?"), nl,
	%first_cousin_niece("Жанна", "Дмитрий"), write("Жанна является двоюродной племянницей Дмитрия."), nl.
	%Вопрос 6.
	%write("Есть ли у Брэнда троюродная сестра Жанна?"), nl,
	%check_any_cousin_sister("Жанна", "Брэнд", 3).
	%Вопрос 7.
	%write("Является ли Катарина женой Ульрика?"), nl,
	%married_couple("Ульрик", "Катарина"), write("Катарина является женой Ульрика."), nl.
	
	%Перечень вопросов, касающихся родственных отношений типа "Кто находится в отношении R с субъектом a? [тип: R(a,Y), R(X,b)]".
	%Вопрос 1.
	%write("Кто является родителями Ноя?"), nl,
	%parent(Parent, "Ной").
	%Вопрос 2.
	%write("Кто является женой Германа?"), nl,
	%wife("Герман", Wife).
	
	%Перечень вопросов, касающихся родственных отношений типа "Найти все пары субъектов, находящихся в отношении R. [тип: R(X,Y)]".
	%Вопрос 1.
	%write ("Список всех двоюродных племянниц:"), nl,
	%first_cousin_niece(Niece, UncleOrAunt).
	%Вопрос 2.
	%write ("Список всех троюродных сестер:"), nl,
	%second_cousin_sister(Sister, Child).
	%Вопрос 3.
	%write("Список всех женатых пар:"), nl,
	%married_couple(Man, Woman).
	