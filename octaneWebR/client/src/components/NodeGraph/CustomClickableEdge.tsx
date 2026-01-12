import { BaseEdge, EdgeProps, getBezierPath } from 'reactflow';
import React from 'react';

/**
 * Custom edge component that handles clicks directly.
 * ReactFlow's onEdgeClick is not firing reliably, so we implement
 * click handling at the edge component level.
 */
export default function CustomClickableEdge({
  id,
  sourceX,
  sourceY,
  targetX,
  targetY,
  sourcePosition,
  targetPosition,
  style = {},
  markerEnd,
  data,
}: EdgeProps) {
  const [edgePath] = getBezierPath({
    sourceX,
    sourceY,
    sourcePosition,
    targetX,
    targetY,
    targetPosition,
  });

  const handleClick = (event: React.MouseEvent) => {
    event.stopPropagation();
    console.log('🔗🔗🔗 CUSTOM EDGE CLICK FIRED!!! 🔗🔗🔗', id);
    
    // Call the onClick handler passed in data
    if (data?.onClick) {
      data.onClick(event, { id, source: data.source, target: data.target, sourceHandle: data.sourceHandle, targetHandle: data.targetHandle });
    }
  };

  return (
    <>
      {/* Visible edge path */}
      <BaseEdge path={edgePath} markerEnd={markerEnd} style={style} />
      
      {/* Invisible wide clickable path */}
      <path
        d={edgePath}
        fill="none"
        stroke="transparent"
        strokeWidth={20}
        onClick={handleClick}
        onMouseEnter={() => console.log('🖱️ Custom Edge MOUSE ENTER:', id)}
        style={{ cursor: 'pointer', pointerEvents: 'all' }}
        className="custom-edge-clickable-overlay"
      />
    </>
  );
}
