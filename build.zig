const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimise = b.standardOptimizeOption(.{});

    const enable_asserts = b.option(
        bool,
        "asserts",
        "Enable/disable asserts. Always disabled in release builds (default - true)",
    ) orelse true;

    const enable_profiling = b.option(
        bool,
        "profiling",
        "Enable/disable profiling (default - true)",
    ) orelse true;

    const enable_logging = b.option(
        bool,
        "logging",
        "Enable/disable logging macros (default - true)",
    ) orelse true;

    const target_linkage = b.option(
        std.builtin.LinkMode,
        "linkage",
        "Whether to build a dynamic library instead of static [options: dynamic/static] (default - static)",
    ) orelse .static;

    const build_examples = b.option(
        bool,
        "examples",
        "Whether to build the examples (default - true)",
    ) orelse true;

    const compile_flags = &[_][]const u8{
        "-Wall",
        "-Werror",
        "-std=c++20",
    };

    const tails_mod = b.addModule("tails", .{
        .target = target,
        .optimize = optimise,
        .link_libcpp = true,
    });

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = optimise,
    });

    tails_mod.linkLibrary(sdl_dep.artifact("SDL3"));

    tails_mod.addIncludePath(b.path("include"));
    tails_mod.addIncludePath(b.path("src/stb"));

    var sources = std.ArrayList([]const u8).empty;
    {
        const tails_src = "src/Tails";
        var dir = try std.fs.openDirAbsolute(
            b.pathJoin(&.{
                b.build_root.path.?,
                tails_src,
            }),
            .{
                .iterate = true,
            },
        );

        var walker = try dir.walk(b.allocator);
        defer walker.deinit();

        while (try walker.next()) |entry| {
            const ext = std.fs.path.extension(entry.basename);
            if (std.mem.eql(u8, ext, ".cpp")) {
                try sources.append(b.allocator, b.pathJoin(&.{ tails_src, entry.path }));
            }
        }
    }

    tails_mod.addCSourceFiles(.{
        .files = sources.items,
        .flags = compile_flags,
        .language = .cpp,
    });

    if (enable_asserts)
        tails_mod.addCMacro("TAILS_ENABLE_ASSERTS", "");
    if (enable_profiling)
        tails_mod.addCMacro("TAILS_ENABLE_PROFILING", "");
    if (enable_logging)
        tails_mod.addCMacro("TAILS_ENABLE_LOGGING", "");

    const tails_lib = b.addLibrary(.{
        .name = "tails",
        .linkage = target_linkage,
        .root_module = tails_mod,
    });

    tails_lib.installHeadersDirectory(b.path("include/"), "", .{
        .exclude_extensions = &.{"CMakeLists.txt"},
        .include_extensions = &.{".hpp"},
    });

    b.installArtifact(tails_lib);

    if (build_examples) {
        const example_mod = b.createModule(.{
            .target = target,
            .optimize = optimise,
            .link_libcpp = true,
        });

        example_mod.linkLibrary(tails_lib);
        example_mod.addCSourceFiles(.{
            .files = &.{
                "example/main.cpp",
                "example/Player.cpp",
            },
            .flags = compile_flags,
            .language = .cpp,
        });
        example_mod.addIncludePath(b.path("include"));

        const example_exe = b.addExecutable(.{
            .name = "example",
            .root_module = example_mod,
        });

        b.installArtifact(example_exe);
    }
}
