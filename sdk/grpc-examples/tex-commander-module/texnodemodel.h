// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _TEX_NODE_MODEL_H_
#define _TEX_NODE_MODEL_H_  1


// system includes
#include <vector>
// application includes
#include "octanegrpcwrappers.h"
#include "apirootnodegraphclient.h"

class ApiImageProxy;

struct ApiNodeProxyWrapper
{
    std::string mName;
    std::string mFileName;
    std::string mPackage;
    ApiNodeProxy mProxy;
};
//--------------------------------------------------------------------------------------------------
/// Tracks the texture nodes in the project and acts as the data model for the table in the user
/// interface.
class TexNodeModel : public OctaneWrap::NodeItemObserver,
                     public OctaneWrap::TableModel,
                     public OctaneWrap::ProjectManagerObserver
{
public:

    TexNodeModel();

    virtual ~TexNodeModel();

    /// Sets the reference to the table component.
    void setTable(
        OctaneWrap::Table *table);

    /// Adds a new texture node from an image on disk.
    void addTextureNode(
        const std::string &imagePath);

    /// Deletes the texture node for the passed in row.
    void deleteTextureNode(
        const int row);

    /// Returns the row index for the passed in node. Returns -1 when the item was not tracked 
    /// by this model.
    int rowForNode(
        const ApiNodeProxy &node) const;

    /// Returns the number of nodes tracked by the model.
    size_t nbOfNodes() const;

    //-- Implementation of NodeItemObserver --

    virtual void onNodeItemChange(
        const GRPCChangeManagerChangeEvent &event) override;

    //-- Implementation of TableModel --

    virtual int numRows() override;

    virtual std::string cellData(
        const int row,
        const int column) override;

    virtual void onSelectionChange(
        const int lastRowSelected) override;

    //-- Implementation of ProjectManagerObserver --

    virtual void onProjectNew() override;

private:

    typedef std::vector<ApiNodeProxyWrapper> NodeArrayT;

    /// Table component that this model serves (can be NULL).
    OctaneWrap::Table        *mTable;
    /// Project root graph (changes when the project is reloaded).
    ApiRootNodeGraphProxy    mProjectGraph;
    /// Array of all the texture nodes in the project.
    NodeArrayT               mTexNodes;

    /// Collects all the texture nodes in the current project.
    void collectTextureNodes();

    void collectTextureNodesAsync();
};



#endif // #ifndef _TEX_NODE_MODEL_H_
