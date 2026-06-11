#ifndef EPISODE_H
#define EPISODE_H

#include <string>
#include <iostream>
#include <vector>

class Episode {
    private:
        std::string title;
        int season;
        double rating;

    public:
        Episode();
        Episode(std::string _title, int _season);
        Episode(std::string _title, int _season, double _rating);

        std::string getTitle() const;
        int getSeason() const;
        double getRating() const;

        void setRating(double _rating);

        friend std::ostream& operator<<(std::ostream& os, const Episode& episode);
};

#endif