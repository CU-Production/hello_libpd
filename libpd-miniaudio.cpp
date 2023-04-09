#include "PdBase.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <iostream>

void audio_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    pd::PdBase* lpd = (pd::PdBase*)pDevice->pUserData;
    if (lpd == nullptr) {
        return;
    }

//    lpd->processFloat(frameCount, (float*)pInput, (float*)pOutput);
// pass audio samples to/from libpd
    int ticks = frameCount / lpd->blockSize();
    lpd->processFloat(ticks, (float*)pInput, (float*)pOutput);
}

int main()
{
//    std::cout << "Hello, World!" << std::endl;

    pd::PdBase lpd;

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

    // init miniaudio
    ma_device_config deviceConfig;
    ma_device device;
    ma_waveform_config sineWaveConfig;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_f32;
    deviceConfig.playback.channels = 2;
    deviceConfig.sampleRate = 48000;
    deviceConfig.noFixedSizedCallback = false;
    deviceConfig.periodSizeInFrames = 64;
    deviceConfig.dataCallback = audio_callback;
    deviceConfig.pUserData = &lpd;

    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        std::cout << "Failed to open playback device." << std::endl;
        exit(2);
    }

    std::cout << "Device Name: " << device.playback.name << std::endl;

    if (ma_device_start(&device) != MA_SUCCESS) {
        std::cout << "Failed to start playback device." << std::endl;
        ma_device_uninit(&device);
        exit(3);
    }

    std::cout << "Press Enter to quit..." << std::endl;
    getchar();

    ma_device_uninit(&device);

    return 0;
}
