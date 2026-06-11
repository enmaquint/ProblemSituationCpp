#include "Movie.h"
#include <iostream>

Movie::Movie() : Video() {}
Movie::Movie(std::string _id, std::string _name, std::string _genre, int _length) : Video(_id, _name, _genre, _length) {}

void Movie::displayData() const {
    std::cout << "ID: " << id << "\n"
        << "Name: " << name << "\n"
        << "Genre: " << genre << "\n"
        << "Length: " << length << " minutes\n"
        << "Rating: " << rating << "/5\n";
}