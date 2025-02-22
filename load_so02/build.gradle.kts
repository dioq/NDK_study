import org.gradle.internal.declarativedsl.parsing.main

plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "cn.my.load_so02"
    compileSdk = 34

    defaultConfig {
        applicationId = "cn.my.load_so2"
        minSdk = 30
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    sourceSets{
        getByName("main"){
            jniLibs.srcDirs("jnilibs") // 将 jnilibs 目录下的 so 编译进 apk
        }
    }
}

dependencies {

    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.activity)
    implementation(libs.constraintlayout)
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)
}