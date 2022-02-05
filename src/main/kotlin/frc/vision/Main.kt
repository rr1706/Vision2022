package frc.vision

import kotlinx.coroutines.runBlocking

import org.opencv.core.*
import org.opencv.videoio.*

fun main() = runBlocking {
    println("Attempting a connection to the robot")
    val client = RobotClient()

    val ball_cam_props = MatOfInt(
        Videoio.CAP_PROP_FRAME_WIDTH, 480,
        Videoio.CAP_PROP_FRAME_HEIGHT, 640
    )
    val tape_cam_props = MatOfInt(
        Videoio.CAP_PROP_FRAME_WIDTH, 480,
        Videoio.CAP_PROP_FRAME_HEIGHT, 640
    )

    println("Creating trackers");
    var ball_cam = BallTracker(VideoCapture(0, Videoio.CAP_FFMPEG, ball_cam_props), client)
    //var tape_cam = TapeTracker(VideoCapture(1, Videoio.CAP_FFMPEG, tape_cam_props), client)

    println("Running trackers")
    ball_cam.runAsync()
    //tape_cam.runAsync()

    // Loop until esc key is pressed
    while(true) {
       // ball_cam.streamFrame("Ball Camera", true);
       // tape_cam.stream("Tape Camera", true);
        println("Waiting")
    }

    println("Exiting");
}