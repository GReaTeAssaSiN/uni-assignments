from tkinter import *


# Работа светофора
class Frame(Tk):
    def __init__(self):
        # Задание начального состояния светофора
        self.state = 0
        super().__init__()
        self.title('Traffic Lights')
        self.c = c = Canvas(self, width=70, height=190, bg="black")
        self.r = c.create_oval(10, 10, 60, 60, fill="#ff0000")
        self.y = c.create_oval(10, 70, 60, 120, fill="#808000")
        self.g = c.create_oval(10, 130, 60, 180, fill="#008000")
        c.pack()
        # Обновление состояния светофора
        self.after(3000, self.update_lights)

    # Изменение светофора в зависимости от состояния
    def update_lights(self):
        if self.state == 0:
            self.state = 1
            self.c.itemconfigure(self.r, fill='#800000')
            self.c.itemconfigure(self.y, fill='#ffff00')
            self.after(1000, self.update_lights)
        elif self.state == 1:
            self.state = 2
            self.c.itemconfigure(self.y, fill='#808000')
            self.c.itemconfigure(self.g, fill='#00ff00')
            self.after(2000, self.update_lights)
        elif self.state == 2:
            self.state = 3
            self.c.itemconfigure(self.g, fill='#008000')
            self.c.itemconfigure(self.y, fill='#ffff00')
            self.after(1000, self.update_lights)
        else:
            self.state = 0
            self.c.itemconfigure(self.r, fill='#ff0000')
            self.c.itemconfigure(self.y, fill='#808000')
            self.after(3000, self.update_lights)


# Вывод
root = Frame()

root.mainloop()
