load("@bazel_gazelle//:deps.bzl", "go_repository")

def go_dependencies():
    go_repository(
        name = "com_github_tzneal_gopicotts",
        build_file_proto_mode = "disable_global",
        importpath = "github.com/tzneal/gopicotts",
	patches = ["@//third_party:gopicotts.patch"], # keep
        sum = "h1:Vzj5VDArJ9bRuocjCQkm3NHqjWdsnACNcHzB2ZxISpY=",
        version = "v0.0.0-20170517233132-149cb8d03413",
    )
