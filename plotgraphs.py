import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

import sys, os

if len(sys.argv) < 2:
    print("Error: file input required as argument")

else:
    data = pd.read_csv(sys.argv[1], sep=';', index_col=0)
    df = pd.DataFrame(data)
    df.plot()
    plt.title("Coste temporal")
    plt.xlabel("Tamaño")
    plt.ylabel("Tiempo (s)")
    plt.savefig(os.path.splitext(sys.argv[1])[0] + ".png")