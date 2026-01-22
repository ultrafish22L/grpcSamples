// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _API_GEOMETRY_EXPORTER_H_
#define _API_GEOMETRY_EXPORTER_H_   1

#include "octaneenums.h"
#include "octanetime.h"

namespace Octane
{

class ApiItem;
class ApiNodeGraph;
struct ApiTimeSampling;

//--------------------------------------------------------------------------------------------------
/// 
/// Exporting geometry
/// ------------------
///
/// Before exporting frames, use addItem() to define which items to export. For geometry nodes,
/// all geometry connected via the inputs of that node are exported as well. In a typical use
/// case, exporting the scene which is currently rendered, only the geometry node connected
/// to the render target needs to be added.
/// 
/// The items passed into addItem() should not be deleted during the export. The geometry 
/// which is connected via the input pins can be disconnected or deleted during the export, 
/// and newly connected geometry will be automatically included.
///
/// ## meshes ##
/// 
/// Mesh nodes should not be deleted and recreated between frames. Otherwise the exporter
/// can't export these mesh nodes as a single moving object. This will slow down loading the
/// exported file and may break vertex motion blur.
///
/// The set of material pins and object layer pins must be constant (i.e. the
/// A_MATERIAL_NAMES and A_OBJECT_NAMES cannot change).
///
/// Note that the names of the material and object inputs will not be exported as material/
/// object layer inputs on the archive. The inputs are defined by the connected nodes.
///
/// ## transforms ##
/// 
/// Transforms may be defined via either scatter nodes or placement nodes. You can use a
/// transform matrix filled with zeros to indicate an instance is invisible in this frame.
/// This can be useful to mark meshes as invisible, or to ensure instances created with a
/// scatter node stay at the same index in that scatter node.
///
/// Sometimes it is necessary to export subframes for a transform node during a frame.
/// To export subframes, pass an interval into the writeFrame() function and assign an
/// animation to the transform node with multiple keyframes within this interval.
///
///
/// Defining the time sampling
/// --------------------------
/// 
/// You should explicitly define the time stamps for the exported frames using
/// writeTimeSampling().
/// 
/// The actual time stamps in the exported nodes will be ignored (and can be set to a
/// fixed interval, eg. [0, 1] or [0, 1/24] if this is more convenient for the plug-in).
/// 
/// Defining the material and object layer inputs
/// ---------------------------------------------
///
/// The material inputs visible on the geometry archive are defined in terms of the material
/// nodes connected to the geometry:
///
///  - all empty material pins will be grouped together into a "Default material" input
///
///  - Connected pins will be grouped together according to their connected node. 
///    This may be either a material node or a linker. Every  distinct node will result
///    in a single input with the same name as that node.
///
///  - If two input nodes have the same name, a number will be appended to one of the
///    names to make them unique.
/// 
/// The object layer inputs are defined in an analogue way.
/// 
/// 
/// Exporting a geometry archive to a scene file (OCS or ORBX)
/// ----------------------------------------------------------
/// 
/// To include the exported Alembic file in a scene file, createGeometryArchive() can be used
/// to create the geometry archive for the exported file.
/// 
/// createGeometryArchive() will try to connect materials and object layer nodes in your scene
/// to the created archive. You should ensure that these nodes are either:
/// 
///   - owned by the input pins of your mesh node. In this case the node will be copied to
///     the input pin on the created archive.
/// 
///   - owned by the same parent node graph as the newly created archive.
/// 
///   - connected via either: an input linker of the parent node graph, or an output linker
///     of another node graph inside the parent graph. In that case that linker node
///     is connected to the archive.
/// 
/// In other cases the material cannot be connected to the archive and the input pin will be
/// left empty. This may happen if for instance both a mesh node and the connected material
/// node are inside a child node graph.
///
/// Later, functions like collectItemTree() or deleteUnconnectedItems() may be used to prune
/// the actual geometry nodes before exporting the scene file.
///
/// @note This is not supported by all SDK flavours. Check @ref ApiGeometryExporter::isSupported()
///     to know whether it is or not.
///
class OCTANEAPI_DECL ApiGeometryExporter
{
public:

    /// Tells whether @ref ApiGeometryExporter is supported by this build
    static bool isSupported();

    /// Creates an exporter to export geometry to a file.
    /// 
    /// @param[in] fileName
    ///     file name, encoded as UTF-8. The file name is taken as is, it usually ends with the
    ///     ".abc" extension. if the filename is relative path, we anchor it with current projet 
    ///     directory if a project exits, otherwise with the current working directory.
    /// @param[in] description
    ///     A line of text describing the contents of this file.
    /// @param[in]  exportFormat
    ///     The format that should be used for the geometry export.
    /// @param[in]  exportGeneratedGeometry
    ///     If set to TRUE, geometry generated by built-in script graphs will be exported as
    ///     regular geometry. If set to FALSE, only transformations leading up to the generator
    ///     script graph will be exported and the script graph will be linked via an input.
    /// @return
    ///     the created object. If the file can't be opened this call returns NULL, which indicates
    ///     that either the file name is invalid or you don't have permissions to create the Alembic
    ///     file or an Alembic file with the same name already exists and is already open somewhere.
    static ApiGeometryExporter *create(
        const char                 *fileName,
        const char                 *description = NULL,
        const GeometryExportFormat exportFormat = GEOMETRY_FORMAT_ALEMBIC,
        const bool                 exportGeneratedGeometry = true);

