import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


df = pd.read_csv('height.csv')

arr = df.to_numpy()
arr = np.delete(arr, -1, axis=1)
#print(arr)

plt.figure(figsize=(10,10))
plt.imshow(arr, cmap = 'gray', vmin = 0, vmax = 255)
plt.savefig('image.png')