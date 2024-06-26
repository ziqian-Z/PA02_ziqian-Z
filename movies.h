
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_map> 
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
struct Comp_al_1{
   bool operator()(const Movie &m1,const Movie &m2){
      return m1.movieName < m2.movieName; // ascending alphabetical order 
   }
};
struct Comp_ra{
   bool operator()(const Movie &m1,const Movie &m2){
      return m1 < m2; // descending order of rate
   }
};

class Movie_Prefix{
   private:
      priority_queue <string, vector<string>,greater<string>> prefixes;
      // vector<string> prefixes;
      unordered_map <string, vector<Movie>> pre_movie;
   public:
      Movie_Prefix(vector<string> &p);
      unordered_map <string, vector<Movie>> getmovie_list() const;
      void push(vector<Movie> &m);
};
