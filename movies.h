
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

// Define the calss for movie name and its rating
class Movie{
   public:
      string movieName;
      double movierate;
      friend bool operator <(const Movie &m1,const Movie &m2);
};
// Overload comparison for priority queue
struct Comp_al{
   bool operator()(const Movie &m1,const Movie &m2){
      return m1.movieName > m2.movieName; // ascending alphabetical order 
   }
};
struct Comp_ra{
   bool operator()(const Movie &m1,const Movie &m2){
      return m1 < m2; // descending order of rate
   }
};

class Movie_Prefix{
   private:
      // vector<vector<Movie>> pre_movie;
      priority_queue<string, vector<string>,greater<string>> prefixes;
      // vector<string> prefixes;
      // vector<Movie> movie_list;
      map <string, vector<Movie>> pre_movie;
   public:
      Movie_Prefix(vector<string> &p, vector<Movie> &movie_list);
      // void push();
      map <string, vector<Movie>> getmovie_list() const;
      // void print();
};
