#!/bin/sh -l
find / -name eisvogel.latex -maxdepth 10
pandoc --version
pandoc /README.md --data-dir=/.pandoc --template=eisvogel -o /github/workspace/README.pdf --verbose