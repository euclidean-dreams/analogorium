#ifndef ANALOGORIUM_CONFIG_H
#define ANALOGORIUM_CONFIG_H

#define AUDIO_DEVICE impresarioUtils::Config::getInstance().getString("audio_device")
#define RING_BUFFER_SIZE_MULTIPLIER impresarioUtils::Config::getInstance().getInt("ring_buffer_size_multiplier")
#define SAMPLE_RATE impresarioUtils::Config::getInstance().getFloat("sample_rate")
#define SEEDLING_SIGNAL_SIZE impresarioUtils::Config::getInstance().getInt("seedling_signal_size")
#define GAIN impresarioUtils::Config::getInstance().getFloat("gain")

// endpoints
#define OUTPUT_ENDPOINT impresarioUtils::Config::getInstance().getString("output_endpoint")
#define VOLITIA_ENDPOINT impresarioUtils::Config::getInstance().getString("volitia_endpoint")

// stft
#define HOP_SIZE impresarioUtils::Config::getInstance().getInt("hop_size")
#define WINDOW_SIZE impresarioUtils::Config::getInstance().getInt("window_size")
#define WINDOW_FUNCTION impresarioUtils::Config::getInstance().getInt("window_function")

#endif //ANALOGORIUM_CONFIG_H
