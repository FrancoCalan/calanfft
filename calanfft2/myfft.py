import numpy as np
import datetime

# constants
e  = 2.7182818285
pi = 3.1415926536 

# input signal
npoints = 1024
xr = np.random.uniform(-0.25, 0.25, npoints)
xi = np.random.uniform(-0.25, 0.25, npoints)
#xr = np.array([0.25, 0.25, 0, 0])
#xi = np.array([0, 0, 0, 0])
#xr = np.array([0.25, 0.25, 0.25, 0.25, 0, 0, 0, 0])
#xi = np.array([0, 0, 0, 0, 0, 0, 0, 0])

# useful variables
nstages = int(np.log2(npoints))
y = xr + 1j*xi

# fft-dif
for s in range(nstages):
    m = 2**(nstages-s)
    w = 1+0j
    wm = e**(-1j*pi/(m/2))
    for j in range(m/2):
        for k in range(j, npoints, m):
            u = y[k]
            t = y[k+m/2]
            y[k] = (u+t)/2
            y[k+m/2] = w*(u-t)/2

        w = w*wm

yr = np.real(y)
yi = np.imag(y)
#print yr
#print yi

# print results
#now = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
fx = open('gold_data/gold_' + str(npoints) + '_x.dat', 'w')
fy = open('gold_data/gold_' + str(npoints) + '_y.dat', 'w')

for xre, xie, yre, yie in zip(xr, xi, yr, yi):
    xrs = "{0:+.20f}".format(xre)
    xis = "{0:+.20f}".format(xie)
    yrs = "{0:+.20f}".format(yre)
    yis = "{0:+.20f}".format(yie)
    fx.write(xrs + " " + xis + "\n")
    fy.write(yrs + " " + yis + "\n")

fx.close()
fy.close()
