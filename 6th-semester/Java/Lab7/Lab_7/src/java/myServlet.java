/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */

import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.util.ArrayList;

/**
 * http://localhost:8081/Lab_7/myServlet?data=-1 -2 -3 -4 -5 -6 -7 -8 -9 -10&name=Горшков Алексей Олегович&groupNumber=4312&resetTextSize=true
 * @alex
 */
@WebServlet(urlPatterns =  {"/myServlet"})
public class myServlet extends HttpServlet {
    static boolean trigger; 
    static int textSize;
    static int minTextSize;
    static int maxTextSize;
    public myServlet() {
        myServlet.trigger = true;
        myServlet.textSize = 20;
        myServlet.minTextSize = 10;
        myServlet.maxTextSize = 20;
        
    }
    
    ArrayList<Integer> lab1Result(String args) {
        //Массив с результирующими суммами.
        ArrayList<Integer> resultList = new ArrayList<>();
        //Получение данных для вычисления.
        String[] numbers = args.split(" ");
        int evenNegativeSum = 0;
        int oddNegativeSum = 0;
        for (String numStr : numbers) {
            int num = Integer.parseInt(numStr);
            if (num < 0) {
                if (num % 2 == 0) {
                    evenNegativeSum += num;
                } else {
                    oddNegativeSum += num;
                }
            }
        }
        //Добавление результрующих сумм в массив.
        resultList.add(evenNegativeSum);
        resultList.add(oddNegativeSum);
        //Возврат результата.
        return resultList;
    }
    
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        //Изменение состояния триггера на противоположное.
        myServlet.trigger = !myServlet.trigger;
        //Обработка URL-параметров.
        String resetTextSize = request.getParameter("resetTextSize");
        String name = request.getParameter("name");
        String groupNumber = request.getParameter("groupNumber");
        if ("true".equalsIgnoreCase(resetTextSize)) {
            myServlet.textSize = maxTextSize;//Если параметр-сброс активен.
        } else if (myServlet.textSize >= minTextSize) {
            myServlet.textSize--;//Иначе уменьшение размера текста в таблице (1 столбец и множество строк).
        }
        //Формирование HTML-страницы.
        try (PrintWriter out = response.getWriter()) {
            //Основные данные.
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>" + name + " | " + groupNumber +  "</title>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet myServlet at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
            //Триггер.
            out.println("<h3>trigger: " + myServlet.trigger + "</h3>");
            //Текст.
            if (myServlet.textSize < myServlet.minTextSize) {
                out.println("<h3>Дальнейшее уменьшение не возможно</h3>");
            }
       
            String data = request.getParameter("data");
            if (data != null && !data.trim().isEmpty()) {
                ArrayList<Integer> result = lab1Result(data);
                out.println("<table style='border-collapse: collapse; font-size:" + myServlet.textSize + "px; border: none;'>");

                out.println("<tr>");
                out.println("<td style='border: none;'>Ввели:</td>");
                out.println("</tr>");

                for (String input : data.split(" ")) {
                    out.println("<tr>");
                    out.println("<td style='border: none;'>" + input + "</td>");
                    out.println("</tr>");
                }

                out.println("<tr>");
                out.println("<td style='border: none;'>Сумма четных и отрицательных чисел:</td>");
                out.println("</tr>");

                out.println("<tr>");
                out.println("<td style='border: none;'>" + result.get(0) + "</td>");
                out.println("</tr>");

                out.println("<tr>");
                out.println("<td style='border: none;'>Сумма нечетных и отрицательных чисел:</td>");
                out.println("</tr>");

                out.println("<tr>");
                out.println("<td style='border: none;'>" + result.get(1) + "</td>");
                out.println("</tr>");

                out.println("</table>");
            }

            out.println("</body>");
            out.println("</html>");
        }
    }
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>
}