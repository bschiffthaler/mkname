# A docker/Ubuntu-like name generator with a bunch of customization features.

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
* `lovecraft` - Nouns in H.P. Lovecraft's combined works with a frequency (>10) and some extra. Manually curated

## Adjectives

Each noun (name) is paired with an adjective from:

* `common-english` - The Part of Speech Database (http://wordlist.aspell.net/pos-readme)
* `lovecraft` - Adjectives in H.P. Lovecraft's combined works with a frequency (>10). Manually curated

## Caveats

The app is geared towards quickly finding alliterations or custom letters. Too restrictive length settings (`-m`, `-M`) or too many output values (`-n`) can cause slow downs. Infinite loops may occur if too restrictive parameters are chosen.

## Options

```
USAGE:

   mkname  [-a] [-D <common-english,lovecraft>] [-M <integer>] [-m
           <integer>] [-L <character>] [-l <character>] [-S <character>]
           [-s <character>] [-d <animals,plants,scientists_last
           ,scientists_full,lovecraft>] [-n <number>] [--] [--version]
           [-h]


Where:

   -a,  --alliterate
     Make the combination an alliteration (default: false)

   -D <common-english,lovecraft>,  --adjective-dict <common-english
      ,lovecraft>
     Dictionary to use for adjectives (default: 'common-english')

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

   -d <animals,plants,scientists_last,scientists_full,lovecraft>,
      --subject-dict <animals,plants,scientists_last,scientists_full
      ,lovecraft>
     Dictionary to use for subjects (default: 'animals')

   -n <number>,  --number <number>
     Number of names to print (default: 1)
```
