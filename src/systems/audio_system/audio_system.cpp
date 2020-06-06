#include "systems/audio_system/audio_system.hpp"

#include "systems/imgui_system.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <imgui.h>

#include <iostream>

namespace aiko
{

    AudioSystem::AudioSystem()
        : m_imguiSystem(nullptr)
        , m_renderImgui(false)
    {

    }

    bool AudioSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        return true;
    }

    bool AudioSystem::init()
    {

        m_imguiSystem->registerSystem("AudioSystem", m_renderImgui);

        static constexpr const auto playTestAudio = false;

        if (playTestAudio == true)
        {

            // Device opening

            ALCdevice* device = nullptr;

            device = alcOpenDevice(NULL);

            if (device == nullptr)
            {
                std::cout << "Default open device for audio not found" << std::endl;
            }

            // Device enumeration

            ALboolean enumeration;

            enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
            if (enumeration == AL_FALSE)
            {
                std::cout << "enumeration not supported" << std::endl;
                // enumeration not supported
            }
            else
            {
                std::cout << "enumeration supported" << std::endl;
                // enumeration supported
            }

            // Retrieving the device list

            auto list_audio_devices = [](const ALCchar *devices)
            {
                const ALCchar *device = devices, *next = devices + 1;
                size_t len = 0;

                fprintf(stdout, "Devices list:\n");
                fprintf(stdout, "----------\n");
                while (device && *device != '\0' && next && *next != '\0') {
                    fprintf(stdout, "%s\n", device);
                    len = strlen(device);
                    device += (len + 1);
                    next += (len + 2);
                }
                fprintf(stdout, "----------\n");
            };

            list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

            // Context creation and initialization

            ALCcontext *context;

            context = alcCreateContext(device, NULL);
            if (!alcMakeContextCurrent(context))
            {
                std::cout << "failed to make context current" << std::endl;
                std::cout << "test for errors here using alGetError()" << std::endl;
            }

            // Definining and configuring the listener

            ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

            alListener3f(AL_POSITION, 0, 0, 1.0f);
            // check for errors
            alListener3f(AL_VELOCITY, 0, 0, 0);
            // check for errors
            alListenerfv(AL_ORIENTATION, listenerOri);
            // check for errors

            // Source generation

            ALuint source;

            alGenSources((ALuint)1, &source);
            // check for errors

            alSourcef(source, AL_PITCH, 1);
            // check for errors
            alSourcef(source, AL_GAIN, 1);
            // check for errors
            alSource3f(source, AL_POSITION, 0, 0, 0);
            // check for errors
            alSource3f(source, AL_VELOCITY, 0, 0, 0);
            // check for errors
            alSourcei(source, AL_LOOPING, AL_TRUE);
            // check for errros

            // Buffer generation
            ALuint buffer;

            alGenBuffers((ALuint)1, &buffer);
            // check for errors

            /* Fill buffer with Sine-Wave */
            float freq = 440.f;
            int seconds = 4;
            unsigned sample_rate = 22050;
            size_t buf_size = seconds * sample_rate;

            short *samples;
            samples = new short[buf_size];
            for (int i = 0; i < buf_size; ++i)
            {
                samples[i] = 32760 * sin((2.f*float(3.1415)*freq) / sample_rate * i);
            }

            /* Download buffer to OpenAL */
            alBufferData(buffer, AL_FORMAT_MONO16, samples, buf_size, sample_rate);

            // Binding a source to a buffer
            alSourcei(source, AL_BUFFER, buffer);
            // check for errors

            alSourcePlay(source);

        }

        return true;
    }

    void AudioSystem::preUpdate()
    {

    }

    void AudioSystem::update()
    {

    }

    void AudioSystem::postUpdate()
    {

    }

    void AudioSystem::preRender()
    {

    }

    void AudioSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("Audio settings", &m_renderImgui);
            ImGui::End();
        }
    }

    void AudioSystem::postRender()
    {

    }

}
