import numpy as np
import matplotlib.pyplot as plt

nx = 81
dx = 2 / (nx-1)
nt = 50
dt = .005
nu = .05

u = np.ones(nx)
u[int(.5 / dx):int(1 / dx + 1)] = 2
for n in range(nt):
    un = u.copy()
    for i in range(1, nx - 1):
        u[i] = un[i] + nu * dt / dx**2 * (un[i+1] - 2 * un[i] + un[i-1])
    plt.plot(np.linspace(0, 2, nx), u)
    plt.axis([0, 2, 0.8, 2.2])
    plt.pause(.01)
    plt.clf()
plt.show()
