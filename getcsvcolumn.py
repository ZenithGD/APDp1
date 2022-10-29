import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

import sys, os

def isfloat(num : str) -> bool:
    """Check if a number is float

    Args:
        num (str): The string to check

    Returns:
        bool: whether the string has a float representation
    """
    try:
        float(num)
        return True
    except ValueError:
        return False

if len(sys.argv) < 4:
    print("Usage: python3 getcsvcolumn.py <input> <col> <output> <scale>")

else:

    scale = 1
    if len(sys.argv) == 5:
        scale = int(sys.argv[4])

    with open(sys.argv[3], 'w') as file:
        data = pd.read_csv(sys.argv[1], sep=',')
        df = pd.DataFrame(data)
        
        # Filter negative values
        datalist = [ int(float(v) * 100) for v in list(filter(isfloat, df[sys.argv[2]].tolist())) if int(float(v) * 100) > 0 ]

        file.write("\n".join(map(str, datalist)))  


        
