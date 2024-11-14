# -*- coding: Windows-1251 -*-
import numpy as np
import matplotlib.pyplot as plt

############################################################
#                �������������� �������                    #
############################################################
# ���� I. ������� ��� ���������� ����������� ���� �� �������� ������, ������� ��������
def calculate_sums(xi, yi):
    xi_squared = xi ** 2
    yi_squared = yi ** 2
    xi_yi_product = xi * yi

    # ���������� ����
    sum_xi = np.sum(xi)
    sum_yi = np.sum(yi)
    sum_xi_squared = np.sum(xi_squared)
    sum_yi_squared = np.sum(yi_squared)
    sum_xi_yi = np.sum(xi_yi_product)

    return sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, xi_squared, yi_squared, xi_yi_product
# ���� I. ������� ��� ���������� ��������������� ������� � ������������� ���������
def calculate_coefficients(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, n):
    # ���������� ��������������� �������
    A = n * sum_xi_squared - sum_xi ** 2
    A0 = sum_yi * sum_xi_squared - sum_xi * sum_xi_yi
    A1 = n * sum_xi_yi - sum_xi * sum_yi
    B = n * sum_yi_squared - sum_yi ** 2
    B0 = sum_xi * sum_yi_squared - sum_yi * sum_xi_yi
    B1 = A1
    # ���������� �������������
    a0 = A0/A
    a1 = A1/A
    b0 = B0/B
    b1 = B1/B
    r1 = A1 / ((A * B) ** 0.5)
    r2 = B1 / ((A * B) ** 0.5)
    r = 0
    if r1!=r2:
        print("������! �������� ������������ ���������� r1 = A1 / sqrt(A * B) � r2 = A2 / sqrt(A * B) ������ ���� �����.")
        return None
    else:
        r = r1
    # ������� ����������� ������� � �������������
    return A, A0, A1, B, B0, B1, a0, a1, b0, b1, r
# ���� I. ������������� ������������ ����������
def interpret_correlation(r):
    if r == 0:
        return "�����������.", "��� �������� ����������� ����� �����������."
    elif 0 < r < 1:
        return "�������������, ������.", "� ����������� X ������������� Y."
    elif -1 < r < 0:
        return "�������������, ��������.", "� ����������� X ����������� Y, � ��������."
    elif r == 1:
        return "��������������, ������.", "������� �������� X ������ ������������� ���� �������� Y, � ����������� X ������������� Y."
    elif r == -1:
        return "��������������, ��������.", "������� �������� X ������ ������������� ���� �������� Y, � ����������� X ����������� Y, � ��������."
# ���� I. ���������� ����������� ���������
def calculate_unbiased_variance(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, n):
    Sy_squared = 1/(n-1)*(sum_yi_squared-1/n * (sum_yi ** 2))
    Sx_squared = 1/(n-1)*(sum_xi_squared-1/n * (sum_xi ** 2))
    return Sx_squared, Sy_squared
# ���� I. ������ �������� ��������������� ���������� ����������� ��������
def calculate_standart_error(Sx_squared, Sy_squared, n):
    Sy_error = (Sy_squared ** 0.5) / (n ** 0.5)
    Sx_error = (Sx_squared ** 0.5) / (n ** 0.5)
    return Sx_error, Sy_error
# ���� I. ������ ���� �����
def evaluate_correlation_strength(r):
    if abs(r) <= 0.3:
        return "����������� �����������"
    elif 0.3 < abs(r) <= 0.5:
        return "������"
    elif 0.5 < abs(r) <= 0.7:
        return "���������"
    elif 0.7 < abs(r) <= 1.0:
        return "�������"

# ���� II. ������� ������� ��������� ������� ������
def gauss(A, B):
    n = len(A)
    
    # ������ ��� (�������� � ������� ����������� �������)
    for i in range(n):
        # ������� ������ � ������������ ��������� ��� ������������
        max_row = max(range(i, n), key=lambda r: abs(A[r][i]))
        A[i], A[max_row] = A[max_row], A[i]
        B[i], B[max_row] = B[max_row], B[i]
        
        # �������� �������� ���� ������� ��������� � ����
        for j in range(i + 1, n):
            ratio = A[j][i] / A[i][i]
            for k in range(i, n):
                A[j][k] -= ratio * A[i][k]
            B[j] -= ratio * B[i]
    
    # �������� ��� (��������� ����������)
    X = [0] * n
    for i in range(n - 1, -1, -1):
        X[i] = B[i] / A[i][i]
        for j in range(i - 1, -1, -1):
            B[j] -= A[j][i] * X[i]

    return X    
