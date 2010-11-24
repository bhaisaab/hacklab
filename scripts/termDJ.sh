# Two minutes terminal DJ hack

mix(){ cmus-remote -n -k 40; }
dj(){ while [ 1==1 ]; do mix; sleep 16; done };

nohup cmus &
cmus-remote -p
echo "Running termDJ, Ctrl+C to break"
dj
