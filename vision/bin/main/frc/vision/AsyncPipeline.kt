package frc.vision

import kotlinx.coroutines.*

interface AsyncPipeline {
    val client: RobotClient

    fun runAsync(): Deferred<Unit>
}