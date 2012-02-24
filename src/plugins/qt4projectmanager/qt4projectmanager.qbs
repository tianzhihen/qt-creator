import qbs.base 1.0

import "../QtcPlugin.qbs" as QtcPlugin

QtcPlugin {
    name: "Qt4ProjectManager"

    Depends { name: "qt"; submodules: ['gui', 'network'] }
    Depends { name: "utils" }
    Depends { name: "extensionsystem" }
    Depends { name: "aggregation" }
    Depends { name: "Core" }
    Depends { name: "ProjectExplorer" }
    Depends { name: "QtSupport" }
    Depends { name: "CppTools" }
    Depends { name: "Debugger" }
    Depends { name: "symbianutils" }
    Depends { name: "QmlJS" }
    Depends { name: "botan" }
    Depends { name: "cplusplus" }
    Depends { name: "TextEditor" }

    Depends { name: "cpp" }
    cpp.defines: {
        return base.concat([
            "PROPARSER_AS_LIBRARY",
            "PROPARSER_THREAD_SAFE",
            "PROEVALUATOR_THREAD_SAFE",
            "PROEVALUATOR_CUMULATIVE"
        ])
    }
    cpp.includePaths: [
        ".",
        "..",
        buildDirectory,
        "customwidgetwizard",
        "../../libs",
        "../../shared",
        "../../shared/symbianutils",
        "../../libs/3rdparty/botan/build"
    ]

    files: [
        "Qt4ProjectManager.mimetypes.xml",
        "librarydetailswidget.ui",
        "qt4projectmanager.qrc",
        "addlibrarywizard.cpp",
        "addlibrarywizard.h",
        "externaleditors.cpp",
        "externaleditors.h",
        "findqt4profiles.cpp",
        "findqt4profiles.h",
        "librarydetailscontroller.cpp",
        "librarydetailscontroller.h",
        "makestep.h",
        "makestep.ui",
        "profilecompletionassist.cpp",
        "profilecompletionassist.h",
        "profileeditor.cpp",
        "profileeditor.h",
        "profileeditorfactory.cpp",
        "profileeditorfactory.h",
        "profilehighlighter.cpp",
        "profilehighlighter.h",
        "profilehoverhandler.cpp",
        "profilehoverhandler.h",
        "profilekeywords.cpp",
        "profilekeywords.h",
        "qmakeparser.cpp",
        "qmakeparser.h",
        "qmakestep.cpp",
        "qmakestep.h",
        "qmakestep.ui",
        "qt4basetargetfactory.h",
        "qt4buildconfiguration.cpp",
        "qt4buildconfiguration.h",
        "qt4nodes.h",
        "qt4project.cpp",
        "qt4project.h",
        "qt4projectconfigwidget.cpp",
        "qt4projectconfigwidget.h",
        "qt4projectconfigwidget.ui",
        "qt4projectmanager_global.h",
        "qt4projectmanagerconstants.h",
        "qt4projectmanagerplugin.cpp",
        "qt4projectmanagerplugin.h",
        "qt4targetsetupwidget.h",
        "qtmodulesinfo.cpp",
        "qtmodulesinfo.h",
        "qtuicodemodelsupport.cpp",
        "qtuicodemodelsupport.h",
        "unconfiguredsettingsoptionpage.cpp",
        "unconfiguredsettingsoptionpage.h",
        "unconfiguredprojectpanel.cpp",
        "unconfiguredprojectpanel.h",
        "winceqtversion.cpp",
        "winceqtversion.h",
        "winceqtversionfactory.cpp",
        "winceqtversionfactory.h",
        "buildconfigurationinfo.h",
        "makestep.cpp",
        "qt4nodes.cpp",
        "qt4projectmanager.cpp",
        "qt4projectmanager.h",
        "qt4target.cpp",
        "qt4target.h",
        "customwidgetwizard/classdefinition.ui",
        "customwidgetwizard/customwidgetpluginwizardpage.ui",
        "customwidgetwizard/customwidgetwidgetswizardpage.ui",
        "customwidgetwizard/classdefinition.cpp",
        "customwidgetwizard/classdefinition.h",
        "customwidgetwizard/classlist.cpp",
        "customwidgetwizard/classlist.h",
        "customwidgetwizard/customwidgetpluginwizardpage.cpp",
        "customwidgetwizard/customwidgetpluginwizardpage.h",
        "customwidgetwizard/customwidgetwidgetswizardpage.cpp",
        "customwidgetwizard/customwidgetwidgetswizardpage.h",
        "customwidgetwizard/customwidgetwizard.cpp",
        "customwidgetwizard/customwidgetwizard.h",
        "customwidgetwizard/customwidgetwizarddialog.cpp",
        "customwidgetwizard/customwidgetwizarddialog.h",
        "customwidgetwizard/filenamingparameters.h",
        "customwidgetwizard/plugingenerator.cpp",
        "customwidgetwizard/plugingenerator.h",
        "customwidgetwizard/pluginoptions.h",
        "images/forms.png",
        "images/headers.png",
        "images/qt_project.png",
        "images/qt_qrc.png",
        "images/run_qmake.png",
        "images/run_qmake_small.png",
        "images/sources.png",
        "images/unknown.png",
        "qt-desktop/desktopqtversion.cpp",
        "qt-desktop/desktopqtversion.h",
        "qt-desktop/desktopqtversionfactory.cpp",
        "qt-desktop/desktopqtversionfactory.h",
        "qt-desktop/qt4desktoptarget.cpp",
        "qt-desktop/qt4desktoptarget.h",
        "qt-desktop/qt4desktoptargetfactory.cpp",
        "qt-desktop/qt4desktoptargetfactory.h",
        "qt-desktop/qt4runconfiguration.cpp",
        "qt-desktop/qt4runconfiguration.h",
        "qt-desktop/qt4simulatortarget.cpp",
        "qt-desktop/qt4simulatortarget.h",
        "qt-desktop/qt4simulatortargetfactory.cpp",
        "qt-desktop/qt4simulatortargetfactory.h",
        "qt-desktop/simulatorqtversion.cpp",
        "qt-desktop/simulatorqtversion.h",
        "qt-desktop/simulatorqtversionfactory.cpp",
        "qt-desktop/simulatorqtversionfactory.h",
        "qt-s60/rvcttoolchainconfigwidget.ui",
        "qt-s60/winscwtoolchainconfigwidget.ui",
        "qt-s60/abldparser.cpp",
        "qt-s60/abldparser.h",
        "qt-s60/certificatepathchooser.cpp",
        "qt-s60/certificatepathchooser.h",
        "qt-s60/gccetoolchain.cpp",
        "qt-s60/gccetoolchain.h",
        "qt-s60/passphraseforkeydialog.cpp",
        "qt-s60/passphraseforkeydialog.h",
        "qt-s60/qt4symbiantarget.cpp",
        "qt-s60/qt4symbiantarget.h",
        "qt-s60/qt4symbiantargetfactory.cpp",
        "qt-s60/qt4symbiantargetfactory.h",
        "qt-s60/rvctparser.cpp",
        "qt-s60/rvctparser.h",
        "qt-s60/rvcttoolchain.cpp",
        "qt-s60/rvcttoolchain.h",
        "qt-s60/s60certificatedetailsdialog.cpp",
        "qt-s60/s60certificatedetailsdialog.h",
        "qt-s60/s60certificatedetailsdialog.ui",
        "qt-s60/s60certificateinfo.cpp",
        "qt-s60/s60certificateinfo.h",
        "qt-s60/s60createpackageparser.cpp",
        "qt-s60/s60createpackageparser.h",
        "qt-s60/s60createpackagestep.cpp",
        "qt-s60/s60createpackagestep.h",
        "qt-s60/s60createpackagestep.ui",
        "qt-s60/s60deployconfiguration.cpp",
        "qt-s60/s60deployconfiguration.h",
        "qt-s60/s60deployconfigurationwidget.cpp",
        "qt-s60/s60deployconfigurationwidget.h",
        "qt-s60/s60devicerunconfiguration.cpp",
        "qt-s60/s60devicerunconfiguration.h",
        "qt-s60/s60devicerunconfigurationwidget.cpp",
        "qt-s60/s60devicerunconfigurationwidget.h",
        "qt-s60/s60manager.h",
        "qt-s60/s60publisherovi.cpp",
        "qt-s60/s60publisherovi.h",
        "qt-s60/s60publishingbuildsettingspageovi.cpp",
        "qt-s60/s60publishingbuildsettingspageovi.h",
        "qt-s60/s60publishingbuildsettingspageovi.ui",
        "qt-s60/s60publishingresultspageovi.cpp",
        "qt-s60/s60publishingresultspageovi.h",
        "qt-s60/s60publishingresultspageovi.ui",
        "qt-s60/s60publishingsissettingspageovi.cpp",
        "qt-s60/s60publishingsissettingspageovi.h",
        "qt-s60/s60publishingsissettingspageovi.ui",
        "qt-s60/s60publishingwizardfactories.cpp",
        "qt-s60/s60publishingwizardfactories.h",
        "qt-s60/s60publishingwizardovi.cpp",
        "qt-s60/s60publishingwizardovi.h",
        "qt-s60/s60symbiancertificate.cpp",
        "qt-s60/s60symbiancertificate.h",
        "qt-s60/sbsv2parser.cpp",
        "qt-s60/sbsv2parser.h",
        "qt-s60/symbianqtversion.cpp",
        "qt-s60/symbianqtversion.h",
        "qt-s60/symbianqtversionfactory.cpp",
        "qt-s60/symbianqtversionfactory.h",
        "qt-s60/winscwparser.cpp",
        "qt-s60/winscwparser.h",
        "qt-s60/winscwtoolchain.cpp",
        "qt-s60/winscwtoolchain.h",
        "qt-s60/codaruncontrol.cpp",
        "qt-s60/codaruncontrol.h",
        "qt-s60/s60deploystep.cpp",
        "qt-s60/s60deploystep.h",
        "qt-s60/s60devicedebugruncontrol.cpp",
        "qt-s60/s60devicedebugruncontrol.h",
        "qt-s60/s60emulatorrunconfiguration.cpp",
        "qt-s60/s60emulatorrunconfiguration.h",
        "qt-s60/s60manager.cpp",
        "qt-s60/s60runcontrolbase.cpp",
        "qt-s60/s60runcontrolbase.h",
        "qt-s60/s60runcontrolfactory.cpp",
        "qt-s60/s60runcontrolfactory.h",
        "wizards/targetsetuppage.ui",
        "wizards/testwizardpage.ui",
        "wizards/wizards.qrc",
        "wizards/abstractmobileapp.cpp",
        "wizards/abstractmobileapp.h",
        "wizards/abstractmobileappwizard.cpp",
        "wizards/abstractmobileappwizard.h",
        "wizards/consoleappwizard.cpp",
        "wizards/consoleappwizard.h",
        "wizards/consoleappwizarddialog.cpp",
        "wizards/consoleappwizarddialog.h",
        "wizards/emptyprojectwizard.cpp",
        "wizards/emptyprojectwizard.h",
        "wizards/emptyprojectwizarddialog.cpp",
        "wizards/emptyprojectwizarddialog.h",
        "wizards/filespage.cpp",
        "wizards/filespage.h",
        "wizards/guiappwizard.cpp",
        "wizards/guiappwizard.h",
        "wizards/guiappwizarddialog.cpp",
        "wizards/guiappwizarddialog.h",
        "wizards/html5app.cpp",
        "wizards/html5app.h",
        "wizards/html5appwizard.cpp",
        "wizards/html5appwizard.h",
        "wizards/html5appwizardpages.cpp",
        "wizards/html5appwizardpages.h",
        "wizards/html5appwizardsourcespage.ui",
        "wizards/libraryparameters.h",
        "wizards/librarywizard.cpp",
        "wizards/librarywizard.h",
        "wizards/librarywizarddialog.cpp",
        "wizards/librarywizarddialog.h",
        "wizards/mobileapp.cpp",
        "wizards/mobileapp.h",
        "wizards/mobileappwizard.cpp",
        "wizards/mobileappwizard.h",
        "wizards/mobileappwizardgenericoptionspage.ui",
        "wizards/mobileappwizardharmattanoptionspage.ui",
        "wizards/mobileappwizardmaemooptionspage.ui",
        "wizards/mobileappwizardpages.cpp",
        "wizards/mobileappwizardpages.h",
        "wizards/mobileappwizardsymbianoptionspage.ui",
        "wizards/mobilelibraryparameters.cpp",
        "wizards/mobilelibraryparameters.h",
        "wizards/mobilelibrarywizardoptionpage.cpp",
        "wizards/mobilelibrarywizardoptionpage.h",
        "wizards/mobilelibrarywizardoptionpage.ui",
        "wizards/modulespage.cpp",
        "wizards/modulespage.h",
        "wizards/qtprojectparameters.cpp",
        "wizards/qtprojectparameters.h",
        "wizards/qtquickapp.cpp",
        "wizards/qtquickapp.h",
        "wizards/qtquickappwizard.cpp",
        "wizards/qtquickappwizard.h",
        "wizards/qtquickappwizardpages.cpp",
        "wizards/qtquickappwizardpages.h",
        "wizards/qtquickcomponentsetoptionspage.ui",
        "wizards/qtwizard.cpp",
        "wizards/qtwizard.h",
        "wizards/subdirsprojectwizard.cpp",
        "wizards/subdirsprojectwizard.h",
        "wizards/subdirsprojectwizarddialog.cpp",
        "wizards/subdirsprojectwizarddialog.h",
        "wizards/targetsetuppage.cpp",
        "wizards/targetsetuppage.h",
        "wizards/testwizard.cpp",
        "wizards/testwizard.h",
        "wizards/testwizarddialog.cpp",
        "wizards/testwizarddialog.h",
        "wizards/testwizardpage.cpp",
        "wizards/testwizardpage.h",
        "wizards/libraryparameters.cpp",
        "wizards/images/console.png",
        "wizards/images/gui.png",
        "wizards/images/html5app.png",
        "wizards/images/lib.png",
        "wizards/images/qtquickapp.png"
    ]
}




