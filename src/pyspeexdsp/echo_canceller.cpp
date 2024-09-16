#include "echo_canceller.h"

// Constructor: Initializes the Speex Echo Canceller with the given parameters
EchoCanceller::EchoCanceller(int frame_size, int filter_length, int sample_rate, int nb_mic, int nb_speakers)
{
    // Initialize the Speex echo canceller state with multi-channel support
    st_echo = speex_echo_state_init_mc(frame_size, filter_length, nb_mic, nb_speakers);
    speex_echo_ctl(st_echo, SPEEX_ECHO_SET_SAMPLING_RATE, &sample_rate);

    // Initialize the echo suppressor state
    st_pre = speex_preprocess_state_init(frame_size, sample_rate);
    speex_preprocess_ctl(st_pre, SPEEX_PREPROCESS_SET_ECHO_STATE, st_echo); // Link echo suppressor to echo canceller

    // Enable echo suppression
    int suppress = 1;
    speex_preprocess_ctl(st_pre, SPEEX_PREPROCESS_SET_ECHO_SUPPRESS, &suppress);

    // Calculate the total number of frames (samples) to be processed
    frames = frame_size * nb_mic;

    // Allocate memory for the output buffer (processed audio samples)
    output_buffer = new int16_t[frames];

    echo_suppression_enabled = true; // Echo suppression enabled by default
}

// Destructor: Cleans up allocated resources
EchoCanceller::~EchoCanceller()
{
    speex_echo_state_destroy(st_echo);      // Free the echo canceller state
    speex_preprocess_state_destroy(st_pre); // Free the echo suppressor state
    delete[] output_buffer;                 // Free the allocated memory for the output buffer
}

// Process method: Performs echo cancellation on the input audio data
std::string EchoCanceller::process(const std::string &near, const std::string &far)
{
    const int16_t *near_data = (const int16_t *)(near.data());
    const int16_t *far_data = (const int16_t *)(far.data());

    // Perform echo cancellation
    speex_echo_cancellation(st_echo, near_data, far_data, output_buffer);

    if (echo_suppression_enabled)
    {
        speex_preprocess_run(st_pre, output_buffer);
    }

    return std::string((const char *)(output_buffer), frames * sizeof(int16_t));
}

void EchoCanceller::set_echo_suppress(int level)
{
    // Set the echo suppress level
    speex_preprocess_ctl(st_pre, SPEEX_PREPROCESS_SET_ECHO_SUPPRESS, &level);
}

void EchoCanceller::enable_echo_suppression(bool enable)
{
    echo_suppression_enabled = enable;
}
