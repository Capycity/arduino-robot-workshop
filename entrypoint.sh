#!/bin/sh -l
pandoc /README.md -o /github/workspace/README.pdf --verbose
ls -la /data
ls -la /github/workspace
ls -la /home
ls -la /github/home