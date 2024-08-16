(trace PrintTree)

; ����������� ����������� ���������������� ������� PrintTree ��� ������ � ��������� �������������� ��������� ������
(defun PrintTree (UTree)
    ; ���� "������" ���������������� �������������� ��������� ������ (������), �� ����������� ������/������, �� �������� �������, �� ���-�� �������� �� ������������ ��������� ����-��.
    (if (not (eq UTree NIL))
        (if (not (atom UTree))
            (if (not (listp (car UTree)))
                (progn (if (eq (car UTree) elem)
                    (setq count (1+ count)))
                (print UTree output-stream))
            )
        )
    )

    ; ����������� ���������� ���������������� ������� PrintTree ��� "������ ������" �������������� ��������� ������
    (if (not (atom UTree))
        (PrintTree (cadr UTree)))
    ; ����������� ���������� ���������������� ������� PrintTree ��� "������" �������������� ��������� ������
    (if (not (atom UTree))
        (PrintTree (cdr UTree)))
)

; ����������� ���������������� ������� UFunc, ����������� ������� � ������������ � ��������
(defun UFunc ()
    ; ������ ��� ����� ��������� ��������� �������� � ������������� �������� ������
    (setq count 0)
    ; ���� ������ �� ����� input_data.txt
    (setq input-stream (open "input_data.txt" :direction :input))
    ; ����� ������ � ���� output_data.txt
    (setq output-stream (open "output_data.txt" :direction :output))
    ; ������ �� ����� input_data.txt �������������� ��������� ������ � �������� ��������
    (setq UTree (read input-stream))
    (setq elem (read input-stream))

    (PrintTree UTree)
    (if (> count 0)
        (print 'YES output-stream)
        (print 'NO output-stream)
    )

    (close input-stream)
    (close output-stream)
    (format T "��������� ������ �������������� ��������� ������ ������� � output_data.txt~%")
)

; ������� ������� ��������� - ����� �����
(defun main ()
    ; ����������� ����������� ������� ��� ������������� ������ �� ��������� ������ XLisp
    (loop
        (format T "������� ����� 0 ��� 1 (0 - TERMINATE, 1 - EXECUTE): ")
        (let ((choice (read)))
            (cond ((= choice 1) (UFunc))
                  ((= choice 0) (RETURN))))))

; ����� ������� ������� ���������
(main)

