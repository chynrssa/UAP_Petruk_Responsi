#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class User {
public:
    string username;
    string password;

    User(string uname, string pwd) : username(uname), password(pwd) {}

    bool login(string uname, string pwd) {
        return username == uname && password == pwd;
    }
};

class Movie {
private:
    string title;
    string schedule;
    string day;
    int price;

public:
    Movie(string t, string s, string d, int p) : title(t), schedule(s), day(d), price(p) {}

    string getTitle() const { return title; }
    void setTitle(const string& t) { title = t; }

    string getSchedule() const { return schedule; }
    void setSchedule(const string& s) { schedule = s; }

    string getDay() const { return day; }
    void setDay(const string& d) { day = d; }

    int getPrice() const { return price; }
    void setPrice(int p) { price = p; }
};

class Cinema {
private:
    vector<vector<int>> seats;
    vector<Movie*> movies;
    const int numSeats = 50; 

    string center(const string &str, int width) {
        int len = str.length();
        if (len >= width) {
            return str;
        }
        int leftPadding = (width - len) / 2;
        int rightPadding = width - len - leftPadding;
        return string(leftPadding, ' ') + str + string(rightPadding, ' ');
    }

    string centerPrice(int price, int width) {
        string priceStr = "Rp " + to_string(price * 10000);
        int len = priceStr.length();
        if (len >= width) {
            return priceStr;
        }
        int leftPadding = (width - len) / 2;
        int rightPadding = width - len - leftPadding;
        return string(leftPadding, ' ') + priceStr + string(rightPadding, ' ');
    }

public:
    Cinema() {
        for (auto movie : movies) {
            delete movie;
        }
    }

    void addMovie(Movie* movie) {
        movies.push_back(movie);
        seats.push_back(vector<int>(numSeats, 0));
    }

    void displayMovies() {
        cout << "\033[1;34m" << setw(5) << center("ID", 5) 
             << setw(30) << center("Judul Film", 30) 
             << setw(15) << center("Hari", 15) 
             << setw(20) << center("Jam Tayang", 20) 
             << setw(15) << center("Harga", 15) 
             << setw(10) << center("Studio", 10) 
             << "\033[0m" << endl;
        cout << "\033[1;34m----------------------------------------------------------------------------------------------\033[0m" << endl;
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << setw(5)  << center(to_string(i + 1), 5)
                 << setw(30) << center(movies[i]->getTitle(), 30)
                 << setw(15) << center(movies[i]->getDay(), 15)
                 << setw(20) << center(movies[i]->getSchedule(), 20)
                 << setw(15) << centerPrice(movies[i]->getPrice(), 15)
                 << setw(10) << center("Studio " + string(1, 'A' + i), 10) 
                 << endl;
        }
        cout << "\033[1;34m-----------------------------------------------------------------------------------------------\033[0m" << endl;
    }

    bool selectSeat(size_t movieID, int seatNumber) {
        if (seats[movieID][seatNumber] == 0) {
            seats[movieID][seatNumber] = 1;
            return true;
        }
        return false;
    }

    Movie* getMovie(size_t movieID) {
        return movies[movieID];
    }

    size_t getNumberOfMovies() {
        return movies.size();
    }