package com.mycompany.lab3;

import java.io.*;

interface IEventOutput{
    void Handler(String message, File log_file);
}

interface IEventAccessArray{
    void Handler(String message, File log_file);
}

interface IEventInput{
    void Handler(String message, File log_file);
}

class SourceOutput{
    IEventOutput iEvent;
    SourceOutput(IEventOutput iEvent){
        this.iEvent = iEvent;
    }
    void genEv(String message, File log_file){
        iEvent.Handler("Event " + message, log_file);
    }
}

class SourceAccessArray{
    IEventAccessArray iEvent;
    SourceAccessArray(IEventAccessArray iEvent){
        this.iEvent = iEvent;
    }
    void genEv(String message, File log_file){
        iEvent.Handler("Event " + message, log_file);
    }
}

class SourceInput{
    IEventInput iEvent;
    SourceInput(IEventInput iEvent){
        this.iEvent = iEvent;
    }
    void genEv(String message, File log_file){
        iEvent.Handler("Event " + message, log_file);
    }
}

class ReceiverOutput implements IEventOutput{
    public void Handler(String message, File log_file){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(log_file.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ReceiverAccessArray implements IEventAccessArray{
     public void Handler(String message, File log_file){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(log_file.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class ReceiverInput implements IEventInput{
     public void Handler(String message, File log_file){
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(log_file.getAbsoluteFile(), true));
            pw.println(message);
            pw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class NumberProcessor{
    private int sumEvenNegativeNumbers = 0;
    private int sumOddNegativeNumbers = 0;
    private File f_src;
    private File f_log;
    SourceOutput eventOut;
    SourceInput eventIn;
    SourceAccessArray eventAccessArray;
    
    NumberProcessor(SourceOutput eventOut, SourceInput eventIn, SourceAccessArray eventAccessArray){
        this.eventOut = eventOut;
        this.eventIn = eventIn;
        this.eventAccessArray = eventAccessArray;
    }
    
    //Сет-методы для f_src и f_log. 
    private void setSrcFile(File src_file){
        this.f_src = src_file;
    }
    private void setLogFile(File log_file){
        this.f_log = log_file;
    }
    // Метод для создания новых/чтения уже существующих файлов.
    private void filesProcessing() {
        String filePath;
        File log_file;
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            try {
                String input = reader.readLine();
                if (!input.isEmpty()) {
                    filePath = input;
                    File src_file = new File(filePath);
                    if (!src_file.exists()) {
                        System.out.println("O: The input data file at the specified path does not exist. Path: " + src_file.getAbsolutePath());
                        System.out.print("I/O: Enter another path of input data file: ");
                    }
                    else{
                        try (BufferedReader fileReader = new BufferedReader(new FileReader(src_file))) {
                            String firstLine = fileReader.readLine();
                            if (!firstLine.isEmpty()) {
                                System.out.println("O: First line of the input data file is the path to the log file. Path: " + firstLine);
                                this.setSrcFile(src_file);
                                log_file = new File(firstLine);
                                this.setLogFile(log_file);
                                if (!log_file.exists()){
                                    log_file.createNewFile();
                                    System.out.println("O: Log file created successfully: " + log_file.getAbsolutePath());
                                    eventOut.genEv("O: Log file created successfully: " + log_file.getAbsolutePath(), log_file);
                                    System.out.println("O: The log file can be succesfully opened for logging.");
                                    eventOut.genEv("O: The log file can be succesfully opened for logging.", log_file);
                                }
                                return;
                            } else {
                                System.out.println("O: Error: The input data file does not contain the path of log file. Search another input data file.");
                                System.out.print("I/O: Path of input data file: ");
                            }
                        }
                        catch (IOException e) {
                            System.out.println("O: Error reading the file: " + e.getMessage());
                        }
                    }
                } else {
                    System.out.print("O: The file path was not retrieved correctly. Re-enter: ");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    // Метод для обработки чисел и генерации событий.
    public void numberProcessing(String[] data) {
        for (String number : data) {
            System.out.println("A/O: Accessing an array from a sequence of numbers. Element in question:: " + number);
            eventAccessArray.genEv("A/O: Accessing an array from a sequence of numbers. Element in question: " + number, this.f_log);
            try {
                int num = Integer.parseInt(number);
                if (num < 0 && num % 2 == 0) {
                    this.sumEvenNegativeNumbers += num;
                }
                if (num < 0 && num % 2 != 0) {
                    this.sumOddNegativeNumbers += num;
                }
            } catch (NumberFormatException e) {
                System.out.println("O: Unhandled exception happened.");
                eventOut.genEv("O: Unhandled exception happened.", this.f_log);
                System.exit(1);
            }
        }
        System.out.println("O: Sum of even and negative numbers: " + this.sumEvenNegativeNumbers);
        eventOut.genEv("O: Sum of even and negative numbers: " + this.sumEvenNegativeNumbers, this.f_log);
        System.out.println("O: Sum of odd and negative numbers: " + this.sumOddNegativeNumbers);
        eventOut.genEv("O: Sum of odd and negative numbers: " + this.sumOddNegativeNumbers, this.f_log);
    }
    // Метод для обработки событий и инициализации файлов.
    public void startProcessing() {
        System.out.print("I/O: Enter the absolute path of the input data file: ");
        this.filesProcessing();

        if (this.f_log.length() != 0) {
            try {
                PrintWriter pw = new PrintWriter(new FileWriter(this.f_log, true));
                pw.println();
                pw.println("/*New log to the same file:*/");
                pw.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        
        StringBuilder sb_data = new StringBuilder();
        if (this.f_src.exists()) {
            try (BufferedReader br_data = new BufferedReader(new FileReader(this.f_src.getAbsoluteFile()))) {
                try {
                    br_data.readLine();
                    
                    String my_data;
                    while ((my_data = br_data.readLine()) != null) {
                        sb_data.append(my_data);
                        sb_data.append("\n");
                    }
                } finally {
                    br_data.close();
                }
            } catch (IOException e) {
                throw new RuntimeException();
            }
        }

        if (sb_data.toString().isEmpty() || sb_data.toString().matches("(\n)+")) {
            this.f_src.delete();
            eventOut.genEv("O: Error: Input data file does not have numeric data.", this.f_log);
            System.out.println("O: Error: Input data file does not have numeric data.");
            eventOut.genEv("O: File " + this.f_src.getAbsolutePath() + " was deleted.", this.f_log);
            System.out.println("O: File " + this.f_src.getAbsolutePath() + " was deleted.");
            eventOut.genEv("O: Please enter the source data:", this.f_log);
            System.out.println("O: Please enter the source data:");

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            eventOut.genEv("O: Enter numbers. Type 'end' to finish:", this.f_log);
            System.out.println("O: Enter numbers. Type 'end' to finish:");

            while (true) {
                try {
                    System.out.print("I: ");
                    String input_number = reader.readLine();
                    if (input_number.equalsIgnoreCase("end")) {
                        System.out.println();
                        break;
                    }
                    int number = Integer.parseInt(input_number);
                    sb_data.append(number).append(" ");
                    eventIn.genEv("I: " + number, f_log);
                } catch (NumberFormatException | IOException e) {
                    eventOut.genEv("O: Invalid input. Please enter a number or 'end' to finish.", f_log);
                    System.out.println("O: Invalid input. Please enter a number or 'end' to finish.");
                }
            }

            eventOut.genEv("O: Entered numbers: " + sb_data, f_log);
            System.out.println("O: Entered numbers: " + sb_data);
        }
        this.numberProcessing(sb_data.toString().split("\\s+|\n"));
    }
}

public class Lab3 {
    public static void main(String[] args) {
        try {
            System.setOut(new PrintStream(System.out, true, "UTF-8"));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        
        ReceiverOutput receiverOut = new ReceiverOutput();
        ReceiverInput receiverIn = new ReceiverInput();
        ReceiverAccessArray receiverAccessArray = new ReceiverAccessArray();
        SourceOutput sourceOut = new SourceOutput(receiverOut);
        SourceInput sourceIn = new SourceInput(receiverIn);
        SourceAccessArray sourceAccessArray = new SourceAccessArray(receiverAccessArray);
        
        NumberProcessor NP_obj = new NumberProcessor(sourceOut, sourceIn, sourceAccessArray);
        NP_obj.startProcessing();
    }
}