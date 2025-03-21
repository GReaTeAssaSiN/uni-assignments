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
    Variable >= -1, Variable =< 1,
    X_M is (1 + 1/4 * Variable), !.
approxCin(N, Variable, X_N):-
    N > 1, integer(N), Variable >= -1, Variable =< 1,
    M_1 is N - 1,
    M_2 is N - 2,
    approxCin(M_1, Variable, X_M_1),
    approxCin(M_2, Variable, X_M_2),
    X_N is (X_M_1 + (-1) * (X_M_1 - X_M_2) * (4*M_1 - 1) / (4*N) * Variable).

% Реализация точного значения функции при заданном значении переменной
%х.
stdCin(Variable, Result):-
    Variable >= -1, Variable =< 1,
    Result is sqrt(sqrt(1  + Variable)).

% Реализация вычисления абсолютной погрешности точного и приближенного
%значений функции.
absError(N, Variable,  Abserr_Res):-
    N >= 0, integer(N), Variable >= -1, Variable =< 1,
    approxCin(N,Variable, ApproxCin_Res),
    stdCin(Variable, StdCin_Res),
    abs(ApproxCin_Res, StdCin_Res, Abs_Res),
    Abserr_Res is Abs_Res.

% Вычисление модуля числа (абсолютного значения) разности точного и
%приближенного значений функции.
abs(F_Number, S_Number, Abs_Res):-
    F_Number >= S_Number, Abs_Res is (F_Number - S_Number);
    F_Number < S_Number, Abs_Res is (S_Number - F_Number).

% Вывод пользователю запрашиваемых данных, а также отлов некорректного
%пользовательского ввода и вывод соответствующего сообщения на экран.
%Приближенное значение функции.
printApproxCin(N, Variable, X_Print):-
    approxCin(N, Variable, X_Print),
    writef("Approximate value of the function ((1+X)^(1/4)) at x = %d with count of row member index %d is ", [Variable, N]),
    format('~6f', [X_Print]),
    nl.
printApproxCin(N,_,_):-
    N < 0,
    writeln("N should be non-negative number (>=0).").
printApproxCin(N,_,_):-
    not(integer(N)),
    writeln("N should be integer number.").
printApproxCin(_,Variable,_):-
    (Variable < -1; Variable > 1),
    writeln("Variable value should lie in the segment: [-1,1].").
%Точное значение функции.
printStdCin(Variable, Print_Result):-
    stdCin(Variable, Print_Result),
    writef("The exact value of the function (1 + %d)^(1/4) is ", [Variable]),
    format('~6f', [Print_Result]),
    nl.
printStdCin(Variable,_):-
    (Variable < -1; Variable > 1),
    writeln("Variable value should lie in the segment: [-1,1].").
%Абсолютная погрешность приближенного и точного значений.
printAbsError(N, Variable, Print_AbsError):-
    absError(N, Variable, Print_AbsError),
    writef("The absolute error between the approximate and exact values of the function (1 + %d)^(1/4) is ", [Variable, N]),
    format('~6f', [Print_AbsError]),
    nl.
printAbsError(N,_,_):-
    N < 0,
    writeln("N should be non-negative number (>=0).").
printAbsError(N,_,_):-
    not(integer(N)),
    writeln("N should be integer number.").
printAbsError(_,Variable,_):-
    (Variable < -1; Variable > 1),
    writeln("Variable value should lie in the segment: [-1,1].").
%Вывод всех результатов.
printResults(N, Variable):-
    N >= 0, integer(N), Variable >= -1, Variable =< 1,
    format('N = ~6f', [N]), nl,
    format('x = ~6f', [Variable]), nl,
    approxCin(N, Variable, ApproxCin_Final_Result),
    format('ApproxCin = ~6f', [ApproxCin_Final_Result]), nl,
    stdCin(Variable, StdCin_Final_Result),
    format('StdCin = ~6f', [StdCin_Final_Result]), nl,
    absError(N, Variable, AbsError_Final_Result),
    format('AbsError = ~6f', [AbsError_Final_Result]), nl.
printResults(N,_):-
    N < 0,
    writeln("N should be non-negative number (>=0).").
printResults(N,_):-
    not(integer(N)),
    writeln("N should be integer number.").
printResults(_,Variable):-
    (Variable < -1; Variable > 1),
    writeln("Variable value should lie in the segment: [-1,1].").




