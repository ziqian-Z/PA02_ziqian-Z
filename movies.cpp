// Movies.cpp -- to sort movies in alphabetical order
// Ziqian Zhao
// 5621867

#include "movies.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

bool operator <(const Movie &m1,const Movie &m2){
  if(m1.movierate == m2.movierate){
    return m1.movieName < m2.movieName;
  }
  else{
    return m1.movierate > m2.movierate;
  }
}

Movie_Prefix :: Movie_Prefix(vector<string> p){
  for (auto e:p){
    prefixes.push_back(e);
  }
  pre_movie.resize(p.size());
}
void Movie_Prefix :: push(vector<Movie> movielist){
  for (int i = 0; i < prefixes.size(); i++){
    vector<Movie> movie_with_pre;
    for(auto e : movielist){
      if (e.movieName.find(prefixes[i]) == 0){
          movie_with_pre.push_back(e);
      }
    }
    sort(movie_with_pre.begin(), movie_with_pre.end(), Comp_ra());
    pre_movie[i] = movie_with_pre;
  }
}

void Movie_Prefix :: print(){ // O(mk+m) 
  //vector <Movie> Best;
  //vector <string> pre_with_movie;
  for (int i = 0; i < pre_movie.size(); i++){ // m
    if(pre_movie[i].empty() == true){
      cout << "No movies found with prefix "<< prefixes[i] << endl;

    }
    else{
      for (auto m : pre_movie[i]){ //k
        cout << m.movieName << ", " << m.movierate << endl;
      }
      cout << endl;
      //pre_with_movie.push_back(prefixes[i]);
      //Best.push_back(pre_movie[i][0]);
    }
  }

  for(int i = 0; i < pre_movie.size();i++){ // m 
    if(pre_movie[i].empty()!= true){
    cout << "Best movie with prefix " << prefixes[i] << " is " ;
    cout << pre_movie[i][0].movieName << " with rating "<< pre_movie[i][0].movierate << endl; 
      // cout << std::fixed << std::setprecision(1) << pre_movie[i][0].movierate << endl;
    }
  }
}