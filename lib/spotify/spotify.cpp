#include "spotify.h"
#include "../credentials.h"

SpotifyClient :: SpotifyClient(): spotify(CLIENT_ID,CLIENT_SECRET,REFRESH_TOKEN){
    lastUpdateTime = 0;
}

void SpotifyClient :: begin(){
    spotify.begin();
}

void SpotifyClient :: update(){
    // Query the Spotify API no more than once every updateInterval (1s)
    if (millis() - lastUpdateTime > updateInterval) {
        lastUpdateTime = millis();

        // Use the simplifed helper functions provided by the SpotifyEsp32 library
        String currentTrack = spotify.current_track_name();
        String currentArtist = spotify.current_artist_names();
        bool playing = spotify.is_playing();

        // Validate responses coming from the library (the library returns "Something went wrong" on error)
        if (currentTrack != "Something went wrong" && currentTrack != "null") {
            trackName = currentTrack;
        } else {
            trackName = String();
        }

        if (currentArtist != "Something went wrong") {
            artistName = currentArtist;
        } else {
            artistName = String();
        }

        isPlaying = playing;
    }
}

String SpotifyClient :: getTrackName(){
    return trackName;
}

String SpotifyClient :: getArtistName(){
    return artistName;
}

void SpotifyClient :: playPause(){
    // Toggle playback based on last known state. If unknown, call start_resume_playback.
    if (isPlaying) {
        spotify.pause_playback();
    } else {
        spotify.start_resume_playback();
    }
    // Immediately update state variable (optimistic)
    isPlaying = !isPlaying;
}

void SpotifyClient :: nextTrack(){
    spotify.skip();
}

void SpotifyClient :: previousTrack(){
    spotify.previous();
}

