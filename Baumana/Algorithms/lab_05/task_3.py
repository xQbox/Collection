##### Лабораторная работа 5 Задание 3
##### Численное вычисление краевой задачи для ОДУ 2-ого порядка

import numpy as np
import pandas as pn
import matplotlib.pyplot as plt

### Заданная функция y'' - y ^ 3 = x ^ 2



# Метод прогонки для трехдиагональной матрицы
def fast_gauss(y : np.array, di : np.array, y_left : float, y_right : float) -> np.array:
    N = len(di)
    result = np.zeros(N)

    Epsilon = np.zeros(N + 1); Teta = np.zeros(N + 1)

# Коэффициенты Диагональ    
    b = np.zeros(N)

    for i in range(N):
        b[i] = y[i, i]
    
    
# Коэффициенты под диагональю
    a = np.zeros(N)
    
    for i in range(1, N):
        a[i] = y[i, i - 1]

# Начальные условия
    a[0] = y_left

# Коэффициенты над диагональю
    c = np.zeros(N)
    for i in range(N - 1):
        c[i] = y[i, i + 1]
    
# Начальное условие
    c[N - 1] = y_right

### Инициализация первых элементов Eps_1 и T_1
    Epsilon[1] = c[0] / (b[0]) 
    Teta[1] =  ((- di[0]) / (b[0]))  

    for i in range(1, N):
        Epsilon[i + 1] = c[i] / (b[i] - (Epsilon[i] * a[i]))
        Teta[i + 1] = ((a[i] * Teta[i]) - di[i]) / (b[i] - Epsilon[i] * a[i])  

    result[N - 1] = Teta[N]

    # print(Epsilon[N])

    for i in range(N - 2, -1, -1):
        result[i] = Epsilon[i + 1] * result[i + 1] + Teta[i + 1]


    return result
# # условие (a1 = 0)
#     # Epsilon[0] = y[0, 1] / (y[0, 0] - y_left)
#     # Teta[0] = (y_left - di[0]) / (y[0, 0] - y_left)

# # Инициализируем первую строчку (Учитывая краевые условия задачи)
#     Epsilon[1] = (y[0, 1] / y[0, 0])
#     Teta[1] = (-di[0] / y[0, 0])


# # Используем прямой ход для вычисления всех коэффициентов матрицы с 1 по N - 2 
# # (1 строку и последнюю инициализируем самостоятельно) 
#     for i in range(1, N - 2):
#         Epsilon[i + 1] = (y[i, i + 1] / (y[i, i] - (y[i, i - 1] * Epsilon[i])))
#         Teta[i + 1] = (((y[i, i - 1] * Teta[i]) - di[i]) / (y[i, i] - (y[i, i - 1] * Epsilon[i])))   

    
#     Epsilon[N - 1] = (y[N - 2, N - 1] / (y[N - 2, N - 2] - (y[N - 2, N - 3] * Epsilon[N - 2])))
#     Teta[N - 1] = (((y[N - 2, N - 3] * Teta[N - 2]) - di[N - 2]) / (y[N - 2, N - 2] - (y[N - 2, N - 3] * Epsilon[N - 2])))   

# # Инициализируем последнюю строчку (условие C_n = 0)
#     Epsilon[N] = 0
#     Teta[N] = (y[N - 1, N - 2] * Teta[N - 1] - di[N - 1]) / (y[N - 1, N - 1])   

# # С учетом краевых условий заполняем первые значения резульата при обратном ходе
#     # result[N - 1] = Epsilon[N - 1] + Teta[N - 1]

#     result[N - 1] =  Teta[N]

#     for i in range(N - 2, -1, -1):
#         result[i] = Epsilon[i + 1] * result[i + 1] + Teta[i + 1]
    
#     print(result)
#     return result



def funcion(y : list, N : int, h : float, y_left : float, y_right : float) -> np.array:
    f = np.zeros(N - 1)
    
    f[0] = (y[1] - 2 * y[0] + y_left) / (h**2) - (y[0]**3) 
    
    x = 0

    for i in range(1, N - 2):
        x = i * h
        f[i] = (y[i + 1] - 2 * y[i] + y[i - 1]) / (h**2) - (y[i]**3) - (x**2)

    f[N - 2] =  (y_right - 2 * y[N - 2] + y[N - 3]) / (h**2) - (y[N - 2]**3) - 1

    return f


# Преобразуем функцию с помощью метода конечных разностей 
# Заменяем y'' на y[n - 1] - 2 * y[n] + y[n + 1] / h ^ 2
# (y[n - 1] - 2 * y[n] + y[n + 1]) / (h**2) - y[n]**3 = x[n]**2
def jakobi(y: np.array, N : int, h: float, y_0: float, y_n: float) -> np.array:

    jakobi_matrix = np.zeros((N - 1, N - 1))
    
