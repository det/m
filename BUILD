cc_library(
    name = "m",
    hdrs = glob(["include/m/*.h"]),
    includes = ["include"],
    copts = ["-std=c++1z"],
    visibility = ["//visibility:public"]
)

cc_test(
    name = "m_test",
    srcs = glob(["tests/*.cpp"]),
    size = "small",
    deps = [
        ":m",
        "@googletest//:gtest_main"
    ]
)
