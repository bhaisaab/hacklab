#! /bin/bash
# Converts all MP4 files in the current directory to MP3s.

for video in *.MP4; do
  #f=`echo $video | tr ' ' '_'`
  #mv "$video" $f
  #video=$f
  #echo "processing: $video"
  ffmpeg -i $video -f mp3 -ab 192000 -vn $video.mp3
  echo "Done: $video"
done

# Put destination, like here:
# cp *.mp3 /meda/<name your path... to your ipod :)>
