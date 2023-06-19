import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.cm


df = pd.read_csv('height.csv')

arr = df.to_numpy()
arr = np.delete(arr, -1, axis=1)
#print(arr)

# create gradient green blue colormap

#cmap = colors.LinearSegmentedColormap.from_list("", ['blue','green'])
cmap = colors.ListedColormap(['blue','green'])
#cmap = 'gray'

plt.figure(figsize=(10,10))
plt.imshow(arr, cmap = cmap, vmin = 0, vmax = 255)
plt.savefig('image.png')