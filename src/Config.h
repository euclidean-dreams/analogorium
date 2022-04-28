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

// equalizer
#define SCALING_FACTOR_100 impresarioUtils::Config::getInstance().getFloat("scaling_factor_100")
#define SCALING_FACTOR_200 impresarioUtils::Config::getInstance().getFloat("scaling_factor_200")
#define SCALING_FACTOR_400 impresarioUtils::Config::getInstance().getFloat("scaling_factor_400")
#define SCALING_FACTOR_1000 impresarioUtils::Config::getInstance().getFloat("scaling_Factor_1000")
#define SCALING_FACTOR_2000 impresarioUtils::Config::getInstance().getFloat("scaling_factor_2000")
#define SCALING_FACTOR_20000 impresarioUtils::Config::getInstance().getFloat("scaling_factor_20000")

#endif //ANALOGORIUM_CONFIG_H
