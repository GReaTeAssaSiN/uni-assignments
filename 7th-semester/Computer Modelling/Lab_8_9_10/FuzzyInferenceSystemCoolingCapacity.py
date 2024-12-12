# -*- coding: Windows-1251 -*-

# ������� ��������������
def triangular(x, a, b, c):
    if a <= x <= b:
        return (x - a) / (b - a)
    elif b <= x <= c:
        return (c - x) / (c - b)
    else:
        return 0
def trapezoidal(x, a, b, c, d):
    if a <= x <= b:
        return (x - a) / (b - a)
    elif b <= x <= c:
        return 1
    elif c <= x <= d:
        return (d - x) / (d - c)
    else:
        return 0

# ������� ������������
def fuzzify_delta_T(value):
    return {
        "�����": triangular(value, -15, 0, 15),
        "�������": triangular(value, 0, 15, 30),
        "�������": trapezoidal(value, 15, 30, 35, 100),
    }
def fuzzify_dT_dt(value):
    return {
        "�����": triangular(value, -0.15, 0, 0.15),
        "�������": triangular(value, 0, 0.15, 0.3),
        "�������": trapezoidal(value, 0.15, 0.3, 0.4, 100),
    }
def fuzzify_compressor_speed(value):
    return {
        "����� �����": trapezoidal(value, -31.5, 0, 0.5, 32),
        "�����": triangular(value, 17, 32, 47),
        "�������": triangular(value, 49, 64, 79),
        "�������": triangular(value, 81, 96, 111),
        "����� �������": trapezoidal(value, 105, 128, 138, 1000),
    }

# ������� �������� ������
rules = [
    (["�����", "�����"], "����� �����"),
    (["�����", "�������"], "�����"),
    (["�����", "�������"], "�������"),
    (["�������", "�����"], "�����"),
    (["�������", "�������"], "�������"),
    (["�������", "�������"], "�������"),
    (["�������", "�����"], "�������"),
    (["�������", "�������"], "�������"),
    (["�������", "�������"], "����� �������"),
]

# ��������� ������
def aggregate_rules(delta_T, dT_dt):
    aggregated = {"����� �����": 0, "�����": 0, "�������": 0, "�������": 0, "����� �������": 0}
    for antecedents, consequent in rules:
        rule_value = min(delta_T[antecedents[0]], dT_dt[antecedents[1]])
        aggregated[consequent] = max(aggregated[consequent], rule_value)
    return aggregated

# ��������������: ����� ������ �������
def defuzzify(aggregated):
    numerator = 0
    denominator = 0
    x_range = list(range(136))
    for x in x_range:
        membership = max(
            trapezoidal(x, -31.5, 0, 0.5, 32) * aggregated["����� �����"],
            triangular(x, 17, 32, 47) * aggregated["�����"],
            triangular(x, 49, 64, 79) * aggregated["�������"],
            triangular(x, 81, 96, 111) * aggregated["�������"],
            trapezoidal(x, 105, 128, 138, 1000) * aggregated["����� �������"],
        )
        numerator += x * membership
        denominator += membership
    return numerator / denominator if denominator != 0 else 0

# ������� ������� ����� ��������������� ����� � ������������
def get_non_negative_float(prompt):
    while True:
        user_input = input(prompt)
        if user_input.lower() == 'exit':
            return None
        try:
            value = float(user_input)
            if value >= 0:
                return value
            else:
                print("������: ������� ��������������� �����.")
        except ValueError:
            print("������: ������� ���������� �����.")

# ������� ������ ������ � ����
def log_to_file(file_name, data):
    with open(file_name, 'a') as file:
        file.write(data + "\n")

# �������� �������
def main():
    file_path = "input_output_log.txt"
    while True:
        # ������ � ������������ �������� ��� ������� ���������
        delta_T_value = get_non_negative_float("������� �������� ��� �������� ���������� (delta_T) (��������������� ����� ��� 'exit' ��� ������): ")
        if delta_T_value is None:
            print("����� �� ���������.")
            break

        dT_dt_value = get_non_negative_float("������� �������� ��� �������� ��������� ����������� (dT/dt) (��������������� ����� ��� 'exit' ��� ������): ")
        if dT_dt_value is None:
            print("����� �� ���������.")
            break

        # ������ � ����
        log_to_file(file_path, f"delta_T: {delta_T_value}")
        log_to_file(file_path, f"dT/dt: {dT_dt_value}")

        # ������������
        delta_T = fuzzify_delta_T(delta_T_value)
        dT_dt = fuzzify_dT_dt(dT_dt_value)
   
        # �����
        print(f"��������� ������������:\n{delta_T},\n{dT_dt}")
        log_to_file(file_path, f"��������� ������������:\n{delta_T},\n{dT_dt}")

        # ���������
        aggregated = aggregate_rules(delta_T, dT_dt)
        
        # �����
        print(f"��������� ���������:\n{aggregated}")
        log_to_file(file_path, f"��������� ���������:\n{aggregated}")

        # ��������������
        compressor_speed = defuzzify(aggregated)
        print(f"��������� ������� �������� �����������: {compressor_speed:.5f}\n")
        log_to_file(file_path, f"��������� ������� �������� �����������: {compressor_speed:.5f}\n")

        # ������ �� ����������� ��� �����
        continue_input = input("������ ������ ������ ��������? (y [any symbols] / exit): ").lower()
        if continue_input == "exit":
            print("����� �� ���������.")
            break

if __name__ == "__main__":
    main()