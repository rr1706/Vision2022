import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

plugins {
    kotlin("jvm") version "1.6.10"
    application
}

val group = "frc.vision"
val version = "0.2.0"

repositories {
    mavenCentral()
}

dependencies {
    implementation("com.pi4j:pi4j-core:2.1.1")
    implementation("org.msgpack:msgpack-core:0.9.0")
    implementation("io.github.dmitributorchin:opencv:4.5.5")
    implementation("org.jetbrains.kotlinx:kotlinx-coroutines-core:1.6.0")

    testImplementation(kotlin("test"))
}

application {
    mainClass.set(group + ".MainKt")
}

tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "11"
}

