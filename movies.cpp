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
#include <unordered_map> 
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
  for (auto e:p){
    prefixes.push(e); // T = log(m)
  }
}
// The run time for input all prefixes in-order (min-heap) is O(log(m))

void Movie_Prefix :: push(vector<Movie> &m){
  vector<Movie> movie_with_pre; // vector for movies with specific prefix -- space complexity O(k)
  int j = 0;
  int pre = 0;
  int post = 0;
  string prev_prefix = " ";
  while(!prefixes.empty()){ //m
    if (prefixes.top().find(prev_prefix) == 0){ //O(1)
      j = pre; 
    }
    else{
      j = post;
    }
    while(!prefixes.empty() && j < m.size()){ //O(n)
      if (m[j].movieName.find(prefixes.top())==0){
        movie_with_pre.push_back(m[j]);
        j++;
      }
      else if(m[j].movieName < prefixes.top()){
        j++;
      }
      else{ 
        break;
      }
    }
    if(movie_with_pre.size()>1){
      sort(movie_with_pre.begin(),movie_with_pre.end(),Comp_ra());//O(klog(k))
    }
    pre_movie[prefixes.top()] = movie_with_pre; // map for storing all keys and values -- O(m)
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
}

unordered_map <string, vector<Movie>> Movie_Prefix :: getmovie_list() const{
  return pre_movie;
}
