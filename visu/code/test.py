from cube_interactive import Cube
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":

	first_shuffle = ["F", "U", "R", "D2", "L'"]

	resolution_shuffle = ["L'", "D2", "R'", "U'", "F'"]

	c = Cube(3)
	c.draw_interactive(first_shuffle, resolution_shuffle)
	plt.show()
