from methods import *
from numpy import linspace, exp, sqrt
from math import pi
import plotly.express as px
from PIL import Image

# Краевые условия
x0 = 0
y0 = 1
x1 = 1
y1 = 3

# Количество отрезков и шаг по x
#N = 10
N = 100
step = (x1 - x0) / (N)

# Массив x
x = linspace(x0, x1, N + 1)

# Функция генерации якобиана для уравнения y'' - y^3 = x^2, при замене второй производной по разностной схеме для всех точек x
# y - Массив текущих приближённых значений 
def jacobian(*y):
    N = len(y)
    res = []
    res.append([1] + [0] * (N - 1))
    for i in range(1, N - 1):
        res.append([0] * (i - 1) + [1 / step**2] + [-2/step**2 - 3 * y[i]**2]  + [1/step**2] + [0] * (N - i - 2))
    res.append([0] * (N - 1) + [1])
    return res

# Функция для генерации n - ой функции в системе нелинейных уравнений при разложении по разностной схеме.
def f(n):
    if n == 0:
        def resf(*y):
            return y[0] - y0
    elif n == N:
        def resf(*y):
            return y[n] - y1
    else:
        def resf(*y):
            return (y[n - 1] + -2 * y[n] + y[n + 1]) / step**2 - y[n]**3 - x[n]**2
    return resf

funcs = [f(i) for i in range(N + 1)]

def starty(x):
    return 2 * x + 1 # Удовлетворяет краевым условиям

# Начальное приближение y
y = [starty(xp) for xp in x]

# res - Найденное методом ньютона значение
res, iters = NewtonSystem(jacobian, funcs, y, maxIter=30, epsilon=1e-15)
print(f"Начальное приближение y[-2]: {y[-2]}")
print(f"Найденный y[-2]: {res[-2]}") # Значение функции в предпоследней точке
print(f"Число итераций: {iters}")
fig = px.line(x=x, y=res)

fig.write_image("plot2.png")
img = Image.open("plot2.png")
fig.show()
#Начальное приближение y[-2]: 2.8
#Найденный y[-2]: 2.46895720610051
#Число итераций: 6


