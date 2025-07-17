// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

#include "octanetypes.h"
#ifdef OCTANEAPI_DECL
#undef OCTANEAPI_DECL
#endif
#define OCTANEAPI_DECL
#include "octanevectypes.h"
#include "grpcbase.h"
#include "clientcallbackmgr.h"
#include "grpcapinodeinfo.h"
class ApiNodeProxy;


#include "apisceneexporter.h"


class Convert;

class GRPCSettings;

/// Proxy class for ApiSceneExporter
class ApiSceneExporterProxy : public GRPCBase
{
public:
    /// Tells whether the @ref ApiSceneExporter is supported by this build
    /// @param[out] status
    ///     Contains the status of the gRPC call
    static bool isSupported();

    /// Starts a new export. If there is still an export going on, it will be cancelled and the
    /// exporter reset.
    ///
    /// @param[in]  sceneFile
    ///     The scene file that will be written during finish(). Can be either an .ocs or .orbx file
    ///     or NULL/empty. All file assets that are created during the export are written into a new
    ///     asset directory. If the scene file name is either an .orbx file or empty, the asset
    ///     directory is temporary and will be deleted when destroy() is called.
    /// @param[in]  rootNodes
    ///     An array of the root nodes that should be tracked. All root nodes must come from the
    ///     same root node graph. Any node can be a root node, including render targets.
    /// @param[in]  rootNodesSize
    ///     The size of the array specified in rootNodes.
    /// @param[in]  timeSamplesPeriod
    ///     The period of the time sampling. (see ApiTimeSampling for more information)
    /// @param[in]  timeSamples
    ///     Pointer to the time sample pattern array. If NULL, a regular time sampling is
    ///     constructed, starting at time 0. The time stamps must be sorted.
    ///     (see ApiTimeSampling for more information)
    /// @param[in]  timeSamplesSize
    ///     The size of the time sample pattern array. If 0, a regular time sampling is constructed.
    ///     (see ApiTimeSampling for more information)
    /// @param[in]  geometryFormat
    ///     The format that should be used for the geometry export.
    /// @param[in]  referencePackageSettings
    ///     If not NULL, the package will include bounding box data exported with these settings.
    ///     Ignored if the sceneFile is not .orbx file.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     The created scene exporter or NULL if an error occurred in which case you should check
    ///     the log for more information.
    static ApiSceneExporterProxy create(
            const char *const                         sceneFile,
            ApiNodeProxy* const                       rootNodes[],
            const size_t                              rootNodesSize,
            const Octane::TimeT                       timeSamplesPeriod,
            const Octane::TimeT *const                timeSamples,
            const size_t                              timeSamplesSize,
            const Octane::GeometryExportFormat        geometryFormat,
            const Octane::ReferencePackageExportSettings * referencePackageSettings
            );

    /// Destroys the instance. The instance pointer is invalid afterwards. This will also delete
    /// any temporary asset directory that was created during the export.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void destroy();

    /// Returns the current state of the scene exporter.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    Octane::ExportState state() const;

    /// Exports the next time sample. Please check state() afterwards to find out whether an error
    /// occurred. You will be able to continue exporting sample after an error occurred but the
    /// exported scene will most likely won't be complete/correct. Any errors that occurred will
    /// have an error message in the log.
    ///
    /// @param[in]  interval
    ///     The time interval that is passed on to the geometry exporters (see
    ///     ApiGeometryExporter::writeFrame() for more details).
    /// @param[out] status
    ///     Contains the status of the gRPC call
    void exportSample(
            const Octane::TimeSpanT   interval
            );

    /// Returns the current sample/frame index of the export.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    uint32_t sampleIx() const;

    /// Finishes the scene export and creates the scene file or creates an OCS string if no
    /// sceneFile.
    ///
    /// NOTE: If a temporary asset directory was created, it will not be deleted yet. That happens
    ///       when the ApiSceneExporter instance gets detroyed.
    ///
    /// @param[in]  framesPerSecond
    ///     The frames per second that should be written into the project settings that are stored
    ///     in the scene.
    /// @param[in]  deleteUnconnectedNodes
    ///     If TRUE, all nodes that are not connected with the specified root nodes, will
    ///     be deleted before the export. If you - for debugging reasons - would like to keep those
    ///     nodes around, set the value to FALSE.
    /// @param[in]  createOcsString
    ///     Enables the creation of the OCS string if no file name was specified in create().
    ///     If a file name was specified, this parameter will be ignored.
    ///     This is useful if you want to upload the project to RNDR.
    /// @param[out] status
    ///     Contains the status of the gRPC call
    /// @return
    ///     TRUE if the executed successfully, FALSE if not (in which case you should check the log
    ///     for more information).
    bool finish(
            const float                               framesPerSecond,
            const bool                                deleteUnconnectedNodes,
            const bool                                createOcsString
            );

    /// Returns the current OCS string that was written during finish() or an empty string if
    /// finish() wasn't called yet or a sceneFile was specified during create().
    /// @param[out] status
    ///     Contains the status of the gRPC call
    std::string ocsString() const;

private:
    static GRPCSettings & getGRPCSettings();
};
