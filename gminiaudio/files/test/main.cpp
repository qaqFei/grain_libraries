void entrypoint() {
    auto data = gdata::Data::MakeFromGrain("test/test_audio");
    auto audio = gminiaudio::decode(data);
    auto engine = gminiaudio::makeAudioEngine();
    auto task = engine->createTask(audio);

    while (!engine->getTaskEnded(task)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
