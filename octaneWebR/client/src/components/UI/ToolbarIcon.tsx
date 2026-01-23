/**
 * ToolbarIcon Component
 * Renders toolbar icons from the /icons/ directory
 * Falls back to Unicode symbols if icon file is not available
 */

import React from 'react';
import { getToolbarIconPath } from '../../constants/ToolbarIconMapping';

interface ToolbarIconProps {
  /** Toolbar action ID */
  id: string;
  /** Fallback Unicode symbol if icon not available */
  fallback?: string;
  /** Alt text for accessibility */
  alt?: string;
  /** Additional CSS classes */
  className?: string;
}

export const ToolbarIcon: React.FC<ToolbarIconProps> = ({ 
  id, 
  fallback = '◯', 
  alt, 
  className = '' 
}) => {
  const iconPath = getToolbarIconPath(id);
  
  // If we have an icon path, render the image
  if (iconPath) {
    return (
      <img
        src={iconPath}
        alt={alt || id}
        className={`toolbar-icon ${className}`}
        draggable={false}
      />
    );
  }
  
  // Otherwise, render the fallback Unicode symbol
  return <span className={`toolbar-icon-fallback ${className}`}>{fallback}</span>;
};
