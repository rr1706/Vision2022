package frc.vision

import org.opencv.core.*
import org.opencv.videoio.*

fun main() {
    println("Attempting a connection to the robot")
    val client = RobotClient()

    val ballCamProps = MatOfInt(
        Videoio.CAP_PROP_FRAME_WIDTH, 480,
        Videoio.CAP_PROP_FRAME_HEIGHT, 640
    )
    val tapeCamProps = MatOfInt(
        Videoio.CAP_PROP_FRAME_WIDTH, 480,
        Videoio.CAP_PROP_FRAME_HEIGHT, 640
    )

    println("Creating trackers");
    var ballCam = BallTracker(VideoCapture(0, Videoio.CAP_FFMPEG, ballCamProps), client)
    //var tapeCam = TapeTracker(VideoCapture(1, Videoio.CAP_FFMPEG, tapeCamProps), client)

    println("Running trackers")
    ballCam.run()
    //tape_cam.runAsync()

    // Loop until esc key is pressed
    while(true) {
       // ball_cam.streamFrame("Ball Camera", true);
       // tape_cam.stream("Tape Camera", true);
        println("Waiting")
    }

    println("Exiting");
}