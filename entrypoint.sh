#!/bin/sh -l
ls -la root
pandoc ./README.md --template=eisvogel -o README.pdf