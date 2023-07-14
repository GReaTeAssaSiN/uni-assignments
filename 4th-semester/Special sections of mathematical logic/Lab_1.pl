%������� �������� ������������ ��������� (������) "����������"
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
%������� �������� ����������� ��������� (������) "��������"
parent("John", "Dean").%�������� ����
parent("Mary", "Dean").
parent("John", "Sam").%�������� ����
parent("Mary", "Sam").
parent("John", "Adam").%�������� �����
parent("Katie", "Adam").
parent("Henry", "John").%�������� �����
parent("Millie", "John").
parent("Samuel", "Mary").%�������� ����
parent("Deanna", "Mary").
parent("Dean", "Emma").%�������� ����
parent("Lydia", "Emma").
%������� �������� ������������ ��������� (������) "�������"
male("Dean").
male("Sam").
male("Adam").
male("John").
male("Henry").
male("Samuel").
%������� �������� ������������ ��������� (������) "�������"
female("Mary").
female("Katie").
female("Millie").
female("Deanna").
female("Emma").
female("Lydia").
%������� �������� ��������� (�������) "����"
father(X,Y) :- parent(X,Y), male(X).
%������� �������� ��������� (�������) "����"
mother(X,Y) :- parent(X,Y), female(X).
%������� �������� ��������� (�������) "�������"
grandfather(X,Y) :- parent(X,Z), parent(Z,Y), male(X).
%������� �������� ��������� (�������) "�������"
grandmother(X,Y) :- parent(X,Z), parent(Z,Y), female(X).
%������� �������� ��������� (�������) "����"
brother(X,Y) :- parent(Z,X), parent(Z,Y), male(X).
%������� ������� ��������� (�������) "����"
uncle(X,Y) :- brother(X,Z), parent(Z,Y), male(X).
%���� �1: "�������� �� Henry ��������� ����?"
goal1 :- parent("Henry", "Mary").
%���� �2: "�������� �� ���� ���������?"
goal2 :- information("John", hunter, _).
%���� �3: "��� �������� ���������?"
goal3(X) :- information(X, hunter, _).
%���� �4: "��� �� ���������� ������������� ��������?"
goal4(X) :- information(X, ordinary, _).
%���� �5: "�������� �� ��� ����� �����?"
goal5 :- parent("John", "Dean"), male("Dean").
%���� �6: "�������� �� ���� �������?"
goal6 :- parent("Mary", _), female("Mary").
%���� �7: "��� �� �������, �� �������� ����-�� �����?"
goal7(X) :- parent(X, _), male(X), not(information(X, hunter, _)).
%���� �8: "��� �������� ������/������� �������?"
goal8 :- parent("Samuel", X), parent(X, Y), writef("%t's grandchild Sumuel's.", [Y]), nl, fail.
%���� �9: "��� - ���� ��� ��� ����?"
goal9 :- parent("Mary", X), parent(X, "Sam"), writeln("Sam is Mery's grandson.");
parent("Mary", "Sam"), writeln("Sam is Mary's son.").
%���� �10: "��� �� ��������� ������� ����� 1954 ����?"
goal10 :- information(X, hunter, Y), not(Y = unknown),Y > 1954, writeln(X), fail.
