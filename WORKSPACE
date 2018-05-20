load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "clang",
    build_file = "//:third_party/clang.BUILD",
    sha256 = "114e78b2f6db61aaee314c572e07b0d635f653adc5d31bd1cd0bf31a3db4a6e5",
    strip_prefix = "clang+llvm-6.0.0-x86_64-linux-gnu-ubuntu-14.04",
    url = "http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-x86_64-linux-gnu-ubuntu-14.04.tar.xz",
)

http_archive(
    name = "com_google_googletest",
    sha256 = "7fa65a00af56aac6d96743aec9d38e6d7259ebfa5e3d72d529a696dc1f221f49",
    strip_prefix = "googletest-59202300f1a774068608caff0351cc084fe79e7c",
    url = "https://github.com/google/googletest/archive/59202300f1a774068608caff0351cc084fe79e7c.tar.gz",
)

http_archive(
    name = "com_github_google_benchmark",
    sha256 = "904f5d19a6804396f16c95a823fabc6bc69913d628a124c96c4cd00358a72b09",
    strip_prefix = "benchmark-e90801ae475f23877319d67b96c07bf0c52405f3",
    url = "https://github.com/google/benchmark/archive/e90801ae475f23877319d67b96c07bf0c52405f3.tar.gz",
)

http_archive(
    name = "fmt",
    build_file = "//:third_party/fmt.BUILD",
    sha256 = "47e17eff058ed52bbe9fd1bd732401e1e542aa818743e17b7c9ea37f39443b8a",
    strip_prefix = "fmt-838400d29b95a02df8a4ea4a722c33aef135afd3",
    url = "https://github.com/fmtlib/fmt/archive/838400d29b95a02df8a4ea4a722c33aef135afd3.tar.gz",
)
