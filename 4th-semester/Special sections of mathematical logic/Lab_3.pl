%Задание простого трехместного предиката (фактов) "информация"
information(sam, hunter, 1983).
information(sam, man_of_letters, 1983).
information(dean, hunter, 1979).
information(dean, man_of_letters, 1979).
information(dean, knight_of_hell, 1979).
information(mary, hunter, 1954).
information(john, hunter, 1954).
information(adam, ordinary, 1990).
information(katie, ordinary, unknown).
information(lydia, ordinary, unknown).
information(emma, ordinary, unknown).
information(deanna, hunter, unknown).
information(samuel, hunter, 1931).
information(henry, man_of_letters, unknown).
information(millie, unknown, unknown).
%Задание простого двуместного предиката (фактов) "родитель"
parent(john, dean).%Родители Дина
parent(mary, dean).
parent(john, sam).%Родители Сэма
parent(mary, sam).
parent(john, adama).%Родители Адама
parent(katie, adam).
parent(henry, john).%Родители Джона
parent(millie, john).
parent(samuel, mary).%Родители Мэри
parent(deanna, mary).
parent(dean, emma).%Родители Эммы
parent(lydia, emma).
%Задание простого одноместного предиката (фактов) "мужчина"
male(dean).
male(sam).
male(adam).
male(john).
male(henry).
male(samuel).
%Задание простого однометсного предиката (фактов) "женщина"
female(mary).
female(katie).
female(millie).
female(deanna).
female(emma).
female(lydia).
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
goal1 :- parent(henry,john), writeln("True.");not(parent(henry,john)), writeln("False.").
%Цель №2: "Является ли Джон охотником?"
goal2 :- information(john, hunter, _), writeln("True."); not(information(john, hunter, _)), writeln("False.").
%Цель №3: "Кто является охотником?"
goal3 :- information(X, hunter, _), writeln(X).
%Цель №4: "Кто не занимается деятельностью охотника?"
goal4 :- information(X, ordinary, _), writeln(X).
%Цель №5: "Является ли Дин сыном Джона?"
goal5 :- parent(john, dean), male(dean), writeln("True.");
    (not(parent(john, dean));not(male(dean))),writeln("False.").
%Цель №6: "Является ли Мэри матерью?"
goal6 :- parent(mary, _), female(mary), writeln("True."),!; (not(parent(mary, _));not(female(mary))), writeln("False.").
%Цель №7: "Кто не охотник, но является чьим-то отцом?"
goal7 :- parent(X, _), male(X), not(information(X, hunter, _)), writeln(X).
%Цель №8: "Кто является внуком/внучкой Сэмюэля?"
goal8 :- parent(samuel, X), parent(X, Y), writef("%t's grandchild Sumuel's.", [Y]), nl, fail.
%Цель №9: "Сэм - внук или сын Мэри?"
goal9 :- parent(mary, X), parent(X, sam), writeln("Sam is Mery's grandson.");
parent(mary, sam), writeln("Sam is Mary's son.").
%Цель №10: "Кто из охотников родился после 1954 года?"
goal10 :- information(X, hunter, Y), not(Y = unknown),Y > 1954, writeln(X), fail.

%Вторая лабораторная работа.
% Выбор номера варианта.
%g = 4212, n = 2,
%v = (2(n–1)+(g(mod5))+1)(mod33),
%v = (2(2-1)+(4212(mod5))+1)(mod33),
%v = (2 + 2 + 1)(mod33),
%v = 5.

% Реализация в виде рекурсии приближенной формулы при заданном значении
%количества членов ряда N и значении переменной x.
approxCin(0, _, 1) :-!.
approxCin(1, Variable, X_M):-
    X_M is (1 + 1/4 * Variable), !.
approxCin(N, Variable, X_N):-
    N > 1,
    M_1 is N - 1,
    M_2 is N - 2,
    approxCin(M_1, Variable, X_M_1),
    approxCin(M_2, Variable, X_M_2),
    X_N is (X_M_1 + (-1) * (X_M_1 - X_M_2) * (4*M_1 - 1) / (4*N) * Variable).

% Реализация точного значения функции при заданном значении переменной
%х.
stdCin(Variable, Result):-
    Result is sqrt(sqrt(1  + Variable)).

% Реализация вычисления абсолютной погрешности точного и приближенного
%значений функции.
absError(N, Variable,  Abserr_Res):-
    approxCin(N,Variable, ApproxCin_Res),
    stdCin(Variable, StdCin_Res),
    Abserr_Res is abs(ApproxCin_Res-StdCin_Res).

% Вывод пользователю запрашиваемых данных, а также отлов некорректного
%пользовательского ввода и вывод соответствующего сообщения на экран.
%Приближенное значение функции.
printApproxCin(N, Variable, X_Print):-
    approxCin(N, Variable, X_Print),
    writef("Approximate value of the function ((1+X)^(1/4)) at x = %d with count of row member index %d is ", [Variable, N]),
    format('~6f', [X_Print]),
    nl.
