import { memo, useState, useEffect, useCallback } from 'react';
import { useStore } from '../../store/useStore';
import { Endpoint } from '../../types';
import { getDefaultParameters } from '../../utils/endpointSchema';
import { getEndpointCostDisplay } from '../../utils/endpointCosts';
import { logger } from '../../services/logger';
import styles from './Layout.module.css';

// Map category to output type color (based on what the endpoint produces)
const getCategoryColor = (category: string): string => {
  // Image outputs (green)
  if (category.includes('to-image')) return '#44ff44';
  if (category === 'upscale' || category === 'edit') return '#44ff44';
  if (category.includes('image') && !category.includes('to-')) return '#44ff44';
  
  // Video outputs (magenta)
  if (category.includes('to-video')) return '#ff44ff';
  if (category.includes('video') && !category.includes('to-')) return '#ff44ff';
  
  // Audio outputs (blue)
  if (category.includes('to-audio')) return '#4499ff';
  if (category.includes('to-speech')) return '#4499ff';
  if (category.includes('audio') && !category.includes('to-')) return '#4499ff';
  if (category.includes('speech')) return '#4499ff';
  
  // 3D outputs (cyan)
  if (category.includes('to-3d') || category.includes('3d')) return '#44ffff';
  
  // Text/Vision/LLM outputs (orange)
  if (category === 'llm' || category === 'vision') return '#ffaa44';
  if (category.includes('to-text') || category.includes('to-json')) return '#ffaa44';
  
  // Utility operations (gray-green)
  if (category === 'removal') return '#88aa88';
  
  return '#aaaaaa'; // Gray - generic/any
};

// Get output type for grouping/sorting
const getCategoryOutputType = (category: string): number => {
  // Return sort priority: lower numbers appear first
  // Image outputs (green)
  if (category.includes('to-image')) return 1;
  if (category === 'upscale' || category === 'edit') return 1;
  if (category.includes('image') && !category.includes('to-')) return 1;
  
  // Video outputs (magenta)
  if (category.includes('to-video')) return 2;
  if (category.includes('video') && !category.includes('to-')) return 2;
  
  // Audio outputs (blue)
  if (category.includes('to-audio')) return 3;
  if (category.includes('to-speech')) return 3;
  if (category.includes('audio') && !category.includes('to-')) return 3;
  if (category.includes('speech')) return 3;
  
  // 3D outputs
  if (category.includes('to-3d') || category.includes('3d')) return 4;
  
  // Text/Vision/LLM outputs (orange)
  if (category === 'llm' || category === 'vision') return 5;
  if (category.includes('to-text') || category.includes('to-json')) return 5;
  
  // Utility operations (removal, etc.)
  if (category === 'removal') return 6;
  
  return 7; // Generic/any
};

