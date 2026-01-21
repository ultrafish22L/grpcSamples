import express from 'express';
import cors from 'cors';
import axios from 'axios';
import { promises as fs } from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const PORT = parseInt(process.env.PORT || '5001');
const LOG_FILE = path.join(__dirname, '../logs/app.log');

const OTOY_API_BASE = 'https://play.otoy.ai/api';

app.use(cors());
app.use(express.json({ limit: '50mb' })); // Increased limit for base64 images/videos

async function ensureLogFile() {
  try {
    await fs.access(LOG_FILE);
  } catch {
    await fs.mkdir(path.dirname(LOG_FILE), { recursive: true });
    await fs.writeFile(LOG_FILE, '');
  }
}

app.post('/api/log', async (req, res) => {
  try {
    const { level, message, timestamp, data } = req.body;
    const logEntry = `[${timestamp}] ${level}: ${message}${
      data ? ` | ${JSON.stringify(data)}` : ''
    }\n`;

    await fs.appendFile(LOG_FILE, logEntry);
    res.status(200).json({ success: true });
  } catch (error) {
    console.error('Failed to write log:', error);
    res.status(500).json({ success: false, error: 'Failed to write log' });
  }
});

app.post('/api/log/clear', async (req, res) => {
  try {
    await fs.writeFile(LOG_FILE, '');
    console.log('Logs cleared');
    res.status(200).json({ success: true });
  } catch (error) {
    console.error('Failed to clear logs:', error);
    res.status(500).json({ success: false, error: 'Failed to clear logs' });
  }
});

app.get('/api/log', async (req, res) => {
  try {
    const logs = await fs.readFile(LOG_FILE, 'utf-8');
    res.status(200).send(logs);
  } catch (error) {
    console.error('Failed to read logs:', error);
    res.status(500).json({ success: false, error: 'Failed to read logs' });
  }
});

// OTOY.AI API Proxy Routes
app.get('/otoy-api/endpoints', async (req, res) => {
  try {
    console.log('Proxying request to play.otoy.ai/api/endpoints');
    const response = await axios.get(`${OTOY_API_BASE}/endpoints`, {
      timeout: 30000,
    });

    console.log(`Fetched ${response.data.endpoints?.length || 0} endpoints`);
    res.json(response.data);
  } catch (error: any) {
    console.error('Failed to fetch endpoints:', error.message);
    res.status(error.response?.status || 500).json({
      success: false,
      error: error.message || 'Failed to fetch endpoints',
    });
  }
});

app.post('/otoy-api/execute', async (req, res) => {
  try {
    const { endpoint_id, parameters } = req.body;

    if (!endpoint_id) {
      return res.status(400).json({
        success: false,
        error: 'endpoint_id is required',
      });
    }

    console.log(`Executing endpoint: ${endpoint_id}`);
    console.log(`Parameters:`, JSON.stringify(parameters, null, 2).substring(0, 500));

    // Construct the full endpoint URL
    // Format: https://play.otoy.ai/api/{vendor}/{model_path}
    // Example: https://play.otoy.ai/api/fal-ai/flux-1/dev
    const executeUrl = `${OTOY_API_BASE}/${endpoint_id}`;

    console.log(`POST to: ${executeUrl}`);

    const response = await axios.post(executeUrl, parameters, {
      timeout: 120000, // 2 minute timeout
      headers: {
        'Content-Type': 'application/json',
      },
    });

    console.log(`Execution successful for ${endpoint_id}`);
    res.json({
      success: true,
      data: response.data,
      request_id: response.headers['x-request-id'] || Date.now().toString(),
    });
  } catch (error: any) {
    console.error('Execution failed:', error.message);

    if (error.response) {
      // API returned an error response
      console.error('API Error Response:', error.response.data);
      res.status(error.response.status).json({
        success: false,
        error: error.response.data?.error || error.response.statusText,
        details: error.response.data,
      });
    } else if (error.request) {
      // Request was made but no response received
      res.status(504).json({
        success: false,
        error: 'Gateway timeout - no response from API',
      });
    } else {
      // Error in setting up the request
      res.status(500).json({
        success: false,
        error: error.message || 'Internal server error',
      });
    }
  }
});

app.get('/health', (req, res) => {
  res.status(200).json({ status: 'ok' });
});

ensureLogFile().then(() => {
  app.listen(PORT, () => {
    console.log(`OtoyaiWeb server running on http://localhost:${PORT}`);
    console.log(`OTOY API proxy: http://localhost:${PORT}/otoy-api/*`);
  });
});
