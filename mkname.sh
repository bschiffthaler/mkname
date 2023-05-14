#!/bin/bash
#
# Construct an Ubuntu'esque unique identifier
# handy when uniqueness is required for Cloud project, storage bucket, etc...
#
# Examples: modest-mandrill-8404871733, nonimpleme-mammal-6091967462, unsuburbed-landfowl-0328066551
#

function cleanup_string {
  str="$1"
  max_chars_per_section=$2
  force_lowercase=$3
  # remove all special chars
  str=$(echo $str | tr -dc "[:alpha:]")
  # truncate if too long
  str="${str:0:$max_chars_per_section}"

  if [[ $force_lowercase -eq 1 ]]; then
    # making lowercase could also have been done with 'tr'
    echo "${str,,}"
  else
    echo "$str"
  fi
}

function show_usage {
  echo "./$(basename $0) [-h] -L <seperator_char> -m <max_chars_per_section> -M <max_chars_total> [-d <adjectives,animals,numbers>]"
  echo ""
  echo -e "-h\thelp"
  echo -e "-L\tseperator character between words, default '_'"
  echo -e "-m\tmax characters per section, default=10"
  echo -e "-m\tmax characters per section, default=40"
  echo -e "-d\tCSV list of sections, default=adjectives,animals,numbers,characters"
  echo ""
  echo "EXAMPLES":
  echo ""
  echo "Example of building '<adjective>-<plant>'"
  echo "./$(basename $0) -d adjectives,plants"
  echo ""
  echo "Example of building '<adjective>-<number>-<scientist>' with max 8 chars per phrase"
  echo "./$(basename $0) -d adjectives,numbers,scientists_last -m8"
  echo ""
  echo "Example of building '<scientist>_<number>' max 20 chars per phrase, 40 chars total"
  echo "./$(basename $0) -L '_' -d scientists_last,numbers -m20 -M40"
  echo ""
  echo "Example of building '<animal> <letters> <numbers>' allow uppercase"
  echo "./$(basename $0) -L ' ' -d animals,letters,numbers -m20 -M40 -c0"
}

########## MAIN ####################

sep_char="-"
max_chars_per_section=10
max_chars_total=40
sections_csv="adjectives,animals,numbers"
force_lowercase=1

# colon as first char means program will provide its own error messages
optionArgs=":hL:c:m:M:d::"
while getopts "$optionArgs" arg; do
  case "${arg}" in
    h)
      show_usage
      exit 1
      ;;
    L)
      sep_char=$OPTARG
      ;;
    c)
      [[ "$OPTARG" == "0" ]] && force_lowercase=0
      ;;
    m)
      max_chars_per_section=$OPTARG
      ;;
    M)
      max_chars_total=$OPTARG
      ;;
    d)
      sections_csv=$OPTARG
      ;;
    # getopts makes value "?" if flag unrecognized
    ?)
      echo "Invalid option: -${OPTARG}."
      exit 3
      ;;
    :)
      # this OOTB check only works when option is last
      # which is why we use enforce_mandatory_value
      echo "$0: Must supply an argument to -$OPTARG." >&2
      exit 3
      ;;
  esac
done
shift $((OPTIND -1))

# show values after processing getopts
#echo "sep_char = $sep_char"
#echo "max_chars_per_section = $max_chars_per_section"
#echo "sections_csv = $sections_csv"

# start with empty string for final output
output_str=""

# iterate through CSV list of sections
IFS=','
for phrase in $sections_csv; do
  # add separator char if string not empty
  [ -n "$output_str" ] && output_str="${output_str}${sep_char}"

  # either synthesize random numbers or characters, OR grab random line in file
  if [ "$phrase" == "numbers" ]; then
    word=$(cat /dev/urandom | tr -dc '0-9' | fold -w $max_chars_per_section | head -n1)
  elif [ "$phrase" == "letters" ]; then
    word=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w $max_chars_per_section | head -n1)
    word=$(cleanup_string $word $max_chars_per_section $force_lowercase)
  else
    [ -f "$phrase.txt" ] || { echo "ERROR could not find file $phrase.txt"; exit 3; }
    word=$(shuf -n1 "$phrase.txt")
    word=$(cleanup_string $word $max_chars_per_section $force_lowercase)
  fi

  # append to final output
  output_str="${output_str}${word}"
done

# output with limitation on max length
echo "${output_str:0:$max_chars_total}"

