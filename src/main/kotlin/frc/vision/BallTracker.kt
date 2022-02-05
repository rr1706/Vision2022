package frc.vision

import kotlinx.coroutines.Deferred
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async
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

    override fun run(): Deferred<Int> = GlobalScope.async {
        var frame = Mat.zeros(0,0,0);
        while(true) {
            capture.read(frame)
            HighGui.imshow("Test", frame)

        }
        return@async 0;
    }

    fun imstream() {
        TODO("Not yet finished")
    }
}