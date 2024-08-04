import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from pathlib import Path


def phi(x, k):
    return x ** k

def Integration(x : list , u : list, p : list) -> float:
    N = len(x) - 1
    result = 0.0
    for i in range(1, N + 1):
        h = x[i] - x[i - 1]
        result += ((u[i] - u[i - 1]) / 2) * h * p[i]
    return result  

def Approximation(x : list, u : list, z : list, p : list, K : int, a : list):
    N = len(x) - 1; A = np.zeros((K + 1, K + 1)); B = np.zeros((K + 1, 1))
    for m in range(K + 1):
        for k in range(K + 1):
            A[m, k] = Integration(x, phi(x, m) * phi(x, k), p)
        B[m, 0] = Integration(x, phi(x, m), p)
    C = np.linalg.solve(A, B)
    result = 0.0
    for i in range(K + 1):
        result += C[i,0] * phi(a, i)
    return result 


if __name__ == "__main__":

    path = Path('data2.csv').absolute()

    df = pd.read_csv(filepath_or_buffer=path, sep=' ')
    headers = df.columns.to_list()

    x_values = df['x']
    y_values = df['y']
    z_values = df['z']
    p_values = df['p']
    x = np.linspace(min(x_values), max(x_values), 100)
    K = int(input())
    u = Approximation(x_values, y_values, z_values, p_values, K, x)
    print(u)
