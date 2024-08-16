/*****************************************************************************

		Copyright (c) My Company

 Project:  MYFAMILY
 FileName: MYFAMILY.PRO
 Purpose: No description
 Written by: Visual Prolog
 Comments:
******************************************************************************/

include "myfamily.inc"

%������� 2. A2, A12, �8, �18, �25, �2 

predicates
	%������� ���������, ���������� � ���� ������.
	nondeterm parent(STRING, STRING)
	nondeterm woman(STRING)
	nondeterm man(STRING)
	nondeterm married_couple(STRING, STRING)
	
	%��������������� ��������� ��� ����������� ���������.
	nondeterm sibling(STRING, STRING)
	nondeterm grandparent(STRING, STRING)
	nondeterm sister(STRING, STRING)
	nondeterm check_any_cousin_sister(STRING, STRING, INTEGER)

	%����������� ���������, ������������ � ������� ������� ���������.
	%A) ������� ������� ������������.
	%2. ���� (mother);
	nondeterm mother(STRING, STRING)
	%12. ���� (uncle) - ������ ���� �������� �������.
	nondeterm uncle(STRING, STRING)
	%�) ��������� ������� ������������.
	%8. ���������� ������ (second_cousin_sister) - ������ ����� ��� ������ ������� ��� �������;
	nondeterm second_cousin_sister(STRING, STRING)
	%18. ���������� ���������� (first_cousin_niece) - ���� ����������� ����� ��� ������ (��� ��� ���� ���� ��� ���� ��������������);
	nondeterm first_cousin_niece(STRING, STRING)
	%25. N-������� ������ (������ ������) (any_cousin_sister).
	nondeterm any_cousin_sister(STRING, STRING, INTEGER)
	%�) ������������ �� ������.
	%2. ���� (wife)
	nondeterm wife(STRING, STRING)

clauses
	%�����.
	parent("������", "�������").
	parent("������", "�����").
	parent("������", "������").
	parent("��������", "�������").
	parent("��������", "�����").
	parent("��������", "������").
	parent("���", "����").
	parent("���", "������").
	parent("������", "����").
	parent("������", "������").
	parent("���", "������").
	parent("�����", "������").
	parent("����", "���").
	parent("���", "���").
	parent("�����", "�����").
	parent("�������", "�����").
	parent("���������", "�����").
	parent("�������", "����").
	parent("������", "��������").
	parent("������", "��������").
	parent("������", "�����").
	parent("������", "�����").
	parent("�����", "�����").
	parent("�����", "�����").
	parent("��������", "��������").
	parent("��������", "���������").
	parent("�����", "��������").
	parent("�����", "���������").
	parent("������", "�����").
	parent("������", "������").
	parent("�����", "������").
	parent("�����", "������").
	parent("�������", "������").
	parent("������", "������").
	parent("�����", "������").
	parent("����", "�������").
	parent("�����", "�������").
	parent("������", "�����").
	parent("������", "�����").
	parent("������", "�������").
	parent("������", "�������").
	parent("�������", "������").
	parent("����", "������").
	parent("������", "�����").
	parent("����", "�����").
	
	man("������").
	man("�������").
	man("������").
	man("����").
	man("������").
	man("���").
	man("����").
	man("�����").
	man("���������").
	man("�������").
	man("������").
	man("������").
	man("�����").
	man("�����").
	man("�����").
	man("�����").
	man("����").
	man("�������").
	man("����").
	man("�����").
	
	woman("�����").
	woman("��������").
	woman("���").
	woman("�����").
	woman("���").
	woman("�����").
	woman("����").
	woman("������").
	woman("�����").
	woman("��������").
	woman("��������").
	woman("���������").
	woman("������").
	woman("������").
	woman("�������").
	woman("������").
	woman("�����").
	woman("������").
	woman("�����").
	woman("����").
	woman("������").
	
	married_couple("�������", "�����").
	married_couple("������", "��������").
	married_couple("������", "������").
	married_couple("������", "���").
	married_couple("������", "�����").
	married_couple("����", "���").
	married_couple("���", "�����").
	married_couple("�����", "������").
	married_couple("�����", "������").
	married_couple("�����", "�������").
	married_couple("����", "�����").
	married_couple("�����", "��������").
	married_couple("������", "������").
	married_couple("�������","����").
	married_couple("������", "����").
	
	%������� (���������������).
	%X ���� ��� ������ Y.
	sibling(X,Y) :- parent(Parent, X), parent(Parent, Y), not(X=Y), !.
	%X ������� ��� ������� Y.
	grandparent(X,Y) :- parent(Parent, Y), parent(X, Parent), not(parent(X, Y)).
	%X ������ Y.
	sister(X,Y) :- parent(Parent, X), parent(Parent, Y), not(X=Y), woman(X).
	%����������� ������� ����� ����������� ������������ ������� any_cousin_sister(...).
	check_any_cousin_sister(Sister, Child, N) :-
					woman(Sister),
					any_cousin_sister(Sister, Child, N).
	
	%������� (�� �������).
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
	%�������� ��������, ���������� ����������� ��������� ���� "��������� �� ������� a � ��������� R � ��������� b? [���: R(a,b)]".
	%������ 1.
	%write("�������� �� ��� ������� ���?"), nl,
	%parent("���", "���"), write("��� �������� ������� ���."), nl.
	%������ 2.
	%write("�������� �� ������ ����� ������?"), nl,
	%uncle("������", "�����"), write("������ �������� ����� ������"), nl.
	%������ 3.
	%write ("�������� �� �������� ���������� ������� �������?"), nl,
	%second_cousin_sister("��������", "������"), write("�������� �������� ���������� ������� �������."), nl.
	%������ 4.
	%write ("�������� �� ����� ���������� ������� ������?"), nl,
	%second_cousin_sister("�����", "�����"), write("����� �������� ���������� ������� ������."), nl.
	%������ 5.
	%write("�������� �� ����� ���������� ����������� �������?"), nl,
	%first_cousin_niece("�����", "�������"), write("����� �������� ���������� ����������� �������."), nl.
	%������ 6.
	%write("���� �� � ������ ���������� ������ �����?"), nl,
	%check_any_cousin_sister("�����", "�����", 3).
	%������ 7.
	%write("�������� �� �������� ����� �������?"), nl,
	%married_couple("������", "��������"), write("�������� �������� ����� �������."), nl.
	
	%�������� ��������, ���������� ����������� ��������� ���� "��� ��������� � ��������� R � ��������� a? [���: R(a,Y), R(X,b)]".
	%������ 1.
	%write("��� �������� ���������� ���?"), nl,
	%parent(Parent, "���").
	%������ 2.
	%write("��� �������� ����� �������?"), nl,
	%wife("������", Wife).
	
	%�������� ��������, ���������� ����������� ��������� ���� "����� ��� ���� ���������, ����������� � ��������� R. [���: R(X,Y)]".
	%������ 1.
	%write ("������ ���� ���������� ���������:"), nl,
	%first_cousin_niece(Niece, UncleOrAunt).
	%������ 2.
	%write ("������ ���� ���������� ������:"), nl,
	%second_cousin_sister(Sister, Child).
	%������ 3.
	%write("������ ���� ������� ���:"), nl,
	%married_couple(Man, Woman).
	