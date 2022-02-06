import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.6.10"
    application
    c
}

group = "frc.vision"
version = "0.2.0"

repositories {
    mavenCentral()
}

dependencies {
    implementation("com.pi4j", "pi4j-core", "2.1.1")
    implementation("org.msgpack", "msgpack-core", "0.9.0")
    implementation("org.jetbrains.kotlinx", "kotlinx-coroutines-core", "1.6.0")
    //compileOnly(files("vendor/opencv/opencv-455.jar"))
    implementation(files("vendor/opencv/opencv-455.jar"))

    testImplementation(kotlin("test"))
}

application {
    mainClass.set("frc.vision.MainKt")
}

tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "11"
    System.setProperty("java.library.path", "vendor/opencv/static/x64:vendor/opencv/shared/x64")
}

