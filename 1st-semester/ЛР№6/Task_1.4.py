from tkinter import *

tk = Tk()

# Рисунок 300x300 пикселей, фон белый
c = Canvas(tk, width=300, height=300, bg="white")
c.create_arc((5, 5, 50, 50), style=PIESLICE)  # Сектор "Кусок пирога"
c.create_arc((55, 5, 1000, 50), style=CHORD)  # Дуга
c.create_arc((105, 5, 150, 50), style=PIESLICE,  # Сегмент
             start=0, extent=150, fill="blue")  # от 0 до 150 градусов
# Ломаная со стрелкой на конце
c.create_line([(5, 55), (55, 55), (30, 95)], arrow=LAST)
# Кривая (сглаженная ломаная)
c.create_line([(105, 55), (155, 55), (130, 95)], smooth=1)
# Многоугольник зелёного цвета
c.create_polygon([(205, 55), (255, 55), (230, 95)], fill="green")
# Овал
c.create_oval((5, 105, 50, 120), )
# Прямоугольник красного цвета с большой серой границей
c.create_rectangle((105, 105, 150, 130), fill="red", outline="grey", width="5")
# Текст
c.create_text((5, 205), text="Hello", anchor="nw")
# Эта точка визуально обозначает угол привязки
c.create_oval((5, 205, 6, 206), outline="red")
# Текст с заданным выравниванием
c.create_text((105, 205), text="Hello,\nmy friend!", justify=LEFT, anchor="c")
c.create_oval((105, 205, 106, 206), outline="red")
# Еще один вариант
c.create_text((205, 205), text="Hello,\nmy friend!", justify=CENTER, anchor="se")
c.create_oval((205, 205, 206, 206), outline="red")
c.pack()
tk.mainloop()
