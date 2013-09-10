import qbs
import qbs.FileInfo

CppApplication {
    type: "application"
    Depends { name: "Qt.test" }
    targetName: "tst_" + name.split(' ').join("")

    // This needs to be absolute, because it is passed to one of the source files.
    destinationDirectory: buildDirectory + '/'
                          + FileInfo.relativePath(project.ide_source_tree, sourceDirectory)

    cpp.rpaths: [
        buildDirectory + '/' + project.ide_library_path,
        buildDirectory + '/' + project.ide_library_path + "/..", // OSX
        buildDirectory + '/' + project.ide_plugin_path + "/QtProject"
    ]
    cpp.defines: base.concat(["QT_USE_FAST_OPERATOR_PLUS"])

    // The following would be conceptually right, but does not work currently as some autotests
    // (e.g. extensionsystem) do not work when installed, because they want hardcoded
    // absolute paths to resources in the build directory.
//    cpp.rpaths: qbs.targetOS.contains("osx")
//            ? ["@executable_path/.."]
//            : ["$ORIGIN/../lib/qtcreator", "$ORIGIN/../lib/qtcreator/plugins/QtProject"]
//    Group {
//        fileTagsFilter: product.type
//        qbs.install: true
//        qbs.installDir: project.ide_bin_path
//    }
}