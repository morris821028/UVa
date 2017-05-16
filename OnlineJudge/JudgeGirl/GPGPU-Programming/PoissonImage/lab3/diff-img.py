"""
	python ./diff-img.py lhs.jpg rhs.jpg
"""
import numpy as np
import sys
from PIL import Image

def rgb(minimum, maximum, value):
    minimum, maximum = float(minimum), float(maximum)
    ratio = 2 * (value-minimum) / (maximum - minimum)
    b = int(max(0, 255*(1 - ratio)))
    r = int(max(0, 255*(ratio - 1)))
    g = 255 - b - r
    return r, g, b

def normalize(arr1, arr2):
    """
    Linear normalization
    """
    arr1 = arr1.astype('float')
    arr2 = arr2.astype('float')
    for i in range(3):
        arr1[...,i] -= arr2[...,i]
        arr1[...,i] = abs(arr1[...,i])

    for i in range(len(arr1)):
        for j in range(len(arr1[i])):
            avg = (arr1[i][j][0] + arr1[i][j][1] + arr1[i][j][2])/3
            for k in range(3):
                arr1[i][j][k] = avg
    diff_mn = 0
#    diff_mx = np.amax(arr1[...,...,0])
    diff_mx = 10
    for i in range(len(arr1)):
        for j in range(len(arr1[i])):
            (arr1[i][j][0], arr1[i][j][1], arr1[i][j][2]) = rgb(diff_mn, diff_mx, arr1[i][j][0])
    return arr1

def demo_normalize(lFILENAME, rFILENAME):
    limg = Image.open(lFILENAME).convert('RGBA')
    rimg = Image.open(rFILENAME).convert('RGBA')
    arr1 = np.array(limg)
    arr2 = np.array(rimg)
    new_img = Image.fromarray(normalize(arr1, arr2).astype('uint8'),'RGBA')
    new_img.save('normalized.jpg')

if __name__ == '__main__':
    demo_normalize(sys.argv[1], sys.argv[2])


