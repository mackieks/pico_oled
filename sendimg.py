#!/usr/bin/python

import sys
import os

from PIL import Image
from PIL import ImageDraw
import struct
import serial

def main():

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