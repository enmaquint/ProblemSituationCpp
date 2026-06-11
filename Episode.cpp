#include "Episode.h"
#include <iostream>

Episode::Episode() : title(""), season(0), rating(0.0) {}
Episode::Episode(std::string _title, int _season) 
    : title(_title), season(_season), rating(0.0) {}
Episode::Episode(std::string _title, int _season, double _rating) : title(_title), season(_season), rating(_rating) {}

std::string Episode::getTitle() const { return title; }
int Episode::getSeason() const { return season; }
double Episode::getRating() const { return rating; }
void Episode::setRating(double _rating) { rating = _rating; }

std::ostream& operator<<(std::ostream& os, const Episode& episode) {
    os << "Titulo: " << episode.title << "\n"
        << "Temporada: " << episode.season << "\n"
        << "Calificacion: " << episode.rating << "/5\n";
    return os;
}
