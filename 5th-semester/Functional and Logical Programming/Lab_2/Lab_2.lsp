; ���������� ������� trace ��� ����������� ������� UFunc
(trace UFunc)

; �������������� �������, ����������� ����������� ������� � ������������ � ��������� �������
(defun UFunc (n)
    (cond ((< n 0) (format T "�������� n ������ ���� >= 0. ������� ������ NIL.~%~%"))
          ((= n 0) 0)
          ((= n 1) 1)
          ((> n 1) (+ (Ufunc (1- n)) (UFunc (- n 2))))))

; ��������������� ������� ��� main
(defun submain ()
    ; ����������� ��� ����� ��������� ��� ����������� ������� UFunc
    (format T "������� ����� ����� ���� ��������� n (������� c n = 0): ")
    ; ������ � ������ n ��������� ������
    (setq n (read))
    (format T "~%~%")
    ; ����� �������������� ������� � ������� ����������� � ������ result
    (setq result (UFunc n))
    (format T "~%~%")
    ; ���������� ����������� ���������� � ����
    (setq our-output-stream (open "out_data_file.txt" :direction :output))
    (print n our-output-stream)
    (print result our-output-stream)
    (close our-output-stream)
    ; ����������� �������� submain � �������� ������ ���������� ��������� ������ ����������,
    ;� ����� ����� ������������ ���������.
    (format T "~A-�� ���� ���� ���������: ~A~%" n result)
    (format T "��������� ���������� ����������� ������� UFunc ������� � ���� output_data_file.txt~%"))

; ������� ������� ��������� - ����� �����
(defun main ()
    ; ����������� ����������� ������� ��� ������������� ������ �� ��������� ������ XLisp
    (loop
        (format T "������� ����� 0 ��� 1 (0 - TERMINATE, 1 - EXECUTE): ")
        (let ((choice (read)))
        (cond ((= choice 1) (submain))
              ((= choice 0) (RETURN))))))

; ����� ������� ������� ���������
(main)
