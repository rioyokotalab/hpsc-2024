import numpy as np
import matplotlib.pyplot as plt

nx = 41
ny = 41
nt = 50
c = 1
dx = 2 / (nx - 1)
dy = 2 / (ny - 1)
dt = .01
nu = .05

x = np.linspace(0, 2, nx)
y = np.linspace(0, 2, ny)
u = np.ones((ny, nx))
u[int(.5 / dy):int(1 / dy + 1),int(.5 / dx):int(1 / dx + 1)] = 2
fig = plt.figure(figsize=(11, 7), dpi=100)
ax = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)

for n in range(nt):
    un = u.copy()
    for j in range(1, ny-1):
        for i in range(1, nx-1):
            u[j, i] = (un[j, i] + nu * dt / dx**2 * (un[j, i+1] - 2 * un[j, i] + un[j, i-1])\
                                + nu * dt / dy**2 * (un[j+1, i] - 2 * un[j, i] + un[j-1, i]))
    ax.plot_surface(X, Y, u[:], cmap=plt.cm.coolwarm)
    ax.set_zlim(1, 2)
    plt.pause(.01)
    ax.cla()
plt.show()
