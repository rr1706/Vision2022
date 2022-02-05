import RobotClient
import BallTracker

import kotlinx.coroutines.*

fun testAsync() = GlobalScope.launch {
    delay(1000L)
    println("from async!")
}

fun main(args: Array<String>) = runBlocking {
    testAsync()
    println("Hello")
}