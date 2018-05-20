# toolchain/BUILD
package(default_visibility = ['//visibility:public'])

cc_toolchain_suite(
    name = "cc-toolchain",
    toolchains = {
         "x86_64|clang": ":ubuntu_x86_64_clang_toolchain",
    },
)

filegroup(name = "empty")

filegroup(
    name = "clang_wrappers",
    srcs = ["@clang//:binaries"] + glob(["wrappers/*.sh"]),
)

filegroup(
    name = "clang_all",
    srcs = [
        ":clang_wrappers",
        "@clang//:includes",
        "@clang//:runtime_libs",
    ],
)

cc_toolchain(
    name = "ubuntu_x86_64_clang_toolchain",
    all_files = ":clang_all",
    compiler_files = ":clang_wrappers",
    cpu = "x86_64",
    dwp_files = ":clang_wrappers",
    dynamic_runtime_libs = ["@clang//:runtime_libs"],
    linker_files = ":clang_wrappers",
    objcopy_files = ":clang_wrappers",
    static_runtime_libs = [":empty"],
    strip_files = ":empty",
    supports_param_files = 1,
)
