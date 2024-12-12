# -*- coding: Windows-1251 -*-

import numpy as np
import pickle
import os

# �������� ������ �� ���������� �����.
def load_data(file_path):
    with open(file_path, 'r', encoding='Windows-1251') as file:
        lines = file.readlines()
    
    # ������� ������� ����� ������ � ��������� ������ �� ��������.
    data = [line.strip().split(',') for line in lines]
    
    # ����������� ������ � �����, ��� ��� ����������.
    for i in range(1, len(data)):
        data[i] = [float(x) for x in data[i]]
    
    return data

# ������� ������������ ������� ������ X.
def normalize_data_X(data):
    X = np.array(data[:-1], dtype=float)
    min_vals = np.min(X, axis=1)
    max_vals = np.max(X, axis=1)

    return np.array([(X[i] - min_vals[i]) / (max_vals[i] - min_vals[i]) for i in range(len(X))])

# ������� ������������ �������� ������ Y.
def normalize_data_Y(data):
    Y = np.array(data[-1], dtype=float)
    min_vals = np.min(Y)
    max_vals = np.max(Y)

    return np.array([(Y[i] - min_vals) / (max_vals - min_vals) for i in range(len(Y))])

# ������� �������������� ������.
def denormalize_data_Y(normalized_Y, min_val, max_val):
    return normalized_Y * (max_val - min_val) + min_val

# ������� ������������� ������������� ����� � ���������� �������� ������� ������� ������� ����.
def initialize_weights(input_size, hidden_size, output_size):
    input_hidden_weights = np.random.uniform(-0.05, 0.05, (input_size, hidden_size))  # ����� ������� � ������� �����.
    hidden_output_weights = np.random.uniform(-0.05, 0.05, (hidden_size, output_size))  # ����� ������� � �������� �����.
    hidden_bias = np.random.uniform(-0.05, 0.05, (hidden_size))  # �������� �������� ����.
    output_bias = np.random.uniform(-0.05, 0.05, (output_size))  # �������� ��������� ����.
    return input_hidden_weights, hidden_output_weights, hidden_bias, output_bias

# ������� ��������� - �������� (������ ��������������� �������).
def sigmoid(x):
    return 1 / (1 + np.exp(-x))
# ����������� �������� (�������� ��������������� ������).
def sigmoid_derivative(sigm_x):
    return sigm_x * (1 - sigm_x)

# ������ ��������������� �������.
def forward_propagation(input_data, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias):
    # ����� �������� ����.
    hidden_layer_input = np.dot(input_data, input_hidden_weights) + hidden_bias # ������� ������������� �����: 1-1, 2-1, 3-1, 4-1, 5-1 - ��� ������ �������� ������ ������, � �.�.
                                                                                # �������� ������� �������� ������� �������� (��������).
    hidden_layer_output = sigmoid(hidden_layer_input)                           # ����� f(�������� ������� ��������).
    
    # ����� ��������� ����.
    output_layer_input = np.dot(hidden_layer_output, hidden_output_weights) + output_bias # ���������� ����.
    predicted_output = sigmoid(output_layer_input)                                        # ���������� ����.

    # ����� �������, � predicted_output ����� �� ��������, ������� ��������� �� ������ ������ ���������� ����������.
    # ��� ����, ����� ��������� �������� ��������� ��������������� ������, ���������� ��������, ���������� �� ������� � �������� �����.
    return hidden_layer_output, predicted_output

# �������� ��������������� ������.
def backward_propagation(input_data, hidden_layer_output, predicted_output, target, 
                         input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, learning_rate):
    # ��� 3. ��� ���� �������� k ���������� ���� ���������� �������� �������.
    # ������ �� �������� ����.
    output_error = target - predicted_output                           # error_k = dk - yk.
    output_delta = output_error * sigmoid_derivative(predicted_output) # �������: delta_k = yk(1-yk)(dk-yk), ��� dk - ������ ��������, yk - ���������� �� �� ������� ��������� (��������)
                                                                       # ����������� �������� �����, ��������, sigm' = sigm * (1 - sigm), ��� sigm = 1/(1+e^(-x)).

    # ��� 4. ��� ������� ������ n, ������� � �������������� - ��� ������� ���� i ������ n ��������� �������.
    # ������ �� ������� ���� (�����������, ��� �� ����. ����������� ������� ���� - ����).
    hidden_error = np.dot(output_delta, hidden_output_weights.T)            # error_j = delta_k * wjk.
    hidden_delta = hidden_error * sigmoid_derivative(hidden_layer_output)   # �������: delta_j = (delta_k * wjk) * yj(1-yj)
    
    # ��� 5. ��� ������� ����� ���� {i, j} �������� �������� �����.
    # �� ��������� ���� � ��������.
    input_hidden_weights += learning_rate * np.outer(input_data, hidden_delta)           # ������������� ���: wij = wij + learning_rate * delta_k * yk.
    hidden_bias += learning_rate * hidden_delta                                          # �����: bj = bj + learning_rate * delta_j.

    # �� �������� ���� � ���������.
    hidden_output_weights += learning_rate * np.outer(hidden_layer_output, output_delta) # ������������� ���: wjk = wjk + learning_rate * delta_k * yk.
    output_bias += learning_rate * output_delta                                          # �����: bk = bk + learning_rate * delta_k.

    return input_hidden_weights, hidden_output_weights, hidden_bias, output_bias

