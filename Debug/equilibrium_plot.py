import matplotlib.pyplot as plt
import numpy as np
import sys


def read_data(filename):
    data = np.genfromtxt(filename, dtype=int)
    return data


def main():
    if len(sys.argv) < 2:
        print("Error: incorrect number of arguments")
        return

    filename = sys.argv[1]
    activity_data = read_data(filename)

    fig, ax = plt.subplots()
    ax.hist(activity_data, bins=10)

    ax.set_xlabel("Steps to reach equilibrium state")
    ax.set_ylabel("Count")
    plt.show()


if __name__ == "__main__":
    main()
