from itertools import groupby
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as anim
import sys


def read_frames(filename):
    frames = []

    with open(filename) as frame_data:
        frame = []
        for line in frame_data:
            if len(line.strip()) != 0:
                frame.append([int(i) for i in line.split()])
            else:
                frames.append(np.array(frame))
                frame = []
    return frames


def main():
    if len(sys.argv) < 2:
        print("Error: incorrect arguments")
        return
    filename = sys.argv[1]
    frames = read_frames(filename)

    fig = plt.figure()
    ax = plt.axes()

    im = plt.imshow(frames[0], animated=True)
    ax.set_axis_off()

    def update_fig(frame, *args):
        im.set_array(frame)
        return im,

    ani = anim.FuncAnimation(
        fig, update_fig, frames=frames, interval=250, blit=True)
    plt.show()


if __name__ == "__main__":
    main()
