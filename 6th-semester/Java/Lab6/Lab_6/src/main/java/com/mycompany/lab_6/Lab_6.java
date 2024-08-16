package com.mycompany.lab_6;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;

class OurWindowAdapter extends WindowAdapter {
    public void windowClosing(WindowEvent wE) {
        System.exit(0);
    }
}

class Lab_6 extends Frame {
    public static final int MAX_OBJECTS_COUNT = 10;
    int count = 0;
    List<Integer> id_objects = new ArrayList<>();
    List<TextLabel> text_labels = new ArrayList<>();
    Frame f;
    Canvas cnv;

    Color color = Color.BLACK;
    
    Label ObjectColorLabel, ObjectRunStartLabel, ObjectTextLabel, ObjectSpeedStartLabel, ObjectRunFinishLabel, ObjectChangeIDLabel, ObjectSpeedFinishLabel;
    Button ObjectColorButton, ObjectAddButton, ObjectChangeIDButton, ObjectChangeSpeedButton;
    Choice ObjectRunStartChoice, ObjectSpeedFinishChoice;
    TextField ObjectSpeedStartTextField, ObjectTextField, ObjectRunFinishTextField, ObjectChangeIDTextField;

    Lab_6() {
        // Управляющее окно.
        this.setLocation(200, 150);
        this.setSize(new Dimension(340, 240));
        this.setTitle("Управляющее окно");
        this.setResizable(false);

        // Цвет объекта.
        ObjectColorLabel = new Label("Цвет объекта: ");
        ObjectColorButton = new Button("Выбрать цвет");
        ObjectColorButton.setActionCommand("SelectColor");

        // Выбор запускаемого объекта.
        ObjectRunStartLabel = new Label("Запускаемый объект: ");
        ObjectRunStartChoice = new Choice();
        ObjectRunStartChoice.addItem("Текстовая надпись");

        // Начальная скорость запускаемого объекта.
        ObjectSpeedStartLabel = new Label("Начальная скорость: ");
        ObjectSpeedStartTextField = new TextField();

        //Текст запускаемого объекта.
        ObjectTextLabel = new Label("Текст объекта: ");
        ObjectTextField = new TextField();
        
        // Выбор запущенного объекта.
        ObjectRunFinishLabel = new Label("ID запущенного объекта: ");
        ObjectRunFinishTextField = new TextField();

        // Новый номер запущенного объекта.
        ObjectChangeIDLabel = new Label("Новый ID запущенного объекта: ");
        ObjectChangeIDTextField = new TextField();

        // Новая скорость запущенного объекта.
        ObjectSpeedFinishLabel = new Label("Новое значение скорости: ");
        ObjectSpeedFinishChoice = new Choice();
        for (int i = 0; i <= 8; i += 2) {
            ObjectSpeedFinishChoice.add(String.valueOf(i));
        }

        // Кнопка добавить.
        ObjectAddButton = new Button("Добавить");
        ObjectAddButton.setActionCommand("Add");

        // Кнопка изменить ID.
        ObjectChangeIDButton = new Button("Изменить ID");
        ObjectChangeIDButton.setActionCommand("ChangeID");

        // Кнопка изменить скорость.
        ObjectChangeSpeedButton = new Button("Изменить скорость");
        ObjectChangeSpeedButton.setActionCommand("ChangeSpeed");

        cnv = new Canvas() {
            public void paint(Graphics g) {
                // Здесь можно добавить код для рисования объектов на холсте.
            }
        };

        GridBagConstraints gbc = new GridBagConstraints();
        this.setLayout(new GridBagLayout());

        // Цвет.
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        this.add(ObjectColorLabel, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 2;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        this.add(ObjectColorButton, gbc);

        // Выбор запускаемого объекта.
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 2;
        this.add(ObjectRunStartLabel, gbc);

        gbc.gridx = 2;
        gbc.gridy = 1;
        gbc.gridwidth = 2;
        this.add(ObjectRunStartChoice, gbc);

        // Начальная скорость запускаемого объекта.
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.gridwidth = 2;
        this.add(ObjectSpeedStartLabel, gbc);

        gbc.gridx = 2;
        gbc.gridy = 2;
        gbc.gridwidth = 2;
        this.add(ObjectSpeedStartTextField, gbc);
          
        //Текст добавляемого объекта.
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        this.add(ObjectTextLabel, gbc);

        gbc.gridx = 2;
        gbc.gridy = 3;
        gbc.gridwidth = 2;
        this.add(ObjectTextField, gbc);
        // Кнопка добавить.
        gbc.gridx = 2;
        gbc.gridy = 4;
        gbc.gridwidth = 2;
        this.add(ObjectAddButton, gbc);
        
        // Создание пустой панели для добавления пустого пространства.
        Panel spacerPanel = new Panel();
        spacerPanel.setPreferredSize(new Dimension(200, 20));
        
        // Добавление пустой панели после кнопки "Добавить"
        gbc.gridx = 0;
        gbc.gridy = 5;
        gbc.gridwidth = 4;
        this.add(spacerPanel, gbc);
        
        // Выбор запущенного объекта.
        gbc.gridx = 0;
        gbc.gridy = 6;
        gbc.gridwidth = 2;
        this.add(ObjectRunFinishLabel, gbc);

        gbc.gridx = 2;
        gbc.gridy = 6;
        gbc.gridwidth = 2;
        this.add(ObjectRunFinishTextField, gbc);

        // Новый номер запущенного объекта.
        gbc.gridx = 0;
        gbc.gridy = 7;
        gbc.gridwidth = 2;
        this.add(ObjectChangeIDLabel, gbc);

        gbc.gridx = 2;
        gbc.gridy = 7;
        gbc.gridwidth = 2;
        this.add(ObjectChangeIDTextField, gbc);

        // Новая скорость запущенного объекта.
        gbc.gridx = 0;
        gbc.gridy = 8;
        gbc.gridwidth = 2;
        this.add(ObjectSpeedFinishLabel, gbc);

        gbc.gridx = 2;
        gbc.gridy = 8;
        gbc.gridwidth = 2;
        this.add(ObjectSpeedFinishChoice, gbc);

        // Кнопка изменить ID.
        gbc.gridx = 0;
        gbc.gridy = 9;
        gbc.gridwidth = 2;
        this.add(ObjectChangeIDButton, gbc);

        // Кнопка изменить скорость.
        gbc.gridx = 2;
        gbc.gridy = 9;
        gbc.gridwidth = 2;
        this.add(ObjectChangeSpeedButton, gbc);

        ObjectAddButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent aE) {
                AddButFunc();
            }
        });

        ObjectChangeIDButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent aE) {
                ChangeButFunc();
            }
        });

        ObjectChangeSpeedButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent aE) {
                ChangeSpeedFunc();
            }
        });

        ObjectColorButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent aE) {
                ChooseColor();
            }
        });

        this.addWindowListener(new OurWindowAdapter());

        // Демонстрационное окно.
        f = new Frame();
        f.setTitle("Демонстрационное окно");
        f.addWindowListener(new OurWindowAdapter());
        f.setSize(500, 500);
        f.add(cnv);
        f.setVisible(true);
        f.setLocation(600, 150);
        f.setResizable(false);
    }

    public void AddButFunc() {
        if (id_objects.size() < MAX_OBJECTS_COUNT) {
            try {
                int speed = Integer.parseInt(ObjectSpeedStartTextField.getText());
                int maxID = -1;
                for (int id : id_objects) {
                    if (id > maxID) {
                        maxID = id;
                    }
                }
                // Присваиваем новому объекту следующий доступный идентификатор
                int newID = maxID + 1;
                String objectText = ObjectTextField.getText();
                TextLabel text = new TextLabel(newID, color, speed, objectText, cnv);
                text.setText(text.getSpecialText() + "(" + newID + ")");
                id_objects.add(newID);
                text_labels.add(text);
                ObjectRunStartChoice.add(String.valueOf(newID));
                text.start();
            } catch (NumberFormatException ex) {
                System.out.println("Invalid speed value");
            }
        } else {
            System.out.println("Maximum number of objects reached");
        }
    }


    public void ChangeButFunc() {
        try {
            int newID = Integer.parseInt(ObjectChangeIDTextField.getText());
            if (id_objects.contains(newID)) {
                System.out.println("Cannot change ID to an existing one");
            } else {
                int selectedID = Integer.parseInt(ObjectRunFinishTextField.getText());
                if (id_objects.contains(selectedID)) {
                    int index = id_objects.indexOf(selectedID);
                    System.out.println("Object ID successfully changed");
                    ObjectRunStartChoice.remove(index);
                    ObjectRunStartChoice.insert(String.valueOf(newID), index);
                    id_objects.set(index, newID);
                    TextLabel text = findTextLabelByID(selectedID);
                    if (text != null) {
                        text.setText(text.getSpecialText() + "(" + newID + ")");
                        text.id = newID;
                    }
                } else {
                    System.out.println("Object with the specified ID does not exist");
                }
            }
        } catch (NumberFormatException ex) {
            System.out.println("Invalid ID value");
        }
    }


    // Метод для поиска объекта TextLabel по ID
    private TextLabel findTextLabelByID(int id) {
        for (TextLabel textLabel : text_labels) {
            if (textLabel.id == id) {
                return textLabel;
            }
        }
        return null;
    }

    public void ChangeSpeedFunc() {
        try {
            int newSpeed = Integer.parseInt(ObjectSpeedFinishChoice.getSelectedItem());
            int selectedID = Integer.parseInt(ObjectRunFinishTextField.getText());
            if (id_objects.contains(selectedID)) {
                System.out.println("Object speed successfully changed");
                TextLabel text = findTextLabelByID(selectedID);
                if (text != null) {
                    text.speed = newSpeed;
                }
            } else {
                System.out.println("Object with the specified ID does not exist");
            }
        } catch (NumberFormatException ex) {
            System.out.println("Invalid ID value");
        }
    }


    public void ChooseColor() {
        color = JColorChooser.showDialog(this, "Choose Color", color);
        if (color != null) {
            ObjectColorButton.setBackground(color);
        }
    }

    public static void main(String[] args) {
        Lab_6 Fr = new Lab_6();
        Fr.setVisible(true);
    }
}

