package com.mycompany.test;

class Dan {
    public int xSup, xSub;
    public boolean b;
    public Dan (int Xsub, int Xsup, boolean B) {xSub= Xsub; xSup= Xsup; b= B;}
}

class SuperClass {
    int x;
    private boolean b;
    public SuperClass (int X, boolean B) {x= X; b= B;}
    public boolean getB () {return b;}
    /*Для второй части первого примера*/
    //Функция FuncSup() базового класса.
    void FuncSup(){};
}

class SubClass extends SuperClass {// Подкласс (sub class)
    int x;
    public SubClass (int Xsup, int Xsub, boolean B) // Конструктор
    {
        super (Xsub, B); // Вызов конструктора базового класса
        x= Xsup;
    }
    // Получить объект типа Dan с данными
    public Dan get () {return new Dan(x, super.x, super.getB());}
    
    /*Для второй части первого примера*/
    //Иллюстрация передачи данных через параметр-ссылку.
    public void get(Dan d) {d.xSub = x; d.xSup = super.x; d.b = super.getB();}
    
    //Переопределение базовой функции FuncSup() класса SuperClass в классе SubClass дополнением вывода.
    void FuncSup() {super.FuncSup(); System.out.println("SubClass");}
}

class Test {
    public static void main (String[] args) {
        SuperClass supC= new SuperClass (5, true );// Создать объект суперкласса
        System.out.println ("supC.x= "+ supC.x + " supC.b= " + supC.getB());
        // Создать объект подкласса
        SubClass subC= new SubClass (55, 555, false );
        // Получить объект данных
        Dan d= subC.get();
        System.out.println ("subC.x= "+ d.xSub + " supC.x= "+ d.xSup + " subC.b= " + d.b);
        
        /*Для второй части первого примера*/
        Dan d1 = new Dan(0, 0, true);
        subC.get(d1);
        System.out.println("SubC.x= " + d1.xSub + " supC.x= " + d1.xSup + " subC.b= " + d1.b);
    }
}