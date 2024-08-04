
# def polinom(x : float, n : int) -> np.array:
#     """
#     Функция считает полином Лежандра заданной степени
#     Принимает :
#         x - значение аргумента 
#         n - степень Полинома
#     Возвращает :
#         result - массив numpy значений полинома Лежандра 
#     """
#     result = np.array(n + 1)
#     if n == 0:
#         result[0] = 1
#     elif n == 1:
#         result[0] = 0
#         result[1] = x
#     else: 
#         result[0] = 1
#         result[1] = x
#         for i in range(1, n):
#             result[i + 1] = (2 * n + 1) / (n + 1) * result[i]  * x - (n) / (n + 1) * result[i - 1]

#     return result    


# def derivative(x : float, N : int) ->  np.array:
#     """
#     Функция считает производную полинома лежандра
#     Принимает : 
#         x - значение аргумента
#         N - степень полинома 
#     Возвращает :
#         result - массив numpy значений производных полинома Лежандра 
#     """
#     data = polinom(x, N)
    
#     if N == 0:
#         data[0] = 0
#     elif N == 1:
#         data[0] = 0
#         data[1] = 1
#     else: 
#         for i in range(1, N):
#             data[i] = (i / (1 - x**2) * data[i - 1] - x * data[i]) 

#     return data




# def legendre_polinom_roots(N : int) -> np.array:
#     """Функция  ищет корни полинома Лежандра для заданной степени полинома"""


# # Количество итераций для поиска полинома Лежандра
#     S = 40

#     res = np.zeros(N // 2 + 1)

#     x = np.zeros(S) 



# ### Алгоритм поиска одного корня (Метод Ньютона)        
#     for s in range(N // 2 + 1):

# # Начальное приближение для каждого корня
#         x0 = m.cos(m.pi * (4 * (s + 1) - 1) / (4 * N + 2))
#         x[0] = x0
#         k = 0
#         for i in range(S - 1):
#             x[i + 1] = x[i] - (polinom(x[i], N) / derivative(x[i], N))
#             k = i
        
#         p = 1 / (1 - ((x[k + 1] - x[k]) / (x[k] - x[k - 1])))
#         print("найдем корень х [{0}] - {1}, с кратность {2}".format(s, x[k], p))

#         res = res / pow(x -  x[k + 1], p)  
    
#     return res


