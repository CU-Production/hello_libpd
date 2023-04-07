#include "z_libpd.h"
#include <iostream>

void pdprint(const char *s) {
    printf("%s", s);
}

void pdnoteon(int ch, int pitch, int vel) {
    printf("noteon: %d %d %d\n", ch, pitch, vel);
}

int main() {
//    std::cout << "Hello, World!" << std::endl;

    // init pd
    int srate = 44100;
    libpd_set_printhook(pdprint);
    libpd_set_noteonhook(pdnoteon);
    libpd_init();
    libpd_init_audio(1, 2, srate);

    // one input channel, two output channels
    // block size 64, one tick per buffer
    float inbuf[64], outbuf[128];

    // compute audio    [; pd dsp 1(
    libpd_start_message(1);
    libpd_add_float(1.0f);
    libpd_finish_message("pd", "dsp");

    // open patch       [; pd open file folder(
    if (!libpd_openfile("test.pd", "."))
        return -1;

    // now run pd for ten seconds (logical time)
    int i;
    for (i = 0; i < 10 * srate / 64; i++) {
        // fill inbuf here
        libpd_process_float(1, inbuf, outbuf);
        // use outbuf here
    }

    for (i = 0; i < 10; i++)
        printf("%g\n", outbuf[i]);

    return 0;
}
