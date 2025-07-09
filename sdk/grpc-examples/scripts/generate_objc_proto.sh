#!/bin/bash
set -e


# Detect platform
case "$(uname -s)" in
        Darwin)
            PLATFORM="macos"
            EXT=""
            ;;
        Linux)
            PLATFORM="linux"
            EXT=""
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
GRPC_BIN="../../thirdparty/grpc/$PLATFORM/bin/"
PROTOBUF_BIN="../../thirdparty/protobuf/$PLATFORM/bin/"
PROTOC="$PROTOBUF_BIN"protoc"$EXT"
GRPC_PLUGIN="$GRPC_BIN"grpc_objective_c_plugin"$EXT"
# Set path to .proto files
PROTODEFS="../../src/api/grpc/protodef/"

mkdir -p proto_objc_out

# Compile .proto files
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"common.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"common.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanenet.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanenet.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanetime.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanetime.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanevectypes.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanevectypes.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apianimationtimetransform.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apianimationtimetransform.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiarray.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiarray.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apibase64.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apibase64.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicaches.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apicaches.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apichangemanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apichangemanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicustomcurveeditorcontroller.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apicustomcurveeditorcontroller.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidbmaterialmanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apidbmaterialmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidiagnostics.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apidiagnostics.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidialogfeedback.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apidialogfeedback.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apifilename.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apifilename.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigeometryexporter.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apigeometryexporter.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiguicomponent.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiguicomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimagebuffer.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiimagebuffer.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimageinfo.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiimageinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiinfo.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilocaldb.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apilocaldb.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilogmanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apilogmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimaterialx.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimaterialx.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinetrendermanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinetrendermanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_1.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_1.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_2.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_2.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_3.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_3.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_4.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_4.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_5.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_5.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_6.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_6.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_7.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_7.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_8.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodesystem_8.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiocioconfig.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiocioconfig.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiocioconfigloader.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiocioconfigloader.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiociocontextmanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiociocontextmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apioctanemodules.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apioctanemodules.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apioutputcolorspaceinfo.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apioutputcolorspaceinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apipackage.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apipackage.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprojectmanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiprojectmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apireferencegraph.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apireferencegraph.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirender.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apirender.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirendercloudmanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apirendercloudmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisceneexporter.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apisceneexporter.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisharedsurface.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apisharedsurface.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitilegrid.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apitilegrid.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitimesampling.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apitimesampling.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apibinaryfile.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apibinaryfile.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilock.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apilock.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodule.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimodule.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimoduledata.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimoduledata.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodulenodegraph.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimodulenodegraph.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiselectionmanager.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiselectionmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apithread.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apithread.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicheckbox.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apicheckbox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicollapsiblepanelstack.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apicollapsiblepanelstack.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicolorswatch.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apicolorswatch.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicombobox.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apicombobox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apifilechooser.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apifilechooser.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigridlayout.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apigridlayout.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimage.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiimage.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimagecomponent.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiimagecomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilabel.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apilabel.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodaldialog.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimodaldialog.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimouselistener.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimouselistener.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinumericbox.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinumericbox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprogressbar.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiprogressbar.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitable.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apitable.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitextbutton.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apitextbutton.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitexteditor.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apitexteditor.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apititlecomponent.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apititlecomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiwindow.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiwindow.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanevolume.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanevolume.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiplugin.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiplugin.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apistart.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apistart.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimainwindow.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apimainwindow.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodegrapheditor.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodegrapheditor.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodeinspector.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodeinspector.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprojectworkspace.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apiprojectworkspace.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirenderview.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apirenderview.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisceneoutliner.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apisceneoutliner.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneenums.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octaneenums.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneids.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octaneids.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneimageexport.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octaneimageexport.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneinfos.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octaneinfos.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanemodulesinfo.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanemodulesinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanereferenceexport.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanereferenceexport.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanerenderpasses.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"octanerenderpasses.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodepininfohelper.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"apinodepininfohelper.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"callback.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out "$PROTODEFS"callback.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"control.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out  "$PROTODEFS"control.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=./proto_objc_out --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"livelink.proto
"$PROTOC" -I "$PROTODEFS" --objc_out=./proto_objc_out  "$PROTODEFS"livelink.proto
