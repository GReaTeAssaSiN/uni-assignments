;Определение пользовательской функции UF1, реализующей функцию UFunc из пред. л/р без рекурсии
(defun UF1 (n)
  (cond ((< n 0) (format T "Значение n должно быть >= 0. Функция вернет NIL.~%~%"))
        ((>= n 0) (let ((n_prevprev 0) (n_prev 1) (value_n 0) (count 0))
                        (loop (cond ((= n 0)(return n_prevprev)) ((= n 1)(return n_prev)) ((= n (1+ count))(return value_n)))
                        (setq count (1+ count))
                        (setq value_n (+ n_prevprev n_prev))
                        (setq n_prevprev n_prev)
                        (setq n_prev value_n))))))

; Определение второй пользовательской функции, реализующей функцию в соответствии с заданием, без рекурсии
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

; Вспомогательная функция для задания символа и его свойств из программы
(defun FigureProps ()
    ; Оперделение свойств символа, передаваемого в функцию UF2 (из программы)
    (setf (get 'Figure 'Perimetr) 70)
    (setf (get 'Figure 'Square) 300)
    (setf (get 'Figure 'b) 15)
    (setf (get 'Figure 'a) 20)
    (setf (get 'Figure 'name) 'rectangle)
)

; Вспомогательная функция для main
(defun submain ()
    (format T "Функция UF1.~%")
    ; Приглашение для ввода параметра функции UF1
    (format T "Введите номер члена ряда Фибоначчи n (начиная c n = 0): ")
    ; Запись в символ n введенных данных
    (setq n (read))
    (format T "~%")
    ; Вызов функции UF1 с записью результатов в символ result
    (setq result (UF1 n))
    ; Сохранение полученного результата в файл
    (setq our-output-stream (open "out_data_file.txt" :direction :output))
    (print n our-output-stream)
    (print result our-output-stream)
    (close our-output-stream)
    ; Возвращение функцией submain в качестве своего результата результат вызова вычисления,
    ;а также вывод информирущих сообщений.
    (format T "~A-ый член ряда Фибоначчи: ~A~%" n result)
    (format T "Результат выполнения рекурсивной функции UF1 записан в файл fibonachi_UF1.txt~%~%~%")


    (format T "Функция UF2.~%")
    (FigureProps)
    ;Пришлашение для ввода параметров функции UF2
    (format T "Исходный символ имеет следующие свойства: ~%'Figure:~%~A~%~%" (symbol-plist 'Figure))
    (format T "Введите число n (числовые свойства символа, значения которых >n, будут удалены):")
    ; Запись в символ n введенных данных
    (setq n (read))
    ; Вызов функции UF2
    (UF2 'Figure n)
    ; Вывод полученных результатов
    (format T "~%Свойства символа после выполнения функции UF2: ~%'Figure:~%~A~%~%" (symbol-plist 'Figure))
)

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

