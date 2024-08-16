package com.mycompany.test;

//Для всех примеров кроме последнего.
//import java.awt.*;
//import java.awt.event.*; //начиная с 3

/*ПРИМЕР 1*/
/* Окно с графикой*/
//class Test extends Frame 
//{
//    @Override
//    public void paint (Graphics g) 
//    {
//        g.drawLine (5, 35, 100, 35); // Нарисовать линию
//        g.setColor (Color.blue); // Установить синий цвет
//        g.drawRect (10, 40, 40, 60); // Нарисовать прямоугольник
//        g.setColor (Color.red); // Установить красный цвет
//        g.fillOval (70, 40, 40, 60); // Нарисовать заполненный эллипс
//        Font f= new Font ("Verdana", Font.BOLD, 30);
//        g.setFont (f);
//        // Установить шрифт
//        g.drawString ("KAI", 5, 130); // Нарисовать текст
//    }
//    public static void main (String[] args) 
//    {
//        Test gr = new Test( ); // Создать объект окна
//        gr.setSize (100, 150); // Установить размеры окна
//        gr.show ( ); // Показать окно
//    }
//}

/*ПРИМЕР 2*/
/* Обработка события закрытия окна*/
//class Test extends Frame 
//{
//    @Override
//    public void paint (Graphics g) 
//    {
//        g.setColor(Color.red);
//        g.fillOval(70, 40, 40, 60);}
//        @Override
//        public boolean handleEvent (Event e) 
//        {
//            if (e.id == Event.WINDOW_DESTROY) 
//                System.exit(0);
//            return (super.handleEvent(e));
//        }
//    public static void main (String[] args) 
//    {
//        Test gr = new Test();
//        gr.setSize(100, 150); 
//        gr.show();
//    }
//}

/*ПРИМЕР 3*/
/* Обработка события закрытия окна*/
//class Test extends Frame 
//{
//    public Test() 
//    {
//        // Подписаться на обработчик закрытия окна
//        this.addWindowListener (new OurWindowAdapter());
//    }
//    @Override
//    public void paint (Graphics g) 
//    {
//        g.setColor(Color.red);
//        g.fillOval(70, 40, 40, 60);
//    }
//    public static void main (String[] args) 
//    {
//        Test gr = new Test();
//        gr.setSize(100, 150);
//        gr.show();
//    }
//}
//class OurWindowAdapter extends WindowAdapter 
//{
//    @Override
//    public void windowClosing (WindowEvent wE) 
//    {
//        System.exit (0);
//    }
//}

/*Пример 4*/
/* Обработка события закрытия окна с использованием анонимного класса*/
//class Test extends Frame 
//{
//    public Test() 
//    {
//        // Подписаться на объект внутреннего анонимного класса
//        this.addWindowListener (new WindowAdapter() 
//        {
//            @Override
//            public void windowClosing (WindowEvent wE)
//            {
//                System.exit (0);
//            }
//        });
//    }
//    @Override
//    public void paint (Graphics g) 
//    {
//        g.setColor(Color.red);
//        g.fillOval(70, 40, 40, 60);
//    }
//    public static void main (String[] args) 
//    {
//        Test gr = new Test();
//        gr.setSize(100, 150);
//        gr.show();
//    }
//}

/*Пример 5*/
/* Обработка событий мыши и закрытия окна*/
//class Test extends Frame 
//{
//    String str = null;
//    public Test() 
//    {
//        str = "";
//        // Подписаться на объект внутреннего анонимного класса (для мыши)
//        this.addMouseListener(new MouseAdapter() 
//        {
//            @Override
//            public void mousePressed (MouseEvent mE) 
//            {
//                str = "x= " + mE.getX() + " y= " + mE.getY();
//                repaint();
//            }
//        });
//        // Подписаться на объект внутреннего анонимного класса (для окна)
//        this.addWindowListener (new WindowAdapter() 
//        {
//            @Override
//            public void windowClosing (WindowEvent wE){System.exit (0);}
//        });
//    }
//    @Override
//    public void paint (Graphics g) 
//    {
//        g.setColor(Color.red);
//        g.fillOval(70, 40, 40, 60);
//        g.drawString(str, 10, 120);
//    }
//    public static void main (String[] args) 
//    {
//        Test gr= new Test();
//        gr.setSize(100, 150);
//        gr.show();
//    }
//}

