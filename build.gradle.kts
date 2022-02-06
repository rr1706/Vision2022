import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

// Meta data
group = "frc.vision"
version = "0.2.0"

// Find and apply plugins
plugins {
    //id("jaci.gradle.EmbeddedTools")
    kotlin("jvm") version "1.6.10"
    application
}

// Define repos & dependencies
repositories {
    mavenCentral()
}

dependencies {
    implementation("org.msgpack", "msgpack-core", "0.9.0")
    implementation("org.jetbrains.kotlinx", "kotlinx-coroutines-core", "1.6.0")
    implementation(fileTree("vendor/"))

    testImplementation(kotlin("test"))
}

// Configure application plugin
application {
    mainClass.set("frc.vision.MainKt")
}

// Kotlin settings
tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "11"
}

