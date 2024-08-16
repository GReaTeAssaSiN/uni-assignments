package homelibraryconsoleapp;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.Types;
import java.util.Scanner;

//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

public class HomeLibraryConsoleApp {

    private static final String JDBC_URL = "jdbc:derby://localhost:1527/databases/HomeLibrary;user=db_user;password=db_user";
    private static final String TABLE_BOOK_LOCATION = "BookLocation";
    private static final String TABLE_BOOK_INFO = "BookInfo";

    public static void main(String[] args) {
        // Установка кодировки для вывода.
        try {
            System.setOut(new PrintStream(System.out, true, "UTF-8"));
            System.setErr(new PrintStream(System.err, true, "UTF-8"));
        } catch (UnsupportedEncodingException e) {//e.printStackTrace();}
        }
        try (Connection connection = DriverManager.getConnection(JDBC_URL)) {
            System.out.println("Подключение к базе данных прошло успешно.");

            Scanner scanner = new Scanner(System.in);

            while (true) {
                System.out.println("\nВаш выбор:");
                System.out.println("1. Вывести издания на указанном этаже в лексикографическом порядке;");
                System.out.println("2. Вывести издания, для которых год издания существенно (> 10 лет) отличается от даты написания;");
                System.out.println("3. Показать все записи;");
                System.out.println("4. Добавить новую запись;");
                System.out.println("5. Изменить запись;");
                System.out.println("6. Удалить запись;");
                System.out.println("7. Сбросить все НЕключевые поля к значениям по умолчанию;");
                System.out.println("8. Показать все полки;");
                System.out.println("9. Выйти из программы.");

                try {
                    int choice = scanner.nextInt();
                    scanner.nextLine();

                    switch (choice) {
                        case 1:
                            viewTitlesOnFloor(connection);
                            break;
                        case 2:
                            viewTitlesWithBigDiff(connection);
                            break;
                        case 3:
                            viewAllRecords(connection);
                            break;
                        case 4:
                            addNewRecord(connection);
                            break;
                        case 5:
                            updateRecord(connection);
                            break;
                        case 6:
                            deleteRecord(connection);
                            break;
                        case 7:
                            resetNonKeyFields(connection);
                            break;
                        case 8:
                            viewAllFloors(connection);
                            break;
                        case 9:
                            System.out.println("Выход из приложения...");
                            return;
                        default:
                            System.out.println("Ошибка ввода! Выберите номер действия из представленного списка.");
                    }
                } catch (java.util.InputMismatchException e) {
                    System.out.println("Ошибка: Неверный формат ввода. Пожалуйста, введите целое число от 1 до 9.");
                    scanner.next();
                }
            }
        } catch (SQLException e) {
            System.err.println("Ошибка подключения к базе данных: " + e.getMessage());
        }
    }

