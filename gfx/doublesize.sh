#!/bin/bash

# creates the screen image
for f in *.png;
do
    echo "Processing $f"
    convert -resize 200% \
        $f ../lgfx/$f
done

