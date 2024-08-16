; Отладочная функция trace для рекурсивной функции UFunc
(trace UFunc)

; Вычислительная функция, реализующая рекурсивную функцию в соответствии с вариантом задания
(defun UFunc (n)
    (cond ((< n 0) (format T "Значение n должно быть >= 0. Функция вернет NIL.~%~%"))
          ((= n 0) 0)
          ((= n 1) 1)
          ((> n 1) (+ (Ufunc (1- n)) (UFunc (- n 2))))))

; Вспомогательная функция для main
(defun submain ()
    ; Приглашение для ввода параметра для рекурсивной функции UFunc
    (format T "Введите номер члена ряда Фибоначчи n (начиная c n = 0): ")
    ; Запись в символ n введенных данных
    (setq n (read))
    (format T "~%~%")
    ; Вызов вычислительной функции с записью результатов в символ result
    (setq result (UFunc n))
    (format T "~%~%")
    ; Сохранение полученного результата в файл
    (setq our-output-stream (open "out_data_file.txt" :direction :output))
    (print n our-output-stream)
    (print result our-output-stream)
    (close our-output-stream)
    ; Возвращение функцией submain в качестве своего результата результат вызова вычисления,
    ;а также вывод информирущих сообщений.
    (format T "~A-ый член ряда Фибоначчи: ~A~%" n result)
    (format T "Результат выполнения рекурсивной функции UFunc записан в файл output_data_file.txt~%"))

; Главная функция программы - точка входа
(defun main ()
    ; Организация пригодности функции для многократного вызова из командной строки XLisp
    (loop
        (format T "Введите число 0 или 1 (0 - TERMINATE, 1 - EXECUTE): ")
        (let ((choice (read)))
        (cond ((= choice 1) (submain))
              ((= choice 0) (RETURN))))))

; Вызов главной функции программы
(main)
