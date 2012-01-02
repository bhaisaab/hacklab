# Make this script run every hour at 1AM:
# 0 1 * * * /path-to/auto-backup.sh
# sudo crontab -u root that-file 

SRC='/media/chandrama'
DST='/media/antrix/Backup'
Dirs='eBooks Lectures Media Rohit'

for folder in $Dirs; do
  rsync -vaxAXt --delete-after --progress --ignore-errors $SRC/$folder/ $DST/$folder/
done;
