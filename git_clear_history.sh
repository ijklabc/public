#!/bin/bash
# https://tecadmin.net/delete-commit-history-in-github/
git checkout --orphan temp_branch
git add -A
git commit -am "the first commit"
git branch -D master
git branch -m master
git push -f origin master
