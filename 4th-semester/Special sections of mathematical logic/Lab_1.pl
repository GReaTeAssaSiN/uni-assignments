%Задание простого трехместного предиката (фактов) "информация"
information("Sam", hunter, 1983).
information("Dean", hunter, 1979).
information("Mary", hunter, 1954).
information("John", hunter, 1954).
information("Adam", ordinary, 1990).
information("Katie", ordinary, unknown).
information("Lydia", ordinary, unknown).
information("Emma", ordinary, unknown).
information("Deanna", hunter, unknown).
information("Samuel", hunter, 1931).
information("Henry", man_of_letters, unknown).
information("Millie", unknown, unknown).
%Задание простого двуместного предиката (фактов) "родитель"
parent("John", "Dean").%Родители Дина
parent("Mary", "Dean").
parent("John", "Sam").%Родители Сэма
parent("Mary", "Sam").
parent("John", "Adam").%Родители Адама
parent("Katie", "Adam").
parent("Henry", "John").%Родители Джона
parent("Millie", "John").
parent("Samuel", "Mary").%Родители Мэри
parent("Deanna", "Mary").
parent("Dean", "Emma").%Родители Эммы
parent("Lydia", "Emma").
%Задание простого одноместного предиката (фактов) "мужчина"
male("Dean").
male("Sam").
male("Adam").
male("John").
male("Henry").
male("Samuel").
%Задание простого однометсного предиката (фактов) "женщина"
female("Mary").
female("Katie").
female("Millie").
female("Deanna").
female("Emma").
female("Lydia").
%Задание сложного предиката (правила) "отец"
father(X,Y) :- parent(X,Y), male(X).
%Задание сложного предиката (правила) "мать"
mother(X,Y) :- parent(X,Y), female(X).
%Задание сложного предиката (правила) "дедушка"
grandfather(X,Y) :- parent(X,Z), parent(Z,Y), male(X).
%Задание сложного предиката (правила) "бабушка"
grandmother(X,Y) :- parent(X,Z), parent(Z,Y), female(X).
%Задание сложного предиката (правила) "брат"
brother(X,Y) :- parent(Z,X), parent(Z,Y), male(X).
%Задание сожного предиката (правила) "дядя"
uncle(X,Y) :- brother(X,Z), parent(Z,Y), male(X).
%Цель №1: "Является ли Henry родителем Мэри?"
goal1 :- parent("Henry", "Mary").
%Цель №2: "Является ли Джон охотником?"
goal2 :- information("John", hunter, _).
%Цель №3: "Кто является охотником?"
goal3(X) :- information(X, hunter, _).
%Цель №4: "Кто не занимается деятельностью охотника?"
goal4(X) :- information(X, ordinary, _).
%Цель №5: "Является ли Дин сыном Джона?"
goal5 :- parent("John", "Dean"), male("Dean").
%Цель №6: "Является ли Мэри матерью?"
goal6 :- parent("Mary", _), female("Mary").
%Цель №7: "Кто не охотник, но является чьим-то отцом?"
goal7(X) :- parent(X, _), male(X), not(information(X, hunter, _)).
%Цель №8: "Кто является внуком/внучкой Сэмюэля?"
goal8 :- parent("Samuel", X), parent(X, Y), writef("%t's grandchild Sumuel's.", [Y]), nl, fail.
%Цель №9: "Сэм - внук или сын Мэри?"
goal9 :- parent("Mary", X), parent(X, "Sam"), writeln("Sam is Mery's grandson.");
parent("Mary", "Sam"), writeln("Sam is Mary's son.").
%Цель №10: "Кто из охотников родился после 1954 года?"
goal10 :- information(X, hunter, Y), not(Y = unknown),Y > 1954, writeln(X), fail.
