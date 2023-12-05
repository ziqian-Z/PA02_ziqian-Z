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
            movielist[i] = ordered_movie.top();
            cout << movielist[i].movieName << ", " << movielist[i].movierate << endl;
            ordered_movie.pop();
            i++;
        }
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
    
    Movie_Prefix movies(prefixes,movielist);
    vector<vector<Movie>> pre_movie = movies.getmovie_list();
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
    // movies.push(movielist);
    // clock_t t;
    // t = clock();
    // movies.print(); //O(mk+m) <= O(n+m)
    // t = clock() - t;
    // printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    // cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/


// In my data structure, movies are stored based on the prefix and desired order
// For printing the process, there is a nested loop, looping over all elements to check if any movies started with i_th prefix 
// if there are movies, print them. So the total run time should be O(mn)
// Then loop over again to check if the prefix has no movie start with. The time complexity for this is O(m*1) = O(m)
// Then loop over again, if the prefix contained in movies, print the first one to get the best rated movie. 
// The time complexity for the third loop is O(m*1) = O(m)
// So the total tun time for the three loop is O(mn+n+n) = O(mn+2m) = O(mn+m)


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}