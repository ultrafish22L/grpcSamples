// Copyright (C) 2025 OTOY NZ Ltd.

#pragma once

// system includes
#include "apiarray.h"

// library includes
#include "octaneenums.h"
#include "octaneids.h"
#include "octaneinfos.h"


namespace Octane
{
    class ApiNodeGraph;
    
    namespace ApiMaterialX
    {
        /// A mapping entry pairing a MaterialX input name to an Octane pin-id
        struct MxInput
        {
            const char* mMxInputName;
            const PinId mPinId;
        };
        
    
        /// Import a MaterialX file (`.mtlx`) as a node graph with material outputs, into a given parent graph (defaults to root)
        /// Each material output is internally connected to a separate sub-graph for each material in the MaterialX file.
        /// There can be further nesting of sub graphs based on the topology of the original material graphs in the source file.
        /// Importing has 2 modes:
        /// - Native: Uses dedicated node types for MaterialX that follow the specification
        /// - Octane: Uses pre-existing Octane node types to emulate the behaviour of the MaterialX material
        ///
        /// @param [in] materialXFilePath
        ///     The file path to a MaterialX file (.mtlx)
        /// @param [in] parentNodeGraph
        ///     The MaterialX file will be imported as a node graph inside this parent graph (defaults to the root node graph)
        /// @param [in] useNativeMaterialXNodes
        ///     TRUE if the intent is to use dedicated MaterialX node types for the import, otherwise FALSE (default is TRUE)
        /// @return
        ///     A node graph containing the imported materials, with a material output for each one
        OCTANEAPI_DECL ApiNodeGraph* importMaterialXFile(
            const char*          materialXFilePath,
            const ApiNodeGraph * parentNodeGraph = nullptr,
            const bool           useNativeMaterialXNodes = true);
        
        /// Get all MaterialX node categories that are supported.
        ///
        /// @return
        ///     Array of all supported MaterialX node categories
        OCTANEAPI_DECL const StringArrayT getAllMxNodeCategories();
        
        /// Get the MaterialX node category represented by a given node type.
        ///
        /// @param [in] nodeType
        ///     A type of node that implements some configurations of a MaterialX node category
        /// @return
        ///     The corresponding MaterialX node category (nullptr if not found)
        OCTANEAPI_DECL const char* getMxNodeCategory(
            NodeType nodeType);
        
        /// Get the MaterialX node category represented by a given node type.
        ///
        /// @param [in] nodeGraphType
        ///     A type of node graph that implements a configuration of a MaterialX node category
        /// @return
        ///     The corresponding MaterialX node category (nullptr if not found)
        OCTANEAPI_DECL const char* getMxNodeCategory(
            NodeGraphType nodeGraphType);
        
        /// Get the MaterialX value type represented by a texture value type.
        ///
        /// @param [in] textureValueType
        ///     An Octane texture value type
        /// @return
        ///     The corresponding MaterialX value type (nullptr if not found)
        OCTANEAPI_DECL const char* getMxValueType(
            TextureValueType textureValueType);
        
        /// Get the texture value type representing a MaterialX value type.
        ///
        /// @param [in] mxValueType
        ///     A MaterialX value type
        /// @return
        ///     The corresponding texture value type (TEXTURE_VALUE_TYPE_UNKNOWN if not found)
        OCTANEAPI_DECL TextureValueType getTextureValueType(
            const char* mxValueTypeName);
        
        /// Get the MaterialX color space represented by an Octane named color space.
        ///
        /// @param [in] colorSpace
        ///     An Octane named color space
        /// @return
        ///     The corresponding MaterialX color space (nullptr if not supported)
        OCTANEAPI_DECL const char* getMxColorSpace(
            NamedColorSpace colorSpace);
        
        /// Get the Octane named color space representing a MaterialX color space.
        ///
        /// @param [in] mxColorSpace
        ///     A MaterialX color space
        /// @return
        ///     The corresponding Octane named color space (NAMED_COLOR_SPACE_OTHER if not supported)
        OCTANEAPI_DECL NamedColorSpace getNamedColorSpace(
            const char* mxColorSpace);
        
