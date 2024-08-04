from methods import *
from numpy import linspace, exp, sqrt
from math import pi
# import plotly.express as px

# Задание 1: Система нелинейных уравнений

def f1(x, y, z):
    return x**2 + y**2 + z**2 - 1

def f2(x, y, z):
    return 2 * x**2 + y**2 - 4 * z

def f3(x, y, z):
    return 3 * x**2 - 4 * y + z**2

# производные функций системы
def jacobian(x, y, z):
    return [
        [2 * x, 2 * y, 2 * z],
        [4 * x, 2 * y, -4],
        [6 * x, -4, 2 * z]
    ]

# начальное приближение
x0, y0, z0 = 100, 1, 20

res, iters = NewtonSystem(jacobian, [f1, f2, f3], [x0, y0, z0], maxIter=30, epsilon=1e-8)

xr, yr, zr = res

print("Система нелинейных уравнений:")
print("x**2 + y**2 + z**2 = 1")
print("2x**2 + y**2 - 4z = 0")
print("3x**2 - 4y + z**2 = 0\n")

print(f"Начальное приближение: ({x0}, {y0}, {z0})\n")
print(f"Решение системы уравнений: ({xr}, {yr}, {zr})")
print(f"Количество итераций: {iters}")
print("Значение при подстановке в систему:")
print(f"x**2 + y**2 + z**2 = {f1(xr, yr, zr) + 1}")
print(f"2x**2 + y**2 - 4z = {f2(xr, yr, zr)}")
print(f"3x**2 - 4y + z**2 = {f3(xr, yr, zr)}")


