#!/bin/bash
set -e


# Detect platform
case "$(uname -s)" in
        Darwin)
            PLATFORM="macos"
            EXT=""
            ;;
        Linux)
            PLATFORM="windows"
            EXT=".exe"
            ;;
        MINGW*|MSYS*|CYGWIN*|Windows_NT)
            PLATFORM="windows"
            EXT=".exe"
            ;;
        *)
        echo "Unsupported platform: $(uname -s)"
        exit 1
        ;;
esac

echo "Detected platform: $PLATFORM"

# Set tool paths
GRPC_BIN="../third_party/grpc/$PLATFORM/bin/"
PROTOBUF_BIN="../third_party/protobuf/$PLATFORM/bin/"
PROTOC="$PROTOBUF_BIN"protoc"$EXT"
GRPC_PLUGIN="$GRPC_BIN"grpc_python_plugin"$EXT"
# Set path to .proto files
PROTODEFS="../sdk/src/api/grpc/protodef/"
PROTOOUT="./generated"

mkdir -p generated

# Compile .proto files
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"common.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"common.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanenet.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanenet.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanetime.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanetime.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanevectypes.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanevectypes.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apianimationtimetransform.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apianimationtimetransform.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiarray.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiarray.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apibase64.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apibase64.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicaches.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apicaches.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apichangemanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apichangemanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicustomcurveeditorcontroller.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apicustomcurveeditorcontroller.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidbmaterialmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apidbmaterialmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidiagnostics.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apidiagnostics.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidialogfeedback.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apidialogfeedback.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apifilename.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apifilename.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigaussiansplatting.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apigaussiansplatting.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigeometryexporter.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apigeometryexporter.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiguicomponent.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiguicomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimagebuffer.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiimagebuffer.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimageinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiimageinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilocaldb.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apilocaldb.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilogmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apilogmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimaterialx.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimaterialx.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinetrendermanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinetrendermanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_1.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_1.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_2.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_2.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_3.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_3.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_4.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_4.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_5.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_5.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_6.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_6.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_7.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_7.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_8.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodesystem_8.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiocioconfig.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiocioconfig.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiocioconfigloader.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiocioconfigloader.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiociocontextmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiociocontextmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apioctanemodules.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apioctanemodules.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apioutputcolorspaceinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apioutputcolorspaceinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apipackage.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apipackage.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprojectmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiprojectmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apireferencegraph.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apireferencegraph.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirender.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apirender.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirendercloudmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apirendercloudmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisceneexporter.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apisceneexporter.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisharedsurface.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apisharedsurface.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitilegrid.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apitilegrid.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitimesampling.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apitimesampling.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apibinaryfile.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apibinaryfile.proto
#"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilock.proto
#"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apilock.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodule.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimodule.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimoduledata.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimoduledata.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodulenodegraph.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimodulenodegraph.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiselectionmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiselectionmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apithread.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apithread.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicheckbox.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apicheckbox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicollapsiblepanelstack.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apicollapsiblepanelstack.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicolorswatch.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apicolorswatch.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicombobox.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apicombobox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apifilechooser.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apifilechooser.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigridlayout.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apigridlayout.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimage.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiimage.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimagecomponent.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiimagecomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilabel.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apilabel.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodaldialog.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimodaldialog.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimouselistener.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimouselistener.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinumericbox.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinumericbox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprogressbar.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiprogressbar.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitable.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apitable.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitextbutton.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apitextbutton.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitexteditor.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apitexteditor.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apititlecomponent.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apititlecomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiwindow.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiwindow.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanevolume.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanevolume.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiplugin.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiplugin.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apistart.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apistart.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimainwindow.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apimainwindow.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodegrapheditor.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodegrapheditor.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodeinspector.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodeinspector.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprojectworkspace.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apiprojectworkspace.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirenderview.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apirenderview.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisceneoutliner.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apisceneoutliner.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneenums.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octaneenums.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneids.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octaneids.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneimageexport.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octaneimageexport.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneinfos.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octaneinfos.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanemodulesinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanemodulesinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanereferenceexport.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanereferenceexport.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanerenderpasses.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"octanerenderpasses.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodepininfohelper.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"apinodepininfohelper.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"callback.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT" "$PROTODEFS"callback.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"control.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT"  "$PROTODEFS"control.proto

"$PROTOC" -I "$PROTODEFS" --grpc_out="$PROTOOUT" --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"livelink.proto
"$PROTOC" -I "$PROTODEFS" --python_out="$PROTOOUT"  "$PROTODEFS"livelink.proto
