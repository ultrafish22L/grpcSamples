#!/bin/bash
set -e


# Detect platform
case "$(uname -s)" in
        Darwin)
            PLATFORM="macos"
            EXT=""
            ;;
        Linux)
#            PLATFORM="linux"
#            EXT=""
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
GRPC_BIN="../$PLATFORM/bin/"
PROTOBUF_BIN="../third_party/protobuf/$PLATFORM/bin/"
PROTOC="$PROTOBUF_BIN"protoc"$EXT"
GRPC_PLUGIN="../third_party/grpc/windows/bin/grpc_python_plugin$EXT"
# Set path to .proto files
PROTODEFS="../sdk/src/api/grpc/protodef/"

mkdir -p generated

# Compile .proto files
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"common.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"common.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanenet.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanenet.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanetime.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanetime.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanevectypes.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanevectypes.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apianimationtimetransform.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apianimationtimetransform.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiarray.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiarray.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apibase64.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apibase64.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicaches.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apicaches.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apichangemanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apichangemanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicustomcurveeditorcontroller.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apicustomcurveeditorcontroller.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidbmaterialmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apidbmaterialmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidiagnostics.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apidiagnostics.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apidialogfeedback.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apidialogfeedback.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apifilename.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apifilename.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigaussiansplatting.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apigaussiansplatting.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigeometryexporter.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apigeometryexporter.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiguicomponent.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiguicomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimagebuffer.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiimagebuffer.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimageinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiimageinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilocaldb.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apilocaldb.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilogmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apilogmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimaterialx.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimaterialx.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinetrendermanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinetrendermanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_1.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_1.proto
#"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_2.proto
#"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_2.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_3.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_3.proto
#"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_4.proto
#"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_4.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_5.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_5.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_6.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_6.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_7.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_7.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodesystem_8.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodesystem_8.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiocioconfig.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiocioconfig.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiocioconfigloader.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiocioconfigloader.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiociocontextmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiociocontextmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apioctanemodules.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apioctanemodules.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apioutputcolorspaceinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apioutputcolorspaceinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apipackage.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apipackage.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprojectmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiprojectmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apireferencegraph.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apireferencegraph.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirender.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apirender.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirendercloudmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apirendercloudmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisceneexporter.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apisceneexporter.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisharedsurface.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apisharedsurface.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitilegrid.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apitilegrid.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitimesampling.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apitimesampling.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apibinaryfile.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apibinaryfile.proto
#"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilock.proto
#"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apilock.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodule.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimodule.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimoduledata.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimoduledata.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodulenodegraph.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimodulenodegraph.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiselectionmanager.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiselectionmanager.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apithread.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apithread.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicheckbox.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apicheckbox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicollapsiblepanelstack.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apicollapsiblepanelstack.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicolorswatch.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apicolorswatch.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apicombobox.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apicombobox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apifilechooser.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apifilechooser.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apigridlayout.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apigridlayout.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimage.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiimage.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiimagecomponent.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiimagecomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apilabel.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apilabel.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimodaldialog.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimodaldialog.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimouselistener.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimouselistener.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinumericbox.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinumericbox.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprogressbar.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiprogressbar.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitable.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apitable.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitextbutton.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apitextbutton.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apitexteditor.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apitexteditor.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apititlecomponent.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apititlecomponent.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiwindow.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiwindow.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanevolume.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanevolume.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiplugin.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiplugin.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apistart.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apistart.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apimainwindow.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apimainwindow.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodegrapheditor.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodegrapheditor.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodeinspector.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodeinspector.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apiprojectworkspace.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apiprojectworkspace.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apirenderview.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apirenderview.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apisceneoutliner.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apisceneoutliner.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneenums.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octaneenums.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneids.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octaneids.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneimageexport.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octaneimageexport.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octaneinfos.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octaneinfos.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanemodulesinfo.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanemodulesinfo.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanereferenceexport.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanereferenceexport.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"octanerenderpasses.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"octanerenderpasses.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN" "$PROTODEFS"apinodepininfohelper.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated "$PROTODEFS"apinodepininfohelper.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"callback.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated  "$PROTODEFS"callback.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"control.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated  "$PROTODEFS"control.proto
"$PROTOC" -I "$PROTODEFS" --grpc_out=generated --plugin=protoc-gen-grpc="$GRPC_PLUGIN"  "$PROTODEFS"livelink.proto
"$PROTOC" -I "$PROTODEFS" --python_out=generated  "$PROTODEFS"livelink.proto
