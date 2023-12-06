
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
struct Comp_prefix{
   bool operator()(const string &str1, const string &str2){
      int idx = (str1.length() <= str2.length())? str1.length() : str2.length();
      int i = 0;
      while(i < idx && str1[i] == str2[i]){
            i++;
      }
      if (i != 0 &&i == idx-1){
         return str1.length()< str2.length();
      }
      else{
         return str1 < str2;
      }
   }
};

class Movie_Prefix{
   private:
      priority_queue <string, vector<string>,greater<string>> prefixes;
      map <string, vector<Movie>> pre_movie;
   public:
      Movie_Prefix(vector<string> &p);
      map <string, vector<Movie>> getmovie_list() const;
      void push(vector<Movie> &m);
};
