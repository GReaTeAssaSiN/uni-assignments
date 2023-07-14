from tkinter import *

# Кнопки
root = Tk()
but = Button(root,
             text="Это кнопка",  # надпись на кнопке
             width=30, height=5,  # ширина и высота
             bg="white", fg="blue")  # цвет фона и надписи
but.pack()

# Метки
lab = Label(root, text="Это метка! \n Из двух строк.", font="Arial 18")
lab.pack()

# Однострочное текстовое поле
ent = Entry(root, width=20, bd=3)
ent.pack()

# Многострочное текстовое поле
tex = Text(root, width=40,
           font="Verdana 12",
           wrap=WORD)
tex.pack()

# Радиокнопки(переключатели)
var = IntVar()
var.set(1)
rad0 = Radiobutton(root, text="Первая",
                   variable=var, value=0)
rad1 = Radiobutton(root, text="Вторая",
                   variable=var, value=1)
rad2 = Radiobutton(root, text="Третья",
                   variable=var, value=2)

# Флажки
c1 = IntVar()
c2 = IntVar()
che1 = Checkbutton(root, text="Первый флажок",
                   variable=c1, onvalue=1, offvalue=0)
che2 = Checkbutton(root, text="Второй флажок",
                   variable=c2, onvalue=2, offvalue=0)

# Списки
r = ['Linux', 'Python', 'Tk', 'Tkinter']
lis = Listbox(root, selectmode=SINGLE, height=4)
for i in r:
    lis.insert(END, i)

# Frame(рамка)
fra1 = Frame(root, width=500, height=100, bg="darkred")
fra2 = Frame(root, width=300, height=200, bg="green", bd=20)
fra3 = Frame(root, width=500, height=150, bg="darkblue")
fra1.pack()
fra2.pack()
fra3.pack()

# Scale(шкала)
sca1 = Scale(fra3, orient=HORIZONTAL, length=300,
             from_=0, to=100, tickinterval=10, resolution=5)
sca2 = Scale(root, orient=VERTICAL, length=400,
             from_=1, to=2, tickinterval=0.1, resolution=0.1)

# Scrollbar(полоса прокрутки)
root = Tk()
tx = Text(root, width=40, height=3, font='14')
scr = Scrollbar(root, command=tx.yview)
tx.configure(yscrollcommand=scr.set)

tx.grid(row=0, column=0)
scr.grid(row=0, column=1)

# Toplevel (окно верхнего уровня)
win = Toplevel(root, relief=SUNKEN, bd=10, bg="lightblue")
win.title("Дочернее окно")
win.minsize(width=400, height=200)

root.mainloop()
