f = open('in.txt', 'r')
text = f.read()

print('Введите слово, которое нужно заменить в тексте:')
word_search = input()
print('Введите слово, на которое нужно заменить введённое слово в тексте:')
word_replace = input()
text = text.replace(word_search, word_replace)

f.close()

f = open('out.txt', 'w')
f.write(text)
f.close()