export const NodeBar = memo(() => {
  const { 
    endpoints, 
    loadingEndpoints, 
    fetchEndpoints, 
    addNode, 
    visibleEndpoints,
    removeVisibleEndpoint 
  } = useStore();
  
  // Filter endpoints to only show visible ones
  const visibleEndpointsList = endpoints.filter((e) =>
    visibleEndpoints.includes(e.endpoint_id)
  );

  const categories = Array.from(
    new Set(visibleEndpointsList.flatMap((e) => e.category))
  ).sort((a, b) => {
    // Sort by output type first, then alphabetically within each type
    const typeA = getCategoryOutputType(a);
    const typeB = getCategoryOutputType(b);
    if (typeA !== typeB) {
      return typeA - typeB;
    }
    return a.localeCompare(b);
  });

  // Default all categories expanded (including 'utility')
  const [expandedCategories, setExpandedCategories] = useState<Set<string>>(() => {
    return new Set(['utility', ...categories]);
  });
  
  const [contextMenu, setContextMenu] = useState<{
    x: number;
    y: number;
    endpointId: string;
  } | null>(null);

  useEffect(() => {
    fetchEndpoints();
  }, [fetchEndpoints]);

  // Update expanded categories when new categories are loaded
  useEffect(() => {
    setExpandedCategories(prev => {
      const newSet = new Set(prev);
      newSet.add('utility');
      categories.forEach(cat => newSet.add(cat));
      return newSet;
    });
  }, [categories.join(',')]); // eslint-disable-line react-hooks/exhaustive-deps

  const toggleCategory = (category: string) => {
    const newExpanded = new Set(expandedCategories);
    if (newExpanded.has(category)) {
      newExpanded.delete(category);
    } else {
      newExpanded.add(category);
    }
    setExpandedCategories(newExpanded);
  };

  const handleAddEndpoint = (endpoint: Endpoint) => {
    const id = `${endpoint.endpoint_id}-${Date.now()}`;
    
    // Calculate position in center of current viewport
    const state = useStore.getState();
    const viewport = state.viewport;
    
    // Get viewport center (assuming typical viewport size)
    const viewportWidth = window.innerWidth - 400; // Minus sidebars
    const viewportHeight = window.innerHeight;
    const centerX = (-viewport.x + viewportWidth / 2) / viewport.zoom;
    const centerY = (-viewport.y + viewportHeight / 2) / viewport.zoom;
    
    // Add small random offset to avoid stacking
    const x = centerX + (Math.random() - 0.5) * 100;
    const y = centerY + (Math.random() - 0.5) * 100;

    // Get default parameter values from schema
    const defaultParams = getDefaultParameters(endpoint);

    logger.info('Adding AI endpoint node', { 
      endpoint: endpoint.endpoint_id, 
      defaultParams 
    });

    addNode({
      id,
      type: 'aiEndpoint',
      position: { x, y },
      data: { 
        endpoint,
        parameters: defaultParams,
        isExecuting: false,
        selectedPin: 'output', // Default to showing output preview
      },
    });
  };

  const handleContextMenu = (e: React.MouseEvent, endpointId: string) => {
    e.preventDefault();
    setContextMenu({
      x: e.clientX,
      y: e.clientY,
      endpointId,
    });
  };

  const handleRemoveEndpoint = () => {
    if (contextMenu) {
      removeVisibleEndpoint(contextMenu.endpointId);
      setContextMenu(null);
    }
  };

  const closeContextMenu = useCallback(() => {
    setContextMenu(null);
  }, []);

  useEffect(() => {
    if (contextMenu) {
      document.addEventListener('click', closeContextMenu);
      return () => document.removeEventListener('click', closeContextMenu);
    }
  }, [contextMenu, closeContextMenu]);

  const handleAddUtilityNode = (type: 'image' | 'video' | 'textInput') => {
    const id = `${type}-${Date.now()}`;
    
    // Calculate position in center of current viewport
    const state = useStore.getState();
    const viewport = state.viewport;
    
    // Get viewport center
    const viewportWidth = window.innerWidth - 400; // Minus sidebars
    const viewportHeight = window.innerHeight;
    const centerX = (-viewport.x + viewportWidth / 2) / viewport.zoom;
    const centerY = (-viewport.y + viewportHeight / 2) / viewport.zoom;
    
    // Add small random offset to avoid stacking
    const x = centerX + (Math.random() - 0.5) * 100;
    const y = centerY + (Math.random() - 0.5) * 100;

    logger.info('Adding utility node', { type });

    const nodeData = {
      image: { items: [] },
      video: { items: [] },
      textInput: { value: '', label: 'Text Input' },
    };

    addNode({
      id,
      type,
      position: { x, y },
      data: nodeData[type],
    });
  };

  const isUtilityExpanded = expandedCategories.has('utility');

  return (
    <>
      <div className={styles.contextMenu}>
        <h2 className={styles.contextMenuHeader}>Node Palette</h2>

        {/* Utility section as collapsible category */}
        <div className={styles.categorySection}>
          <div
            className={`${styles.categoryTitle} ${isUtilityExpanded ? styles.active : ''}`}
            onClick={() => toggleCategory('utility')}
            style={{ color: getCategoryColor('utility') }}
          >
            <span>utility</span>
            <span>{isUtilityExpanded ? '▼' : '▶'}</span>
          </div>

          {isUtilityExpanded && (
            <div className={styles.endpointList}>
              <div
                className={styles.endpointItem}
                onClick={() => handleAddUtilityNode('textInput')}
                title="Text input node for prompts and text data"
              >
                <div className={styles.endpointItemTitle}>Text Input</div>
              </div>
              <div
                className={styles.endpointItem}
                onClick={() => handleAddUtilityNode('image')}
                title="Image input node for uploading and managing images"
              >
                <div className={styles.endpointItemTitle}>Image</div>
              </div>
              <div
                className={styles.endpointItem}
                onClick={() => handleAddUtilityNode('video')}
                title="Video input node for uploading and managing videos"
              >
                <div className={styles.endpointItemTitle}>Video</div>
              </div>
            </div>
          )}
        </div>

        {loadingEndpoints && <div className={styles.loading}>Loading endpoints...</div>}

        {categories.map((category) => {
          const categoryEndpoints = visibleEndpointsList.filter((e) =>
            e.category.includes(category)
          );
          const isExpanded = expandedCategories.has(category);
          const categoryColor = getCategoryColor(category);

          return (
            <div key={category} className={styles.categorySection}>
              <div
                className={`${styles.categoryTitle} ${isExpanded ? styles.active : ''}`}
                onClick={() => toggleCategory(category)}
                style={{ color: categoryColor }}
              >
                <span>{category}</span>
                <span>{isExpanded ? '▼' : '▶'}</span>
              </div>

              {isExpanded && (
                <div className={styles.endpointList}>
                  {categoryEndpoints.map((endpoint) => {
                    const cost = getEndpointCostDisplay(endpoint.endpoint_id);
                    return (
                      <div
                        key={endpoint._id}
                        className={styles.endpointItem}
                        onClick={() => handleAddEndpoint(endpoint)}
                        onContextMenu={(e) => handleContextMenu(e, endpoint.endpoint_id)}
                        title={endpoint.description}
                      >
                        <div className={styles.endpointItemTitle}>
                          {endpoint.title}
                        </div>
                        {cost && (
                          <div className={styles.endpointCost}>
                            {cost}
                          </div>
                        )}
                      </div>
                    );
                  })}
                </div>
              )}
            </div>
          );
        })}
      </div>

      {contextMenu && (
        <div
          className={styles.contextMenuOverlay}
          style={{
            position: 'fixed',
            left: contextMenu.x,
            top: contextMenu.y,
          }}
        >
          <div className={styles.contextMenuItem} onClick={handleRemoveEndpoint}>
            Remove from Node Palette
          </div>
        </div>
      )}
    </>
  );
});

NodeBar.displayName = 'NodeBar';
