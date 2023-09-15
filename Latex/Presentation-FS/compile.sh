#!/bin/sh

pdflatex HLS-CNN.tex
pdflatex HLS-CNN.tex

mv HLS-CNN.pdf ../../HLS-CNN-presentation-FS.pdf
