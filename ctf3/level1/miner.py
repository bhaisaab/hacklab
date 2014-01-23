import hashlib
import sys
import thread
import threading

def git_content(content):
    return hashlib.sha1("commit %d\0%s" % (len(content), content)).hexdigest()

body="""tree %s
parent %s
author bhaisaab <bhaisaab@baagi.org> 54321 +0000
committer bhaisaab <bhaisaab@baagi.org> 54321 +0000

Give me a Gitcoin

""" % (sys.argv[1], sys.argv[2])

difficulty = sys.argv[3]
counter = 10000000

done = False
lock = threading.Lock()

def mine(slot):
    global body
    global done
    global lock
    counter = slot * 10000000
    limit = 10000000 * (slot + 1)
    while (counter < limit):
        if done: break
        proof_of_work = "%s\n%d\n" % (body, counter)
        sha = git_content(proof_of_work)
        if not done and sha < difficulty:
            if not lock.locked():
                lock.acquire()
                print proof_of_work
                done = True
            break
        counter += 1

for i in range(10):
    thread.start_new_thread(mine, (i,))

while 1:
   if done: sys.exit(0)