%Точное значение функции.
printStdCin(Variable, Print_Result):-
    stdCin(Variable, Print_Result),
    writef("The exact value of the function (1 + %d)^(1/4) is ", [Variable]),
    format('~6f', [Print_Result]),
    nl.
%Абсолютная погрешность приближенного и точного значений.
printAbsError(N, Variable, Print_AbsError):-
    absError(N, Variable, Print_AbsError),
    writef("The absolute error between the approximate and exact values of the function (1 + %d)^(1/4) is ", [Variable, N]),
    format('~6f', [Print_AbsError]),
    nl.
%Вывод всех результатов.
printResults(N, Variable):-
    format('N = ~6f', [N]), nl,
    format('x = ~6f', [Variable]), nl,
    approxCin(N, Variable, ApproxCin_Final_Result),
    format('ApproxCin = ~6f', [ApproxCin_Final_Result]), nl,
    stdCin(Variable, StdCin_Final_Result),
    format('StdCin = ~6f', [StdCin_Final_Result]), nl,
    absError(N, Variable, AbsError_Final_Result),
    format('AbsError = ~6f', [AbsError_Final_Result]), nl.
%Третья лабораторная работа.
start:-
    repeat,
    nl,
    menu,
    readln(Ans),
    check(Ans).
menu:-
    writeln("Choose a command - enter:"),
    writeln(" goal1 - Is Genry the parent of Mary?"),
    writeln(" goal2 - Is John a hunter?"),
    writeln(" goal3 - Who is the hunter?"),
    writeln(" goal4 - Who is not engaged in the activities of the hunter?"),
    writeln(" goal5 - Is Dean John's son?"),
    writeln(" goal6 - Is Mary a mother?"),
    writeln(" goal7 - Who is not a hunter, but is someone's father?"),
    writeln(" goal8 - Who is Samuel's grandson/granddaughter?"),
    writeln(" goal9 - Is Sam the grandson or son of Mary?"),
    writeln(" goal10 - Which of the hunters was born after 1954?"),
    writeln(" printResults - get all calculates of task values (approximate and real value, their comparison)"),
    writeln("   exit - terminate the program.").
check([goal1]):-
    writeln("Is Genry the parent of Mary?"),
    goal1,
    fail.
check([goal2]):-
    writeln("Is John a hunter?"),
    goal2,
    fail.
check([goal3]):-
    writeln("Who is the hunter (dean, sam, adam, john, henry, samuel, mary, katie, millie, deanna, emma, lydia)?"),
    goal3,
    fail.
check([goal4]):-
    writeln("Who is not engaged in the activities of the hunter (dean, sam, adam, john, henry, samuel, mary, katie, millie, deanna, emma, lydia)?"),
    goal4,
    fail.
check([goal5]):-
    writeln("Is Dean John's son?"),
    goal5,
    fail.
check([goal6]):-
    writeln("Is Mary a mother?"),
    goal6,
    fail.
check([goal7]):-
    writeln("Who is not a hunter, but is someone's father?"),
    goal7,
    fail.
check([goal8]):-
    writeln("Who is Samuel's grandson/granddaughter?"),
    goal8,
    fail.
check([goal9]):-
    writeln(" Is Sam the grandson or son of Mary?"),
    goal9,
    fail.
check([goal10]):-
    writeln("Which of the hunters was born after 1954?"),
    goal10,
    fail.
check([printResults]):-
    write("Enter number for value of X and count of row member index: "),
    readln(List),
    checkListLab2(List,Value,I, Flag),
    Flag = 1,
    printResults(I,Value),
    fail.
check([exit]):-
    writeln("Program exucution terminated.").

listLength([],0):-!.
listLength([_|Tail],Length_List):-
    listLength(Tail, Length_T),
    Length_List is Length_T+1.

checkListLab2([Head|Tail],_,_, Flag):-
    listLength([Head|Tail], Length_List),
    (Length_List < 2; Length_List >3),
    writeln("Error data length. You shoud input two numeric arguments: negative or nonnegative number for X and nonnegative number for index."),
    Flag is 0, !.
checkListLab2([Head|Tail],_,_, Flag):-
    listLength([Head|Tail],Length),
    ( Length = 2, [A,B]=[Head|Tail], (not(integer(A)),not(float(A)); not(abs(A)=<1); not(integer(B));
   not(B>=0));
   Length = 3, [A,B,C]=[Head|Tail], (not(A = '-'; A = '+'); not(integer(B)), not(float(B)); not(abs(B)=<1); not(integer(C)); not(C >= 0))),
   writeln("You shoud input two numeric arguments: X should lie in the interval [-1;1] and Row member index (I) should be integer and nonnegative (I>=0) "),
   Flag is 0, !.

checkListLab2([Head|Tail], Number_1, Number_2, Flag):-
    listLength([Head|Tail], Length),
    (   Length = 2, [A, B] = [Head|Tail];
    Length = 3, [A, B, C] = [Head|Tail]),
    (   Length = 2, Number_1 is A, Number_2 is B;
    Length = 3, A = '-', Number_1 is B*(-1), Number_2 is C;
    Length = 3, A = '+', Number_1 is B, Number_2 is C), Flag is 1.
