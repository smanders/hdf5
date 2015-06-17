#!/bin/bash

## issue: the live-clones/hdf5 github repo, which mirrors the svn repo, is great - but lacks branches and tags

## create a git repo from the svn repo (from svn r14000 to HEAD)
#git svn clone -s -r14000:HEAD https://svn.hdfgroup.uiuc.edu/hdf5/ -T trunk -b branches -t tags

## checkout the svn repo so we can determine the svn revision of when a branch or tag was created
#svn checkout https://svn.hdfgroup.uiuc.edu/hdf5/trunk hdf5svn
#cd hdf5svn
#svn log --stop-on-copy https://svn.hdfgroup.uiuc.edu/hdf5/branches/hdf5_1_8
## result: hdf5_1_8 r14525
#svn log --stop-on-copy https://svn.hdfgroup.uiuc.edu/hdf5/branches/hdf5_1_8_15
## result: hdf5_1_8_15 r26753
#svn log --stop-on-copy https://svn.hdfgroup.uiuc.edu/hdf5/tags/hdf5-1_8_15
## result: hdf5-1_8_15 r27047
#svn log --stop-on-copy https://svn.hdfgroup.uiuc.edu/hdf5/tags/hdf5-1_8_15-patch1
## result: hdf5-1_8_15-patch1 r27148
#cd ..

## if we need to clone a forked live-clones/hdf5 repo
#git clone git@github.com:smanders/hdf5.git
#cd hdf5

## it would be great if I knew how to graft these branches/tags into the existing git repo
## (so that a git log would show all the commits that lead up to the branch/tag)
## really, I only care about tags for now (for externpro): so I can branch off the tag to create a patch

## hdf5_1_8 branch
#git config --add svn-remote.hdf5_1_8.url https://svn.hdfgroup.uiuc.edu/hdf5/branches/hdf5_1_8/
#git config --add svn-remote.hdf5_1_8.fetch :refs/remotes/svnbranch/hdf5_1_8
#git svn fetch hdf5_1_8 -r 14525
#git svn fetch hdf5_1_8

## hdf5_1_8_15 branch
#git config --add svn-remote.hdf5_1_8_15.url https://svn.hdfgroup.uiuc.edu/hdf5/branches/hdf5_1_8_15/
#git config --add svn-remote.hdf5_1_8_15.fetch :refs/remotes/svnbranch/hdf5_1_8_15
#git svn fetch hdf5_1_8_15 -r 26753
#git svn fetch hdf5_1_8_15

## hdf5-1_8_15 tag
#git config --add svn-remote.hdf5-1_8_15.url https://svn.hdfgroup.uiuc.edu/hdf5/tags/hdf5-1_8_15/
#git config --add svn-remote.hdf5-1_8_15.fetch :refs/remotes/svntags/hdf5-1_8_15
#git svn fetch hdf5-1_8_15 -r 27047
#git svn fetch hdf5-1_8_15
#git tag hdf5-1_8_15 svntags/hdf5-1_8_15

## hdf5-1_8_15-patch1 tag
#git config --add svn-remote.hdf5-1_8_15-patch1.url https://svn.hdfgroup.uiuc.edu/hdf5/tags/hdf5-1_8_15-patch1/
#git config --add svn-remote.hdf5-1_8_15-patch1.fetch :refs/remotes/svntags/hdf5-1_8_15-patch1
#git svn fetch hdf5-1_8_15-patch1 -r 27148
#git svn fetch hdf5-1_8_15-patch1
#git tag hdf5-1_8_15-patch1 svntags/hdf5-1_8_15-patch1
