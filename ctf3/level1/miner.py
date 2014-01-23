import hashlib
import sys

def git_content(content):
    return hashlib.sha1("commit %d\0%s" % (len(content), content)).hexdigest()

body="""tree %s
parent %s
author bhaisaab <bhaisaab@baagi.org> 12345 +0000
committer bhaisaab <bhaisaab@baagi.org> 12345 +0000

Give me a Gitcoin


""" % (sys.argv[1], sys.argv[2])

difficulty = sys.argv[3]
counter = 10000000
while(True):
    proof_of_work = "%s\n%d\n" % (body, counter)
    sha = git_content(proof_of_work)
    if sha < difficulty:
        print proof_of_work
        break
    counter += 1

