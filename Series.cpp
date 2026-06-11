#include "Series.h"
#include <iostream>

Series::Series() : Video() {}
Series::Series(std::string _id, std::string _name, std::string _genre, int _length) 
    : Video(_id, _name, _genre, _length) {}

void Series::addEpisode(const Episode& _episode) {
    episodes.push_back(_episode);
    
    double sum = 0.0;
    for (const auto& ep : episodes) {
        sum += ep.getRating();
    }
    if (!episodes.empty()) {
        setRating(sum / episodes.size());
    }
}

std::vector<Episode> Series::getEpisodes() const {
    return episodes;
}

void Series::displayData() const {
    std::cout << "ID: " << id << "\n"
        << "Name: " << name << "\n"
        << "Genre: " << genre << "\n"
        << "Length: " << length << " minutes\n"
        << "Rating: " << rating << "/5\n"
        << "Episodes: " << episodes.size() << "\n";
    for (const auto& episode : episodes) {
        std::cout << episode << "\n";
    }
}