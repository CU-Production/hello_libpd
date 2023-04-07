#include "PdBase.hpp"
#include <iostream>

int main() {
//    std::cout << "Hello, World!" << std::endl;

    pd::PdBase lpd;
    // one input channel, two output channels
    // block size 64, one tick per buffer
    float inbuf[64], outbuf[128];

    // init pd
    int srate = 44100;
    if (!lpd.init(0, 2, srate)) {
        std::cerr << "Could not init pd" << std::endl;
        exit(1);
    }

    // compute audio    [; pd dsp 1(
//    lpd.startMessage();
//    lpd.addFloat(1.0f);
//    lpd.finishMessage("pd", "dsp");
    lpd.computeAudio(true);

    // open patch       [; pd open file folder(
    pd::Patch patch = lpd.openPatch("test.pd", ".");
    std::cout << patch << std::endl;

    // close patch
    lpd.closePatch(patch);
    std::cout << patch << std::endl;

    // open patch again
    patch = lpd.openPatch(patch);
    std::cout << patch << std::endl;

    // now run pd for ten seconds (logical time)
    int i;
    for (i = 0; i < 10 * srate / 64; i++) {
        // fill inbuf here
        lpd.processFloat(1, inbuf, outbuf);
        // use outbuf here
    }

    for (i = 0; i < 10; i++)
        std::cout << outbuf[i] << std::endl;

    return 0;
}