class TextLabel extends Thread {
    Point point = new Point(50, 50);
    Canvas cnv;
    Graphics g;
    Color color;
    String special_text;
    String text;
    public int speed;
    double angle;
    int id;
    int step = 4;

    TextLabel(int id, Color color, int speed, String special_text, Canvas cnv) {
        this.id = id;
        this.color = color;
        this.speed = speed;
        this.special_text = special_text;
        this.cnv = cnv;
        this.g = cnv.getGraphics();
        // Генерация случайного угла для движения в случайном направлении из левого верхнего угла.
        this.angle = Math.random() * Math.PI / 2;
    }

    void moveTo() {
        this.show(g, false);
        this.point.x += this.speed * Math.cos(this.angle) * step;
        this.point.y += this.speed * Math.sin(this.angle) * step;
        checkBorder();
        this.show(g, true);
    }

    void show(Graphics g, boolean sh) {
        if (sh)
            g.setColor(color);
        else
            g.setColor(Color.white);
        g.drawString(this.text, point.x, point.y);
    }
    
    String getSpecialText(){
        return this.special_text == null ? "" : this.special_text;
    }
    
    void setText(String new_text){
        this.text = new_text;
    }

    void checkBorder() {
        boolean border = false;
        int dd = 5; // Минимальное расстояние до границы
        // Получаем размеры текста
        FontMetrics fm = g.getFontMetrics();
        int textWidth = fm.stringWidth(text);
        int textHeight = fm.getHeight();

        if (point.x <= dd && Math.cos(angle) < 0) {
            angle = Math.PI - angle;
            border = true;
        } else if (point.x + textWidth >= cnv.getWidth() - dd && Math.cos(angle) > 0) {
            angle = Math.PI - angle;
            border = true;
        } else if (point.y <= dd + 15 && Math.sin(angle) < 0) {
            angle = -angle;
            border = true;
        } else if (point.y + textHeight >= cnv.getHeight() - dd && Math.sin(angle) > 0) {
            angle = -angle;
            border = true;
        }

        if (border) {
            point.x += speed * Math.cos(angle);
            point.y += speed * Math.sin(angle);
        }
    }

    public void run() {
        while (true) {
            moveTo();
            try {
                sleep(130);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}