        /// Get the Octane node types representing a MaterialX node category.
        ///
        /// @param [in] mxNodeCategory
        ///     A MaterialX node category
        /// @return
        ///     An array of Octane node types representing a MaterialX node category
        OCTANEAPI_DECL ApiArray<NodeType> getNodeTypes(
            const char* mxNodeCategory);
        
        /// Get the Octane graph type representing a MaterialX node category.
        ///
        /// @param [in] mxNodeCategory
        ///     A MaterialX node category
        /// @return
        ///     The Octane graph type representing the given MaterialX node category (GT_UNKNOWN if not found)
        OCTANEAPI_DECL NodeGraphType getGraphType(
            const char* mxNodeCategory);
        
        /// Get the mapping of MaterialX input names to Octane pin ids for a given node type
        ///
        /// @param [in] nodeType
        ///     A type of node that implements some configurations of a MaterialX node category
        /// @return
        ///     A mapping from MaterialX input names to Octane pin ids for the given node type
        OCTANEAPI_DECL const ApiArray<MxInput> getMxInputNamesAndPinIds(
            NodeType nodeType);
        
        /// Get the names of inputs of a MaterialX node category represented as an Octane node graph
        /// Note: Graphs have dynamic pins, so there will be no pin ids.
        /// Instead, the input names are provided as an array of strings in the order they appear in the node graph.
        /// Each input name's placement in the array corresponds to the index of the input in the graph.
        ///
        /// @param [in] nodeGraphType
        ///     An Octane node graph type representing a MaterialX node category
        /// @return
        ///     The names of MaterialX inputs of the node category represented by the given node graph
        OCTANEAPI_DECL const StringArrayT getGraphMxInputNames(
            NodeGraphType nodeGraphType);
        
        /// Get the names of outputs of a MaterialX node category represented as an Octane node graph
        /// Note: Graphs have dynamic outputs, so there will be no pin ids.
        /// Instead, the output names are provided as an array of strings in the order they appear in the node graph.
        /// Each output name's placement in the array corresponds to the index of the output in the graph.
        ///
        /// @param [in] nodeGraphType
        ///     An Octane node graph type representing a MaterialX node category
        /// @return
        ///     The names of MaterialX outputs of the node category represented by the given node graph
        OCTANEAPI_DECL const StringArrayT getGraphMxOutputNames(
            NodeGraphType nodeGraphType);
        
        /// Find a typed texture node configuration corresponding to a given inputs and output type interface
        ///
        /// @param [in] mxNodeCategory
        ///     A MaterialX node category
        /// @param [in]  configurationInterface
        ///     The types of output and inputs a node would have in the desired configuration
        /// @return
        ///     The configuration that was found to match the given interface (nullptr if not found)
        OCTANEAPI_DECL const ApiTextureNodeTypeInfo::Configuration * findConfiguration(
            const char*                                              mxNodeCategory,
            const ApiTextureNodeTypeInfo::Configuration::Interface & configurationInterface);

        /// Find a typed texture node configuration corresponding to a given inputs and output type interface,
        /// specified as MaterialX input names and value types.
        ///
        /// @param [in] mxNodeCategory
        ///     A MaterialX node category
        /// @param [in] mxOutputValueType
        ///     The value type of the output port
        /// @param [in] mxInputNames
        ///     The names of input ports
        /// @param [in] mxInputValueTypes
        ///     The value types of input ports (corresponding to the names in mxInputNames)
        /// @param [in] mxInputCount
        ///     The numer of input names and types provided
        /// @return
        ///     A pointer to the matching node configuration (nullptr if not found)
        OCTANEAPI_DECL const ApiTextureNodeTypeInfo::Configuration * findConfiguration(
            const char*         mxNodeCategory,
            const char*         mxOutputValueType,
            const char *const * mxInputNames,
            const char *const * mxInputValueTypes,
            const size_t        mxInputCount);
    }
}