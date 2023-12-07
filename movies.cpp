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
  for (auto e:p){
    prefixes.push(e); // O(log(m))
  }
}
// The run time for input all prefixes in-order (min-heap) is O(log(m))

void Movie_Prefix :: push(vector<Movie> &m){
  vector<Movie> movie_with_pre;
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
}
// We have m prefixes in alphabetical order, n movies in alphabetical order,
// and k movies for each prefixes (for the worst case)
// We iterate through the m prefix -- O(m)
// While iterating through the prefix, we check if the movie start with the specific prefix
// if the previous prefix is a prefix of the next prefix, 
// we iterate movielist from where the previous prefix started for next prefix
// For the worst case, every next prefix is a prefix of previous prefix,
// then we iterate the whole movie list for every prefix --> O(mn)
// If we find movie start with the prefix, we store it in to a vector
// After we find all movies start with that prefix, we sort the movies in desired order
// For the worst case, we have a k movies for every prefix --> O(m*(klog(k)))
// Therefore, overall, we have mn + mklog(k) --> O(m*n+m*klog(k))
map <string, vector<Movie>> Movie_Prefix :: getmovie_list() const{
  return pre_movie;
}
