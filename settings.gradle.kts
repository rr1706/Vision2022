pluginManagement {
    repositories {
        mavenLocal()
        mavenCentral()
        gradlePluginPortal()

        var frcYear = "2022"
        val frcHomeMaven = File("${System.getProperty("user.home")}/wpilib/${frcYear}/maven")
        maven {
            name = "frcHome"
            url = uri(frcHomeMaven)
        }
    }
}

rootProject.name = "Vision2022"
include("vision")
//include("comms")
//include("robot")
