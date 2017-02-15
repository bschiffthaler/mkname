A docker/Ubuntu-like name generator with a bunch of customization features.

## Requirements

  * TCLAP

On Ubuntu, install with:

```
apt install libtclap-dev
```

## Installation

```
git clone https://github.com/bschiffthaler/mkname
cd mkname
make
```

## Dictionaries

* `animals` - [List of animals by common name](https://en.wikipedia.org/wiki/List_of_animals_by_common_name)
* `plants` - [List of plants by common name](https://en.wikipedia.org/wiki/List_of_plants_by_common_name)
* `scientists_full` - [Full names of famous scientists](https://www.famousscientists.org/list/)
* `scientists_last` - [Last names of famous scientists](https://www.famousscientists.org/list/)

## Adjectives

Each noun (name) is paired with an adjective from the Part of Speech Database (http://wordlist.aspell.net/pos-readme)

## Options

```
USAGE:

   ./mkname  [-a] [-M <integer>] [-m <integer>] [-L <character>] [-l
             <character>] [-S <character>] [-s <character>] [-d <animals
             ,plants,scientists_last,scientists_full>] [-n <number>] [--]
             [--version] [-h]


Where:

   -a,  --alliterate
     Make the combination an alliteration (default: false)

   -M <integer>,  --max-length <integer>
     Maximum name length (default: 80)

   -m <integer>,  --min-length <integer>
     Minimum name length (default: 8)

   -L <character>,  --word-delim <character>
     Delimiter between words (default: ' ')

   -l <character>,  --pair-delim <character>
     Delimiter between pairs (default: ' ')

   -S <character>,  --start-adjective <character>
     Start adjective with letter (default: random)

   -s <character>,  --start-subject <character>
     Start subject with letter (default: random)

   -d <animals,plants,scientists_last,scientists_full>,  --dict <animals
      ,plants,scientists_last,scientists_full>
     Dictionary to use (default: 'animals')

   -n <number>,  --number <number>
     Number of names to print (default: 1)
```
