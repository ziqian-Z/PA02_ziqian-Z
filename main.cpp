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
#include <unordered_map> 
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

    // clock_t start, end;
    // start = clock();
    sort(movielist.begin(),movielist.end(),Comp_al_1()); // constant space for movielist
    Movie_Prefix movies(prefixes); // O(m) for having a new min-heap
    movies.push(movielist); 
    unordered_map<string, vector<Movie>> pre_movie = movies.getmovie_list();
    for (int i = 0; i < prefixes.size();i++){ // Iterate m times
        string search_prefix = prefixes[i];
        vector<Movie> p = pre_movie.find(prefixes[i])->second; //(1)
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
        vector<Movie> p = pre_movie.find(prefixes[i])->second; // constant time
        if(p.empty()!= true){
            cout << "Best movie with prefix " << prefixes[i] << " is " ;
            cout << p[0].movieName << " with rating "<< p[0].movierate << endl; 
      // cout << std::fixed << std::setprecision(1) << pre_movie[i][0].movierate << endl;
        }
    }
    // end = clock();
    // cout << "Run time is: " << (end - start)/double(CLOCKS_PER_SEC);

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    // cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;
    return 0;
}
// Specific execution time for
// input_20_random, prefix_large: 95ms
// input_100_random, prefix_large: 86ms
// input_1000_random, prefix_large: 106ms
// input_76920_random, prefix_large: 483ms

/* Add your run time analysis for part 3 of the assignment here as commented block*/

/***************************** Run Time Analysis *************************************/ 
/*Reorder prefixes and movielist in alphabetical order*/ 
// use a min-heap for prefixes --> O(log(m))
// use vector or movielist--> O(nlog(n))
// Overall we have T = (log(m)+nlog(n)) for soriting

/* Run time for store values into my data structure*/

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
// Therefore, overall, we have T = m*n+m*klog(k)

/*Run Time for Printing*/
// We have a unordered map with key of prefix, and value of sorted movie vector with that prefix
// Iterating through prefix list to check all prefixes -- m
// For each prefix, find the value of that prefix key -- O(1)
// If the vector is empty, print information; if not print all movies
// For the worst case, every prefix have k movies stored in -- O(mk)
// So, overall movielist print with specific prefix -->T = m+mk

// Then we iterate through the prefix again for the best movies -- m
// We find the prefix in the map -- O(1)
// If the value is not empty, we access the first element
// For the worst case, every prefix has movies -- O(1)
// So, overala priting best movies -->  T = const

// Therefore, the overall runtime is T = log(m)+nlog(n) + m*n+m*klog(k) + m+mk + const
// --> O(mn + nlog(n)+ mklog(k))

/***************************** Space Analysis *************************************/ 
// Using a priority queue to sort prefix in alphabetical order -- O(m)
// Using a vector to store movies with specific prefix -- O(k)
// Using a map to store all prefix and movies -- O(m)
// So, the overall space complexity is O(m+k)
/* Part 3c */
// I re-organized prefixes and movielists to make them into alphabetical order, 
// and try to traverse both list only once to minimize my time complexity
// It is hard to also obtain low space complexity 
// because I would require new space for sorting prefixes and movies
// Inserting prefixes into a min-heap has time complexity of (log(m)), but sorting has time complexity of O(mlog(m))





bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}