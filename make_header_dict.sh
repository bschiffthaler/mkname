#!/bin/bash

echo "#ifndef SRC_HEADER_DICTS" > header_dicts.h
echo "#define SRC_HEADER_DICTS" >> header_dicts.h
echo "#include <map>" >> header_dicts.h
echo "#include <vector>" >> header_dicts.h
echo "#include <string>" >> header_dicts.h

python3 mkmap.py adjectives.txt adjectives >> header_dicts.h
python3 mkmap.py plants.txt plants >> header_dicts.h
python3 mkmap.py animals.txt animals >> header_dicts.h
python3 mkmap.py scientists_last.txt scientists_last >> header_dicts.h
python3 mkmap.py scientists_full.txt scientists_full >> header_dicts.h
python3 mkmap.py lcraft_nou.txt lovecraft >> header_dicts.h
python3 mkmap.py lcraft_adj.txt lovecraft_adj >> header_dicts.h

echo "#endif" >> header_dicts.h
