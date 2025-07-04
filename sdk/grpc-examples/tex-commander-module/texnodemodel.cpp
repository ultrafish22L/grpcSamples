// Copyright (C) 2025 OTOY NZ Ltd.

// system includes
#include <stack>
// myself
#include "texnodemodel.h"
#include "apiitemarrayclient.h"
#include "apiselectionmanagerclient.h"
#include "apiprojectmanagerclient.h"
#include "apichangemanagerclient.h"
#include "apicontrol.h"
#include "grpcsettings.h"
//API_RLOG_DECLARE(texCommander, "texCom", "Logging for the texture commander");



TexNodeModel::TexNodeModel()
:
    mTable(),
    mProjectGraph()
{
    // listen for the project renew event
    ApiProjectManagerProxy::addObserver(*this);
    //ApiProjectManagerProxy::removeObserver(*this, status);
    //ApiProjectManagerProxy::addObserver(*this, status);
    //ApiProjectManagerProxy::removeObserver(*this, status);
}


TexNodeModel::~TexNodeModel()
{
    // stop listening to everything
    ApiProjectManagerProxy::removeObserver(*this);
    ApiChangeManagerProxy::stopObserving(*this);
}


void TexNodeModel::setTable(
    OctaneWrap::Table *table)
{
    mTable = table;
    if (mTable) { mTable->updateContent(); }
}


void TexNodeModel::addTextureNode(
    const std::string &imagePath)
{
    if (imagePath.empty()) { return; }
    if (mProjectGraph.isNull())
    {
        return;
    }
    // create the texture node -> the add event will put it in our list
    grpc::Status status;
    ApiNodeProxy texNode = ApiNodeProxy::create(Octane::NT_TEX_IMAGE, mProjectGraph, false);
    if (!texNode.isNull())
    {
        texNode.set(Octane::A_FILENAME, imagePath.c_str(), false);
        texNode.setName(imagePath.c_str());
    }
}


void TexNodeModel::deleteTextureNode(
    const int row)
{
    if (row >= 0 && row < (int)mTexNodes.size())
    {
        // the delete event will take care of the rest
        mTexNodes[row].mProxy.destroy();
    }
}


int TexNodeModel::rowForNode(
    const ApiNodeProxy & node) const
{
    for (size_t i = 0; i < mTexNodes.size(); ++i)
    {
        if (mTexNodes[i].mProxy.getObjectHandle() == node.getObjectHandle())
        {
            return (int)i;
        }
    }

    // not found
    return -1;
}


size_t TexNodeModel::nbOfNodes() const
{
    return mTexNodes.size();
}


void TexNodeModel::onNodeItemChange(
    const GRPCChangeManagerChangeEvent & event)
{
    if (!event.mChangedItem->isNode())
    {
        return;
    }
    bool update = false;

    switch (event.mType)
    {
        case GRPCChangeManagerChangeEvent::ITEM_ADDED:
        {
            // texture node added
            if (event.mChangedItem->toNode().type() == Octane::NT_TEX_IMAGE)
            {
              /*  API_RLOG(texCommander, "texture node added: '%s'",
                         event.mChangedItem->toNode(status).name(status));*/

                ApiNodeProxyWrapper tex;
                tex.mProxy = event.mChangedItem->toNode();
                tex.mName = tex.mProxy.name();
                tex.mFileName = tex.mProxy.getString(A_FILENAME);
                tex.mPackage = tex.mProxy.getString(A_PACKAGE);
                mTexNodes.push_back(tex);

                // listen to this node for deletion and name change
                int mask = GRPCChangeManagerChangeEvent::ITEM_NAME_CHANGED
                           | GRPCChangeManagerChangeEvent::ITEM_DELETE;
                ApiChangeManagerProxy::observeApiItem(mTexNodes.back().mProxy, *this, mask);
                update = true;
            }
            break;
        }
        case GRPCChangeManagerChangeEvent::ITEM_DELETE:
        {
            /*  API_RLOG(texCommander, "texture node removed: '%s'", event.mChangedItem->toNode(status).name(status));*/

            // texture node was deleted
            auto removedHandle = event.mChangedItem->getObjectHandle();

            auto it = std::find_if(
                mTexNodes.begin(),
                mTexNodes.end(),
                [removedHandle](const ApiNodeProxyWrapper& node)
                {
                    return node.mProxy.getObjectHandle() == removedHandle;
                }
            );

            if (it != mTexNodes.end())
            {
                mTexNodes.erase(it);
            }
            /*    mTexNodes.erase(std::find(mTexNodes.begin(),
                                            mTexNodes.end(),
                                            (ApiNodeProxy*)event.mChangedItem));*/
            update = true;
            break;
        }
        case GRPCChangeManagerChangeEvent::ITEM_NAME_CHANGED:
        {
          /*  API_RLOG(texCommander, "texture node name changed: '%s'",
                     event.mChangedItem->toNode(status).name(status));*/

            // name of a texture node changed

            //ApiNodeProxyWrapper tex;
            //tex.mName = event.mChangedItem->toNode(status).name(status);

            update = true; 
            break;
        }
        default:
        {

        }
    }

    // signal that the content changed
    if (update && mTable)
    { 
        mTable->updateContent();
    }
}


