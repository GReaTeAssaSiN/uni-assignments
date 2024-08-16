;����������� ���������������� ������� UF1, ����������� ������� UFunc �� ����. �/� ��� ��������
(defun UF1 (n)
  (cond ((< n 0) (format T "�������� n ������ ���� >= 0. ������� ������ NIL.~%~%"))
        ((>= n 0) (let ((n_prevprev 0) (n_prev 1) (value_n 0) (count 0))
                        (loop (cond ((= n 0)(return n_prevprev)) ((= n 1)(return n_prev)) ((= n (1+ count))(return value_n)))
                        (setq count (1+ count))
                        (setq value_n (+ n_prevprev n_prev))
                        (setq n_prevprev n_prev)
                        (setq n_prev value_n))))))

; ����������� ������ ���������������� �������, ����������� ������� � ������������ � ��������, ��� ��������
(defun UF2 (symbol n)
    (setq list (symbol-plist symbol))
    (setq len (length list))
    (do
        ((i len (1- i)))
        ((< i 0) list)
        ;(format T "i = ~A~%" i)
        ;(format T "list = ~A~%" list)
        (cond ((numberp (nth i list))
            (cond ((< n (nth i list))(remprop symbol (nth (1- i) list))))
        ))
    )
)

; ��������������� ������� ��� ������� ������� � ��� ������� �� ���������
(defun FigureProps ()
    ; ����������� ������� �������, ������������� � ������� UF2 (�� ���������)
    (setf (get 'Figure 'Perimetr) 70)
    (setf (get 'Figure 'Square) 300)
    (setf (get 'Figure 'b) 15)
    (setf (get 'Figure 'a) 20)
    (setf (get 'Figure 'name) 'rectangle)
)

; ��������������� ������� ��� main
(defun submain ()
    (format T "������� UF1.~%")
    ; ����������� ��� ����� ��������� ������� UF1
    (format T "������� ����� ����� ���� ��������� n (������� c n = 0): ")
    ; ������ � ������ n ��������� ������
    (setq n (read))
    (format T "~%")
    ; ����� ������� UF1 � ������� ����������� � ������ result
    (setq result (UF1 n))
    ; ���������� ����������� ���������� � ����
    (setq our-output-stream (open "out_data_file.txt" :direction :output))
    (print n our-output-stream)
    (print result our-output-stream)
    (close our-output-stream)
    ; ����������� �������� submain � �������� ������ ���������� ��������� ������ ����������,
    ;� ����� ����� ������������ ���������.
    (format T "~A-�� ���� ���� ���������: ~A~%" n result)
    (format T "��������� ���������� ����������� ������� UF1 ������� � ���� fibonachi_UF1.txt~%~%~%")


    (format T "������� UF2.~%")
    (FigureProps)
    ;����������� ��� ����� ���������� ������� UF2
    (format T "�������� ������ ����� ��������� ��������: ~%'Figure:~%~A~%~%" (symbol-plist 'Figure))
    (format T "������� ����� n (�������� �������� �������, �������� ������� >n, ����� �������):")
    ; ������ � ������ n ��������� ������
    (setq n (read))
    ; ����� ������� UF2
    (UF2 'Figure n)
    ; ����� ���������� �����������
    (format T "~%�������� ������� ����� ���������� ������� UF2: ~%'Figure:~%~A~%~%" (symbol-plist 'Figure))
)

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

