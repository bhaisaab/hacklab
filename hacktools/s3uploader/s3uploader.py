#!/usr/bin/python
import sys
import mimetypes
import os
import progressbar
import time

from ConfigParser import SafeConfigParser
from optparse import OptionParser
from boto.s3.connection import VHostCallingFormat
from boto.s3.connection import S3Connection
from boto.s3.key import Key
from boto.exception import S3ResponseError

ACCESS_KEY=""
PASS_KEY=""

def sizeof_fmt(num):
    for x in ['bytes','KB','MB','GB','TB']:
        if num < 1024.0:
            return "%3.1f%s" % (num, x)
        num /= 1024.0

def progress_callback(current, total):
    try:
        pbar.update(current)
    except AssertionError, e:
        print e

def upload_file(filename, bucket, prefix=None):

    global pbar

    key = Key(bucket)
    if prefix:
        key.key = '%s/%s' % (prefix, filename)
    else:
        key.key = '%s' % (filename)

    size = os.stat(filename).st_size
    if size == 0:
        print 'Bad filesize for "%s"' % (filename)
        return 0

    widgets = [
        unicode(filename, errors='ignore').encode('utf-8'), ' ',
        progressbar.FileTransferSpeed(),
        ' <<<', progressbar.Bar(), '>>> ',
        progressbar.Percentage(), ' ', progressbar.ETA()
    ]
    pbar = progressbar.ProgressBar(widgets=widgets, maxval=size)
    pbar.start()

    try:
        key.set_contents_from_filename(
            filename,
            cb=progress_callback,
            num_cb=100,
        )
        key.set_acl('public-read')
    except IOError, e:
        print e
        return 0

    pbar.finish()
    return size

#        mime = mimetypes.guess_type(filename)[0]
#    k.set_metadata("Content-Type", mime)

def main():
    parser = OptionParser(usage='usage: %prog [options] ')
    parser.add_option("-b", "--bucket", dest="bucket", default="dl.rohityadav.in", help="s3 bucket name!")
    parser.add_option("-p", "--prefix", dest="prefix", default=None, help="set mimetype")
    (options, args) = parser.parse_args()

    bucketName = options.bucket
    print "[+] Bucket name: %s" % bucketName
    print "[+] Args{%s}: %s" % (len(args), args)

    conn = S3Connection(ACCESS_KEY, PASS_KEY)
    try:
        bucket = conn.get_bucket(bucketName)
    except S3ResponseError, e:
        if e.error_code == 'NoSuchBucket':
            bucket = conn.create_bucket(bucketName)
        else:
            raise e

    stime = time.time()
    total_bytes = 0
    count = 0
    for arg in args:
        print "Uploding file: %s\n" % arg
        size = upload_file(arg, bucket, options.prefix)
        total_bytes += size
        count += 1

    if len(args) > 1:
        print
        print '%s files %s at %.2f kb/s' % (count, sizeof_fmt(total_bytes), (total_bytes / 1024)/time.time() - stime)

if __name__ == '__main__':
    main()
