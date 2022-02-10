package frc.vision

import kotlinx.coroutines.*
import kotlinx.coroutines.sync.*

import org.opencv.core.*
import org.opencv.imgproc.*
import org.opencv.videoio.*
import org.opencv.highgui.*
import kotlin.math.E

class BallTracker(cap: VideoCapture, net: RobotClient): AsyncPipeline {

    var currentFrame = Mat()
    override val client = net

    private val mutex = Mutex()
    private val _ballWidth_mm = 241.3
    private val _focalLength_mm = 305.76460593 // Update this
    private val _capture = cap
    private val _kernel = Imgproc.getStructuringElement(Imgproc.MORPH_ELLIPSE, Size(5.0, 5.0))

    private fun process(img: Mat, range: Pair<Scalar, Scalar>): Mat {
        var threshed = Mat()

        Imgproc.cvtColor(img, img, Imgproc.COLOR_BGR2HSV)
        Core.inRange(img, range.first, range.second, threshed)

        // Should I open twice?
        Imgproc.morphologyEx(threshed, threshed, Imgproc.MORPH_OPEN, _kernel)

        return threshed
    }

    private fun track(threshed: Mat): Map<String, Double> {
        // Find contours(A list of points)
        var hierarchy = Mat()
        var cnts = listOf(MatOfPoint())
        Imgproc.findContours(threshed, cnts, hierarchy, Imgproc.RETR_EXTERNAL, Imgproc.CHAIN_APPROX_SIMPLE)

        // If no contours are found then ignore
        if(cnts.isNotEmpty()) {
            // Find the largest contour and use that
            var largestCnt = MatOfPoint2f()
            for(cnt in cnts) {
                // Is this right? is width the width of the contour or of the variable?
                if(cnt.size().width > largestCnt.size().width)
                    largestCnt = MatOfPoint2f(cnt)
            }

            // Find the points of the largest contour
            var center = Point()
            var radius = FloatArray(0)
            Imgproc.minEnclosingCircle(largestCnt, center, radius)

            println(radius)
            //val distance = (_ballWidth_mm * _focalLength_mm)/(radius*2)
            //println(distance)
        }
        throw Exception("No contour found!")
    }

    override fun runAsync() = GlobalScope.async {
        val blue = Pair<Scalar, Scalar>(
            Scalar(92.0, 139.0, 76.0),
            Scalar(115.0, 210.0, 175.0)
        )
        val red = Pair<Scalar, Scalar>(
            Scalar(165.0, 92.0, 52.0),
            Scalar(175.0, 218.0, 213.0)
        )

        while(_capture.isOpened) {
            mutex.withLock {
                if(_capture.read(currentFrame)) {
                    val processed = process(currentFrame, blue)
                    val trackerData = track(processed)
                } else {
                    throw Exception("Unable to read frame from camera")
                }
            }
        }
        throw Exception("Unable to open camera")
    }

    suspend fun imstream(img: Mat) {
        mutex.withLock {
            HighGui.imshow("Ball cam", img)
        }
    }
}