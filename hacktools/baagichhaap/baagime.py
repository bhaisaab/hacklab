#!/usr/bin/env python
# baagichhaap: Takes your decent photo and makes it Baagi!
# dependency: python-opencv
# author: bhaisahab

import sys, os
import cv

def detectObjects(imagePath, debug=False):
  import cv
  image = cv.LoadImage(imagePath) #, cv.CV_LOAD_IMAGE_COLOR)
  if debug:
    oimage = cv.LoadImage(imagePath, cv.CV_LOAD_IMAGE_COLOR)

  storage = cv.CreateMemStorage(0)

  cascade = cv.Load('haarcascade_frontalface_default.xml')
  faces = cv.HaarDetectObjects(image, cascade, storage, 1.1, 3, 0, (50,50))

  moochstr = ""
  if not faces:
    return

  for ((fx, fy, fw, fh), fn) in faces:
    if debug: cv.Rectangle(oimage, (fx, fy), (fx+fw, fy+fh), cv.CV_RGB(255,0,0))
    img = cv.GetSubRect(image, (fx, fy, fw, fh))
    cascade = cv.Load('haarcascade_mcs_mouth.xml')
    mouths = cv.HaarDetectObjects(img, cascade, storage, 1.1, 3, 0, (30,30))
    cascade = cv.Load('haarcascade_mcs_nose.xml')
    noses = cv.HaarDetectObjects(img, cascade, storage, 1.1, 3, 0, (20,15))

    if mouths and noses:
      nose = (0,0,0,0)
      mouth = (0,0,0,0)

      for ((nx, ny, nw, nh), nn) in noses:
        if debug: cv.Rectangle(oimage, (fx+nx, fy+ny), (fx+nx+nw, fy+ny+nh), cv.CV_RGB(0,0,255))
        if ny+nh >= nose[1]+nose[3]:
          nose = (nx, ny, nw, nh)

      for ((mx, my, mw, mh), mn) in mouths:
        if debug: cv.Rectangle(oimage, (fx+mx, fy+my), (fx+mx+mw, fy+my+mh), cv.CV_RGB(0,255,0))
        if my > nose[1]:
          mouth = (mx, my, mw, mh)
          break

      if mouth[1] < nose[1]:
        mouth = (nose[0], nose[1]+nose[3]/2, nose[2], nose[3])

      moochw, moochh = fw, 400*fw/1600
      moochx, moochy = fx + (mouth[0] + mouth[2]/2 + nose[0] + nose[2]/2)/2 - moochw/2, fy + (nose[1] + nose[3] + mouth[1] + mouth[3]/3)/2 - moochh/2
      moochstr += """ -draw 'image SrcOver %d,%d %d,%d mooch.png'""" % (moochx, moochy, moochw, moochh)

  if moochstr == "": return
  os.system("convert %s '%s' '%s'" % (moochstr, imagePath, imagePath))

  if debug:
    windown = "baagichaap"
    cv.NamedWindow(windown, 1)
    cv.ShowImage(windown, oimage);
    cv.WaitKey(0);

def main():
  detectObjects(sys.argv[1], len(sys.argv) > 2)

if __name__ == "__main__":
  main()
