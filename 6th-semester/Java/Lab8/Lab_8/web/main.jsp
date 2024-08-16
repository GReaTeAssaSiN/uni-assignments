<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList" %>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Главная страница</title>
    </head>
    <body>
    <%! int counter; %>
    <jsp:useBean id="bean" scope="session" class="lab1Bean.lab1Bean" />
    <form action="main.jsp" method="post">
        <label for="numbers">Введите последовательность чисел через пробел:</label><br/>
        <input type="text" name="numbers">
        <input type="submit" value="ОК">
    </form>
    <% 
        bean.setErrorMessage("");
        String numbers = request.getParameter("numbers");
        if (numbers != null && !numbers.isEmpty()) {
            bean.setNumbers(numbers);
            String[] numbersArray = numbers.split("\\s+");
            int evenNegativeSum = 0;
            int oddNegativeSum = 0;
            for (String number : numbersArray) {
                try {
                    int num = Integer.parseInt(number);
                    if (num < 0) {
                        if (num % 2 == 0) {
                            evenNegativeSum += num;
                        } else {
                            oddNegativeSum += num;
                        }
                    }
                } catch (NumberFormatException e) {
                    bean.setErrorMessage("Ошибка: " + e.getMessage());
                }
            }
            bean.setEvenNegativeSum(evenNegativeSum);
            bean.setOddNegativeSum(oddNegativeSum);
            response.sendRedirect("finish.jsp");
        }
    %>
    <h3>Счётчик <%=++counter %></h3>
    </body>
</html>
