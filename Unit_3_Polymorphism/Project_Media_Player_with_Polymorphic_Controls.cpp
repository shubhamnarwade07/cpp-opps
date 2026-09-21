#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Media {
protected:
    string title;
    string format;

public:
    Media(string t, string f) : title(t), format(f) {}
    virtual ~Media() = default;

    virtual void play() const = 0;
    virtual void pause() const = 0;
    virtual void stop() const = 0;
    virtual void showDetails() const {
        cout << "Title: " << title << " | Format: " << format;
    }
};

class Audio : public Media {
private:
    double lengthInMinutes;

public:
    Audio(string t, string f, double length) : Media(t, f), lengthInMinutes(length) {}

    void play() const override { cout << "Playing audio: " << title << "..." << endl; }
    void pause() const override { cout << "Paused audio: " << title << "." << endl; }
    void stop() const override { cout << "Stopped audio: " << title << "." << endl; }
    
    void showDetails() const override {
        cout << "[Audio] ";
        Media::showDetails();
        cout << " | Duration: " << lengthInMinutes << " mins" << endl;
    }
};

class Video : public Media {
private:
    string resolution;

public:
    Video(string t, string f, string res) : Media(t, f), resolution(res) {}

    void play() const override { cout << "Playing video: " << title << " at " << resolution << "..." << endl; }
    void pause() const override { cout << "Paused video: " << title << "." << endl; }
    void stop() const override { cout << "Stopped video: " << title << "." << endl; }
    
    void showDetails() const override {
        cout << "[Video] ";
        Media::showDetails();
        cout << " | Resolution: " << resolution << endl;
    }
};

class Image : public Media {
private:
    int width, height;

public:
    Image(string t, string f, int w, int h) : Media(t, f), width(w), height(h) {}

    // Images are 'played' by displaying them
    void play() const override { cout << "Displaying image: " << title << "..." << endl; }
    void pause() const override { cout << "Cannot pause an image." << endl; }
    void stop() const override { cout << "Closed image: " << title << "." << endl; }
    
    void showDetails() const override {
        cout << "[Image] ";
        Media::showDetails();
        cout << " | Dimensions: " << width << "x" << height << endl;
    }
};

int main() {
    vector<unique_ptr<Media>> playlist;

    playlist.push_back(make_unique<Audio>("Podcast Episode 1", "MP3", 45.5));
    playlist.push_back(make_unique<Video>("Tutorial Video", "MP4", "1080p"));
    playlist.push_back(make_unique<Image>("Vacation Photo", "JPEG", 1920, 1080));

    cout << "=== Media Library ===" << endl;
    for (const auto& media : playlist) {
        media->showDetails();
    }

    cout << "\n=== Media Player Actions ===" << endl;
    for (const auto& media : playlist) {
        media->play();
        media->pause();
        media->stop();
        cout << "------------------------" << endl;
    }

    return 0;
}
