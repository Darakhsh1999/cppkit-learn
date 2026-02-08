import numpy as np
import matplotlib.pyplot as plt

# parameters in C++ file
n_dims = 2
K = 5
N = 100

centroids = np.memmap("centroid_data.bin", np.float32, "r", shape=(K,n_dims))
X = np.memmap("X_data.bin", np.float32, "r", shape=(N,n_dims))
print(X.shape)
print(centroids.shape)
print(centroids)


plt.scatter(X[:,0], X[:,1], marker="o", label="data")
plt.scatter(centroids[:,0], centroids[:,1], marker="x", label="centroid")
plt.grid()
plt.legend(frameon=True)
plt.axis([-2,2,-2,2])
plt.show()