// server.js
const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const path = require('path');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });
const PORT = process.env.PORT || 3000;;

app.use(express.json());
app.use(express.static('.')); // index.html и прочее

// ======================================================
// (а) REST API: Задачи
// ======================================================
let tasks = [
  { id: 1, title: 'Купить хлеб', done: false },
  { id: 2, title: 'Сделать ДЗ', done: true },
];

app.get('/tasks', (req, res) => {
  res.json(tasks);
});

app.post('/tasks', (req, res) => {
  const newTask = { id: Date.now(), ...req.body };
  tasks.push(newTask);
  res.status(201).json(newTask);
});

app.put('/tasks/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const index = tasks.findIndex(t => t.id === id);
  if (index === -1) return res.status(404).json({ error: 'Task not found' });

  tasks[index] = { ...tasks[index], ...req.body };
  res.json(tasks[index]);
});

app.delete('/tasks/:id', (req, res) => {
  const id = parseInt(req.params.id);
  tasks = tasks.filter(t => t.id !== id);
  res.status(204).end();
});

// ======================================================
// (б) WebSocket: Чат
// ======================================================
function broadcast(message) {
  wss.clients.forEach(client => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(message);
    }
  });
}

wss.on('connection', ws => {
  console.log('Новый клиент подключился');
  broadcast(JSON.stringify({ type: 'status', message: 'Новый пользователь вошёл в чат' }));

  ws.on('message', msg => {
    broadcast(JSON.stringify({ type: 'chat', message: msg.toString(), timestamp: new Date().toLocaleTimeString() }));
  });

  ws.on('close', () => {
    broadcast(JSON.stringify({ type: 'status', message: 'Пользователь покинул чат' }));
  });
});

// бітокоін
// ======================================================
// (в) SSE: Цена Bitcoin
// ======================================================

let fetchFn = global.fetch;
if (!fetchFn) {
    // Якщо Node < 18 - встанови node-fetch@2: npm i node-fetch@2
    try {
        fetchFn = require('node-fetch');
    } catch (err) {
        console.error('Fetch не доступний. Якщо у тебе Node < 18, виконай: npm install node-fetch@2');
        process.exit(1);
    }
}
app.use(express.static(path.join(__dirname, 'public')));

// SSE endpoint
app.get('/price-stream', (req, res) => {
    res.writeHead(200, {
        'Content-Type': 'text/event-stream',
        'Cache-Control': 'no-cache',
        Connection: 'keep-alive'
    });

    // початкова коментар-рядок (підтримка SSE)
    res.write(': connected\n\n');

    let closed = false;
    const sendPrice = async () => {
        if (closed) return;
        try {
            const resp = await fetch('https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd');
            const data = await resp.json();
            let usd = null;
            if (data && data.bitcoin && data.bitcoin.usd) {
                usd = data.bitcoin.usd;
            }

            res.write(`data: ${JSON.stringify({ usd })}\n\n`);
        } catch (err) {
            console.error('Fetch price error:', err);
            res.write(`data: ${JSON.stringify({ error: 'fetch error' })}\n\n`);
        }
    };

    sendPrice();
    const iv = setInterval(sendPrice, 10_000); // кожні 10 с

    req.on('close', () => {
        closed = true;
        clearInterval(iv);
    });
});

// ======================================================
// Запуск сервера
// ======================================================
server.listen(PORT, () => {
  console.log(`Сервер: http://localhost:${PORT}`);
});

app.use(express.static(__dirname));
