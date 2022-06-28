#include <allegro.h>

void start_audio()
{
    SAMPLE *start = load_sample("audio/inicio.wav");
    SAMPLE *soundtrack = load_sample("audio/soundtrack.wav");
    SAMPLE *tiro = load_sample("audio/tiro.wav");
    play_sample(start, 100, 128, 1000, 0);
    play_sample(soundtrack, 100, 128, 1000, 1);
}