import cv2
from PIL import Image

def center_crop(img, dim):
	width, height = img.shape[1], img.shape[0]
	crop_width = dim[0] if dim[0]<img.shape[1] else img.shape[1]
	crop_height = dim[1] if dim[1]<img.shape[0] else img.shape[0] 
	mid_x, mid_y = int(width/2), int(height/2)
	cw2, ch2 = int(crop_width/2), int(crop_height/2) 
	crop_img = img[mid_y-ch2:mid_y+ch2, mid_x-cw2:mid_x+cw2]
	return crop_img

img = cv2.imread('screenshot.png', cv2.IMREAD_UNCHANGED)
img = cv2.cvtColor(img, cv2.COLOR_BGR2BGRA)
img2 = cv2.imread('wheel.png', cv2.IMREAD_UNCHANGED)

# img.shape[1] = width
# img.shape[0] = height

if img.shape[1] > img.shape[0]: # height smaller than width
	r = 128.0 / img.shape[0]
	dim = (int(img.shape[1] * r), 128)
elif img.shape[0] > img.shape[1]: # width smaller than height
	r = 128.0 / img.shape[1]
	dim = (128, int(img.shape[0] * r))
else: # 1:1 aspect ratio
	dim = (128,128)

img = cv2.resize(img, dim, interpolation=cv2.INTER_AREA)
img = cv2.copyMakeBorder(img, 128, 128, 128, 128, cv2.BORDER_CONSTANT,value=[0,0,0,0])
img = center_crop(img, (128,128))

r = 128.0 / img2.shape[1]
dim = (128, int(img2.shape[0] * r))

img2 = cv2.resize(img2, dim, interpolation=cv2.INTER_AREA)
img2 = cv2.copyMakeBorder(img2, 128, 128, 128, 128, cv2.BORDER_CONSTANT,value=[0,0,0,0])
img2 = center_crop(img2, (128,128))

cv2.imwrite('screenshot_scaled.png', img)
cv2.imwrite('wheel_scaled.png', img2)

background = Image.open('screenshot_scaled.png')
foreground = Image.open('wheel_scaled.png')

output = Image.alpha_composite(background, foreground).save('combined.png')