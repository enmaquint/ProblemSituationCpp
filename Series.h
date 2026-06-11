#ifndef SERIES_H
#define SERIES_H

#include "Video.h"
#include "Episode.h"

class Series : public Video {
    private:
        std::vector<Episode> episodes;

    public:
        Series();
        Series(std::string _id, std::string _name, std::string _genre, int _length);

        void addEpisode(const Episode& _episode);
        std::vector<Episode> getEpisodes() const;

        void displayData() const override;
};

#endif