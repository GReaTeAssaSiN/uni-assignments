(trace PrintTree)

; Определение рекурсивной пользовательской функции PrintTree для вывода и обработки упорядоченного бинарного дерева
(defun PrintTree (UTree)
    ; Если "голова" рассматриваемого упорядоченного бинарного дерева (списка), не являющегося пустым/атомом, не является списком, то вып-ся проверка на соответствие заданному элем-ту.
    (if (not (eq UTree NIL))
        (if (not (atom UTree))
            (if (not (listp (car UTree)))
                (progn (if (eq (car UTree) elem)
                    (setq count (1+ count)))
                (print UTree output-stream))
            )
        )
    )

    ; Рекурсивное выполнение пользовательской функции PrintTree для "головы хвоста" упорядоченного бинарного дерева
    (if (not (atom UTree))
        (PrintTree (cadr UTree)))
    ; Рекурсивное выполнение пользовательской функции PrintTree для "хвоста" упорядоченного бинарного дерева
    (if (not (atom UTree))
        (PrintTree (cdr UTree)))
)

; Определение пользовательской функции UFunc, реализующей функцию в соответствии с заданием
(defun UFunc ()
    ; Символ для учета вхождения заданного элемента в упорядоченное бинарное дерево
    (setq count 0)
    ; Ввод данных из файла input_data.txt
    (setq input-stream (open "input_data.txt" :direction :input))
    ; Вывод данных в файл output_data.txt
    (setq output-stream (open "output_data.txt" :direction :output))
    ; Чтение из файла input_data.txt упорядоченного бинарного дерева и искомого элемента
    (setq UTree (read input-stream))
    (setq elem (read input-stream))

    (PrintTree UTree)
    (if (> count 0)
        (print 'YES output-stream)
        (print 'NO output-stream)
    )

    (close input-stream)
    (close output-stream)
    (format T "Результат вывода упорядоченного бинарного дерева записан в output_data.txt~%")
)

; Главная функция программы - точка входа
(defun main ()
    ; Организация пригодности функции для многократного вызова из командной строки XLisp
    (loop
        (format T "Введите число 0 или 1 (0 - TERMINATE, 1 - EXECUTE): ")
        (let ((choice (read)))
            (cond ((= choice 1) (UFunc))
                  ((= choice 0) (RETURN))))))

; Вызов главной функции программы
(main)