/*Пример 6*/
/*-----------------------------------------
|Окно и управляющие интерфейсные элементы |
-----------------------------------------*/
/* Окно, кнопка и редактор текста*/
// Класс прикладного окна
//class Test extends Frame 
//{
//    TextField ourTextBox; // Ссылка на редактор текста
//    Button ourButton; // Ссылка на кнопку
//    Point point; // Начальные координаты строки
//    Color[] colors; // Ссылка на массив цветов флага
//    int n; // Индекс массива цветов colors
//    // Конструктор
//    public Test() 
//    { 
//        setSize (new Dimension (400, 200));
//        this.setBackground (Color.lightGray);
//        setLayout (new FlowLayout ( ));
//        ourTextBox = new TextField ( ); // Создать редактор
//        ourTextBox.setSize (150, 20); // Установить размер
//        ourTextBox.setText ("Russia"); // Установить текст в редакторе
//        add (ourTextBox); // Добавить редактор в форму
//        ourButton= new Button ("OK"); // Создать кнопку
//        add (ourButton); // Добавить кнопку к форме
//        // Подписать обработчик на событие кнопки
//        ourButton.addActionListener (new ActionListener() 
//        {
//            @Override
//            public void actionPerformed (ActionEvent aE) 
//            {
//                n++; if (n >= 3) n= 0;
//            }
//        });
//        // Подписать обработчик на событие мыши
//        this.addMouseListener (new MouseAdapter() 
//        {
//            @Override
//            public void mousePressed (MouseEvent mE) 
//            {
//                System.out.println ("Mouse: x = " + mE.getX() + " y= " + mE.getY());
//                point.x = mE.getX(); point.y = mE.getY();
//                repaint();
//            }
//        });
//        // Подписать обработчик для закрытия окна
//        this.addWindowListener (new WindowAdapter() 
//        {
//            @Override
//            public void windowClosing (WindowEvent wE) 
//            {
//                System.exit (0);
//            }
//        });
//        n = 0;
//        point= new Point (100, 100);
//        colors = new Color[3]; // Создать массив цветов
//        colors[0]= Color.white; // Белый цвет
//        colors[1]= Color.blue; // Синий цвет
//        colors[2]= Color.red; // Красный цвет
//    }
//    // Перерисовать область клиента окна
//    @Override
//    public void paint (Graphics g) 
//    {   
//        // Нарисовать строку от носика курсора мыши
//        g.setColor (colors[n]);
//        g.drawString (ourTextBox.getText(), point.x, point.y);
//    }
//    public static void main (String[] args) 
//    {
//        Test cT = new Test();
//        cT.show();
//    }
//}

/*Пример 7*/
/*---------------------
|Окно и дочерние окна |
---------------------*/
/* Окно с дочерним окном*/
//class Test extends Frame 
//{
//    Frame childFrame ; // Дочерняя форма
//    TextField ourTextBox; // Редактор
//    Button ourButton; // Кнопка
//    Point point; // Начальные координаты строки
//    Color [] colors; // Массив цветов флага
//    int n; // Индекс массива цветов colors
//    public Test() 
//    {
//        setTitle("Russian flag");
//        setSize (400, 200);
//        // Установить заголовок прикладного окна63
//        this.setBackground(Color.lightGray);
//        ourTextBox = new TextField();
//        // Создать редактор
//        ourTextBox.setSize(new Dimension(150, 20)); // Установить позицию
//        ourTextBox.setText ("Russia"); // Установить текст в редакторе
//        ourButton = new Button ("OK"); // Создать кнопку
//        // Подписать обработчик на событие кнопки
//        ourButton.addActionListener(new ActionListener() 
//        {
//            @Override
//            public void actionPerformed (ActionEvent aE) 
//            {
//                n++;
//                if (n >= 3) 
//                    n = 0;
//            }
//        });
//        // Подписать обработчик на событие MouseDown мыши
//        this.addMouseListener(new MouseAdapter() 
//        {
//            @Override
//            public void mousePressed (MouseEvent mE) 
//            {
//                point.x = mE.getX();
//                point.y = mE.getY();
//                repaint ( );
//            }
//        });
//        // Подписать обработчик для закрытия окна
//        this.addWindowListener (new WindowAdapter() 
//        {
//            @Override
//            public void windowClosing (WindowEvent wE) 
//            {
//                System.exit(0);
//            }
//        });
//        n = 0;
//        point = new Point (100, 100);
//        colors = new Color [3]; // Создать массив цветов
//        colors[0] = Color.white; // Белый цвет
//        colors[1] = Color.blue; // Синий цвет
//        colors[2] = Color.red; // Красный цвет
//        childFrame = new Frame(); // Создать дочернюю форму и
//        childFrame.setSize (200, 100); // с размером
//        childFrame.setLocation (410, 0);
//        childFrame.setLayout (new FlowLayout ( ));
//        childFrame.add (ourTextBox); // Добавить редактор
//        childFrame.add (ourButton); // Добавить кнопку
//        childFrame.show();
//    }
//    // Перерисовать область клиента окна
//    @Override
//    public void paint (Graphics g) 
//    {
//        // Нарисовать строку от носика курсора мыши
//        g.setColor(colors[n]);
//        g.drawString(ourTextBox.getText(), point.x, point.y);
//    }
//    public static void main (String[] args) 
//    {
//        Test cT = new Test();
//        cT.show();
//    }
//}

