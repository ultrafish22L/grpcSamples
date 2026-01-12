import { BaseEdge, EdgeProps, getBezierPath } from '@xyflow/react';
import React, { CSSProperties } from 'react';

type CustomEdgeData = {
  onClick?: (event: React.MouseEvent, edge: any) => void;
  source?: string;
  target?: string;
  sourceHandle?: string | null;
  targetHandle?: string | null;
} & Record<string, unknown>;

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
  data = {},
}: EdgeProps) {
  const typedData = data as CustomEdgeData;
  const [edgePath] = getBezierPath({
    sourceX,
    sourceY,
    sourcePosition,
    targetX,
    targetY,
    targetPosition,
  });

  const handleMouseDown = (event: React.MouseEvent) => {
    // Only handle left clicks (button 0)
    if (event.button !== 0) return;
    
    event.stopPropagation();
    event.preventDefault(); // Prevent ReactFlow's drag behavior
    
    // Call the onClick handler passed in data
    if (typedData?.onClick) {
      typedData.onClick(event, { id, source: typedData.source, target: typedData.target, sourceHandle: typedData.sourceHandle, targetHandle: typedData.targetHandle });
    }
  };

  return (
    <>
      {/* Visible edge path */}
      <BaseEdge path={edgePath} markerEnd={markerEnd} style={style as CSSProperties} />
      
      {/* Invisible wide clickable path */}
      <path
        d={edgePath}
        fill="none"
        stroke="transparent"
        strokeWidth={20}
        onMouseDownCapture={handleMouseDown}
        style={{ cursor: 'pointer', pointerEvents: 'all' }}
        className="custom-edge-clickable-overlay"
      />
    </>
  );
}