# ���� II. ����������� ������� ������� ���������� ���������
def create_normal_equations(x, y, degree=6):    
    # ����������� ������� A � ������� B
    A = np.zeros((degree + 1, degree + 1))
    B = np.zeros(degree + 1)
    
    for i in range(degree + 1):
        for j in range(degree + 1):
            A[i][j] = np.sum(x**(i + j))  # ����� x^(i+j)
        B[i] = np.sum(y * (x**i))  # ����� y * x^i

    return A, B

############################################################
#                ������� �� ����������                     #
############################################################
# ���� II. ������ �������� ���������    
def direct_linear_regression(xi, yi, sum_yi, n, a0, a1):
    y_mean = sum_yi / n
    y_pred = a0 + a1 * xi
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator)/np.sum(denominator)
    return y_mean, y_pred, numenator, denominator, R_squared
# ���� II. �������� �������� ���������
def reverse_linear_regression(xi, yi, sum_xi, n, b0, b1):
    x_mean = sum_xi / n
    x_pred = b0 + b1 * yi
    numenator = (x_pred - x_mean) ** 2
    denominator = (xi - x_mean) ** 2
    R_squared = np.sum(numenator)/np.sum(denominator)
    return x_mean, x_pred, numenator, denominator, R_squared
# ���� II. ���������������� ���������
def exponential_regression(xi, yi, n):
    ln_yi = np.log(yi)
    ln_yi_xi = np.log(yi) * xi
    b1 = (n * np.sum(ln_yi_xi) - np.sum(ln_yi) * np.sum(xi)) / (n * np.sum(xi ** 2) - np.sum(xi) ** 2)
    b0 = 1 / n * (np.sum(ln_yi) - b1 * np.sum(xi))
    a0 = np.exp(b0)
    a1 = b1
    
    y_mean = np.sum(yi) / n;
    ln_y_pred = b0 + b1 * xi
    numenator = (ln_y_pred - np.log(y_mean)) ** 2
    denominator = (np.log(yi) - np.log(y_mean)) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)

    return ln_yi, ln_yi_xi, y_mean, ln_y_pred, numenator, denominator, R_squared, a0, a1, b0, b1
# ���� II. ��������������� ���������
def hyperbolic_regression(xi, yi, n):
    zi = 1 / xi
    zi_squared = zi ** 2
    yi_zi = yi * zi
    a1 = (n * np.sum(yi_zi) - np.sum(yi) * np.sum(zi)) / (n * np.sum(zi_squared) - np.sum(zi) ** 2)
    a0 = 1/n * (np.sum(yi) - a1 * np.sum(zi))
    
    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * zi
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared_hyperbolic = np.sum(numenator) / np.sum(denominator)

    return zi, zi_squared, yi_zi, a1, a0, y_mean, y_pred, numenator, denominator, R_squared_hyperbolic
# ���� II. �������������� ���������
def parabolic_regression(xi, yi, n):
    xi_squared = xi ** 2
    xi_cubed = xi ** 3
    xi_quarter = xi ** 4
    yi_xi_squared = yi * xi_squared
    A = [
        [n, np.sum(xi), np.sum(xi_squared)],
        [np.sum(xi), np.sum(xi_squared), np.sum(xi_cubed)],
        [np.sum(xi_squared), np.sum(xi_cubed), np.sum(xi_quarter)]
        ]
    B = [np.sum(yi), np.sum(yi * xi), np.sum(yi_xi_squared)]
    a0, a1, a2 = gauss(A, B)
    
    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * xi + a2 * xi_squared
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)
    
    return xi_squared, xi_cubed, xi_quarter, yi_xi_squared, a0, a1, a2, y_mean, y_pred, numenator, denominator, R_squared
# ���� II. �������������� ��������� 6-� �������
def polynom_regression(xi, yi, n):
    A, B = create_normal_equations(xi, yi, 6)
    a0, a1, a2, a3, a4, a5, a6 = gauss(A, B)
    xi_fifth = xi ** 5
    xi_sixth = xi ** 6

    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * xi + a2 * (xi ** 2) + a3 * (xi ** 3) + a4 * (xi ** 4) + a5 * xi_fifth + a6 * xi_sixth
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)
    
    return xi_fifth, xi_sixth, a0, a1, a2, a3, a4, a5, a6, y_mean, y_pred, numenator, denominator, R_squared
