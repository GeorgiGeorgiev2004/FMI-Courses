#include<iostream>
#include<cstring>
#include<fstream>

enum class ErrorInCatalog {
    catalog_not_open,
    read_from_empty_catalog,
    movie_not_in_catalog,
    no_error_occurred
};

struct SafeAnswer {
    int number;
    ErrorInCatalog error;
};

struct Movie {
    char name[128];
    unsigned int price;
};

SafeAnswer getNumberOfMovies(const char* catalogName) {
    SafeAnswer answer;
    std::ifstream ifs(catalogName);
  
    if (!ifs.is_open())
    {
        answer.error = ErrorInCatalog::catalog_not_open;
        answer.number = 0;
    }
    else
    {
        int counter = 0;
        while (!ifs.eof())
        {
            char ch;
            ifs.get(ch);
            if (ch=='\n')
            {
                counter++;
            }
        }
        if (counter==0)
        {
            answer.error = ErrorInCatalog::read_from_empty_catalog;
            answer.number = 0;
        }
        else
        {
            answer.error = ErrorInCatalog::no_error_occurred;
            answer.number=counter+1;
        }
    }
    
    ifs.close();

    return answer;
}

SafeAnswer averagePrice(const char* catalogName) {
    SafeAnswer answer;
    
    std::ifstream ifs(catalogName);

    if (!ifs.is_open())
    {
        answer.number = 0;
        answer.error = ErrorInCatalog::catalog_not_open;
    }
    int moviesCount = 0;
    double priceSum = 0;
    if (ifs.eof())
    {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        answer.number = 0;
        return answer;
    }
    while (!ifs.eof())
    {
        char name[128];
        double price;
        ifs >> name >> price;
        moviesCount++;
        priceSum += price;
    }
    ifs.close();
    if (moviesCount<=0)
    {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        answer.number = 0;
    }    
    else
    {
        answer.error = ErrorInCatalog::no_error_occurred;
        answer.number = priceSum / (moviesCount * 1.0);
    }  
    return answer;
}

SafeAnswer getMoviePrice(const char* catalogName, const char* movieName) {
    SafeAnswer answer;

    std::ifstream ifs(catalogName);

    if (!ifs.is_open())
    {
        answer.number = 0;
        answer.error = ErrorInCatalog::catalog_not_open;
    }
    if (ifs.eof())
    {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        answer.number = 0;
        return answer;
    }
    bool foundMovie = false;
    while (!ifs.eof())
    {
        char name[128];
        double price;
        ifs >> name >> price;
        if (strcmp(movieName,name)==0)
        {
            answer.error = ErrorInCatalog::no_error_occurred;
            answer.number = price;
            foundMovie = true;
            break;
        }
    }
    if (!foundMovie)
    {
        answer.number = 0;
        answer.error = ErrorInCatalog::movie_not_in_catalog;
    }
    return answer;
}

Movie readMovie(std::ifstream& file) {
    Movie movie;
    file >> movie.name >> movie.price;
    return movie;
}

Movie* saveMoviesInArray(std::ifstream& file, int numberOfMovies) {
    Movie* movies = new Movie[numberOfMovies];
    for (size_t i = 0; i < numberOfMovies; i++)
    {
        movies[i] = readMovie(file);
    }
    return movies;
}

void freeMoviesFromArray(Movie*& moviesArray) {
    delete[]moviesArray;
}


void sortMoviesInArray(Movie*& moviesArray, int numberOfMovies) {
    int indexMin = 0;
    for (size_t i = 0; i < numberOfMovies-1; i++)
    {
        indexMin = i;
        for (size_t j = i+1; j < numberOfMovies; j++)
        {
            if (moviesArray[j].price < moviesArray[indexMin].price)
            {
                indexMin = j;
            }
        }
        if (indexMin!=i)
        {
            Movie temp = { "",moviesArray[i].price };
            strcpy_s(temp.name, moviesArray[i].name);
            
            moviesArray[i] = moviesArray[indexMin];

            moviesArray[indexMin] = temp;
        }
    }
}

ErrorInCatalog saveMoviesSorted(const char* catalogName, const char* catalogSortedName) {
    std::ifstream ifs(catalogName);
    
    if (!ifs.is_open())
    {
        return ErrorInCatalog::catalog_not_open;
    }
   
    SafeAnswer movieCount = getNumberOfMovies(catalogName);
    if (movieCount.error==ErrorInCatalog::no_error_occurred)
    {
        Movie* movies = saveMoviesInArray(ifs, movieCount.number);
   
        sortMoviesInArray(movies, movieCount.number);
    
        std::ofstream ofs(catalogSortedName);
        if (!ofs.is_open())
        {
            return ErrorInCatalog::catalog_not_open;
        }
        for (size_t k=0;k<movieCount.number;k++)
        {
            ofs << movies[k].name;
            ofs << " ";
            ofs << movies[k].price;
            ofs << "\n";
        }
        ofs.close();
        freeMoviesFromArray(movies);
    }

    return ErrorInCatalog::no_error_occurred;
}

int main() {
    SafeAnswer safeNumberOfMovies = getNumberOfMovies("movieCatalog.txt");
    if (safeNumberOfMovies.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The number of movies is: " << safeNumberOfMovies.number << std::endl;
    }
    SafeAnswer safeAveragePrice = averagePrice("movieCatalog.txt");
    if (safeAveragePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The average price is: " << safeAveragePrice.number << std::endl;
    }

    SafeAnswer safePrice = getMoviePrice("movieCatalog.txt", "Black-bullet");
    if (safePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The price for the Black bullet movies is: " << safePrice.number << std::endl;
    }

    ErrorInCatalog errorSorting = saveMoviesSorted("movieCatalog.txt", "movieCatalogSorted.txt");
    if (errorSorting == ErrorInCatalog::no_error_occurred) {
        std::cout << "Look the content of the movieCatalogSorted.txt file" << std::endl;
    }
}