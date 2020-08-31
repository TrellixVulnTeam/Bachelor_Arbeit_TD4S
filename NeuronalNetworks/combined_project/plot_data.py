from util import read_input_file_no_duplicates
from parameters import data_limit
import matplotlib.pyplot as plt

input_data_set_list = read_input_file_no_duplicates(normalize=True, remove_len_2_and_3=True)

coord_pair_lengths = [len(item.coordinate_pairs) for item in input_data_set_list]

plt.hist(coord_pair_lengths, bins=400)
plt.xlabel("number of terminals in net")
plt.ylabel("number of nets in training set")
plt.title("distribution of terminal counts (no duplicates) in training set\n(loaded from file 'stereovision.txt')")

plt.savefig("../../../Thesis/plots/data-distribution-full-fine.png")
plt.show()

plt.hist(coord_pair_lengths, bins=10)
plt.xlabel("number of terminals in net")
plt.ylabel("number of nets in training set")
plt.title("distribution of terminal counts (no duplicates) in training set\n(loaded from file 'stereovision.txt')")

plt.savefig("../../../Thesis/plots/data-distribution-full-coarse.png")
plt.show()

# sort training data by length / number of coordinate pairs
list_of_equal_length_data_lists = []
for item in coord_pair_lengths:
    while len(list_of_equal_length_data_lists) < item - 1:
        list_of_equal_length_data_lists.append([])
    list_of_equal_length_data_lists[item - 2].append(item)
print("data sorted by length.")

list_of_equal_length_data_lists = [item[:data_limit] for item in list_of_equal_length_data_lists]
coord_pair_lengths = [item for current_list in list_of_equal_length_data_lists for item in current_list]

plt.hist(coord_pair_lengths, bins=406)
plt.xlabel("number of terminals in net")
plt.ylabel("number of nets in training set")
plt.title("distribution of terminal counts (no duplicates) in 'balanced' training set\n(loaded from file 'stereovision.txt' with 'data_limit'=4000)")

plt.savefig("../../../Thesis/plots/data-distribution-limited-fine.png")
plt.show()

plt.hist(coord_pair_lengths, bins=10)
plt.xlabel("number of terminals in net")
plt.ylabel("number of nets in training set")
plt.title("distribution of terminal counts (no duplicates) in 'balanced' training set\n(loaded from file 'stereovision.txt' with 'data_limit'=4000)")

plt.savefig("../../../Thesis/plots/data-distribution-limited-coarse.png")
plt.show()
