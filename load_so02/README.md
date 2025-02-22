# 加载外部 so

把编译好的so 放到 jnilibs 目录下, 编译进apk。java 代码可以直接通过 System.loadLibrary(); 加载jnilibs
目录下的so

## 配置

build.gradle.kts
sourceSets{
    getByName("main"){
        jniLibs.srcDirs("jnilibs") // 将 jnilibs 目录下的 so 编译进 apk
    }
}
