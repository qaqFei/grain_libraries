void entrypoint() {
    auto audio = gdecoded_audio::DecodedAudio::Make();

    audio->data.push_back(1234);
    audio->data.push_back(4567);

    audio->data.push_back(7654);
    audio->data.push_back(4321);

    audio->channels = 2;
    audio->sampleRate = 44100;

    std::cout << audio->sampleAt(0, 0, 1, 44100) << std::endl;
}
