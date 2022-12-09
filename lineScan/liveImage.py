import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

nx = 5
ny = 128

fig = plt.figure()
data = np.zeros((nx, ny))
im = plt.imshow(data, cmap='gist_gray_r', vmin=0, vmax=1023)
#image = np.random.rand(1, 128)
image = np.array([[156,157,160,159,164,0,0,212,218,223,232,244,256,269,281,293,303,314,327,338,347,376,439,506,565,627,687,734,787,838,893,931,964,992,1015,1023,1023,1023,1023,1023,1023,1021,989,953,905,855,800,747,686,620,550,483,412,333,250,201,188,183,177,175,172,170,170,170,170,170,172,173,175,170,147,142,143,145,145,149,150,175,198,204,209,219,230,241,254,267,279,290,302,314,322,332,363,422,488,550,613,670,718,769,822,877,917,949,977,999,1014,1023,1023,1023,1023,1022,1014,986,948,901,852,795,743,683,618,546,480,410,329,247,195,182]])

def init():
    im.set_data(image)

def animate(i):
    xi = i // ny
    yi = i % ny
    data[xi, yi] = 1
    image = np.array([[156,157,160,159,164,0,0,212,218,223,232,244,256,269,281,293,303,314,327,338,347,376,439,506,565,627,687,734,787,838,893,931,964,992,1015,1023,1023,1023,1023,1023,1023,1021,989,953,905,855,800,747,686,620,550,483,412,333,250,201,188,183,177,175,172,170,170,170,170,170,172,173,175,170,147,142,143,145,145,149,150,175,198,204,209,219,230,241,254,267,279,290,302,314,322,332,363,422,488,550,613,670,718,769,822,877,917,949,977,999,1014,1023,1023,1023,1023,1022,1014,986,948,901,852,795,743,683,618,546,480,410,329,247,195,182]])

    im.set_data(image)
    return im

anim = animation.FuncAnimation(fig, animate, init_func=init, frames=nx * ny, interval=5)
plt.show()
