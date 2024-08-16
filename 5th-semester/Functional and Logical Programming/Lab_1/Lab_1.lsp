; ����������� ��������������� ������� ctg ����� tan
(defun ctg (a)
    (/ 1.0 (tan a)))

; ����������� ���������������� ������� UF1
(defun UF1 (x)
    (+ (tan(/ x 8.0)) (ctg(/ x 8.0))))

; ����������� ���������������� ������� UF2
(defun UF2 (x)
    (expt (log (+ x 4.0)) 2.0))

(defun main ()
    ; ���� ������������� ������������ �������� ���������� ������� UF1 � UF2
    (format T "������� �������� ���������� x ��� UF1: ")
    (setq x_UF1 (read))
    (format T "������� �������� ���������� x ��� UF2: ")
    (setq x_UF2 (read))
    ; ������ ����������� ���������� ������� �������������� � result_UF1 � result_UF2
    (setq result_UF1 (UF1 x_UF1))
    (setq result_UF2 (UF2 x_UF2))
    ; ������ � ������ UFR ������ �� ���������� �����������
    (setq UFR (list result_UF1 result_UF2))
    ; ������ � ������ X1 ������, ��������� ������ UFR
    (setq X1 (reverse UFR))
    ; ������ � ������ X2 ����� ������ UFR
    (setq X2 (length UFR))
    ; ������ � ������ X3 ����� ��������� ������ UFR
    (setq X3 (apply #'+ UFR))

    ; ����� ���������� �����������
    (format T "UF1: ~a~%" result_UF1)
    (format T "UF2: ~a~%" result_UF2)
    (format T "UFR: ~a~%" UFR)
    (format T "X1: ~a~%" X1)
    (format T "X2: ~a~%" X2)
    (format T "X3: ~a~%" X3))

(main)
