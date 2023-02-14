#!/bin/sh -l
pandoc /README.md -o /data/README.pdf --verbose
ls -la /data
ls -la /home
ls -la /github/home