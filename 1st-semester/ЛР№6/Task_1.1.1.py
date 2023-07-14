from tkinter import *


def printer(event):
    print("Как всегда очередной 'Hello world!'")


root = Tk()
but = Button(root)
but["text"] = "Печать"
but.bind("<Button-1>", printer)

but.pack()
root.mainloop()
