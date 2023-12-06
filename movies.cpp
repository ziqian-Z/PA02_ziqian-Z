// Movies.cpp -- to sort movies in alphabetical order
// Ziqian Zhao
// 5621867

#include "movies.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

bool operator <(const Movie &m1,const Movie &m2){
  if(m1.movierate == m2.movierate){
    return m1.movieName < m2.movieName;
  }
  else{
    return m1.movierate > m2.movierate;
  }
}

Movie_Prefix::Movie_Prefix(vector<string> &p){
  // priority_queue <string, vector<string>> pre;
  for (auto e:p){
    prefixes.push(e);
  }
}

void Movie_Prefix :: push(vector<Movie> &m){
  vector<Movie> movie_with_pre;
  int j = 0;
  int pre = 0;
  int post = 0;
  string prev_prefix = " ";
  while(!prefixes.empty()){
    if (prefixes.top().find(prev_prefix) == 0){
      j = pre;
    }
    else{
      j = post;
    }
    while(!prefixes.empty() && j < m.size()){
      if (m[j].movieName.find(prefixes.top())==0){
        movie_with_pre.push_back(m[j]);
        // cout << prefixes.top() << " " << m[j].movieName << endl;
        j++;
      }
      else if(m[j].movieName < prefixes.top()){
        j++;
      }
      else{ 
      //   pre_movie[prefixes.top()] = movie_with_pre;
      //   movie_with_pre.clear();
        break;
      }
    }
    if(movie_with_pre.size()>1){
      sort(movie_with_pre.begin(),movie_with_pre.end(),Comp_ra());
    }
    pre_movie[prefixes.top()] = movie_with_pre;
    movie_with_pre.clear();

    if (prefixes.top().find(prev_prefix) == 0){
      pre = j;
    }
    else{
      pre = post;
      post = j;
    }
    prev_prefix = prefixes.top();
    prefixes.pop();
  }

  while(!prefixes.empty()){
    pre_movie[prefixes.top()] = movie_with_pre;
    // movie_with_pre.clear();
    prefixes.pop();
  }
}

map <string, vector<Movie>> Movie_Prefix :: getmovie_list() const{
  return pre_movie;
}
