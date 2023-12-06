// Spring'22
// Instructor: Diba Mirza
// Student name: Ziqian Zhao
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <map>
#include "movies.h"
using namespace std;



bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies

    string line, movieName;
    double movieRating;

    vector<Movie> movielist;
    priority_queue <Movie, vector<Movie>,Comp_al> ordered_movie;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
        movielist.push_back({movieName,movieRating});
    }
    
    movieFile.close();

    if (argc == 2){
        //print all the movies in ascending alphabetical order of movie names
        for (auto e:movielist){
            ordered_movie.push(e);
        }
        int i = 0;
        while(ordered_movie.empty() == false){
            // movielist[i] = ordered_movie.top();
            cout << ordered_movie.top().movieName << ", " << ordered_movie.top().movierate << endl;
            ordered_movie.pop();
            i++;
        }
        // for (auto e:movielist){
        //     cout << e.movieName << endl;
        // }
        return 0;
    }
    // Part 2
    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    // cout << "No movies found with prefix "<<"<replace with prefix>" << endl << endl;

    sort(movielist.begin(),movielist.end(),Comp_al_1());
    Movie_Prefix movies(prefixes);
    movies.push(movielist);
    map<string, vector<Movie>> pre_movie = movies.getmovie_list();
    for (int i = 0; i < prefixes.size();i++){ // m
        string search_prefix = prefixes[i];
        vector<Movie> p = pre_movie.find(prefixes[i])->second; //log(m)
        if (p.empty() == true){
            cout << "No movies found with prefix "<< prefixes[i] << endl;
        }
        else{
            for (auto m : p){ //k
                cout << m.movieName << ", " << m.movierate << endl;
            }
            cout << endl;
        }
    }

    for(int i = 0; i < prefixes.size();i++){ // m
        vector<Movie> p = pre_movie.find(prefixes[i])->second; // log(m)
        if(p.empty()!= true){
            cout << "Best movie with prefix " << prefixes[i] << " is " ;
            cout << p[0].movieName << " with rating "<< p[0].movierate << endl; 
      // cout << std::fixed << std::setprecision(1) << pre_movie[i][0].movierate << endl;
        }
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    // cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/



bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}