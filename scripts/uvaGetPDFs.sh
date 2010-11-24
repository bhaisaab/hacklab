#Hack Script: DOWNLOAD UVa Problem Set 1 to 8 from this script :D
# Author: Rohit Yadav <rohityadav89@gmail.com>

#Download pdfs

for ((  j = 1;  j <= 8;  j++  ))
do
  for ((  i = 0 ;  i <= 99;  i++  ))
  do
      k=`expr 100 \* $j + $i`;
      wget http://uva.onlinejudge.org/external/$j/$k.pdf
  done
done

#Move into corresponding dirs

for (( i = 1 ; i <= 8; i++ ))
do
  mkdir Vol\ $i
  mv $i*.pdf ./Vol\ $i
done