### Задать вопрос Градову по поводу решения системы уравнения вида
### y'' = F(x, y) - где F(x, y) нелинейная по y
# Тогда след реализация:

    jakobi_matrix[0, 0] = (-2.0 / (h**2)) - 3 * (y[0]**2)
    jakobi_matrix[N - 2, N - 2] = (-2.0 / (h**2)) - 3 * (y[N - 2]**2)
    
    for i in range(1, N - 1):
        jakobi_matrix[i, i - 1] = 1.0 / (h**2)
    
    for i in range(1, N - 2):
        jakobi_matrix[i, i] = -2.0 / (h**2) - 3 * (y[i] ** 2)
    
    for i in range(N - 2):
        jakobi_matrix[i, i + 1] = 1.0 / (h**2)     
    # print(jakobi_matrix)

    return jakobi_matrix

# Для решения нелинейной системы будем использовать метод Ньютона
def newtonMethod() -> np.array:
    a = 0.; b = 1; y_left = 1; y_right = 3

# Начальные значения
# При S > 10 разница при поиске корня системы меньше чем поддерживает Python3 (доделать с заданной погрешностью) 
    S = 10
# Количестов точек для  разбиения отрезка b - a
    N = 10

# u - матрица решений ; y - матрица промежуточных значений ; 
    u = np.zeros((S + 1, N + 1)); y = np.zeros((S + 1, N - 1))


### Инициализация сетки (от а до b)
# x - матрица ( массив ) равномерной сетки
    x = np.linspace(a, b, N + 1)
# Шаг отрезка
    h = (b - a) / N 


# Начальное приближение -> функция удовлетворяющая начальным краевым условиям
# y(0) = 1.0; y(1) = 3.0
    for i in range(N - 1):
        y[0, i] = 1.0 + (2.0 * (i + 1) * h)   


    for s in range(S):
        y[s + 1] = y[s] - np.linalg.solve(jakobi(y[s], N, h, y_left, y_right), funcion(y[s], N, h, y_left, y_right))     
        
        # gauss_method(jakobi(y[s], N, h, y_left, y_right), funcion(y[s], N, h, y_left, y_right))
         
        # - np.linalg.solve(jakobi(y[s], N, h, y_left, y_right), funcion(y[s], N, h, y_left, y_right))     
        # - fast_gauss((jakobi(y[s], N, h, y_left, y_right)), (funcion(y[s], x[0], N, h, y_left, y_right)), y_left, y_right)
        # gauss_method(jakobi(y[s], N, h, y_left, y_right), funcion(y[s], x[0], N, h, y_left, y_right))
        
        u[s + 1, 0] = y_left
        u[s + 1, 1:N] = y[s + 1,:]
        u[s + 1, N] = y_right

    return u

# def gauss_method(a,b):
	
# 	n = len(b)
	
# 	for k in range(0,n-1):

# 		for i in range(k+1,n):

# 			if a[i,k] != 0.0:

# 				lam = a [i,k]/a[k,k]

# 		a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n]

# 		b[i] = b[i] - lam*b[k]

# 	for k in range(n-1,-1,-1):

# 		b[k] = (b[k] - np.dot(a[k,k+1:n],b[k+1:n]))/a[k,k]

# 	return b

def gauss_method(a,b): 
    n = len(b) 

    for k in range(0,n-1): 
        for i in range(k+1,n):
            if a[i,k] != 0.0:
                lam = a [i,k]/a[k,k] 

        a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n] 
        b[i] = b[i] - lam*b[k] 

    for k in range(n-1,-1,-1):
        b[k] = (b[k] - np.dot(a[k,k+1:n],b[k+1:n]))/a[k,k] 

    return b



if __name__ == "__main__":
    y = newtonMethod()
    # x = np.linspace(0, 1, 99)

    print(y[9])
    plt.plot(y[9])
    plt.xlabel('x*100')
    plt.ylabel('y')
    # Показываем график
    plt.show()

    # for i in range(10):
        # print("Step [", i,"] : \n")
        # for k in range(99):
        #     print(y[i, k])
        # print("\n")

        # plt.plot(x, y[i], '-r', label='y = x*100')
        # plt.xlabel('Ось х')
        # plt.ylabel('Ось y')
        
        # # Добавляем легенду
        # plt.legend(loc='upper left')

        # # Показываем график
        # plt.show()
    # Отрисовка решения 59   style.use('dark_background') 60   61   fig1 = figure() 62   ax1 = axes(xlim=(a,b), ylim=(-6,8.)) 63   ax1.set_xlabel('x'); ax1.set_ylabel('y') 64   ax1.plot(x,u[S],'-ow',markersize=5)
