#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Video.h"
#include "Movie.h"
#include "Series.h"
#include "Episode.h"

void loadDataFile(const std::string& fileName, std::vector<Video*>& catalog) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo '" << fileName << "'.\n";
        return;
    }

    std::string line;
    Series* lastSeriesPointer = nullptr;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, ',');

        if (type == "M") {
            std::string id, name, genre, lengthStr, ratingStr;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, lengthStr, ',');
            std::getline(ss, ratingStr, ',');

            // Creamos la película con tus parámetros originales
            Movie* newMovie = new Movie(id, name, genre, std::stoi(lengthStr));
            // Le asignamos el rating que leímos usando setRating
            newMovie->setRating(std::stod(ratingStr)); 
            
            catalog.push_back(newMovie);
            lastSeriesPointer = nullptr;

        } else if (type == "S") {
            std::string id, name, genre, lengthStr, ratingStr;
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, lengthStr, ',');
            std::getline(ss, ratingStr, ',');

            Series* newSeries = new Series(id, name, genre, std::stoi(lengthStr));
            newSeries->setRating(std::stod(ratingStr)); 

            catalog.push_back(newSeries);
            lastSeriesPointer = newSeries;

        } else if (type == "E") {
            std::string title, seasonStr, ratingStr;
            std::getline(ss, title, ',');
            std::getline(ss, seasonStr, ',');
            std::getline(ss, ratingStr, ',');

            if (lastSeriesPointer != nullptr) {
                Episode newEpisode(title, std::stoi(seasonStr));
                newEpisode.setRating(std::stod(ratingStr));
                lastSeriesPointer->addEpisode(newEpisode);
            } else {
                std::cout << "Warning: Episodio sin serie.\n";
            }
        }
    }

    file.close();
    std::cout << "Datos cargados! Total: " << catalog.size() << " videos.\n";
}

int readInt(std::string prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "  Entrada invalida. Ingresa un numero entre " << min << " y " << max << ".\n";
        } else {
            std::cin.ignore(1000, '\n');
            return value;
        }
    }
}

double readDouble(std::string prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "  Entrada invalida. Ingresa un numero entre " << min << " y " << max << ".\n";
        } else {
            std::cin.ignore(1000, '\n');
            return value;
        }
    }
}

std::string readString(std::string prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) return value;
        std::cout << "  El campo no puede estar vacio.\n";
    }
}

void printMenu() {
    std::cout << "\nStreaming Service\n";
    std::cout << "1. Cargar datos\n";
    std::cout << "2. Mostrar videos por rating o genero\n";
    std::cout << "3. Mostrar episodios de una serie por rating\n";
    std::cout << "4. Mostrar peliculas por rating\n";
    std::cout << "5. Calificar un video\n";
    std::cout << "6. Salir\n";
}

int main() {
    std::vector<Video*> catalog;
    bool dataLoaded = false;

    int option;
    do {
        printMenu();
        option = readInt("Elige una opcion: ", 1, 6);

        switch (option) {

        case 1: {
            std::string fileName = readString("Nombre del archivo: ");
            loadDataFile(fileName, catalog);
            dataLoaded = !catalog.empty();
            break;
        }

        case 2: {
            if (!dataLoaded) { std::cout << "  Primero carga los datos.\n"; break; }
            std::cout << "  1. Por rating minimo\n  2. Por genero\n";
            int sub = readInt("  Elige: ", 1, 2);
            if (sub == 1) {
                double minRating = readDouble("  Rating minimo (1-5): ", 1.0, 5.0);
                std::cout << "\n--- Videos con rating >= " << minRating << " ---\n";
                for (auto* v : catalog)
                    if (v->getRating() >= minRating) v->displayData();
            } else {
                std::string genre = readString("  Genero: ");
                std::cout << "\n--- Videos del genero \"" << genre << "\" ---\n";
                for (auto* v : catalog)
                    if (v->getGenre() == genre) v->displayData();
            }
            break;
        }

        case 3: {
            if (!dataLoaded) { std::cout << "  Primero carga los datos.\n"; break; }
            std::string sname = readString("  Nombre de la serie: ");
            double minRating = readDouble("  Rating minimo de episodios (1-5): ", 1.0, 5.0);
            bool found = false;
            for (auto* v : catalog) {
                Series* s = dynamic_cast<Series*>(v);
                if (s != nullptr && s->getName() == sname) {
                    found = true;
                    std::cout << "\n--- Episodios de \"" << sname << "\" con rating >= " << minRating << " ---\n";
                    for (const auto& e : s->getEpisodes())
                        if (e.getRating() >= minRating) std::cout << e;
                }
            }
            if (!found) std::cout << "  Serie no encontrada.\n";
            break;
        }

        case 4: {
            if (!dataLoaded) { std::cout << "  Primero carga los datos.\n"; break; }
            double minRating = readDouble("  Rating minimo (1-5): ", 1.0, 5.0);
            std::cout << "\n--- Peliculas con rating >= " << minRating << " ---\n";
            for (auto* v : catalog) {
                Movie* m = dynamic_cast<Movie*>(v);
                if (m != nullptr && m->getRating() >= minRating) m->displayData();
            }
            break;
        }

        case 5: {
            if (!dataLoaded) { std::cout << "  Primero carga los datos.\n"; break; }
            std::string vname = readString("  Nombre del video a calificar: ");
            double rating = readDouble("  Rating (1-5): ", 1.0, 5.0);
            bool found = false;
            for (auto* v : catalog) {
                if (v->getName() == vname) {
                    v->setRating(rating);
                    std::cout << "  Rating actualizado.\n";
                    found = true;
                }
            }
            if (!found) std::cout << "  Video no encontrado.\n";
            break;
        }

        case 6:
            std::cout << "  Hasta luego!\n";
            break;
        }

        } while (option != 6);

    for (auto* v : catalog) delete v;
    return 0;
}