# ������� �������� ��������� �� ��������� ��������� ��������������� ������ �� ������� ������.
def train_neural_network(data, targets, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, learning_rate, epochs, delta_threshold, output_file):
    # ��� ���������� � ������� �������� MSE � MAE, �������� ������ ����� ��������.
    MSE_mass = []
    MAE_mass = []
    for epoch in range(epochs):
        # ������������� ������
        data = np.array(data)
        indices = np.arange(len(targets)) # ������� ������ ��������.
        np.random.shuffle(indices) # ������������ �������.
        data = data[indices] # �������������� ������������ ������� �������� ������.
        targets = targets[indices] # ����� ��� �� ������������ ������� ������ ��������.

        #������� ��� �������� �������� � �������� (����������) MSE � MAE.
        total_predictions = []  # ��� �������� ������������ �� ������� �����.
        total_targets = []      # ��� �������� �������� �������� �� ������� �����.
        
        for input_data, target in zip(data, targets):
            # ��� 2. ������ �� ���� ���� ��������� ��������� ������ � ���������� ������.
            hidden_layer_output, predicted_output = forward_propagation(input_data, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias)
            total_predictions.append(predicted_output)  # ��������� ������� ������������.
            total_targets.append(target)                # ��������� �������� ��������.
            
            # ��� 3-5. ����������� ����� � ������� �� ������ ��������� ��������� ��������������� ������.
            input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = backward_propagation(
                input_data, hidden_layer_output, predicted_output, target, 
                input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, learning_rate
            )
        
        # ����� ������ ����� ��������� �������.
        total_predictions = np.array(total_predictions)
        total_targets = np.array(total_targets)
        
        # MSE (Mean Squared Error)
        MSE = np.mean((total_targets - total_predictions) ** 2)
        # MAE (Mean Absolute Error)
        MAE = np.mean(np.abs(total_targets - total_predictions))
        # ���������� �������� MSE � MAE � �������.
        MSE_mass.append(MSE)
        MAE_mass.append(MAE)
        
        # ����� ������ ������ 1000 ����.
        if (epoch + 1) % 1000 == 0:
            write_to_file(output_file, f'����� {epoch + 1},\tMSE: {MSE:.8f},\tMAE: {MAE:.8f}')
            print(f"�� ���� ������� �� ����� {epoch + 1}. �������� {epochs - epoch - 1} ���� :)")
        
        # �������� �������� ���������.
        if MSE < delta_threshold:  # ���� ������ ������ ��������� ������.
            write_to_file(output_file, f'�������� ����������� �� ����� {epoch}, MSE: {MSE:.8f}, MAE: {MAE:.8f}.')
            break
    
    # ������� ������ �� ���� ������.
    mean_MSE = np.mean(MSE_mass)
    mean_MAE = np.mean(MAE_mass)
    write_to_file(output_file, f'������ MSE ����� ��������� � �������������� ����������: {mean_MSE:.8f}.')
    write_to_file(output_file, f'������� MAE ����� ��������� � �������������� ����������: {mean_MAE:.8f}.')
    
    return input_hidden_weights, hidden_output_weights, hidden_bias, output_bias

# ������� ���������� ��������� �� ������� ������ �������� ������.
def save_neural_network(file_path, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, output_file):
    model_data = {
        "input_hidden_weights": input_hidden_weights,
        "hidden_output_weights": hidden_output_weights,
        "hidden_bias": hidden_bias,
        "output_bias": output_bias
    }
    with open(file_path, 'wb') as file:
        pickle.dump(model_data, file)
    write_to_file(output_file, f"��������� ��������� ��������� ��������� � ����: {file_path}.\n\n") 

# ������� ��� ������ � ����.
def write_to_file(file_path, text):
    with open(file_path, 'a') as f:
        f.write(text + '\n')   

