#! /usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np

from array import *

import math


def g(x,y):
	return math.exp(-(x-0.5)**2-(y-0.5)**2)
	#return x**2+y**2
	#return x+y
	
	

def tab (g,n):
	
	h=1.0/(n-1)	

	ftab=np.array([0.0 for j in range(n*n)])

#y0=np.array([1.0,2.0,3.0])

	k=-1

	for i in range(0,n):
			
		for j in range(0,n):
			
			y=i*h
			
			x=j*h
			k=k+1
			ftab[k]=g(x,y)
	return ftab

#матрица xym(n) -- координаты точек по их последовательным номерам	в сетке
def xym(n):
	xy = np.array([[0.0 for j in range(n*n)] for i in range(2)])
	k = -1
	h = 1.0/ (n - 1)
	for i in range(0, n):	
		for j in range(0, n):
		
			y = i * h
			
			x = j * h 
			k = k + 1 
			xy[0, k] = x
			xy[1, k] = y
	return xy


def gauss_method(a,b):
	
	n = len(b)
	
	for k in range(0,n-1):

		for i in range(k+1,n):

			if a[i,k] != 0.0:

				lam = a [i,k]/a[k,k]

		a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n]

		b[i] = b[i] - lam*b[k]

	for k in range(n-1,-1,-1):
		
		#if a[k,k] != 0.0:
		b[k] = (b[k] - np.dot(a[k,k+1:n],b[k+1:n]))/a[k,k]

	return b		


def fim (m,x,y,n,q):
	xy = xym(n)
	#return math.log((x-xy[0,m])**2+(y-xy[1,m])**2+0.1)
	return math.log(math.sqrt((x-xy[0,m])**2+(y-xy[1,m])**2)+q)
	
def interpol(n):
    M = n * n
    c = np.zeros(M)
    b = np.zeros(M)
    a = np.zeros((M, M))

	# c=np.array([0.0 for j in range(M)])
	# b=np.array([0.0 for j in range(M)])
	# a=np.array([[0.0 for j in range(M)] for i in range(M)])

    b = tab(g, n)
    xy = xym(n)
    for i in range(0, M):
            
        for j in range(0, M):
            a[i, j] = fim(i, xy[0,j], xy[1,j], n, q)

    c = gauss_method(a, b)

    return c

#Вычисление полинома Лежандра
def pol(n, x) :
	p0 = 1
	p1 = x
	if n == 0:
		return p0
	if n == 1:
		return p1
	#for k in range(1,n-1):
	for k in range(1, n):
		pn = x * (2 * k + 1) / (k + 1) * p1 - p0 * k / (k + 1)
		p0 = p1
		p1 = pn
	return p1
    	

#Вычисление производной полинома Лежандра
def derpol(n, x):
	return n * (pol(n - 1, x) - x * pol(n, x)) / (1 - x * x)


#Вычисление k-го корня полинома Лежандра
def xkpol(n, k):
    pi = 3.1415926536
    eps = 1.0e-09
    x0 = math.cos(pi * (4 * k - 1) / (4 * n + 2))
    e=1
    while e > eps :
        x = x0 - pol(n, x0) / derpol(n, x0)
        e = abs(x - x0)
        x0 = x
    return x
    
#Вычисление весовых множителей в квадратуре Гаусса
def ank(n, k):

    x = xkpol(n, k)
    y = derpol(n, x)
    return  2 / ((1 - x * x) * y * y)
    



def Jm(m, n, ng, ns):
    s = 0
    for k in range(1,ng+1):
        xk = xkpol(ng, k)  # xk - корни полинома Лежандра
        x = 0.5 * (xk + 1.0)
        Ak = ank(ng, k) * 0.5	
    #ank(n, k) - весовые множители  квадратуры Гаусса			
    #Метод Симсона
        h = 0.5 * (1 - x) / ns
        ss = fim (m, x, 0, n, q) + fim(m, x, 1 - x, n, q)
        for l in range(1, ns + 1):
            y = h * (2 * l - 1)
            ss = ss + 4 * fim(m, x, y, n, q)
        for l in range(1, ns):
            y = h * 2 * l
            ss = ss + 2 * fim(m, x, y, n, q)
        #s=s+ss*0.5*(1-x)*Ak
        s = s + Ak * ss * h / 3

    return s
	
#Численный рассчет с аналитически заданной функцией	
def Jmg(m, n, ng, ns):
	s=0
	for k in range(1, ng + 1):
		xk = xkpol(ng, k)  # xk - корни полинома Лежандра
		x = 0.5*(xk + 1.0)
		Ak = ank(ng, k) * 0.5	
#ank(n, k) - весовые множители  квадратуры Гаусса			
#Метод Симсона
		h = 0.5 * (1 - x) / ns
		ss = g(x, 0) + g(x, 1 - x)
		for l in range(1, ns + 1):
			y = h * (2 * l - 1)
			ss = ss + 4 * g(x, y)
		for l in range(1, ns):
			y = h * 2 * l
			ss = ss + 2 * g(x, y)
		#s=s+ss*0.5*(1-x)*Ak/30
		s = s + Ak * ss * h / 3
	return s
	
# Печать таблицы
def Tabliza(m,n,a):
	print ("ng/ns",end=" ")
	for j in range(0,n):
			print ("{:d}".format(j+3), "    ", end=" ")
	print()
	for i in range(0,m):
		print ("{:2d}".format(i+3), end=" ")
	
		for j in range(0,n):
			print ("{:06.4f}".format(a[i,j]), end=" ")
		print() 
	return
	


if __name__ == "__main__":
    q = 0.1
    #Заполнение сеточной таблицы n*n
    n = 3
    eps = 0.00001
    ftab = np.array([0.0 for j in range(n*n)])

    h = 1.0 / (n - 1)	
    ftab = tab(g, n)

    #Заполнение матрицы xym(n) -- координат точек по их последовательным номерам

    xy=np.array([[0.0 for j in range(n*n)] for i in range(2)])

    xy=xym(n)

    print ("Сеточная функция f(x,y)")
    #print("g=",ftab)
    k=-1
    for i in range(0, n):
    #	print ("{:06.4f}".format(xy[0,i]),end=" ")
        for j in range(0, n):
            k = k + 1
            print ("{:06.4f}".format(ftab[k]),end=" ")
        print() 



    #print("xy=",xy)
    print()
    print()
    # Вызов процедуры интерполирования
    c=interpol(n)
    print("Коэффициенты двумерной интерполяции")
    print(c)
    print()
    print()
    Mm = n*n
    ng = 10 #количество узлов в методе Гаусса
    ns = 10 #количество узлов в методе Симпсона

    Sij = np.array([[0.0 for j in range(ns - 2)] for i in range(ng - 2)])
    print("Результаты расчетов:")
    for i in range(3, ng + 1):
        for j in range(3, ns + 1):
            S=0
            for m in range(0, Mm):
                S= S + c[m] * Jm(m, n, i, j)	
            #print (i,j,"{:06.4f}".format(S))
            Sij[i - 3, j - 3] = S
    Tabliza(ng - 2, ns - 2, Sij)
    print()
    print()
    print ("аналитический расчет: S=","{:06.4f}".format(Jmg(m,n,ng,ns)))