# ���� II. ��������� ���������
def power_regression(xi, yi, n):
    ln_xi = np.log(xi)
    ln_yi = np.log(yi)
    ln_xi_squared = ln_xi ** 2
    ln_yi_ln_xi = ln_yi * ln_xi

    b1 = (n * np.sum(ln_yi_ln_xi) - np.sum(ln_yi) * np.sum(ln_xi)) / (n * np.sum(ln_xi_squared) - np.sum(ln_xi) ** 2)
    b0 = 1 / n * (np.sum(ln_yi) - b1 * np.sum(ln_xi))
    a0 = np.exp(b0)
    a1 = b1

    y_mean = np.sum(yi) / n
    ln_y_pred = b0 + b1 * ln_xi
    numenator = (ln_y_pred - np.log(y_mean)) ** 2
    denominator = (ln_yi - np.log(y_mean)) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)

    return ln_xi, ln_yi, ln_xi_squared, ln_yi_ln_xi, a0, a1, b0, b1, y_mean, ln_y_pred, numenator, denominator, R_squared
# ���� II. ��������������� ���������
def logarithmic_regression(xi, yi, n):
    ln_xi = np.log(xi)
    ln_xi_yi = ln_xi * yi
    
    a1 = (n * np.sum(ln_xi_yi) - np.sum(ln_xi) * np.sum(yi)) / (n * np.sum(ln_xi ** 2) - np.sum(ln_xi) ** 2)
    a0 = 1/n * (np.sum(yi) - a1 * np.sum(ln_xi))

    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * ln_xi
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)

    return a0, a1, ln_xi, ln_xi_yi, y_pred, numenator, denominator, R_squared

