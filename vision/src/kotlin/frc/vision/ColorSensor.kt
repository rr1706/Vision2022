package frc.vision

import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.async

import com.pi4j.Pi4J
import com.pi4j.io.i2c.*

class ColorSensor(net: RobotClient): AsyncPipeline {
    override val client = net
    val ctx = Pi4J.newAutoContext()

    override fun runAsync() = GlobalScope.async {
        while(true) {

        }
    }
}