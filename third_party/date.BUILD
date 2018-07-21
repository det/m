cc_library(
    name = "date",
    hdrs = glob(["include/date/*.h"]),
    srcs = glob(["src/*.cpp"]),
    includes = ["include"],
    data = ["@tzdata"],
    defines = ["HAS_REMOTE_API=0"],
    copts = ["-DINSTALL=external"],  # this is a non-inherited define
    visibility = ["//visibility:public"],
)
