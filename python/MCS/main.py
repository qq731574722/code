from PIL import Image

im = Image.open(r'C:\code\python\MCS\partially-cloudy.png')
pix = im.load()
width = im.size[0]
height = im.size[1]
print(pix[0, 0])
for x in range(width):
    for y in range(height):
        r, g, b ,a = pix[x, y]
