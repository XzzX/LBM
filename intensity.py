import numpy as np
import matplotlib.pyplot as pl
import scipy.interpolate

x, y, ux, uy, rho = np.loadtxt("20.txt").transpose()

#Set up a regular grid of interpolation points
xi, yi = np.linspace(x.min(), x.max(), 60), np.linspace(y.min(), y.max(), 20)
xi, yi = np.meshgrid(xi, yi)

#Interpolate; there's also method='cubic' for 2-D data such as here
zi = scipy.interpolate.griddata((x, y), rho, (xi, yi), method='linear')

pl.imshow(zi, vmin=rho.min(), vmax=rho.max(), origin='lower',
           extent=[x.min(), x.max(), y.min(), y.max()])
pl.scatter(x, y, c=rho)
pl.colorbar()

pl.quiver(x,y,ux,uy, width=0.002)
pl.show()

import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim=(x.min(), x.max()), ylim=(y.min(), y.max()))
line = ax.imshow(zi, vmin=1, vmax=2, origin='lower', cmap="autumn", extent=[x.min(), x.max(), y.min(), y.max()])
line2 = ax.quiver(x,y,ux,uy, width=0.001, scale = 15)

# initialization function: plot the background of each frame
def init():
    line.set_data(zi)
    line2.set_UVC(ux,uy)
    return line,

# animation function.  This is called sequentially
def animate(i):
	print i
	x, y, ux, uy, rho = np.loadtxt("{0}.txt".format(i)).transpose()

	# Set up a regular grid of interpolation points
	xi, yi = np.linspace(x.min(), x.max(), 60), np.linspace(y.min(), y.max(), 20)
	xi, yi = np.meshgrid(xi, yi)

	# Interpolate; there's also method='cubic' for 2-D data such as here
	zi = scipy.interpolate.griddata((x, y), rho, (xi, yi), method='linear')
	line.set_data(zi)
	#line.autoscale()
	line2.set_UVC(ux,uy)
	return line,line2

# call the animator.  blit=True means only re-draw the parts that have changed.
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=400, interval=100, blit=True)

# save the animation as an mp4.  This requires ffmpeg or mencoder to be
# installed.  The extra_args ensure that the x264 codec is used, so that
# the video can be embedded in html5.  You may need to adjust this for
# your system: for more information, see
# http://matplotlib.sourceforge.net/api/animation_api.html
#anim.save('basic_animation.avi', fps=30)

plt.show()