############################################################
#                  �������� �������                        #
############################################################
# ����������� �������� �� ������ ��������� ������, ����� ����������� � ���� � ����������� �����������
def initial_process(xi, yi, output_file):
    try:
        # ������ ����������� ������ �� ������ ���������
        n = len(xi)
        sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, xi_squared, yi_squared, xi_yi_product = calculate_sums(xi, yi)
        # ������ ������������� � ��������� �� ���������� ������������ ���������� ��� ������� �� ���� ��������
        result = calculate_coefficients(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, n)
        if result is None:
            print("���������� �� ��������� ��-�� ������. ���������� ���������...")
            return None
        # ��������� �������������
        A, A0, A1, B, B0, B1, a0, a1, b0, b1, r = result
        # ������������� ������������ ����������
        correlation_type, description = interpret_correlation(r) # ��� � ��������
        correlation_strength = evaluate_correlation_strength(r) # ���� �����
        # ������ ����������� ���������
        Sx_squared, Sy_squared = calculate_unbiased_variance(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, n)
        # ������ ���������� ��������������� ���������� ����������� ��������
        Sx_error, Sy_error = calculate_standart_error(Sx_squared, Sy_squared, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # �������� �������
            output_data = np.column_stack((yi, xi, yi_squared, xi_squared, xi_yi_product))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'yi^2'.ljust(12) + 'xi^2'.ljust(14) + 'xi*yi'.ljust(14)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.4f}{row[3]:<14.8f}{row[4]:<14.8f}\n")
            # ��������������� ��������
            f.write("\n���������� ��������������� ������� ��� ������� ������������� ���������:\n")
            f.write(f"A = {A:.10f}\n")
            f.write(f"A0 = {A0:.10f}\n")
            f.write(f"A1 = {A1:.10f}\n")
            f.write(f"B = {B:.10f}\n")
            f.write(f"B0 = {B0:.10f}\n")
            f.write(f"B1 = {B1:.10f}\n")
            # ������������ ����������
            f.write("\n���������� ������������� ���������:\n")
            f.write(f"a0 = {a0:.10f}\n")
            f.write(f"a1 = {a1:.10f}\n")
            f.write(f"b0 = {b0:.10f}\n")
            f.write(f"b1 = {b1:.10f}\n")
            f.write(f"r = {r:.10f}\n")
            # ������������� ����������
            f.write("\n���������� ����������� ����������� r ��������� ������� ��������� ������:\n")
            f.write(f"��� �����: {correlation_type}\n")
            f.write(f"�������� �����: {description}\n")
            f.write(f"���� �����: {correlation_strength}\n")
            # ����������� ���������
            f.write("\n����������� ����������� ���������:\n")
            f.write(f"Sx^2 = {Sx_squared}\n")
            f.write(f"Sy^2 = {Sy_squared}\n")
            # ������� �������������� ���������� ����������� ��������
            f.write("\n����������� ������� �������������� ���������� ����������� ��������:\n")
            f.write(f"Sx^2_c� = {Sx_error}\n")
            f.write(f"Sy^2_�� = {Sy_error}\n")
            f.write("===================================================================================================\n")
        print(f"����������, ���������� �� ������ ��������� ������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        plt.scatter(xi, yi, color='green', label='����������������� ������')
        plt.xlabel(f'$x_{{i}}$', fontsize=12)
        plt.ylabel(f'$y_{{i}}$', fontsize=12)
        plt.title("���������� ������������� ������ �� ����������� ������������", fontsize=14)
        plt.axhline(0, color='black', linewidth=0.5)
        plt.axvline(0, color='black', linewidth=0.5)
        plt.grid(True, which='both', linestyle='--', linewidth=0.5)
        
        return sum_xi, sum_yi, n, a0, a1, b0, b1
    except Exception as e:
        print(f"������ ��� ����������� �� �������� ������: {e}")
        return None
# ����������� �������� ��� ������ �������� ���������, ����� ����������� � ���� � ����������� �����������
def direct_linear_regression_process(xi, yi, sum_yi, n, a0, a1, output_file):
    try:
        y_mean, y_pred, numenator, denominator, R_squared_direct_linear = direct_linear_regression(xi, yi, sum_yi, n, a0, a1)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� ������ �������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("������ �������� ���������: y = {:.10f} + {:.10f} * x\n".format(a0, a1))
            f.write("������������:\na0 = {:.10f},\na1 = {:.10f}\n".format(a0, a1))
            output_data = np.column_stack((yi, xi, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'yi^p'.ljust(12) + '(yi^p - y��)^2'.ljust(16) + '(yi - y��)^2'.ljust(16)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.4f}{row[3]:<16.10f}{row[4]:<16.10f}\n")
            f.write(f"\ny_�� = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_direct_linear:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� ������ �������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        plt.plot(xi, y_pred, color='red', label='������ �������� ���������')
        return R_squared_direct_linear
    except Exception as e:
        print(f"������ ��� ����������� ��� ������ �������� ���������: {e}")
        return None
# ���������� �������� ��� �������� �������� ���������, ����� ����������� � ���� � ����������� �����������
def reverse_linear_regression_process(xi, yi, sum_xi, n, b0, b1, output_file):
    try:
        x_mean, x_pred, numenator, denominator, R_squared_reverse_linear = reverse_linear_regression(xi, yi, sum_xi, n, b0, b1)
        # ���������� ������ � ����
        with open(output_file, 'a') as f:
            # ��������� �������� �������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("�������� �������� ���������: x = {:.10f} + {:.10f} * y\n".format(b0, b1))
            f.write("������������:\nb0 = {:.10f},\nb1 = {:.10f}\n".format(b0, b1))
            output_data = np.column_stack((xi, yi, x_pred, numenator, denominator))
            header = 'xi'.ljust(12) + 'yi'.ljust(12) + 'xi^p'.ljust(12) + '(xi^p - x��)^2'.ljust(16) + '(xi - x��)^2'.ljust(16)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.4f}{row[1]:<12.2f}{row[2]:<12.4f}{row[3]:<16.10f}{row[4]:<16.10f}\n")
            f.write(f"\nx_�� = {x_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_reverse_linear:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� �������� �������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� ������� �������� ���������
        plt.plot(x_pred, yi, color='blue', label='�������� �������� ���������')
        return R_squared_reverse_linear
    except Exception as e:
        print(f"������ ��� ����������� ��� �������� �������� ���������: {e}")
        return None
# ����������� �������� ��� ���������������� ���������, ����� ����������� � ���� � ����������� �����������
def exponential_regression_process(xi, yi, n, output_file):
    try:
        ln_yi, ln_yi_xi, y_mean, ln_y_pred, numenator, denominator, R_squared_exponential, a0, a1, b0, b1 = exponential_regression(xi, yi, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� ���������������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("���������������� ���������: y = {:.10f} + {:.10f} * x ��� y = ln({:.10f} * exp^({:.10f} * x))\n".format(b0, b1, a0, a1))
            f.write("������������:\nb0 = {:.10f},\nb1 = {:.10f},\na0 = {:.10f},\na1 = {:.10f}\n".format(b0, b1, a0, a1))
            output_data = np.column_stack((yi, xi, ln_yi, ln_yi_xi, ln_y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'ln_yi'.ljust(12) + 'ln_yi_xi'.ljust(12) + 'ln_yi^p'.ljust(12) + '(ln_yi^p - ln_y_��)^2'.ljust(23) + '(ln_yi - ln_y_��)^2'.ljust(23)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.6f}{row[3]:<12.8f}{row[4]:<12.6f}{row[5]:<23.10f}{row[6]:<23.10f}\n")
            f.write(f"\nln_y_�� = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_exponential:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� ���������������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        plt.plot(xi, np.exp(ln_y_pred), color='orange', label='���������������� ���������')
        return R_squared_exponential
    except Exception as e:
        print(f"������ ��� ����������� ��� ���������������� ���������: {e}")
        return None 
# ����������� �������� ��� ��������������� ���������, ����� ����������� � ���� � ����������� �����������
def hyperbolic_regression_process(xi, yi, n, output_file):
    try:
        zi, zi_squared, yi_zi, a1, a0, y_mean, y_pred, numenator, denominator, R_squared_hyperbolic = hyperbolic_regression(xi, yi, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� ��������������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("��������������� ���������: y = {:.10f} + {:.10f} / x ��� y = {:.10f} + {:.10f} * z\n".format(a0, a1, a0, a1))
            f.write("������������:\na0 = {:.10f},\na1 = {:.10f}\n".format(a0, a1))
            output_data = np.column_stack((yi, xi, zi, zi_squared, yi_zi, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'zi'.ljust(12) + 'zi^2'.ljust(14) + 'yi*zi'.ljust(14) + 'yi^p'.ljust(10) + '(yi^p - y_��)^2'.ljust(18) + '(yi - y_��)^2'.ljust(18)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.4f}{row[3]:<14.4f}{row[4]:<14.6f}{row[5]:<10.2f}{row[6]:<18.8f}{row[7]:<18.8f}\n")
            f.write(f"\ny_�� = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_hyperbolic:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� ��������������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='purple', label='��������������� ���������')
        return R_squared_hyperbolic
    except Exception as e:
        print(f"������ ��� ����������� ��� ��������������� ���������: {e}")
        return None 
# ����������� �������� ��� �������������� ���������, ����� ����������� � ���� � ����������� �����������
def parabolic_regression_process(xi, yi, n, output_file):
    try:
        xi_squared, xi_cubed, xi_quarter, yi_xi_squared, a0, a1, a2, y_mean, y_pred, numenator, denominator, R_squared_parabolic = parabolic_regression(xi, yi, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� �������������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("�������������� ���������: y = {:.10f} + {:.10f} * x + {:.10f} * x^2\n".format(a0, a1, a2))
            f.write("������������:\na0 = {:.10f},\na1 = {:.10f},\na2 = {:.10f}\n".format(a0, a1, a2))
            output_data = np.column_stack((yi, xi, xi_squared, xi_cubed, xi_quarter, yi_xi_squared, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'xi^2'.ljust(16) + 'xi^3'.ljust(16) + 'xi^4'.ljust(16) + 'yi*xi^2'.ljust(16) + 'yi^p'.ljust(16) + '(yi^p - y_��)^2'.ljust(18) + '(yi - y_��)^2'.ljust(18)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<16.8f}{row[3]:<16.8E}{row[4]:<16.8E}{row[5]:<16.8E}{row[6]:<16.6E}{row[7]:<18.8E}{row[8]:<18.8E}\n")
            f.write(f"\ny_�� = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_parabolic:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� �������������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='black', label='�������������� ���������')
        return R_squared_parabolic
    except Exception as e:
        print(f"������ ��� ����������� ��� �������������� ���������: {e}")
        return None 
# ����������� �������� ��� �������������� ���������, ����� ����������� � ���� � ����������� �����������
def polynom_regression_process(xi, yi, n, output_file):
    try:
        xi_fifth, xi_sixth, a0, a1, a2, a3, a4, a5, a6, y_mean, y_pred, numenator, denominator, R_squared_polynom = polynom_regression(xi, yi, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� �������������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("�������������� ���������: y = {:.10f} + {:.10f} * x + {:.10f} * x^2 + {:.10f} * x^3 + {:.10f} * x^4 + {:.10f} * x^5 + {:.10f} * x^6\n".format(a0, a1, a2, a3, a4, a5, a6))
            f.write("������������:\na0 = {:.10f},\na1 = {:.10f},\na2 = {:.10f},\na3 = {:.10f},\na4 = {:.10f},\na5 = {:.10f},\na6 = {:.10f}\n".format(a0, a1, a2, a3, a4, a5, a6))
            output_data = np.column_stack((yi, xi, xi_fifth, xi_sixth, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'xi^5'.ljust(16) + 'xi^6'.ljust(16) + 'yi^p'.ljust(16) + '(yi^p - y_��)^2'.ljust(18) + '(yi - y_��)^2'.ljust(18)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<16.8E}{row[3]:<16.8E}{row[4]:<16.8E}{row[5]:<18.8E}{row[6]:<18.8E}\n")
            f.write(f"\ny_�� = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_polynom:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� �������������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='gray', label='�������������� ��������� 6-� �������')
        return R_squared_polynom
    except Exception as e:
        print(f"������ ��� ����������� ��� �������������� ���������: {e}")
        return None   
# ����������� �������� ��� ��������� ���������, ����� ����������� � ���� � ����������� �����������
def power_regression_process(xi, yi, n, output_file):
    try:
        ln_xi, ln_yi, ln_xi_squared, ln_yi_ln_xi, a0, a1, b0, b1, y_mean, ln_y_pred, numenator, denominator, R_squared_power = power_regression(xi, yi, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� ��������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("��������� ���������: y = {:.10f} * x^{:.10f}\n".format(a0, a1))
            f.write("������������:\nb0 = {:.10f},\nb1 = {:.10f}\n\na0 = {:.10f},\na1 = {:.10f}\n".format(b0, b1, a0, a1))
            output_data = np.column_stack((yi, xi, ln_xi, ln_yi, ln_xi_squared, ln_yi_ln_xi, ln_y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'ln_xi'.ljust(16) + 'ln_yi'.ljust(16) + 'ln_xi_squared'.ljust(16) + 'ln_yi_ln_xi'.ljust(16) +'ln_yi^p'.ljust(16) + '(ln_yi^p - ln_y_��)^2'.ljust(22) + '(ln_yi - ln_y_��)^2'.ljust(22)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<16.8f}{row[3]:<16.8f}{row[4]:<16.8f}{row[5]:<16.8f}{row[6]:<16.8f}{row[7]:<22.8f}{row[8]:<22.8f}\n")
            f.write(f"\ny_�� = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_power:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� ��������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = ln_y_pred[sorted_indices]
        plt.plot(xi_sorted, np.exp(y_pred_sorted), color='yellow', label='��������� ���������')
        return R_squared_power
    except Exception as e:
        print(f"������ ��� ����������� ��� ��������� ���������: {e}")
        return None
# ����������� �������� ��� ��������������� ���������, ����� ����������� � ���� � ����������� �����������
def logarithmic_regression_process(xi, yi, n, output_file):
    try:
        a0, a1, ln_xi, ln_xi_yi, y_pred, numenator, denominator, R_squared_logarithmic = logarithmic_regression(xi, yi, n)
        # ���������� ������ � ����   
        with open(output_file, 'a') as f:
            # ��������� ��������������� ���������
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("��������������� ���������: y = {:.10f} + {:.10f} * ln(x)\n".format(a0, a1))
            f.write("������������:\na0 = {:.10f},\na1 = {:.10f}\n".format(a0, a1))
            # ������������ ������� ��������
            output_data = np.column_stack((yi, xi, ln_xi, ln_xi_yi, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'ln(xi)'.ljust(16) + 'ln(xi)*yi'.ljust(16) + 'yi^p'.ljust(16) + '(yi^p - y_��)^2'.ljust(18) + '(yi - y_��)^2'.ljust(18)
            f.write("������� ��������:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<16.8f}{row[3]:<16.8f}{row[4]:<16.8f}{row[5]:<18.8f}{row[6]:<18.8f}\n")
            f.write(f"\ny_�� = {np.mean(yi):.4f}\n")
            f.write(f"R^2 = {R_squared_logarithmic:.4f}\n")
        print(f"����������, ���������� ��� ���������� ��� ��������������� ���������, ��������� � ���� '{output_file}'.")
        # ���������� �������
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='brown', label='��������������� ���������')
        return R_squared_logarithmic
    except Exception as e:
        print(f"������ ��� ����������� ��� ��������������� ���������: {e}")
        return None   
    
# ������� ��� �������� � �������� ������ �� �����
def load_and_validate_data(input_file):
    try:
        with open(input_file, 'r') as file:
            lines = file.readlines()[1:]

        cleaned_lines = []
        for line in lines:
            cleaned_line = "\t".join(line.strip().split())
            if cleaned_line:
                cleaned_lines.append(cleaned_line)

        data = np.array([line.split('\t') for line in cleaned_lines], dtype=float)

        yi = data[:, 0]
        xi = data[:, 1]

        if yi.shape[0] != xi.shape[0]:
            raise ValueError("����������� �������� yi � xi ������ ���� �������.")

        return xi, yi
    except Exception as e:
        print(f"������ ��� ������ ��� �������� ������: {e}")
        return None, None
# �������� ������� ��� ��������� ������ � ���������� �������
def main():
    # ����������� ������ � ������� � �������� ���������� ������ �� �����
    input_file = input("������� ���� � �������� ����� (�� ��������� 'input_data.txt'): ") or "input_data.txt"
    output_file = input("������� ���� � ��������� ����� ��� ���������� ���������� (�� ��������� 'output_data.txt'): ") or "output_data.txt"
    xi, yi = load_and_validate_data(input_file)
    if xi is None or yi is None:
        print("�������� ������ �� �������.")
        return
    
    # ������� ��� �������� ������������� ������������ (R^2) ��� ������ ����� ���������
    regression_r_squared = {
        "linear_direct": None,   
        "linear_reverse": None,
        "exponential": None,
        "hyperbolic": None,         
        "logarithmic": None,        
        "parabolic": None,          
        "polynomial": None,
        "logarithmic": None,
        "power": None
    }

    # ���������� �������
    plt.figure(figsize=(10, 6))
    
    ### ���� I ###
    with open(output_file, 'w') as f:
        f.write("���� I.���������� ����� ������ ��� ������������ ������.\n\n")
    result = initial_process(xi, yi, output_file)
    if result is None:
        return
    ### ���� II ###
    with open(output_file, 'a') as f:
        f.write("���� II. ���������� �� ������ ���������� ������ ��������� ������ � �������� ��������, ���������������, ����������������, ��������������, �������������� ���������\n")
    sum_xi, sum_yi, n, a0, a1, b0, b1 = result
    
    # ������ �������� ���������
    result = direct_linear_regression_process(xi, yi, sum_yi, n, a0, a1, output_file)
    if result is None:
        return
    regression_r_squared['linear_direct'] = result
    
    # �������� �������� ���������
    result = reverse_linear_regression_process(xi, yi, sum_xi, n, b0, b1, output_file)
    if result is None:
        return
    regression_r_squared['linear_reverse'] = result
    
    # ���������������� ���������
    result = exponential_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['exponential'] = result
    
    # ��������������� ���������
    result = hyperbolic_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['hyperbolic'] = result
    
    # �������������� ���������
    result = parabolic_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['parabolic'] = result
    
    # �������������� ���������
    result = polynom_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['polynomial'] = result
    
    # ��������� ���������
    result = power_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['power'] = result
    
    # ��������������� ���������
    result = logarithmic_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['logarithmic'] = result

    plt.legend()
    plt.show()
    
    # ��������������� ������ �� ������, � ������� ���� �������� R^2 (�� None)
    filtered_regression_r_squared = {key: value for key, value in regression_r_squared.items() if value is not None}
    # ������� ������ � ������������ ��������� R^2 ����� ���������������
    best_model = max(filtered_regression_r_squared, key=filtered_regression_r_squared.get)
    # ���������� ��������� � ����
    with open(output_file, 'a') as f:
        f.write("=====================================================================================================\n")
        f.write("������ ������ �� �������� �������� ������������ ������������ R^2 = {:.10f}: {}\n".format(filtered_regression_r_squared[best_model], best_model))



# ����� ���������
if __name__ == "__main__":
    main()