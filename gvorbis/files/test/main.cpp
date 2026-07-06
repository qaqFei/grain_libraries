void entrypoint() {
    auto data = gdata::Data::MakeFromGrain("test/test_audio");
    auto audio = gvorbis::decode(data);

    std::cout << audio.get() << std::endl;
    std::cout << audio->data.size() << std::endl;
    std::cout << audio->channels << std::endl;
    std::cout << audio->sampleRate << std::endl;
}
