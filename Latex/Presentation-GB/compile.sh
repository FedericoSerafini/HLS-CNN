#!/bin/sh

pdflatex main.tex
pdflatex main.tex
bibtex main
pdflatex main.tex

mv main.pdf ../../HLS-CNN-presentation-GB.pdf
