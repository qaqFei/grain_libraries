void entrypoint() {
    gvideoenc::VideoCap cap {};
    cap.init("./test.mp4", 1920, 1080, 60.0);
}
