package frc.vision

import kotlinx.coroutines.*

interface AsyncPipeline {
    val client: RobotClient

    enum class ProcessType {
        ball_blue, ball_red, tape, color_sensor
    }

    fun runAsync() {
        GlobalScope.launch {
            run()
        }
    }

    fun run(): Deferred<Int>
}