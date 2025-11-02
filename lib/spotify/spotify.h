#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <Arduino.h>
#include <SpotifyEsp32.h>

class SpotifyClient{
    public:
        //it does not only construct the object it also sets everything up
        SpotifyClient();
        //ONLY USE THE FUNCTION WHEN FIRST USING THE API
        void begin();
        void update();

        String getTrackName();
        String getArtistName();

        void playPause();
        void nextTrack();
        void previousTrack();

    private:
        Spotify spotify;

        String trackName;
        String artistName;
        bool isPlaying;
        
        unsigned long lastUpdateTime;
        const long updateInterval = 5000;
};
#endif