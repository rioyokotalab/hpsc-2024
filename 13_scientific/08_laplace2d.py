import numpy as np
import matplotlib.pyplot as plt

nx = 41
ny = 41
nt = 50
dx = 2 / (nx - 1)
dy = 2 / (ny - 1)

x = np.linspace(0, 2, nx)
y = np.linspace(0, 2, ny)

p = np.zeros((ny, nx))
p[:, -1] = y

fig = plt.figure(figsize=(11, 7), dpi=100)
ax = fig.gca(projection='3d')
X, Y = np.meshgrid(x, y)

for n in range(nt):
    pn = p.copy()
    for j in range(1, ny-1):
        for i in range(1, nx-1):
            p[j, i] = (dy**2 * (pn[j, i+1] + pn[j, i-1]) +\
                       dx**2 * (pn[j+1, i] + pn[j-1, i])) \
                      / (2 * (dx**2 + dy**2))
    p[:, 0] = 0
    p[:, -1] = y
    p[0, :] = p[1, :]
    p[-1, :] = p[-2, :]
    ax.plot_surface(X, Y, p[:], cmap=plt.cm.coolwarm)
    ax.set_zlim(0, 2)
    ax.view_init(30, 225)
    plt.pause(.01)
    ax.cla()
plt.show()
