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
  priority_queue <string, vector<string>> pre;
  for (auto e:p){
    pre.push(e);
  }
  while(!pre.empty()){
    prefixes.push_back(pre.top());
    int idx = prefixes.size()-1;
    int pre_idx = idx-1;
    if(pre_idx >= 0 && prefixes[pre_idx].find(prefixes[idx]) == 0){
      swap(prefixes[pre_idx],prefixes[idx]);
    }
    pre.pop();
  }
  // while(!prefixes.empty()){
  //   cout << prefixes.back()<<endl;
  //   prefixes.pop_back();
  // }
}

void Movie_Prefix :: push(vector<Movie> &m){
  vector<Movie> movie_with_pre;
  int j = 0;
  while(!prefixes.empty() && j < m.size()){
    if (m[j].movieName.find(prefixes.back())==0){
      movie_with_pre.push_back(m[j]);
      // cout << prefixes.top() << " " << m[j].movieName << endl;
      j++;
    }
    else if(m[j].movieName < prefixes.back()){
      j++;
    }
    else{ 
      pre_movie[prefixes.back()] = movie_with_pre;
      prefixes.pop_back();
      movie_with_pre.clear();
    }
  }
  while(!prefixes.empty()){
    pre_movie[prefixes.back()] = movie_with_pre;
    movie_with_pre.clear();
    prefixes.pop_back();
  }
  
  while(!prefixes.empty()){
    if(movie_with_pre.size()>1){
      sort(movie_with_pre.begin(),movie_with_pre.end(),Comp_ra());
    }
    pre_movie[prefixes.back()] = movie_with_pre;
    movie_with_pre.clear();
    prefixes.pop_back();
  }



  // while (!prefixes.empty()){
  //     vector<Movie> movie_with_pre;
  //     for(auto e : m){
  //       if (e.movieName.find(prefixes.top()) == 0){
  //           movie_with_pre.push_back(e);
  //       }
  //     }
  //     // sort(movie_with_pre.begin(), movie_with_pre.end(), Comp_ra());
  //     pre_movie.insert(make_pair(prefixes.top(),movie_with_pre));
  //     prefixes.pop();
  //   }

}


map <string, vector<Movie>> Movie_Prefix :: getmovie_list() const{
  return pre_movie;
}

// Movie_Prefix :: Movie_Prefix(vector<string> &p,vector<Movie> &movie_list){
//   //p: prefix list, in random order
//   //movie_list: vector of alphabetical order
//   for (auto e:p){
//     prefixes.push(e); // min-heap: sort prefix in alphabetical order
//   }
//   int j = 0;
//   while(prefixes.empty() == false && j < movie_list.size()){
//     vector<Movie> movie_with_pre; // vector of movies with certain prefix
//     if (movie_list[j].movieName.find(prefixes.top()) == 0){ // see if the movie start with certain prefix
//       movie_with_pre.push_back(movie_list[j]); // if yes, push back to the vector list
//       j++; // trace next movie
//     }
//     else if(movie_list[j].movieName < prefixes.top()){ // if movie start with letter prioir to prefix
//       j++; // trace next movie
//     }
//     else{ // if movie start with letter later than the prefix
//       sort(movie_with_pre.begin(),movie_with_pre.end(),Comp_ra()); // sort the current stored vector in desired order
//       pre_movie.insert(make_pair(prefixes.top(),movie_with_pre)); // insert the vector to the map with key = prefix, value= movie_vector
//       //j++;
//     }
//     movie_with_pre.clear(); // clear the vector for next prefix
//     prefixes.pop(); // pop current prefix, move to the next one
//   }
// }
// map <string, vector<Movie>> Movie_Prefix :: getmovie_list() const{
//   return pre_movie;
// }
