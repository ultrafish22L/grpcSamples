/**
 * Concurrency Limiter for API Calls
 * Allows controlled parallel processing to balance speed vs stability
 */

class ConcurrencyLimiter {
    constructor(maxConcurrent = 2, delayBetweenBatches = 100) {
        this.maxConcurrent = maxConcurrent;
        this.delayBetweenBatches = delayBetweenBatches;
    }
    
    /**
     * Process items with controlled concurrency
     * @param {Array} items - Items to process
     * @param {Function} processor - Async function to process each item
     * @returns {Promise<Array>} Results array
     */
    async processWithLimit(items, processor) {
        const results = [];
        
        // Process items in batches
        for (let i = 0; i < items.length; i += this.maxConcurrent) {
            const batch = items.slice(i, i + this.maxConcurrent);
            console.log(`🔄 Processing batch ${Math.floor(i/this.maxConcurrent) + 1}: items ${i + 1}-${Math.min(i + this.maxConcurrent, items.length)}`);
            
            // Process batch concurrently
            const batchPromises = batch.map(async (item, index) => {
                try {
                    return await processor(item, i + index);
                } catch (error) {
                    console.error(`💥 Error processing item ${i + index}:`, error);
                    return null; // Continue with other items
                }
            });
            
            const batchResults = await Promise.all(batchPromises);
            results.push(...batchResults);
            
            // Delay between batches to prevent overwhelming Octane
            if (i + this.maxConcurrent < items.length) {
                await new Promise(resolve => setTimeout(resolve, this.delayBetweenBatches));
            }
        }
        
        return results;
    }
}

// Export for use in other modules
window.ConcurrencyLimiter = ConcurrencyLimiter;