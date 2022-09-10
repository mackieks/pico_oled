#!/usr/bin/python

import sys
import os

import cv2
from PIL import Image
from PIL import ImageDraw
import struct
import serial

def center_crop(img, dim):
    width, height = img.shape[1], img.shape[0]
    crop_width = dim[0] if dim[0]<img.shape[1] else img.shape[1]
    crop_height = dim[1] if dim[1]<img.shape[0] else img.shape[0] 
    mid_x, mid_y = int(width/2), int(height/2)
    cw2, ch2 = int(crop_width/2), int(crop_height/2) 
    crop_img = img[mid_y-ch2:mid_y+ch2, mid_x-cw2:mid_x+cw2]
    return crop_img

def main():

    img = cv2.imread('screenshot.png', cv2.IMREAD_UNCHANGED)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2BGRA)
    img2 = cv2.imread('wheel.png', cv2.IMREAD_UNCHANGED)

    # img.shape[1] = width
    # img.shape[0] = height

    if img.shape[1] > img.shape[0]: # height smaller than width
        r = 96.0 / img.shape[0]
        dim = (int(img.shape[1] * r), 64)
    elif img.shape[0] > img.shape[1]: # width smaller than height
        r = 64.0 / img.shape[1]
        dim = (96, int(img.shape[0] * r))
    else: # 1:1 aspect ratio
        dim = (96,64)

    img = cv2.resize(img, dim, interpolation=cv2.INTER_AREA)
    img = cv2.copyMakeBorder(img, 128, 128, 128, 128, cv2.BORDER_CONSTANT,value=[0,0,0,0])
    img = center_crop(img, (96,64))

    r = 96.0 / img2.shape[1]
    dim = (96, int(img2.shape[0] * r))

    img2 = cv2.resize(img2, dim, interpolation=cv2.INTER_AREA)
    img2 = cv2.copyMakeBorder(img2, 128, 128, 128, 128, cv2.BORDER_CONSTANT,value=[0,0,0,0])
    img2 = center_crop(img2, (96,64))

    cv2.imwrite('screenshot_scaled.png', img)
    cv2.imwrite('wheel_scaled.png', img2)

    background = Image.open('screenshot_scaled.png')
    foreground = Image.open('wheel_scaled.png')

    output = Image.alpha_composite(background, foreground).save('combined.png')

    len_argument = len(sys.argv)
    filesize = 0
    if (len_argument != 3):
      print ("")
      print ("Correct Usage:")
      print ("\tpython png2rgb565.py <png_file> <binary_file>")
      print ("")
      sys.exit(0)

    try:
        im=Image.open(sys.argv[1])
        #print ("/* Image Width:%d Height:%d */" % (im.size[0], im.size[1]))
    except:
        print ("Fail to open png file ", sys.argv[1])
        sys.exit(0)

    image_height = im.size[1]
    image_width = im.size[0]

    try:
        binoutfile = open(sys.argv[2],"wb")
    except:
        print ("Can't write the binary file %s" % sys.argv[2])
        sys.exit(0)

    pix = im.load()  #load pixel array
    for h in range(image_height):
        for w in range(image_width):

            if w < im.size[0]:
                R=pix[w,h][0]>>3
                G=pix[w,h][1]>>2
                B=pix[w,h][2]>>3

                rgb = (R<<11) | (G<<5) | B

                binoutfile.write(struct.pack('H', rgb))

            else:
                rgb = 0

    binoutfile.close()

    ser = serial.Serial('COM3', 921600)

    data = open("out.bin","rb")

    ser.write(data.read())  

    data.close()

if __name__=="__main__":
  main()