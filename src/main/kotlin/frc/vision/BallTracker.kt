package frc.vision

import org.opencv.core.*
import org.opencv.videoio.*
import org.opencv.highgui.*

class BallTracker(cap: VideoCapture, net: RobotClient): AsyncPipeline {

    private val capture = cap
    override val client = net

    fun process() {

    }

    fun track() {

    }

    override suspend fun run() {
        var frame = Mat.zeros(0,0,0);
        while(true) {
            capture.read(frame)
            HighGui.imshow("Test", frame)
        }
    }

    fun imstream() {
        TODO("Not yet finished")
    }
}