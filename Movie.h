#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"

class Movie : public Video {
    private:
    //Nada... No hay nada... todo viene de Video
    public:
        Movie();
        Movie(std::string _id, std::string _name, std::string _genre, int _length);

        void displayData() const override;
};

#endif