    //Метод для вывода изданий на выбранном этаже в лексикографическом порядке.
    private static void viewTitlesOnFloor(Connection connection) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите номер этажа: ");
        try {
            int floor = scanner.nextInt();

            String sql = "SELECT publication_title FROM " + TABLE_BOOK_INFO + " INNER JOIN " + TABLE_BOOK_LOCATION
                    + " ON " + TABLE_BOOK_INFO + ".id = " + TABLE_BOOK_LOCATION + ".id WHERE floor = ? ORDER BY publication_title";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setInt(1, floor);
                ResultSet resultSet = statement.executeQuery();
                System.out.println("\nНазвания изданий на этаже " + floor + ":");
                int count = 0;
                while (resultSet.next()) {
                    count++;
                    System.out.println(resultSet.getString("publication_title"));
                }
                if (count == 0) {
                    System.out.println("В базе данных 'HomeLibrary' отсутствуют записи, удовлетворяющие запросу.");
                }
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка: Неверный формат ввода. Пожалуйста, введите целое число.");
            scanner.next();
        }
    }

    //Метод для вывода изданий, для которых год создания существенно (>10 лет) отличается от даты написания.
    private static void viewTitlesWithBigDiff(Connection connection) throws SQLException {
        String sql = "SELECT publication_title FROM " + TABLE_BOOK_INFO + " WHERE year_of_writing IS NOT NULL AND ABS(year_of_publication - year_of_writing) > 10";
        try (Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            System.out.println("\nНазвания изданий, у которых год издания существенно (>10 лет) отличается от года написания:");
            int count = 0;
            while (resultSet.next()) {
                count++;
                System.out.println(resultSet.getString("publication_title"));
            }
            if (count == 0) {
                System.out.println("В базе данных 'HomeLibrary' отсутствуют записи, удовлетворяющие запросу.");
            }
        }
    }

    //Метод для вывода всех записей из БД.
    private static void viewAllRecords(Connection connection) throws SQLException {
        String bookInfoSql = "SELECT * FROM " + TABLE_BOOK_INFO;
        try (Statement bookInfoStatement = connection.createStatement(); ResultSet bookInfoResultSet = bookInfoStatement.executeQuery(bookInfoSql)) {
            System.out.println("\nВсе записи в БД 'HomeLibrary':");
            System.out.printf("| %-15s | %-5s | %-30s | %-20s | %-20s | %-15s | %-20s | %-15s | %-10s | %-5s | %-5s | %-5s |\n",
                    "Номер записи", "ID", "ФИО Автора", "Название издания", "Издательство", "Год издания", "Количество страниц", "Год написания", "Вес в г", "Этаж", "Шкаф", "Полка");
            System.out.println("|-----------------|-------|--------------------------------|----------------------|----------------------|-----------------|----------------------|-----------------|------------|-------|-------|-------|");
            printRecords(connection, bookInfoResultSet);
        }
    }

    //Вспомогательный метод для вывода всех записей в БД.
    private static void printRecords(Connection connection, ResultSet bookInfoResultSet) throws SQLException {
        //Текущий номер записи.
        int currentIndex = 1;
        //Пока есть, что выводить из таблицы 'BookInfo'.
        while (bookInfoResultSet.next()) {
            //Получение соответствующей записи из таблицы 'BookLocation'.
            int bookInfoId = bookInfoResultSet.getInt("id");
            String bookLocationSql = "SELECT * FROM " + TABLE_BOOK_LOCATION + " WHERE id = ?";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, bookInfoId);
                try (ResultSet bookLocationResultSet = bookLocationStatement.executeQuery()) {
                    //Если нашлась запись из таблицы 'BookLocation'.
                    if (bookLocationResultSet.next()) {
                        //Обработка года написания книги и вывод результатов.
                        int yearOfWriting = bookInfoResultSet.getInt("year_of_writing");
                        String yearOfWritingValue = (bookInfoResultSet.wasNull()) ? "-" : String.valueOf(yearOfWriting);
                        System.out.printf("| %-15d | %-5d | %-30s | %-20s | %-20s | %-15d | %-20d | %-15s | %-10d | %-5d | %-5d | %-5d |\n",
                                currentIndex++,
                                bookInfoId,
                                bookInfoResultSet.getString("author_full_name"),
                                bookInfoResultSet.getString("publication_title"),
                                bookInfoResultSet.getString("publisher"),
                                bookInfoResultSet.getInt("year_of_publication"),
                                bookInfoResultSet.getInt("number_of_pages"),
                                yearOfWritingValue,
                                bookInfoResultSet.getInt("weight_in_grams"),
                                bookLocationResultSet.getInt("floor"),
                                bookLocationResultSet.getInt("shelf"),
                                bookLocationResultSet.getInt("rack"));
                    }
                }
            }
        }
    }

    //Метод для изменения записи в БД.
    private static void updateRecord(Connection connection) throws SQLException {
        viewAllRecords(connection);
        System.out.println();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите номер записи, которую хотите изменить: ");

        try {
            int recordNumber = scanner.nextInt();
            scanner.nextLine();

            int id = getIdFromRecordNumber(connection, recordNumber);
            if (id == -1) {
                System.out.println("Запись с указанным номером не найдена в БД 'HomeLibrary'. Проверьте корректность указанного номера и повторите снова.");
                return;
            }

            //Отключение автокоммита для отката транзакции обновления в случае неудачи.
            connection.setAutoCommit(false);

            System.out.print("Введите новое ФИО автора книги: ");
            String authorFullName = scanner.nextLine();
            System.out.print("Введите новое название издания: ");
            String publicationTitle = scanner.nextLine();
            System.out.print("Введите новое издательство: ");
            String publisher = scanner.nextLine();
            System.out.print("Введите новый год публикации: ");
            int yearOfPublication = scanner.nextInt();
            System.out.print("Введите новое количество страниц в книге: ");
            int numberOfPages = scanner.nextInt();

            System.out.print("Введите новый год написания книги (оставьте пустым, если год написания неизвестен):\n");
            scanner.nextLine();
            String yearOfWritingInput = scanner.nextLine();
            Integer yearOfWriting = null;
            if (yearOfWritingInput.isEmpty()) {
            } else {
                yearOfWriting = Integer.valueOf(yearOfWritingInput);
            }

            System.out.print("Введите новый вес книги в граммах: ");
            int weightInGrams = scanner.nextInt();

            System.out.print("Введите новый номер этажа: ");
            int floorNumber = scanner.nextInt();
            System.out.print("Введите новый номер шкафа на этаже: ");
            int shelfNumber = scanner.nextInt();
            System.out.print("Введите новый номер полки в шкафу: ");
            int rackNumber = scanner.nextInt();

            String bookInfoSql = "UPDATE " + TABLE_BOOK_INFO + " SET author_full_name = ?, "
                    + "publication_title = ?, publisher = ?, year_of_publication = ?, "
                    + "number_of_pages = ?, year_of_writing = ?, weight_in_grams = ? WHERE id = ?";
            try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                bookInfoStatement.setString(1, authorFullName);
                bookInfoStatement.setString(2, publicationTitle);
                bookInfoStatement.setString(3, publisher);
                bookInfoStatement.setInt(4, yearOfPublication);
                bookInfoStatement.setInt(5, numberOfPages);
                if (yearOfWriting != null) {
                    bookInfoStatement.setInt(6, yearOfWriting);
                } else {
                    bookInfoStatement.setNull(6, Types.INTEGER);
                }
                bookInfoStatement.setInt(7, weightInGrams);
                bookInfoStatement.setInt(8, id);
                int rowsUpdated = bookInfoStatement.executeUpdate();
                System.out.println(rowsUpdated + " запись(-ей) была(-о) обновлена(-о) в таблице 'BookInfo'.");
            }

            String bookLocationSql = "UPDATE " + TABLE_BOOK_LOCATION + " SET floor = ?, "
                    + "shelf = ?, rack = ? WHERE id = ?";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, floorNumber);
                bookLocationStatement.setInt(2, shelfNumber);
                bookLocationStatement.setInt(3, rackNumber);
                bookLocationStatement.setInt(4, id);
                int rowsUpdated = bookLocationStatement.executeUpdate();
                System.out.println(rowsUpdated + " запись(-ей) была(-о) обновлена(-о) в таблице 'BookLocation'.");
            }
            //Коммит транзакции.
            connection.commit();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка: Неверный формат ввода. Пожалуйста, введите номер записи в виде целого числа.");
            scanner.next();
            connection.rollback();
        } finally {
            //Включение автокоммита транзакции.
            connection.setAutoCommit(true);
        }
    }

    //Вспомогательный метод для проверки наличия записи с указанным номером (не id) в БД.
    private static int getIdFromRecordNumber(Connection connection, int recordNumber) throws SQLException {
        String recordIdSql = "SELECT id FROM " + TABLE_BOOK_INFO + " ORDER BY id OFFSET ? ROWS FETCH FIRST 1 ROW ONLY";
        try (PreparedStatement statement = connection.prepareStatement(recordIdSql)) {
            statement.setInt(1, recordNumber - 1);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt("id");
                }
            }
        }
        return -1;
    }

    //Метод для удаления записи из БД.
    private static void deleteRecord(Connection connection) throws SQLException {
        viewAllRecords(connection);
        System.out.println();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите номер записи, которую хотите удалить: ");
        try {
            int recordNumber = scanner.nextInt();

            int id = getIdFromRecordNumber(connection, recordNumber);
            if (id == -1) {
                System.out.println("Запись с указанным номером не найдена в БД 'HomeLibrary'. Проверьте корректность указанного номера и повторите снова.");
                return;
            }

            //Отключение автокоммита для отката транзакции удаления в случае неудачи.
            connection.setAutoCommit(false);
            try {
                String bookInfoSql = "DELETE FROM " + TABLE_BOOK_INFO + " WHERE id = ?";
                try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                    bookInfoStatement.setInt(1, id);
                    int rowsDeletedBookInfo = bookInfoStatement.executeUpdate();
                    System.out.println(rowsDeletedBookInfo + " запись(-ей) была(-о) удалена(-о) из таблицы 'BookInfo'.");
                }
                String bookLocationSql = "DELETE FROM " + TABLE_BOOK_LOCATION + " WHERE id = ?";
                try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                    bookLocationStatement.setInt(1, id);
                    int rowsDeletedBookLocation = bookLocationStatement.executeUpdate();
                    System.out.println(rowsDeletedBookLocation + " запись(-ей) была(-о) удалена(-о) из таблицы 'BookLocation'.");
                }
                //Коммит транзакции.
                connection.commit();
            } catch (SQLException e) {
                System.out.println("Произошла ошибка выполнения транзакции. Транзакция была отменена.");
                connection.rollback();
            } finally {
                //Включение автокоммита транзакции.
                connection.setAutoCommit(true);
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка: Неверный формат ввода. Пожалуйста, введите номер записи в виде целого числа.");
            scanner.next();
        }
    }

    //Метод для добавления новых записей в БД.
    private static void addNewRecord(Connection connection) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        try {
            //Отключение автокоммита для отката транзакции добавления в случае неудачи.
            connection.setAutoCommit(false);

            System.out.print("Введите ФИО автора книги: ");
            String authorFullName = scanner.nextLine();
            System.out.print("Введите название издания: ");
            String publicationTitle = scanner.nextLine();
            System.out.print("Введите издательство: ");
            String publisher = scanner.nextLine();
            System.out.print("Введите год издания: ");
            int yearOfPublication = scanner.nextInt();
            System.out.print("Введите количество страниц в книге: ");
            int numberOfPages = scanner.nextInt();

            System.out.print("Введите год написания книги (оставьте пустым, если год написания неизвестен):\n");
            scanner.nextLine();
            String yearOfWritingInput = scanner.nextLine();
            Integer yearOfWriting = null;
            if (yearOfWritingInput.isEmpty()) {
            } else {
                yearOfWriting = Integer.valueOf(yearOfWritingInput);
            }

            System.out.print("Введите вес книги в граммах: ");
            int weightInGrams = scanner.nextInt();

            System.out.print("Введите номер этажа: ");
            int floorNumber = scanner.nextInt();
            System.out.print("Введите номер шкафа на этаже: ");
            int shelfNumber = scanner.nextInt();
            System.out.print("Введите номер полки в шкафу: ");
            int rackNumber = scanner.nextInt();

            int maxBookId = getMaxId(connection, TABLE_BOOK_INFO, "id");
            int maxLocationId = getMaxId(connection, TABLE_BOOK_LOCATION, "id");

            String bookInfoSql = "INSERT INTO " + TABLE_BOOK_INFO
                    + " (id, author_full_name, publication_title, publisher, year_of_publication, "
                    + "number_of_pages, year_of_writing, weight_in_grams) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                bookInfoStatement.setInt(1, maxBookId + 1);
                bookInfoStatement.setString(2, authorFullName);
                bookInfoStatement.setString(3, publicationTitle);
                bookInfoStatement.setString(4, publisher);
                bookInfoStatement.setInt(5, yearOfPublication);
                bookInfoStatement.setInt(6, numberOfPages);
                if (yearOfWriting != null) {
                    bookInfoStatement.setInt(7, yearOfWriting);
                } else {
                    bookInfoStatement.setNull(7, Types.INTEGER);
                }
                bookInfoStatement.setInt(8, weightInGrams);
                int rowsInserted = bookInfoStatement.executeUpdate();
                System.out.println(rowsInserted + " запись(-ей) была(-о) вставлена(-а) в таблицу 'BookInfo'.");
            }

            String bookLocationSql = "INSERT INTO " + TABLE_BOOK_LOCATION
                    + " (id, floor, shelf, rack) VALUES (?, ?, ?, ?)";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, maxLocationId + 1);
                bookLocationStatement.setInt(2, floorNumber);
                bookLocationStatement.setInt(3, shelfNumber);
                bookLocationStatement.setInt(4, rackNumber);
                int rowsInserted = bookLocationStatement.executeUpdate();
                System.out.println(rowsInserted + " запись(-ей) была(-о) вставлена(-о) в таблицу 'BookLocation'.");
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка: Неверный формат ввода. Пожалуйста, вводите целые числа во все поля, кроме 'ФИО автора', 'Название издания' и 'Издательство'.");
            scanner.next();
            connection.rollback();
        } finally {
            //Включение автокоммита транзакции.
            connection.setAutoCommit(true);
        }
    }

    //Метод поиска максимального ID в указанной таблице в БД (для корректного добавления первичного ключа).
    private static int getMaxId(Connection connection, String tableName, String idColumnName) throws SQLException {
        String sql = "SELECT MAX(" + idColumnName + ") FROM " + tableName;
        try (Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            if (resultSet.next()) {
                return resultSet.getInt(1);
            }
        }
        return 0;
    }

    //Метод для сброса всех НЕключевых полей указанной записи на значения по умолчанию.
    private static void resetNonKeyFields(Connection connection) throws SQLException {
        viewAllRecords(connection);
        System.out.println();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите номер записи, которую хотите сбросить: ");
        try {
            int recordNumber = scanner.nextInt();

            int id = getIdFromRecordNumber(connection, recordNumber);
            if (id == -1) {
                System.out.println("Запись с указанным номером не найдена в БД 'HomeLibrary'. Проверьте корректность указанного номера и повторите снова.");
                return;
            }
            
            //Отключение автокоммита для отката транзакции сброса в случае неудачи.
            connection.setAutoCommit(false);
            
            String bookInfoSql = "UPDATE " + TABLE_BOOK_INFO + " SET author_full_name = ?, "
                    + "publication_title = ?, publisher = ?, year_of_publication = ?, "
                    + "number_of_pages = ?, year_of_writing = ?, weight_in_grams = ? WHERE id = ?";
            try (PreparedStatement bookInfoStatement = connection.prepareStatement(bookInfoSql)) {
                bookInfoStatement.setString(1, "Default Author");
                bookInfoStatement.setString(2, "Default Title");
                bookInfoStatement.setString(3, "Default Publisher");
                bookInfoStatement.setInt(4, 2024);
                bookInfoStatement.setInt(5, 101);
                bookInfoStatement.setInt(6, 2024);
                bookInfoStatement.setInt(7, 500);
                bookInfoStatement.setInt(8, id);
                int rowsUpdated = bookInfoStatement.executeUpdate();
                System.out.println(rowsUpdated + " запись(-ей) была(-о) обновлена(-о) в таблице 'BookInfo'.");
            }

            String bookLocationSql = "UPDATE " + TABLE_BOOK_LOCATION + " SET floor = ?, "
                    + "shelf = ?, rack = ? WHERE id = ?";
            try (PreparedStatement bookLocationStatement = connection.prepareStatement(bookLocationSql)) {
                bookLocationStatement.setInt(1, 1);
                bookLocationStatement.setInt(2, 1);
                bookLocationStatement.setInt(3, 1);
                bookLocationStatement.setInt(4, id);
                int rowsUpdated = bookLocationStatement.executeUpdate();
                System.out.println(rowsUpdated + " запись(-ей) была(-о) обновлена(-о) в таблице 'BookLocation'.");
            }
        } catch (java.util.InputMismatchException e) {
            System.out.println("Ошибка: Неверный формат ввода. Пожалуйста, введите номер записи в виде целого числа.");
            scanner.next();
            connection.rollback();
        } finally {
            //Включение автокоммита транзакции.
            connection.setAutoCommit(true);
        }
    }

    //Метод для оторажения всех записей в таблице 'BookLocation' (сортировка по полкам).
    private static void viewAllFloors(Connection connection) throws SQLException {
        String sql = "SELECT rack FROM " + TABLE_BOOK_LOCATION + " ORDER BY rack";
        try (Statement statement = connection.createStatement(); ResultSet resultSet = statement.executeQuery(sql)) {
            System.out.println("\nВсе полки таблицы 'BookLocation' в лексикографическом порядке:");
            int count = 0;
            while (resultSet.next()) {
                count++;
                System.out.println(resultSet.getInt("rack"));
            }
            if (count == 0) {
                System.out.println("В базе данных 'HomeLibrary' отсутствуют записи, удовлетворяющие запросу.");
            }
        }
    }
}
