import express from 'express';
import cors from 'cors';
import { promises as fs } from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const PORT = parseInt(process.env.PORT || '5001');
const LOG_FILE = path.join(__dirname, '../logs/app.log');

app.use(cors());
app.use(express.json());

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

app.get('/health', (req, res) => {
  res.status(200).json({ status: 'ok' });
});

ensureLogFile().then(() => {
  app.listen(PORT, () => {
    console.log(`OtoyaiWeb server running on http://localhost:${PORT}`);
  });
});