int TexNodeModel::numRows()
{
    return (int)mTexNodes.size();
}


std::string TexNodeModel::cellData(
    const int row,
    const int column)
{
    grpc::Status status;
    if (row < (int)mTexNodes.size())
    {
        switch (column)
        {
            // display node name
            case 0:
            {
                return mTexNodes[row].mName;
            }
            // display filename attribute
            case 1:
            {
                const std::string fileName = mTexNodes[row].mFileName;  // getString(Octane::A_FILENAME, status);
                const std::string packageName = mTexNodes[row].mPackage;// getString(Octane::A_PACKAGE, status);
                // loaded from memory
                if (fileName.empty() && packageName.empty())
                {
                    return "in-memory";
                }
                // loaded from file on disk
                else if (packageName.empty())
                {
                    return fileName;
                }
                // loaded from file
                else
                {
                    return fileName + "::" + packageName;
                }
            }
            default:
                return "";
        }
    }

    return "";
}


void TexNodeModel::onSelectionChange(
    const int lastRowSelected)
{

    // select the selected node
    if (lastRowSelected >= 0 && lastRowSelected < (int)mTexNodes.size())
    {
        if (!ApiSelectionManagerProxy::isItemSelected(mTexNodes[lastRowSelected].mProxy))
        {
            ApiSelectionManagerProxy::clearSelection();
            ApiSelectionManagerProxy::select(mTexNodes[lastRowSelected].mProxy, true);
        }
    }
}


void TexNodeModel::onProjectNew()
{
    mTexNodes.clear();

    // stop listening to everything that is related with the old project (This is very important
    // because the old project is only de^leted after the new project is created)
    ApiChangeManagerProxy::stopObserving(*this);

    // fetch the new graph
    mProjectGraph = ApiProjectManagerProxy::rootNodeGraph();

    // listen for changes in the project rootgraph
    const int mask = GRPCChangeManagerChangeEvent::ITEM_ADDED;

    ApiItemProxy* item = &mProjectGraph;
    ApiChangeManagerProxy::observeApiItem(*item, *this, mask);

    // collect the existing texturen nodes
    collectTextureNodes();
}


void TexNodeModel::collectTextureNodesAsync()
{
    // find all the texture nodes owned by pins (via a dfs)
    std::stack<ApiItemProxy*> stack;
    std::vector<ApiItemProxy*> itemsToDelete;
    stack.push(&mProjectGraph);
    while (!stack.empty())
    {
        // fetch the current item
        const ApiItemProxy* item = stack.top();
        stack.pop();

        // item is an image texture node
        if (item->isNode() && item->toNode().type() == Octane::NT_TEX_IMAGE)
        {
            ApiNodeProxyWrapper tex;
            tex.mProxy = item->toNode();
            tex.mName = tex.mProxy.name();
            tex.mFileName = tex.mProxy.getString(A_FILENAME);
            tex.mPackage = tex.mProxy.getString(A_PACKAGE);
            mTexNodes.push_back(tex);
        }
        // item is a graph
        else if (item->isGraph())
        {
            // search all the owned items
            ApiItemArrayProxy ownedItems;
            item->toGraph().getOwnedItems(ownedItems);
            int size = ownedItems.size();
            for (size_t i = 0; i < size; ++i)
            {
                ApiItemProxy* item = new ApiItemProxy();
                *item = ownedItems.get(i);
                itemsToDelete.push_back(item);
                stack.push(item);
            }
        }
        // item is a node
        else
        {
            //temp = &(item->toNode(status));
            const ApiNodeProxy  node = (item->toNode());
            // search all the nodes owned by the pins of the item
            for (size_t i = 0; i < node.pinCount(); ++i)
            {
                ApiNodeProxy * inputNode = new ApiNodeProxy();
                itemsToDelete.push_back(inputNode);
                *inputNode = node.inputNodeIx(i, false);
                if (!inputNode->isNull() && inputNode->pinOwned())
                {
                    stack.push(inputNode);
                }
            }
        }
    }

    // delete temporary items
    for( auto & item : itemsToDelete)
    {
        delete item;
    }
    itemsToDelete.clear();
    //API_RLOG(texCommander, "Collected %llu texture nodes", mTexNodes.size());

    // update content of table
    if (mTable)
    {
        mTable->updateContent();
    }

    // listen for deletion of the texture nodes
    for (size_t i=0; i<mTexNodes.size(); ++i)
    {
        const int mask = GRPCChangeManagerChangeEvent::ITEM_DELETE 
            | GRPCChangeManagerChangeEvent::ITEM_NAME_CHANGED;
        ApiChangeManagerProxy::observeApiItem(mTexNodes[i].mProxy, *this, mask);
    }
}

void TexNodeModel::collectTextureNodes()
{
    // clear all the nodes we currently have
    mTexNodes.clear();

    std::string uniqueModuleId = GRPCSettings::getInstance().callbackSource();

    ApiControlService::startBlockingOperation(
        uniqueModuleId,
        "test message 123",
        [this]() {
            this->collectTextureNodesAsync();  // or just TestFunc();
        });
     
}
