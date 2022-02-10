package frc.vision

import kotlinx.coroutines.runBlocking

import org.bytedeco.javacpp.Loader
import org.bytedeco.opencv.opencv_java

import org.opencv.core.*
import org.opencv.videoio.*

fun main() = runBlocking {
    // Load native libraries, mainly opencv
    //System.load("native/lib${Core.NATIVE_LIBRARY_NAME}.*")
    Loader.load(opencv_java::class.java)

    println("Attempting a connection to the robot")
    val client = RobotClient()

    // Camera properties
    val ballCamProps = MatOfInt(
        Videoio.CAP_PROP_FRAME_WIDTH, 480,
        Videoio.CAP_PROP_FRAME_HEIGHT, 640
    )
    val tapeCamProps = MatOfInt(
        Videoio.CAP_PROP_FRAME_WIDTH, 480,
        Videoio.CAP_PROP_FRAME_HEIGHT, 640
    )

    println("Creating trackers")
    val ballCam = BallTracker(VideoCapture(-1, Videoio.CAP_ANY, ballCamProps), client)
    //var tapeCam = TapeTracker(VideoCapture(1, Videoio.CAP_ANY, tapeCamProps), client)

    println("Running trackers")
    ballCam.runAsync()
    //tapeCam.runAsync()

    println("Starting video stream")
    while(true) {
        if(!ballCam.currentFrame.empty()){
            ballCam.imstream(ballCam.currentFrame);
            //tapeCam.imstream(tapeCam.currentFrame);
        } else {
            throw Exception("Current frame is empty")
        }
    }

    println("Exiting")
}