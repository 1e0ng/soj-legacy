#!/bin/sh

git filter-branch --env-filter '

an="$GIT_AUTHOR_NAME"
am="$GIT_AUTHOR_EMAIL"
cn="$GIT_COMMITTER_NAME"
cm="$GIT_COMMITTER_EMAIL"

if [ "$GIT_COMMITTER_EMAIL" = "alazyrabbit@gmail.com" ]
then
    cn="Liang Sun"
    cm="i@liangsun.org"
fi
if [ "$GIT_AUTHOR_EMAIL" = "alazyrabbit@gmail.com" ]
then
    an="Liang Sun"
    am="i@liangsun.org"
fi

export GIT_AUTHOR_NAME="$an"
export GIT_AUTHOR_EMAIL="$am"
export GIT_COMMITTER_NAME="$cn"
export GIT_COMMITTER_EMAIL="$cm"
'
