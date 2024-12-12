# -*- coding: Windows-1251 -*-

import numpy as np
import matplotlib.pyplot as plt
import pickle
import os

from numpy.core.numeric import outer

# ������� ��� ������ � ����.
def write_to_file(file_path, text):
    with open(file_path, 'a') as f:
        f.write(text + '\n')  
        
# ��������� ������ �� �����.
def process_csv(file_path):
    headers = []
    subheaders = []
    data = []

    with open(file_path, 'r') as file:
        for i, line in enumerate(file):
            # ��������� ������ �� �������.
            elements = line.strip().split(',')

            if i == 0:
                # ������ ������: ���������� � headers.
                headers = elements
            else:
                elements = line.strip().split(';')
                # ��������� ������
                subheaders.append(elements[0])  # ������ ������� ��������� � subheaders.
                # ��������� �������� ������� �� �������� � ��������� � data.
                row_data = [elem.replace(' ', '') for elem in elements[1:]]
                data.append(row_data)

    return headers, subheaders, data

# ������� ������������ ������.
def normalize_data(data):
    data_array = np.array(data, dtype=float)
    data_transposed = data_array.T
    row_sums = np.sum(data_transposed, axis=1)
    normalized_data = data_transposed / row_sums[:, np.newaxis]
    normalized_data_transposed = normalized_data.T

    return normalized_data_transposed

# ������������� ���� ��������.
def initialize_network(grid_size, num_features):
    return np.random.rand(grid_size, grid_size, num_features)

# ���������� ���������� ����� ���������.
def calculate_distance(input_vector, weight_vector):
    return np.linalg.norm(input_vector - weight_vector)

# ���������� ����� �������� ������������ �������-����������.
def update_weights(grid_size, weights, input_vector, winner_coords, learning_rate, neighborhood_radius):
    for x in range(grid_size):
        for y in range(grid_size):
            distance_to_winner = np.sqrt((x - winner_coords[0]) ** 2 + (y - winner_coords[1]) ** 2) # ���������� ��������� ���������� ����� �������� � ��������-�����������.
            if distance_to_winner <= neighborhood_radius:
                influence = np.exp( - (distance_to_winner ** 2) / (2 * (neighborhood_radius ** 2))) # ��������, ��� distance_to_winner = ��������� ���������� (��� ���������).
                weights[x, y] += influence * learning_rate * (input_vector - weights[x, y]) # ���������� ����� � ������ ������� ��������, �.�. ��� ������ ������� �� �������-����������, ��� ������ �������.

# �������� ���� ��������.
def train_kohonen(data, grid_size, num_epochs, initial_learning_rate, initial_radius, output_file):
    num_features = data.shape[1] # ���������� ��������� (������������� �����) �������� = ����� �������� (X) � �������� ������.
    # ��� 1. ������������� ����.
    weights = initialize_network(grid_size, num_features)
    learning_rate = initial_learning_rate # �������� �������� ���������.
    radius = initial_radius # ������ ��������� �������-����������.

    # �������� ��������� �� ������.
    for epoch in range(num_epochs):
        # ��� 2. ������������ ���� ������ �������� �������.
        for input_vector in data:
            # ��� 3. ���������� ���������� �� ���� �������� ����.
            distances = np.array(
                [[calculate_distance(input_vector, weights[x, y]) for y in range(grid_size)] for x in range(grid_size)]
            )
            # ��� 4. ����� ������� � ���������� �����������.
            winner_coords = np.unravel_index(np.argmin(distances), distances.shape) # np.agrmin - ���������� ������ ���. �������� ���������� �� �����;
                                                                                    # .shape - ����� ������� � ���� ������� (_;_);
                                                                                    # np.unreavel_index - ����������� ������ ������������ ����� �������, �.�. ������ 14 � ������� 10x10 ������ (1;5).
            # ��� 5. ������������ ����� ������� � ��� �������.
            update_weights(grid_size, weights, input_vector, winner_coords, learning_rate, radius)

        # ��������� �������� �������� ("������ �������") � ������ ������� �� �������
        learning_rate *= 0.9
        radius *= 0.9
        # ��� 6. ������������ � ���� 2.

        if (epoch + 1) % 10 == 0:
            print(f"���� �������� ������ �������� �� {epoch + 1}/{num_epochs} ����.")
            write_to_file(output_file, f"���� �������� ������ �������� �� {epoch + 1}/{num_epochs} ����.")
    return weights

# ������������� ������ �� �������� (������������� ��������).
def assign_data_to_neurons(data, weights, grid_size, output_file):
    # �������� �������: ���� - �����. �������, �������� - ������� ��������.
    clusters = {(x, y): [] for x in range(grid_size) for y in range(grid_size)}

    # �������� �� �������� �������.
    for idx, input_vector in enumerate(data):
        # ���������� ���������� ������� �� ������� ���������� �������.
        distances = np.array(
            [[calculate_distance(input_vector, weights[x, y]) for y in range(grid_size)] for x in range(grid_size)]
        )
        # ����������� �������-����������.
        winner_coords = np.unravel_index(np.argmin(distances), distances.shape)
        # �� ����������� ������� ���������� ��������� ������ �������.
        clusters[winner_coords].append(idx)

    # ����� ��������� � �������
    write_to_file(output_file, f"������� ���� ��������� �� ��������� ��������:")
    for (x, y), indices in clusters.items():
        write_to_file(output_file, f"������ ({x}, {y}) ����� ��������� ������� ��������: {indices}")

    write_to_file(output_file, "")

    print(f"������� ������ ���� ������������ �� ���������.")
    return clusters

