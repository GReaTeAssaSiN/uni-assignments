<%@page contentType="text/html" pageEncoding="UTF-8"%>
<jsp:useBean id="bean" class="lab1Bean.lab1Bean" scope="session" />
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Стартовая страница</title>
    </head>
    <body>
        <h1>Горшков Алексей Олегович</h1>
        <ol>
            <li>В зависимости от варианта выполняется разработка web-приложения. Пример
приложения похожего на то, которое нужно разработать, см. выше. Показать работу
приведённого выше примера.</li>
            <li>В целом, нужно создать web-приложение в NetBeans IDE, которое должно состоять
из трёх JSP-страниц – стартовой, главной и финишной, а также при необходимости
использовать для обмена данными между страницами Bean-компоненту.</li>
            <li>На «Главной странице» инициировать вычисление функции из задания первой
лабораторной работы.</li>
            <li>Параметры необходимые для работы функции реализуемой на «Главной странице»
задавать на ней в текстовом поле, а результат её работы показывать на «Финишной
странице».</li>
            <li>Программный код вычисляемой функции разместить: 0 - на «Главной странице», 1 –
в классе Bean-компоненты.</li>
            <li>Заголовки страниц должны иметь следующий вид: 0 – «Стартовая страница»,
«Главная страница» и «Финишная страница»; 1 - «Раз», «Два» и «Три».</li>
            <li>Формат «Стартовой страницы»: 0 – содержит текст задания на лабораторную работу,
ФИО студента и ссылку для перехода на «Главную страницу», 1 – содержит текст
задания на лабораторную работу, группа студента и кнопку для перехода на
«Главную страницу».</li>
            <li>Организовать вывод результатов работы функции на «Финишной странице»: 0 -
строки следуют одна за другой сверху вниз (таблица без видимых границ, состоящая
из одного столбца и множества строк); 1 – результаты должны быть каким-то
образом размещены в видимой таблице, в таблице допускается произвольное число
столбцов и строк.</li>
            <li>При повторном переходе на «Главную страницу», например при нажатии кнопки
«Возврат» на «Финишной странице», на «Главной странице» должно отображаться: 0
– изменение триггера, размещённого на «Главной странице»; 0 – изменение триггера,
размещённого в Bean-компоненте; 1 – изменение счётчика, размещённого на
«Главной странице»; 2 – изменение счётчика, размещённого в Bean-компоненте; 3 –
общее число переходов (обновлений) страниц Web-приложения.</li>
            <li>Среди средств автоматизации разработки web-приложения можно выделить
инструмент окно «Палитра» для JSP – страниц и средства реорганизации кода для
класса bean-компоненты, см. рисунки выше.</li> 
            <li>Вариант: 2.</li>
            <li>Двоичное число: 1<sub>10</sub> = 000001<sub>2</sub></li>
        </ol>
        <a href="main.jsp">На главную</a>
    </body>
</html>
