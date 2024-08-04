import math as m
import numpy as np
# import sympy as sm

# Вычисление полинома Лежандра
def polinom(x : float, n : int):
    """
    Функция считает полином Лежандра заданной степени
    Принимает :
        x - значение аргумента 
        n - степень Полинома
    """
    if n == 0:
        return 1
    elif n == 1:
        return x
    else: 
        result = np.zeros(n + 1)
        result[0] = 1
        result[1] = x
        for i in range(2, n):
            result[i] = ((2 * n - 1) / (n)) * result[i - 1] * x - ((n - 1) / (n)) * result[i - 1]

        return result[n]    

def derivative(x : float, N : int):
    """
    Функция считает производную полинома лежандра
    Принимает : 
        x - значение аргумента
        N - степень полинома 
    """
    data = np.zeros(N)
    for i in range(N):
        data[i] = polinom(x, i)
    
    if N == 0:
        return 0
    elif N == 1:
        return (N  * (-(x**2))) / (1 - x**2)
    else: 
        return (N  * (data[N - 2] - x * data[N - 1])) / (1 - x**2)

    
def legendre_polinom_roots(N : int) -> np.array:
    """
    Функция  ищет корни полинома Лежандра для заданной степени полинома
    """

# Максимальное количество итераций для поиска полинома Лежандра
    S = 40

    res = np.zeros((N, 2))

    x = np.zeros(S + 1) 

    

# Точность вычисления метода Ньютона
    eps = 0.000001
    for s in range(N):

### Алгоритм поиска одного корня (Метод Ньютона)        

# Начальное приближение для каждого корня (Википедия) погрешность около 0.01 на каждый найденный корень
        x0 = m.cos(m.pi * (4 * (s + 1) - 1) / (4 * N + 2))
        x[0] = x0
        k = 0
        for i in range(S - 1):
            x[i + 1] = x[i] - (polinom(x[i], N) / derivative(x[i], N))
          
            if i >= 1 and abs((x[i + 1] - x[i]) / (1 - (x[i + 1] - x[i]) / (x[i] - x[i - 1]))) < eps:
                k = i + 1
                break
        # print("Приближенные решения:\n", x)
# Поиск кратности корня  
        p = (1 / (1 - ((x[k] - x[k - 1]) / (x[k - 1] - x[k - 2]))))
        # print("найден корень х [{0}] = {1:.5f}, с кратность {2}".format((s + 1), x[k + 1], p))

        res[s, 0] = x[k]
        res[s, 1] = p
    
    return res


def take_two_dimensional_integral(N_x : int, M_y : int) -> float:
    """Функция принимает количество точек для интегрирования по х и у"""    
    result = np.array((N_x, M_y))
# Считаем последовательно интеграл от функции двух переменных. Методом последовательного интегрирования.
    for i in range(N_x):
        for k in range(M_y):
            result[i, k] = el_quadrado_de_gauss(result[i, k])
        


def legandra(t, N):
    temp1 = 1
    temp2 = t
    
    for i in range(2, N + 1):
        cur = 1 / i * ((2 * i - 1) * t * temp2 - (i - 1) * temp1)
        temp2, temp1 = cur, temp2
    return cur

def dichotomy_method(a, b):
    return bisect(legandra, a, b, xtol = EPS)

def legandra_roots(N):
    # ищем отрезки с корнями
    h = 2 / N
    count_root = 0
    while (count_root != N):
        cur = -1
        count_root = 0
        SEGMENT = []
        while (cur < 1):
            if legandra(cur, N) * legandra(cur + h, N) < 0:
                SEGMENT.append([cur, cur + h])
                count_root += 1
            cur += h
        h /= 2
    
    return SEGMENT
    # ищем корни
    # ROOT = []
    # for seg in SEGMENT:
    #     ROOT.append(dichotomy_method(seg[0], seg[1]))

    # return ROOT            
# 



if __name__ == "__main__":

    Readed_data = int(input())    

# Поиск полинома Лежандра
    value = legendre_polinom_roots(Readed_data)

    for i in range(Readed_data):
        print("Найденный корень x уравнения[{0}] = {1:.9f}, кратности {2}".format((i + 1), value[i, 0], value[i, 1]))

    for i in range(Readed_data):
   
        print(legandra_roots(Readed_data))


