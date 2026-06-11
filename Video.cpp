#include "Video.h"

Video::Video() : id(""), name(""), genre(""), length(0), rating(0.0) {}
Video::Video(std::string _id, std::string _name, std::string _genre, int _length) 
    : id(_id), name(_name), genre(_genre), length(_length), rating(0.0) {}

Video::~Video() {}

std::string Video::getId() const { return id; }
std::string Video::getName() const { return name; }
int Video::getLength() const { return length; }
std::string Video::getGenre() const { return genre; }
double Video::getRating() const { return rating; }
void Video::setRating(double _rating) { rating = _rating; }


std::ostream& operator<<(std::ostream& os, const Video& video) {
    os << "ID: " << video.id << "\n"
        << "Name: " << video.name << "\n"
        << "Genre: " << video.genre << "\n"
        << "Length: " << video.length << " minutes\n"
        << "Rating: " << video.rating << "/5\n";
    return os;
}