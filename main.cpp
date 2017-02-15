#include "header_dicts.h"
#include <tclap/CmdLine.h>
#include <random>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <set>

std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

std::string uc(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

std::string lc(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
}

std::string make_delim(std::string s, char delim = ' ')
{
  for(auto it = s.begin(); it != s.end(); it++)
    {
      if( std::isspace(*it) )
        {
          (*it) = delim;
        }
    }
  return s;
}

std::string get_rand_subject(std::map<char,
                             std::vector<std::string> > dict)
{
  std::vector<char> keys;
  for(auto c : dict)
    keys.push_back(c.first);
      
  std::uniform_int_distribution<size_t> d_first(0,keys.size() - 1);
  char k = keys[ d_first(generator) ];

  std::vector<std::string>& subs = dict[k];
  std::uniform_int_distribution<size_t> d_second(0,subs.size() - 1);
  return subs[ d_second(generator) ];
}

std::string get_rand_adjective(std::map<char,
                               std::vector<std::string> > dict)
{
  std::vector<char> keys;
  for(auto c : dict)
    keys.push_back(c.first);

  std::uniform_int_distribution<size_t> d_first(0,keys.size() - 1);
  char k = keys[ d_first(generator) ];

  std::vector<std::string>& adjs = dict[k];
  std::uniform_int_distribution<size_t> d_second(0,adjs.size() - 1);
  return adjs[ d_second(generator) ];
}

std::string get_adjective_by_first(char k,
                                   std::map<char,
                                   std::vector<std::string> > dict)
{
  auto it = dict.find(toupper(k));
  if(it == dict.end())
    return "";
  std::vector<std::string>& a = it->second;
  std::uniform_int_distribution<size_t> d(0, a.size() - 1);
  return a[ d(generator) ];
}

std::string get_subject_by_first(char k,
                                 std::map<char,
                                 std::vector<std::string> > dict)
{
  auto it = dict.find(toupper(k));
  if(it == dict.end())
    return "";
  std::vector<std::string>& s = it->second;
  std::uniform_int_distribution<size_t> d(0, s.size() - 1);
  return s[ d(generator) ];
}

int main(int argc, char ** argv)
{
  size_t n = 1;
  std::string dict = "animals";
  std::string adj_dict = "common-english";
  bool alliterate = false;
  char s = '\0';
  char S = '\0';
  char pair_delim = ' ';
  char word_delim = ' ';
  size_t minlength = 8;
  size_t maxlength = 80;
  try
    {
      TCLAP::CmdLine cmd("Generate random adjective - subject combinations", ' ', "0.9");
      TCLAP::ValueArg<size_t> arg_n("n", "number",
                                    "Number of names to print (default: 1)",
                                    false, 1, "number");
      TCLAP::ValueArg<std::string> arg_d("d", "subject-dict",
                                         "Dictionary to use for subjects (default: 'animals')",
                                         false, "animals", "animals,plants,scientists_last,scientists_full,lovecraft");
      TCLAP::ValueArg<std::string> arg_D("D", "adjective-dict",
                                         "Dictionary to use for adjectives (default: 'common-english')",
                                         false, "animals", "common-english,lovecraft");
      TCLAP::ValueArg<char> arg_s("s", "start-subject",
                                  "Start subject with letter (default: random)",
                                  false, '\0', "character");
      TCLAP::ValueArg<char> arg_S("S", "start-adjective",
                                  "Start adjective with letter (default: random)",
                                  false, '\0', "character");
      TCLAP::ValueArg<char> arg_l("l", "pair-delim",
                                  "Delimiter between pairs (default: ' ')",
                                  false, ' ', "character");
      TCLAP::ValueArg<char> arg_L("L", "word-delim",
                                  "Delimiter between words (default: ' ')",
                                  false, ' ', "character");
      TCLAP::ValueArg<size_t> arg_m("m", "min-length",
                                  "Minimum name length (default: 8)",
                                  false, 8, "integer");
      TCLAP::ValueArg<size_t> arg_M("M", "max-length",
                                  "Maximum name length (default: 80)",
                                  false, 80, "integer");
      cmd.add(arg_n);
      cmd.add(arg_d);
      cmd.add(arg_s);
      cmd.add(arg_S);
      cmd.add(arg_l);
      cmd.add(arg_L);
      cmd.add(arg_m);
      cmd.add(arg_M);
      cmd.add(arg_D);
      TCLAP::SwitchArg switch_a("a","alliterate",
                                "Make the combination an alliteration (default: false)",
                                cmd, false);
      cmd.parse(argc, argv);

      n = arg_n.getValue();
      dict = arg_d.getValue();
      alliterate = switch_a.getValue();
      s = arg_s.getValue();
      S = arg_S.getValue();
      pair_delim = arg_l.getValue();
      word_delim = arg_L.getValue();
      minlength = arg_m.getValue();
      maxlength = arg_M.getValue();
      adj_dict = arg_D.getValue();
    }
  catch (TCLAP::ArgException &e)
    {
      std::cerr << "error: " << e.error() << " for arg " << e.argId() << '\n';
    }

  if(minlength < 8)
    {
      std::cerr << "Setting min-length < 8 probably leads to an infinite loop.\n";
    }
  
  std::map<char, std::vector<std::string> >& subject_dict =
    dict == "animals" ? animals :
    dict == "plants" ? plants :
    dict == "scientists_last" ? scientists_last :
    dict == "lovecraft" ? lovecraft :
    animals; //default

  std::map<char, std::vector<std::string> >& adjective_dict =
    dict == "common-english" ? adjectives :
    dict == "lovecraft" ? lovecraft_adj :
    adjectives; //default
  
  std::set<std::string> res;
  while(res.size() < n)
    {
      std::string subj, adj;
      while(subj.size() + adj.size() + 1 < minlength ||
            subj.size() + adj.size() + 1 > maxlength)
        {
          if(s == '\0')
            {
              subj = get_rand_subject(subject_dict);
              if(S != '\0')
                {
                  adj = get_adjective_by_first(S, adjective_dict);
                }
              else if(alliterate)
                {
                  adj = get_adjective_by_first(subj[0], adjective_dict);
                }
              else
                {
                  adj = get_rand_adjective(adjective_dict);;
                }
              if( adj == "" && S != '\0' )
                {
                  std::cerr << "Current dict has no adjectives for letter "
                            <<  S << '\n';
                  return 1;
                }
              else if(adj == "")
                {
                  subj = "";
                  continue;
                }
                
            }
          else
            {
              subj = get_subject_by_first(s, subject_dict);
              if(S != '\0')
                {
                  adj = get_adjective_by_first(S, adjective_dict);
                }
              else if(alliterate)
                {
                  adj = get_adjective_by_first(subj[0], adjective_dict);
                }
              else
                {
                  adj = get_rand_adjective(adjective_dict);
                }
              if( ( adj == "" && S != '\0' ) ||
                  ( adj == "" && alliterate ) )
                {
                  std::cerr << "Current dict has no adjectives for letter "
                            <<  s << '\n';
                  return 1;
                }
              else if(adj == "")
                {
                  subj = "";
                  continue;
                }
            }
        }
      res.insert(make_delim(lc(adj), word_delim) +
                 std::string(1, pair_delim) +
                 make_delim(lc(subj), word_delim));
    }

  for(auto& p : res)
    std::cout << p << '\n';
  
  return 0;
}
