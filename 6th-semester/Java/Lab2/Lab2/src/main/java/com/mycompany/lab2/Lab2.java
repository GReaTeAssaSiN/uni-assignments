//Автоматически созданный пакет при создании проекта для его структурирования.
package com.mycompany.lab2;

//Импорт классов для настройки корректного отображения кириллических символов из пакета java.io в NetBeans.
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;

//Создание интерфейса функции для вычисления искомых сумм и обработки исключений при последующей реализации класса.
interface FuncsNumberProcessor{
    static final int MIN_ARRAY_LENGTH = 5;
    static final int MAX_ARRAY_LENGTH = 20;
    static final char SPECIAL_SYMBOL = '-';
    void calculateEvenAndOddNegativeSum(String[] args) throws MinimumLengthException, SymbolException, MaximumLengthException;
    void handleException(String message);
}
//Создание интерфейса функции для вывода искомых сумм при последующей реализации класса.
interface PrintResultsNumberProcess{
    void printResults(int sumEvenNegativeNumbers, int sumOddNegativeNumbers);
}

//Исключение: В массиве число элементов меньше указанного (минимальное число элементов = 5).
class MinimumLengthException extends Exception{
    public MinimumLengthException(String message){
        super(message);
    }
}

//Исключение: В строке отсутствует какой-то символ (в строке должен присутствовать символ -).
class SymbolException extends Exception{
    public SymbolException(String message){
        super(message);
    }
}

//Исключение: В массиве число элементов больше указанного (максимальное число элементов = 20).
class MaximumLengthException extends Exception{
    public MaximumLengthException(String message){
        super(message);
    }
}

//Основной класс, реализующий интерфейсы.
class NumberProcessor implements FuncsNumberProcessor, PrintResultsNumberProcess{
    //Поля класса.
    private int sumEvenNegativeNumbers = 0;
    private int sumOddNegativeNumbers = 0;
    //Класс имеет конструктор по умолчанию.
    //Методы класса.
    @Override
    public void calculateEvenAndOddNegativeSum(String[] args) throws MinimumLengthException, SymbolException, MaximumLengthException{
        if (args.length < FuncsNumberProcessor.MIN_ARRAY_LENGTH){
            throw new MinimumLengthException("MinimumLengthException happened: Command line arguments length is less than " + FuncsNumberProcessor.MIN_ARRAY_LENGTH + ".");
        }
        if (args.length > FuncsNumberProcessor.MAX_ARRAY_LENGTH){
            throw new MaximumLengthException("MaximumLengthException happened: Command line arguments length is more than " + FuncsNumberProcessor.MAX_ARRAY_LENGTH + ".");
        }
        boolean specialSymbol = false;
        for (String arg: args){
            char[] charArray = arg.toCharArray();
            for (char ch: charArray){
                if (!specialSymbol && ch == FuncsNumberProcessor.SPECIAL_SYMBOL)
                    specialSymbol = true;
            }
            try{
                int num = Integer.parseInt(arg);
                if (num < 0 && num % 2 == 0){
                    this.sumEvenNegativeNumbers += num;
                }
                if (num < 0 && num % 2 != 0){
                    this.sumOddNegativeNumbers += num;
                }
            }
            catch (NumberFormatException e){
                System.out.println("Unhandled NumberFormatException happened: " + e.getMessage());
                System.exit(1);
            }
        }
        if (!specialSymbol){
            throw new SymbolException("SymbolException happened: The command line argument string must contain the - symbol, i.e. at least one negative number." );
        }
    }
    @Override
    public void printResults(int sumEvenNegativeNumbers, int sumOddNegativeNumbers){
       System.out.println("Sum of even and negative numbers: " + sumEvenNegativeNumbers);
       System.out.println("Sum of odd and negative numbers: " + sumOddNegativeNumbers);
    }
    @Override
    public void handleException(String message){
        System.out.println(message);
    }
    public int getSumEvenNegativeNumbers(){
        return this.sumEvenNegativeNumbers;
    }
    public int getSumOddNegativeNumbers(){
        return this.sumOddNegativeNumbers;
    }
}

public class Lab2{
    public static void main(String[] args){
        //Установка кодировки для вывода.
        try {
            System.setOut(new PrintStream(System.out, true, "UTF-8"));
        } 
        catch (UnsupportedEncodingException e){e.printStackTrace();}
        
        NumberProcessor numberProcessor = new NumberProcessor();
        try{
            numberProcessor.calculateEvenAndOddNegativeSum(args);
            numberProcessor.printResults(numberProcessor.getSumEvenNegativeNumbers(), numberProcessor.getSumOddNegativeNumbers());
        }
        catch (MinimumLengthException | SymbolException | MaximumLengthException e){
            numberProcessor.handleException(e.getMessage());
        }
    }
}