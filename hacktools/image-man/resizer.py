# Depends on python modules: PIL, numpyb

from PIL import Image
from numpy import floor
import glob, os

files = glob.glob("*.JPG")
print files
outputdir = 'output/'
os.mkdir(outputdir)
count = 1
for file in files:
  print "Processing files to output dir: %s... %d%%" % (file, 100 * count / len(files))
  img = Image.open(file)
  width, height = img.size
  ratio = height * 1.0 / width
  newwidth = 1600
  newheight = int(floor(newwidth * ratio))
  img = img.resize((newwidth, newheight), Image.ANTIALIAS)
  img.save(outputdir+file, format="JPEG")
  count += 1