/*Пример 8*/
/*--------------------
|Понятие об Layout-ах|
--------------------*/
/* FlowLayout*/
//class Test extends Frame 
//{
//    public Test() 
//    {
//        this.setSize(200, 100);
//        String items[]= {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
//        Button but[]= new Button[10];
//        setLayout (new FlowLayout (FlowLayout.LEFT));
//        for (int i = 0; i < items.length; i++) 
//        {
//            but[i]= new Button (items[i]);
//            add(but[i]);
//        }
//        this.show ( );
//    }
//    public static void main (String[] args) 
//    {
//        Test f = new Test();
//    }
//}

/*Пример 9 */
/* BorderLayout*/
//class Test extends Frame 
//{
//    public Test() 
//    {
//        this.setSize(200, 100);
//        String items[]= {"1", "2", "3", "4", "5"};
//        String locs[]= {"North", "South", "East", "West", "Center"};
//        Button but[]= new Button[10];
//        setLayout(new BorderLayout ( ));
//        for (int i= 0; i < 5; i++) 
//        {
//            /*this.*/add (locs[i], new Button (items[i]));
//        }
//        this.show ( );
//    }
//    public static void main (String[] args) 
//    {
//        Test b = new Test();
//    }
//}

/*Пример 10*/
/* GridLayout*/
//class Test extends Frame 
//{
//    public Test() 
//    {
//        this.setSize(200, 100);
//        String items[]= {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
//        Button but[]= new Button[10];
//        setLayout(new GridLayout (2, 5));
//        for (int i= 0; i < items.length; i++) 
//        {
//            add (new Button (items[i]));
//        }
//        this.show();
//    }
//    public static void main (String[] args) 
//    {
//        Test g = new Test();
//    }
//}

/*Пример 1. Программа, где используются элементы GUI, события и потоки*/
import java.util.*;
import java.util.LinkedList;
import java.awt.*;
import java.awt.event.*;
public class Test
{
    static int count;
    public static void main(String[] args)
    {
        count = 0;
        Balls balls = new Balls();
    }
}
class Balls extends Frame implements Observer, ActionListener, ItemListener 
{
    private LinkedList LL = new LinkedList(); //Связный список
    private Color col; //Выбранный цвет
    private Frame f; //Окно
    private Button b; //Кнопка
    private Choice c; //Выпадающий список
    private TextField tf; //Текстовое поле
    Balls()
    {
        this.addWindowListener(new WindowAdapter2());
        f = new Frame();
        f.setSize(new Dimension(300,100));
        f.setTitle("Контроль");
        f.setLayout(new GridLayout());
        f.addWindowListener(new WindowAdapter2());
        b = new Button("Пуск");
        b.setSize(new Dimension(10,40));
        b.setActionCommand("OK");
        b.addActionListener(this);
        f.add(b, new Point(20,20));
        c = new Choice();
        c.addItem("Синий");
        c.addItem("Зелёный");
        c.addItem("Красный");
        c.addItem("Чёрный");
        c.addItem("Жёлтый");
        c.addItemListener(this);
        f.add(c, new Point(60,20));
        tf = new TextField();
        f.add(tf);
        f.setVisible(true);
        this.setSize(500,200);
        this.setVisible(true);
        this.setLocation(100, 150);
    }
    @Override
    public void update(Observable o, Object arg) 
    {
        Ball ball = (Ball)arg;
        System.out.println ("x= " + ball.thr.getName() + ball.x);
        repaint();
    }
    @Override
    public void paint (Graphics g) 
    {
        if (!LL.isEmpty())
        {
            for (Object LL1 : LL) 
            {
                Ball ball = (Ball) LL1;
                g.setColor(ball.col);
                g.drawOval(ball.x, ball.y, 20, 20);
            }
        }
    }
    public void itemStateChanged (ItemEvent iE) {}
    public void actionPerformed (ActionEvent aE) 
    {
        String str = aE.getActionCommand();
        if (str.equals ("OK"))
        {
            switch (c.getSelectedIndex()) 
            {
                case 0: col= Color.blue; break;
                case 1: col= Color.green; break;
                case 2: col= Color.red; break;
                case 3: col= Color.black; break;
                case 4: col= Color.yellow; break;
            }
            Ball ball= new Ball(col, this.tf.getText());
            LL.add(ball);
            ball.addObserver(this);
        }
        repaint();
    }
}
class Ball extends Observable implements Runnable 
{
    Thread thr;
    private boolean xplus;
    private boolean yplus;
    int x; int y;
    Color col;
    public Ball (Color col, String text) 
    {
        xplus = true; yplus = true;
        x = 0; y = 30;
        this.col = col;
        Test.count++;
        thr = new Thread(this, Test.count+":"+text+":");
        thr.start();
    }
    public void run()
    {
        while (true)
        {
            if(x==475) xplus = false;
            if(x==-1) xplus = true;
            if(y==175) yplus = false;
            if(y==29) yplus = true;
            if(xplus) x++; else x--;
            if(yplus) y++; else y--;
            setChanged();
            notifyObservers (this);
            try
            {
                Thread.sleep (10);
            }
            catch (InterruptedException e){}
        }
    }
}
class WindowAdapter2 extends WindowAdapter 
{
    public void windowClosing (WindowEvent wE) {System.exit (0);}
}