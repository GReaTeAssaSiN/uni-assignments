number = int(input("Введите трехзначное число: "))
print("Получено число ", number//10 % 10*100 + number % 10*10 + number//100)
