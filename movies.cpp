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
using namespace std;

bool operator <(const Movie &m1,const Movie &m2){
  if(m1.movierate == m2.movierate){
    return m1.movieName < m2.movieName;
  }
  else{
    return m1.movierate > m2.movierate;
  }
}

Movie_Prefix :: Movie_Prefix(vector<string> &p,vector<Movie> &m){
  for (auto e:p){
    prefixes.push_back(e);
  }
  sort(prefixes.begin(),prefixes.end()); // sort prefix in alphabetical order

  pre_movie.resize(p.size());
  for (auto e:m){
    movie_list.push_back(e);
  }
  sort(movie_list.begin(),movie_list.end(),Comp_al()); // sort movie in alphabetical order
// }
// void Movie_Prefix :: push(){
  for (int i = 0; i < prefixes.size(); i++){
    vector<Movie> movie_with_pre;
    for(int j = 0; j < movie_list.size();){
      if (movie_list[j].movieName.find(prefixes[i]) == 0){
          movie_with_pre.push_back(movie_list[j]);
      }
      if (movie_list[j].movieName < prefixes[i]){
        j++;
      }
    }
    // sort(movie_with_pre.begin(), movie_with_pre.end(), Comp_ra());
    pre_movie[i] = movie_with_pre;
  }
}

vector<vector<Movie>> Movie_Prefix :: getmovie_list() const{
  return pre_movie;
}
// void Movie_Prefix :: print(){ // O(mk+m) 
//   //vector <Movie> Best;
//   //vector <string> pre_with_movie;
//   for (int i = 0; i < pre_movie.size(); i++){ // m
//     if(pre_movie[i].empty() == true){
//       cout << "No movies found with prefix "<< prefixes[i] << endl;

//     }
//     else{
//       for (auto m : pre_movie[i]){ //k
//         cout << m.movieName << ", " << m.movierate << endl;
//       }
//       cout << endl;
//       //pre_with_movie.push_back(prefixes[i]);
//       //Best.push_back(pre_movie[i][0]);
//     }
//   }

//   for(int i = 0; i < pre_movie.size();i++){ // m 
//     if(pre_movie[i].empty()!= true){
//     cout << "Best movie with prefix " << prefixes[i] << " is " ;
//     cout << pre_movie[i][0].movieName << " with rating "<< pre_movie[i][0].movierate << endl; 
//       // cout << std::fixed << std::setprecision(1) << pre_movie[i][0].movierate << endl;
//     }
//   }
// }