    /// Sets the aspect ratio used for exporting cameras. This is needed to export correct lens
    /// shift values. A call to this method affects any camera nodes added afterwards.
    /// 
    /// @param[in] ratio
    ///     film width / film height
    void setAspectRatio(
        float ratio);

    /// Sets additional FBX options
    ///
    /// @param[in] fastScatterExport
    ///     If TRUE, the child of a scatter node is exported only on the first transform node.
    ///     So readers of the exported FBX should copy or attach it to all other transform nodes. Otherwise
    ///     the child will be cloned to all transform nodes.
    /// @param[in] exportMaterial
    ///     If TRUE, basic materials and textures will be exported with geometry. Textures are generated 
    ///     using preview render
    /// @param[in] asStingrayMaterial
    ///     If TRUE, materials are exported in Stingray format. Read only by Max, Maya and unity applications.
    /// @param[in] renderSizeX
    ///     Texture render dimension in X. larger the value, slower the export.
    /// @param[in] renderSizeY
    ///     Texture render dimension in Y. larger the value, slower the export.
    /// @param[in] writeOcsData
    ///     export octane OCS data of the material into FBX file. all the corresponding external files are also
    ///     embedded into the FBX. This data will be read only by octane.
    void setFbxOptions(
        const bool     fastScatterExport,
        const bool     exportMaterial,
        const bool     asStingrayMaterial,
        const uint32_t renderSizeX,
        const uint32_t renderSizeY,
        const bool     writeOcsData);

    /// Adds an item to this exporter. Currently any geometry node type, and thin lens cameras are
    /// allowed (or linker nodes with one of those as input node).
    /// 
    /// If the item is a node graph, all compatible output linkers are added, and this method 
    /// returns TRUE if at least one node was added successfully.
    /// 
    /// All items should be added before the first frame is exported.
    bool addItem(
        ApiItem *item);

    /// Write the current state of the node graph to the file. This is then considered one frame of
    /// the animation. This may take some time.
    /// 
    /// Returns FALSE if an error occurs or the node given to create() was destroyed.
    /// 
    /// @param[in] interval
    ///     The interval covered by the current frame.
    ///     
    ///     If an empty interval is given, all objects are exported with one key frame for every
    ///     exported frame, based on current attribute values.
    ///     
    ///     If not empty, geometry with an animator which provides more than one frame within
    ///     the given interval will be exported with a corresponding number of key frames.
    ///     To avoid interpolation between frames, the animator should provide key frames at time
    ///     stamps `interval.begin + i/N * (interval.end - interval.begin), for 0 <= i < N.
    ///     
    ///     Some exporters will not change the key frame rate of an exported object once the
    ///     object is created, therefore you should consistently provide the same number of
    ///     subframes for each object as the export progresses. The last frame may be exported
    ///     with an empty frame to avoid trailing key frames after the time stamp of the last
    ///     frame.
    bool writeFrame(
        const Octane::TimeSpanT interval);

    /// Write the current state of the node graph to the file, using an empty interval so no
    /// sub frames will be exported for any object.
    bool writeFrame();

    /// Saves the time sampling pattern to the file. This determines which time stamp is associated
    /// with every frame written with writeFrame().
    /// 
    /// If this function is not called before the exporter is destroyed, then the time sampling is
    /// derived from the node graph time stamps when the frames were written.
    /// 
    /// @param[in] times
    ///     The time sampling pattern which was used.
    /// @return
    ///     TRUE if the given time sampling was valid and can be written to the file.
    bool writeTimeSampling(
        const ApiTimeSampling &times);

    /// Creates a geometry archive node for this exported geometry, containing all the input pins
    /// which will be created when the exported file is loaded into this node. If the given parent 
    /// node graph also contains the items connected to the material and object layer inputs, then
    /// these will be connected to the created geometry archive.
    ///
    /// NOTE: To be able write the scene into a package (which will copy the exported geometry file
    ///       into the package), the geometry file must be accessible, which means that the
    ///       ApiGeoemtryExporter needs to be destroyed BEFORE you call the export functions.
    /// 
    /// @param[in] owner
    ///     The parent node graph where to place the node graph. Should be the same node graph where
    ///     the materials are located, so they can be connected to the inputs of the created
    ///     archive.
    /// @param[in] createObjectInputs
    ///     TRUE if the created node graph should contain inputs for object layer entries
    /// @return
    ///     A geometry archive. This archive will have its file name set, but it will not be
    ///     evaluated, so its contents are not loaded. It can be exported to an ORBX package without
    ///     evaluating first.
    ApiNodeGraph *createGeometryArchive(
        ApiNodeGraph *owner,
        bool         createObjectInputs) const;

    /// Closes the file and destroys this exporter. The written file will not be usable until the
    /// exporter is closed.
    void destroy();
};

} // namespace Octane


#endif // #ifndef _API_GEOMETRY_EXPORTER_H_