# ������������ ����� � ���������.
def visualize_kohonen_with_labels(weights, clusters, region_names, grid_size, output_file):
    umatrix = np.zeros((grid_size, grid_size))
    # ���������� U-������� (�������� ����� ���������).
    for x in range(grid_size):
        for y in range(grid_size):
            neighbors = []
            if x > 0:
                neighbors.append(weights[x - 1, y])
            if x < grid_size - 1:
                neighbors.append(weights[x + 1, y])
            if y > 0:
                neighbors.append(weights[x, y - 1])
            if y < grid_size - 1:
                neighbors.append(weights[x, y + 1])
            umatrix[x, y] = np.mean([np.linalg.norm(weights[x, y] - neighbor) for neighbor in neighbors])
            write_to_file(output_file, f"������ ({x},{y}): {umatrix[x,y]}")

    # ���������������� ������� umatrix ��� �������� �������� (���������� ����������� �� ����).
    umatrix = umatrix.T

    # �������� ������������.
    plt.figure(figsize=(10, 8))
    plt.imshow(umatrix, cmap='coolwarm', interpolation='nearest', origin='lower')
    plt.colorbar(label="Cluster Similarity")
    plt.title("Self-Organizing Map with Region Labels")
    write_to_file(output_file, "�������� ��������:")
    for (x, y), indices in clusters.items():
        if indices:
            label = ", ".join([region_names[idx] for idx in indices])[:10] + "..." if len(indices) > 1 else region_names[indices[0]][:10] + "..."
            plt.text(x, y, label, ha='center', va='center', fontsize=4, color='white', wrap=True)
            write_to_file(output_file, f"������ ({x},{y}) �������� �������: {', '.join([region_names[idx] for idx in indices])}")

    plt.xlabel("Neuron X")
    plt.ylabel("Neuron Y")
    plt.show() 

# ���������� ��������� ���� � ����.
def save_kohonen_network(weights, file_path):
    with open(file_path, 'wb') as file:
        pickle.dump(weights, file)

# �������� ��������� ���� �� �����.
def load_kohonen_network(file_path):
    with open(file_path, 'rb') as file:
        return pickle.load(file)

# �������� �������
def main():
    # ������ �������� ������.
    file_path = "����������_��������.txt"
    output_file = "output_log.txt"
    trained_model_path = "kohonen_network.pkl"

    # ������� ���� ����� �������.
    with open(output_file, 'w') as f:
        f.write('Training Log...\n\n')

    headers, subheaders, data = process_csv(file_path)

    # ������������ ������.
    normalized_data = normalize_data(data)

    # ��������� ���� ��������.
    grid_size = 10  # ������ ����� �������� (10x10).
    num_epochs = 100 # ����� ���� ��������.
    initial_learning_rate = 0.5 # ��������� �������� ��������.
    initial_radius = 3 # ��������� ������ ������� �������-���������� �� �������.

    # ������ ������������.
    user_choice = input("������ ������������ ��� ��������� ������ (y/n [any symbols])? ").strip().lower()
    if user_choice == 'n':
        # ������ � ����.
        write_to_file(output_file, '�������� ������ ������� ���������.')
        write_to_file(output_file, f'������ ��������� �������: {len(normalized_data[0])} ��������.')
        print("�������� ���� ��������...")
        write_to_file(output_file, "�������� ���� ��������...")
        weights = train_kohonen(normalized_data, grid_size, num_epochs, initial_learning_rate, initial_radius, output_file)
        # ���������� ��������� ����.
        save_kohonen_network(weights, trained_model_path)
        print("��������� ������ ���� ��������� � ���� {trained_model_path}\n")
        write_to_file(output_file, f"��������� ������ ���� ��������� � ���� {trained_model_path}\n")
    else:
        # �������� ������� ����� � ��������� �����.
        if not os.path.exists('kohonen_network.pkl'):
            print("���� � ��������� ����� �� ������. ���������� ���������.")
            return
        # �������� ��������� ����.
        print("��������� ��������� ������...")
        write_to_file(output_file, "��������� ��������� ������...")
        weights = load_kohonen_network('kohonen_network.pkl')

    # ������������� ������ �� �������� (������������� ��������).
    data_clusters = assign_data_to_neurons(normalized_data, weights, grid_size, output_file)

    # ������������ ����� � ��������� ��� ��������.
    print("������������ ����� ��������...")
    write_to_file(output_file, "����� �������� ���� ���������������!")
    region_names = subheaders
    visualize_kohonen_with_labels(weights, data_clusters, region_names, grid_size, output_file)

# ������ ���������
if __name__ == '__main__':
    main()
