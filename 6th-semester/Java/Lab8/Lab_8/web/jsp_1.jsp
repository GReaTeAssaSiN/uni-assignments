<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Словарь-переводчик</title>
    </head>
    <body>
        <jsp:useBean id="mybean" scope="session" class="jspappl.NameHandler" />
        <h3>Введите ваше имя</h3>
        <form name="Input form" action="jsp_2.jsp">
        <input type="text" name="name" />
        <input type="submit" value="OK" name="button1" />
        <%mybean.addCounter(1);%>
        </form>
        <a href="jsp_2.jsp?name=123">Переход</a>
    </body>
</html>