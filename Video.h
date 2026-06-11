#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <iostream>

class Video {
    protected:
        std::string id;
        std::string name;
        std::string genre;
        int length;
        double rating;
    public:
        Video();
        Video(std::string _id, std::string _name, std::string _genre, int _length);

        virtual ~Video();

        std::string getId() const;
        std::string getName() const;
        int getLength() const;
        std::string getGenre() const;
        double getRating() const;
        
        void setRating(double _rating);

        virtual void displayData() const = 0;
        friend std::ostream& operator<<(std::ostream& os, const Video& video);
};

#endif