# ������� ��� ������������ ���������.
def test_neural_network_to_file(test_size, output_file, data, targets, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias, min_val_Y, max_val_Y):
    # ������ �������� �������.
    write_to_file(output_file, f"������ �������� �������: {test_size}")
    
    # ������������� ������.
    data = np.array(data)
    indices = np.arange(len(targets))
    np.random.shuffle(indices)
    shuffled_data = data[indices]
    shuffled_targets = targets[indices]
    
    # ����� ���� ��������� ��������
    test_examples = shuffled_data[:test_size]   # ������ test_size ������� ����� �������������.
    test_targets = shuffled_targets[:test_size] # �� ��������������� �������� ��������.
    
    # ������ ����� ���������.
    for i, (input_data, real_value) in enumerate(zip(test_examples, test_targets)):
        _, predicted_output = forward_propagation(input_data, input_hidden_weights, hidden_output_weights, hidden_bias, output_bias)

        # ��������������.
        # �������� � ������������� ��������
        denorm_real = denormalize_data_Y(np.array([real_value]), min_val_Y, max_val_Y)[0]
        denorm_predicted = denormalize_data_Y(predicted_output, min_val_Y, max_val_Y)[0]
        
        # ������ ����������� � ����
        write_to_file(output_file, f"������ {i + 1}:")
        write_to_file(output_file, f"  �������� �������� (������.): {denorm_real:.8f}")
        write_to_file(output_file, f"  ������������� �������� (������.): {denorm_predicted:.8f}")
        write_to_file(output_file, f"  ���������� ������: {np.abs(denorm_real - denorm_predicted):.8f}")
        print(f"�������� ������ {i + 1} ������� ��� ����� ��.")

# ������� ��� �������� ����������� ������.
def load_trained_model(file_path):
    if os.path.exists(file_path):
        with open(file_path, 'rb') as file:
            model_data = pickle.load(file)
        return (model_data['input_hidden_weights'], 
                model_data['hidden_output_weights'], 
                model_data['hidden_bias'], 
                model_data['output_bias'])
    else:
        print(f"������ �� ������� �� ����: {file_path}")
        return None

# �������� �������.
def main():
    file_path = "�������������_�_�������_��.txt"
    output_file = "output_log.txt"
    trained_model_path = "trained_neural_network.pkl"
    
    # ������� ���� ����� �������.
    with open(output_file, 'w') as f:
        f.write('Training Log...\n\n')

    # ��� 0. ������ �������� ������ � �� ������������.
    data = np.array(load_data(file_path), dtype=float)

    # ������������ ������� � �������� ������.
    normalized_X = normalize_data_X(data.T)
    normalized_Y = normalize_data_Y(data.T)

    # ������ ������������, ��� ������ ������.
    user_choice = input("������ ������������ ��� ��������� ������ (y/n [any symbols])? ").strip().lower()
    if user_choice == 'y':
        print("��������� ��������� ������...")
        input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = load_trained_model(trained_model_path)
    else:
        # ������ � ����.
        write_to_file(output_file, '�������� ������ ������� ���������.')
        write_to_file(output_file, f'������ ��������� �������: {len(data.T[0])} ��������.')
        print("������� ���������... :<")
        # ��� 1. ������������� �������������� ����� � ������.
        input_size = 5   # (�.�. 5 ���������)
        hidden_size = 11 # (�� ����. �����������)
        output_size = 1  # (�.�. 1 ������� ��������)   
    
        input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = initialize_weights(input_size, hidden_size, output_size)

        # ��� 6. ��������� ���� 2-5 ��� ���������� ���������� �������.
        learning_rate = 0.1
        epochs = 10000
        delta_threshold = 0.002 # ������� �� ��������������� �������.
    
        input_hidden_weights, hidden_output_weights, hidden_bias, output_bias = train_neural_network(
            normalized_X.T, normalized_Y.T, 
            input_hidden_weights, hidden_output_weights, 
            hidden_bias, output_bias, 
            learning_rate, epochs,
            delta_threshold, output_file
        )

        # ��� 7. ������ � ��������� ��������� ��������� ���������.
        save_neural_network(trained_model_path, 
                        input_hidden_weights, hidden_output_weights, 
                        hidden_bias, output_bias, output_file)
        
    print(f"��� ������������� ����������� ��������� ��������������� ������ �������� � ����: {output_file}.")

    # ��� 8. ������������ ���������.
    test_size = 10
    test_neural_network_to_file(
        test_size,                # ������ �������� �������
        output_file, 
        normalized_X.T,           # �������� ������
        normalized_Y.T,           # �������� ���� ������� ������ ������
        input_hidden_weights,     # ��������� ���� ������� ���� -> ������� ����
        hidden_output_weights,    # ��������� ���� ������� ���� -> �������� ����
        hidden_bias,              # �������� �������� ����
        output_bias,              # �������� ��������� ����
        np.min(np.array(data.T[-1], dtype=float)),
        np.max(np.array(data.T[-1], dtype=float))
    )

# ������ ���������.
if __name__ == '__main__':
    main()