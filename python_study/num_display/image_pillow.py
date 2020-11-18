# -*- coding: utf-8 -*-

from PIL import Image
import numpy as np

if 0:
    im = np.array(Image.open("./beijing.jpg"))
    print(im.shape, im.dtype)
    
    a = [255, 255, 255] - im
    b = Image.fromarray(a.astype('uint8'))
    b.save("./beijing1.jpg")

if 0:
    a = np.array(Image.open("./beijing.jpg").convert("L"))
    b = 255 - a
    im = Image.fromarray(b.astype('uint8'))
    im.save("./beijing2.jpg")
    
if 0:
    a = np.array(Image.open("./beijing.jpg").convert("L"))
    # area transfer
    b = (100/255) * a + 150
    im = Image.fromarray(b.astype("uint8"))
    im.save("./beijing3.jpg")

    c = 255 * (a/255)**2
    im = Image.fromarray(c.astype("uint8"))
    im.save("./beijing4.jpg")

if 1:
    # 手绘图像效果：
    # 1 黑白灰色
    # 2 边缘线条较重
    # 3 相同或相近色彩趋于白色
    # 4 略有光源效果
    a = np.array(Image.open("./beijing.jpg").convert("L")).astype("float")
    
    depth = 10.
    # 取图像灰度的梯度值
    grad = np.gradient(a)
    # 分别取横纵图像梯度值
    grad_x, grad_y = grad
    grad_x = grad_x * depth / 100.
    grad_y = grad_y * depth / 100.
    A = np.sqrt(grad_x ** 2 + grad_y ** 2 + 1.)
    uni_x = grad_x / A
    uni_y = grad_x / A
    uni_z = 1./A

    # 光源的俯视角度，弧度值
    vec_el = np.pi/2.2
    # 光源的方位角度，弧度值
    vec_az = np.pi/4.
    # 光源对 x轴的影响
    dx = np.cos(vec_el) * np.cos(vec_az)
    dy = np.cos(vec_el) * np.sin(vec_az)
    dz = np.sin(vec_el)

    b = 255 * (dx * uni_x + dy * uni_y + dz * uni_z)
    b = b.clip(0, 255)

    #光源归一化
    im = Image.fromarray(b.astype("uint8"))
    im.save("./beijing5.jpg")
