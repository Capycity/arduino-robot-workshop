#!/bin/sh -l
find / -name eisvogel.latex -maxdepth 10
pandoc /README.md --template=eisvogel -o /github/workspace/README.pdf --verbose