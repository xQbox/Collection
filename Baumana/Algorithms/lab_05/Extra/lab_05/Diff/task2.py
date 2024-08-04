from methods import *
from numpy import linspace, exp, sqrt
from math import pi
import plotly.express as px
from PIL import Image

def Laplas(x, integralCount=10, integralMethod=SympsonIntegral):
    # Функцию, которую будем интегрировать
    def underIntegral(x):
        return exp(-x ** 2 / 2)
    
    # генерируем четное количество отрезков разбиения для метода Симсона(Костеса)
    intx = linspace(0, x, integralCount)
    
    # вернуть посчитанный приближенно интеграл
    return 2 / sqrt(2 * pi) * integralMethod(intx, underIntegral)


x = linspace(-5, 5, 100)
y = [Laplas(i) for i in x]

y_pred = linspace(-0.99, 0.999999, 50)
# По значению y найти x на функции Лапласа с помощью метода половинного деления
x_pred = [HalfDivision(Laplas, y, min(x), max(x), maxIter=30, epsilon=1e-8)[0] for y in y_pred]

# print(y_pred)
# print(x_pred)
fig = px.line(x=x, y=y)


fig.add_scatter(x=x_pred, y=y_pred, mode='markers', name='HalfDivision')

# print(HalfDivision(Laplas, -1, -5, 5))

fig.write_image("plot.png")
# img = Image.open("plot.png")
fig.show()

# (4.990234375, 10)
x_answer = HalfDivision(Laplas, 0.9926, min(x), max(x), maxIter=30, epsilon=1e-8)
print(f"Laplas({x_answer[0]}) = 0.9926")


