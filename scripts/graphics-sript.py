# -*- coding: UTF-8 -*-

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import mlab

# Значения по оси X

X = []

lower_bound = 1
upper_bound = 1000000
i = lower_bound

while(i <= upper_bound):
    X.append(i)
    i += 10000
      
# Набор значений по оси Y

Y_B = []
Y_Q = []

f_b = open('log_bucket_sort.txt', 'r')
for line in f_b:
	Y_B.append(float(line))

f_b.close()

f_q = open('log_std_sort.txt', 'r')
for line in f_q:
	Y_Q.append(float(line))

f_q.close()
# Строим диаграмму
# Задаем исходные данные для каждой линии диаграммы, внешний вид линий и маркеров.
# Функция plot() возвращает кортеж ссылок на объекты класса matplotlib.lines.Line2D


line_b, line_q = plt.plot(X, Y_B, 'b-', X, Y_Q, 'r-' )


# Задаем интервалы значений по осям X и Y

plt.axis([0.0, 1000000.0, 0.0, 1000.0])

# Задаем заголовок диаграммы

plt.title(u'Зависимость времени работы алгоритма от кол-ва эллементов')

# Задаем подписи к осям X и Y

plt.xlabel(u'Кол-во эллементов ')
plt.ylabel(u'Время, ms ')

# Задаем исходные данные для легенды и ее размещение

plt.legend((line_b, line_q), (u'Bucket-Sort', u'STL-Sort'), loc = 'best')

# Включаем сетку

plt.grid()

# Сохраняем построенную диаграмму в файл

# Задаем имя файла и его тип

plt.savefig('graphic.png', format = 'png')
