import tkinter

window = tkinter.Tk()
# Модель
counter = tkinter.IntVar()
counter.set(0)


# Два контроллера
def click_up():
    counter.set(counter.get() + 1)


def click_down():
    counter.set(counter.get() - 1)


# Вид
frame = tkinter.Frame(window)
frame.pack()
button = tkinter.Button(frame, text="Up", command=click_up)
button.pack()
button = tkinter.Button(frame, text="Down", command=click_down)
button.pack()
label = tkinter.Label(frame, textvariable=counter)
label.pack()
window.mainloop()
