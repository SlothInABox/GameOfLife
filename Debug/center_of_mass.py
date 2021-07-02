import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
import sys


def read_data(filename):
    data = np.genfromtxt(filename, dtype=int)
    return data


def get_fit(data):
    def f(x, m, c):
        return m * x + c

    popt, pcov = curve_fit(f, data[:, 0], data[:, 1])

    gradient = popt[0]
    gradient_error = pcov[0, 0]

    return popt, pcov


def main():
    if len(sys.argv) < 2:
        print("Error: Incorrect number of arguments")
        return
    filename = sys.argv[1]
    data = read_data(filename)

    data[:, 1] = ((data[:, 1] / 50)**2 + (data[:, 1] % 50)**2)**0.5

    gradients = []

    x = data[:, 0]
    y = data[:, 1]

    fig, ax = plt.subplots()
    ax.scatter(x, y, s=5)

    start_pointer = 0
    while start_pointer < len(data):
        pointer = start_pointer
        previous_pointer = start_pointer
        while True:
            if abs((data[pointer, 1] - data[previous_pointer, 1])) >= 5:
                break
            previous_pointer = pointer
            pointer += 1

            if pointer == len(data) - 1:
                break

        selected_data = data[start_pointer:previous_pointer]
        popt, pcov = get_fit(selected_data)
        gradients.append(popt[0])

        x = selected_data[:, 0]
        y = popt[0] * x + popt[1]

        ax.plot(x, y, linewidth=2, c="black")

        start_pointer = pointer + 10

    gradients = np.array(gradients)
    speed = np.mean(gradients)

    print("Speed: " + str(speed) + " [Cells/Step]")

    ax.set_xlabel("Steps")
    ax.set_ylabel("Position")

    plt.show()


if __name__ == "__main__":
    main()
