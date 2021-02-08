TRANSLATIONS = \
        translation/xpeviewer_it.ts \
        translation/xpeviewer_ar.ts \
        translation/xpeviewer_de.ts \
        translation/xpeviewer_ja.ts \
        translation/xpeviewer_pl.ts \
        translation/xpeviewer_ru.ts \
        translation/xpeviewer_vi.ts \
        translation/xpeviewer_es.ts \
        translation/xpeviewer_fr.ts \
        translation/xpeviewer_pt_BR.ts \
        translation/xpeviewer_ko.ts \
        translation/xpeviewer_zh.ts \
        translation/xpeviewer_zh_TW.ts\
        translation/xpeviewer_tr.ts\
        translation/xpeviewer_he.ts

FORMS += \
    ../FormatDialogs/dialoghexsignature.ui \
    ../FormatDialogs/dialoginfo.ui \
    ../FormatDialogs/dialogtextinfo.ui \
    ../FormatWidgets/DEX/dexsectionheaderwidget.ui \
    ../FormatWidgets/DEX/dexwidget.ui \
    ../FormatWidgets/DEX/dialogdex.ui \
    ../FormatWidgets/ELF/elfsectionheaderwidget.ui \
    ../FormatWidgets/LE/lesectionheaderwidget.ui \
    ../FormatWidgets/MACH/machsectionheaderwidget.ui \
    ../FormatWidgets/NE/nesectionheaderwidget.ui \
    ../FormatWidgets/PE/pesectionheaderwidget.ui \
    ../FormatWidgets/SearchStrings/dialogsearchstrings.ui \
    ../FormatWidgets/SearchStrings/dialogsearchstringsprocess.ui \
    ../FormatWidgets/formatswidget.ui \
    ../StaticScan/dialogstaticscanprocess.ui \
    ../XDisasm/dialogasmsignature.ui \
    ../XDisasm/dialogdisasm.ui \
    ../XDisasm/dialogdisasmprocess.ui \
    ../XDisasmView/dialogmultidisasm.ui \
    ../XDisasmView/dialogmultidisasmsignature.ui \
    ../XDisasmView/xmultidisasmwidget.ui \
    ../XEntropyWidget/dialogentropy.ui \
    ../XHashWidget/dialoghash.ui \
    ../XHashWidget/dialoghashprocess.ui \
    ../XHashWidget/xhashwidget.ui \
    ../XHexView/dialoghexview.ui \
    ../XHexView/xhexviewwidget.ui \
    ../XMemoryMapWidget/dialogmemorymap.ui \
    ../XShortcuts/dialogshortcuts.ui

SOURCES += \
    ../Controls/xabstracttableview.cpp \
    ../FormatDialogs/dialoghexsignature.cpp \
    ../FormatDialogs/dialoginfo.cpp \
    ../FormatDialogs/dialogtextinfo.cpp \
    ../FormatWidgets/DEX/dex_defs.cpp \
    ../FormatWidgets/DEX/dexprocessdata.cpp \
    ../FormatWidgets/DEX/dexsectionheaderwidget.cpp \
    ../FormatWidgets/DEX/dexwidget.cpp \
    ../FormatWidgets/DEX/dialogdex.cpp \
    ../FormatWidgets/ELF/elfsectionheaderwidget.cpp \
    ../FormatWidgets/LE/lesectionheaderwidget.cpp \
    ../FormatWidgets/MACH/machsectionheaderwidget.cpp \
    ../FormatWidgets/NE/nesectionheaderwidget.cpp \
    ../FormatWidgets/PE/pesectionheaderwidget.cpp \
    ../FormatWidgets/SearchStrings/dialogsearchstrings.cpp \
    ../FormatWidgets/SearchStrings/dialogsearchstringsprocess.cpp \
    ../FormatWidgets/SearchStrings/searchstrings.cpp \
    ../FormatWidgets/formatswidget.cpp \
    ../Formats/xcom.cpp \
    ../StaticScan/dialogstaticscanprocess.cpp \
    ../XArchive/xarchive.cpp \
    ../XArchive/xarchives.cpp \
    ../XArchive/xcab.cpp \
    ../XArchive/xmachofat.cpp \
    ../XArchive/xrar.cpp \
    ../XArchive/xsevenzip.cpp \
    ../XArchive/xzip.cpp \
    ../XDEX/xandroidbinary.cpp \
    ../XDEX/xdex.cpp \
    ../XDisasm/dialogasmsignature.cpp \
    ../XDisasm/dialogdisasm.cpp \
    ../XDisasmView/dialogmultidisasm.cpp \
    ../XDisasmView/dialogmultidisasmsignature.cpp \
    ../XDisasmView/xdisasmview.cpp \
    ../XDisasmView/xmultidisasmwidget.cpp \
    ../XEntropyWidget/dialogentropy.cpp \
    ../XHashWidget/dialoghash.cpp \
    ../XHashWidget/dialoghashprocess.cpp \
    ../XHashWidget/hashprocess.cpp \
    ../XHashWidget/xhashwidget.cpp \
    ../XHexView/dialoghexview.cpp \
    ../XHexView/xhexview.cpp \
    ../XHexView/xhexviewwidget.cpp \
    ../XMemoryMapWidget/dialogmemorymap.cpp \
    ../XShortcuts/dialogshortcuts.cpp \
    ../XShortcuts/xshortcuts.cpp \
    ../winloader_source/winloader.cpp
