<%@page contentType="text/html" pageEncoding="UTF-8"%>
<jsp:useBean id="bean" scope="session" class="lab1Bean.lab1Bean"/>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Финишная страница</title>
        <style>
            .error-message {
                color: red;
            }
        </style>
    </head>
    <body>
        <%
            String numbers = bean.getNumbers();
            String errorMessage = bean.getErrorMessage();
            String[] numbersArray = null;
            if (numbers != null && !numbers.isEmpty()) {
                numbersArray = numbers.split("\\s+");
            }
        %>
        <table>
            <% 
                if (errorMessage != null && !errorMessage.isEmpty()) { %>
                    <tr>
                        <td class="error-message"><%= errorMessage %></td>
                    </tr>
            <%  } else if (numbersArray != null) { %>
                    <tr>
                        <td>Ввели:</td>
                    </tr>
            <%      for (String num : numbersArray) { %>
                        <tr>
                            <td><%= num %></td>
                        </tr>
            <%      
                    }
            %>
                    <tr>
                        <td>Сумма отрицательных четных чисел:</td>
                        <td><%= bean.getEvenNegativeSum() %></td>
                    </tr>
                    <tr>
                        <td>Сумма отрицательных нечетных чисел:</td>
                        <td><%= bean.getOddNegativeSum() %></td>
                    </tr>
            <%      
                }
            %>
        </table>
        <a href="main.jsp">Возврат</a>
    </body>
</html>
