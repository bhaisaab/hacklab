# About rbtool-cloudstack

This is a fork of the reviewboard tool from reviewboard.org:
http://downloads.reviewboard.org/releases/RBTools/0.4/RBTools-0.4.2.tar.gz

I enhanced this tool as per my needs to automate and productivize my
day to day encounters with RB on apache.org.

- Rohit Yadav <bhaisaab@baagi.org>

Do these things to use this
tool:

Append this to your ~/.gitconfig, this is how the tools finds the RB. Or with
the command pass --server=https://reviews.apache.org:

    [reviewboard]
      url = https://reviews.apache.org

Get this tool:

    $ mkdir -p ~/bin && cd ~/bin
    $ git clone git://github.com/bhaisaab/RBTool.git

Let's add a script that saves you from lengthy commands and having to type in
username and password everytime:

    $ echo #!/bin/bash >> rbtool-cs
    $ echo export PYTHONPATH=~/bin/RBTools/:$PYTHONPATH >> rbtool-cs
    $ echo python ~/bin/RBTools/rbtools/postreview.py --username=<put your username here> --password='put here password' --target-groups=cloudstack $* -d -o >> rbtool-cs

Update your PATH:

    $ echo export PATH=~/bin:$PATH >> ~/.zshrc # or ~/.aliasrc or ~/.bashrc or ~/.profile
    $ source ~/.zshrc

If everything goes well, run the following and learn the different options one
can use with reviewboard tool:

    $ rbtool-cs --help

## Setup a patchbin

By default for this tool, I wrote a small python/tornado webapp which can CRUD
patches for me. The source of which is in the rbtools/patchbin directory.

I've hosted this patchbin on my virtual personal server baagi.org and anyone is
free to use it as long as you don't abuse it. While posting the patch for a
review with this tool, it upload the patch to my patchbin

Why? I want my patches to retain my commit messages and signature, and claim
those ohloh points :D

It's easier for the committers/reviewers to just do a git am <patch>, test and
push to the origin/branch.

## Usage AKA Git Workflow

This is my git workflow;

    $ git checkout <the remote branch on which I'm working, master for example>
    $ git pull origin <branch>
    $ git checkout -b my-fix-branch

Try to use commit message with this format: CLOUDSTACK-bugid: \<message\>
Or, if it is not a bug, Submodule: message, like; Api: Fix damn ApiCmdImpl

    $ #work on code, do a lot of git commits :D
    $ git rebase -i HEAD~4 # I squash all commits I made into one
    $ git format-patch -o patches HEAD~1

Now that you've a patch, send it for review:

    $ rbtool-cs --diff-filename=patches/0001-My-Awesome.patch --branch=master --testing-done=master --bugs-closed=CLOUDSTACK-219 --target-people="tsp,edison" -p

In above command or the bash scripts, remove args if you don't need that;

    -d debug mode (default)

    -o opens in browser (default)

    --target-groups=cloudstack (default)

    -p to publish it right away

    --target-people to add comma separated reviewer nicks with no spaces after comma

I modified the tool to automatically take description and summary from the git
formatted patch's subject and commit message.

To get list of open/pending reviews on the RB, do this:

    $ rbtool-cs -l

The output will have this format;

id | submitter | branch (version) | reviewer | update | last review/comment by non-submitter

## Contact

I may ignore if your email don't interest me, feel free to fork this repository
and pimp your own tool. Anyway, email me:
bhaisaab@baagi.org
