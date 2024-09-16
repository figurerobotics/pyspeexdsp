#ifndef __ECHO_CANCELLER_H__
#define __ECHO_CANCELLER_H__

#include <string>
#include <stdint.h>
#include "speex/speex_echo.h"
#include "speex/speex_preprocess.h"
#include "speex/speex_preprocess.h"

class EchoCanceller
{
public:
    EchoCanceller(int frame_size = 512, int filter_length = 2048, int sample_rate = 16000, int nb_mic = 1, int nb_speakers = 1);
    ~EchoCanceller();

    std::string process(const std::string &near, const std::string &far); // perform echo cancellation and suppression

    void set_echo_suppress(int level);         // Method to set the echo suppress level
    void enable_echo_suppression(bool enable); // Method to enable or disable echo suppression

private:
    SpeexEchoState *st_echo;
    SpeexPreprocessState *st_pre;
    int16_t *output_buffer;
    int frames;
    bool echo_suppression_enabled; // Flag to enable or disable echo suppression
};

#endif /* __ECHO_CANCELLER_H__ */