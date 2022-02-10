import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

// Meta data
val user = "frc"
val host = "jetson"
val frcYear = "2022"
val teamNumber = "1706"
group = "frc.vision"
version = "$frcYear.2.0"

// Find and apply plugins
plugins {
    //id("jaci.gradle.EmbeddedTools") version "2020.12.23"
    id("edu.wpi.first.GradleRIO") version "2022.2.1"
    kotlin("jvm") version "1.6.10"
    application
}

// Define repos & dependencies
repositories {
    mavenCentral()
}

dependencies {
    for(dep in wpi.java.deps.wpilib()) {
        implementation(dep)
    }
    implementation("com.pi4j", "pi4j-core", "2.1.1")
    implementation("org.bytedeco", "opencv-platform", "4.5.3-1.5.6")
    implementation("org.jetbrains.kotlinx", "kotlinx-coroutines-core", "1.6.0")

    testImplementation(kotlin("test"))
}

// Configure application
application {
    mainClass.set("$group.MainKt")
}

/*
// Added by embedded tools, doesn't work for some reason
// Running `./gradlew deploy` should trigger this and deploy the program
deploy {}
*/

// Kotlin settings
kotlin {
    sourceSets["main"].apply {
        kotlin.srcDir("src/kotlin")
    }
}
tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "11"
}