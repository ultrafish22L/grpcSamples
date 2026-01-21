import { memo, useState, useMemo } from 'react';
import { useStore } from '../../store/useStore';
import { Endpoint } from '../../types';
import styles from './AddNodeDialog.module.css';

interface AddNodeDialogProps {
  onClose: () => void;
}

export const AddNodeDialog = memo(({ onClose }: AddNodeDialogProps) => {
  const { endpoints, visibleEndpoints, addVisibleEndpoint } = useStore();
  const [searchTerm, setSearchTerm] = useState('');
  const [expandedCategories, setExpandedCategories] = useState<Set<string>>(new Set());

  const filteredEndpoints = useMemo(() => {
    if (!searchTerm) return endpoints;
    const term = searchTerm.toLowerCase();
    return endpoints.filter(
      (e) =>
        e.title.toLowerCase().includes(term) ||
        e.endpoint_id.toLowerCase().includes(term) ||
        e.vendor.toLowerCase().includes(term) ||
        e.category.some((cat) => cat.toLowerCase().includes(term))
    );
  }, [endpoints, searchTerm]);

  const categories = useMemo(() => {
    return Array.from(new Set(filteredEndpoints.flatMap((e) => e.category))).sort();
  }, [filteredEndpoints]);

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
    addVisibleEndpoint(endpoint.endpoint_id);
  };

  const isEndpointAdded = (endpointId: string) => {
    return visibleEndpoints.includes(endpointId);
  };

  return (
    <div className={styles.overlay} onClick={onClose}>
      <div className={styles.dialog} onClick={(e) => e.stopPropagation()}>
        <div className={styles.header}>
          <h3>Add AI Model to Node Palette</h3>
          <button className={styles.closeButton} onClick={onClose}>
            ×
          </button>
        </div>

        <div className={styles.searchBar}>
          <input
            type="text"
            placeholder="Search endpoints..."
            value={searchTerm}
            onChange={(e) => setSearchTerm(e.target.value)}
            autoFocus
          />
        </div>

        <div className={styles.content}>
          {categories.length === 0 ? (
            <div className={styles.emptyMessage}>No endpoints found</div>
          ) : (
            categories.map((category) => {
              const categoryEndpoints = filteredEndpoints.filter((e) =>
                e.category.includes(category)
              );
              const isExpanded = expandedCategories.has(category);

              return (
                <div key={category} className={styles.categorySection}>
                  <div
                    className={`${styles.categoryTitle} ${isExpanded ? styles.active : ''}`}
                    onClick={() => toggleCategory(category)}
                  >
                    <span>{category}</span>
                    <span className={styles.categoryCount}>
                      {categoryEndpoints.length} {isExpanded ? '▼' : '▶'}
                    </span>
                  </div>

                  {isExpanded && (
                    <div className={styles.endpointList}>
                      {categoryEndpoints.map((endpoint) => {
                        const isAdded = isEndpointAdded(endpoint.endpoint_id);
                        return (
                          <div
                            key={endpoint._id}
                            className={`${styles.endpointItem} ${isAdded ? styles.added : ''}`}
                            onClick={() => !isAdded && handleAddEndpoint(endpoint)}
                          >
                            <div className={styles.endpointInfo}>
                              <div className={styles.endpointTitle}>{endpoint.title}</div>
                              <div className={styles.endpointVendor}>{endpoint.vendor}</div>
                            </div>
                            {isAdded && (
                              <div className={styles.addedBadge}>✓ Added</div>
                            )}
                          </div>
                        );
                      })}
                    </div>
                  )}
                </div>
              );
            })
          )}
        </div>

        <div className={styles.footer}>
          <div className={styles.stats}>
            {visibleEndpoints.length} nodes in Node Palette
          </div>
          <button onClick={onClose}>Done</button>
        </div>
      </div>
    </div>
  );
});

AddNodeDialog.displayName = 'AddNodeDialog';
