// server.js
const http = require('http');
const fs = require('fs');
const path = require('path');
const url = require('url');
const querystring = require('querystring');

// Допоміжна функція для надсилання JSON
function sendJSON(res, statusCode, data) {
  res.writeHead(statusCode, { 'Content-Type': 'application/json' });
  res.end(JSON.stringify(data));
}

// a. Створення сервера
const server = http.createServer((req, res) => {
  const parsedUrl = url.parse(req.url, true);
  const pathname = parsedUrl.pathname;
  const method = req.method;

  // b. Надсилання заголовків (приклад: кастомні заголовки)
  if (pathname === '/headers') {
    res.writeHead(200, {
      'Content-Type': 'text/plain',
      'X-Custom-Header': 'MyValue',
      'Access-Control-Allow-Origin': '*'
    });
    res.end('Headers sent successfully');
    return;
  }

  // c. Маршрутизація
  if (method === 'GET' && pathname === '/product') {
    // Завдання варіанту: JSON API
    const product = {
      name: 'Ноутбук Lenovo IdeaPad 3',
      price: 24999,
      category: 'Електроніка'
    };
    sendJSON(res, 200, product);
    return;
  }

  // d. Переадресація (301 Moved Permanently)
  if (pathname === '/old-page') {
    res.writeHead(301, { Location: '/new-page' });
    res.end();
    return;
  }

  if (pathname === '/new-page') {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Це нова сторінка');
    return;
  }

  // e. Надсилання файлів
  if (pathname === '/download') {
    const filePath = path.join(__dirname, 'test.txt');
    fs.readFile(filePath, (err, data) => {
      if (err) {
        res.writeHead(404);
        res.end('File not found');
        return;
      }
      res.writeHead(200, {
        'Content-Type': 'text/plain',
        'Content-Disposition': 'attachment; filename="test.txt"'
      });
      res.end(data);
    });
    return;
  }

  // f. Отримання даних від клієнта (GET запити з query параметрами)
  if (method === 'GET' && pathname === '/search') {
    const query = parsedUrl.query;
    sendJSON(res, 200, { received: query, message: 'GET data received' });
    return;
  }

  // g. Відправлення та обробка форм (POST)
  if (method === 'POST' && pathname === '/submit-form') {
    let body = '';
    req.on('data', chunk => {
      body += chunk.toString();
    });
    req.on('end', () => {
      const parsedData = querystring.parse(body);
      sendJSON(res, 200, { formData: parsedData, message: 'Form submitted' });
    });
    return;
  }

  // Головна сторінка з HTML формою
  if (pathname === '/' || pathname === '/index.html') {
    const html = `
<!DOCTYPE html>
<html>
<head>
  <title>Node.js Приклади</title>
  <meta charset="utf-8">
</head>
<body>
  <h1>Тестування API та форм</h1>
  
  <h2>Отримати продукт (JSON)</h2>
  <button onclick="fetch('/product').then(r=>r.json()).then(d=>alert(JSON.stringify(d)))">
    Отримати /product
  </button>

  <h2>Надіслати форму</h2>
  <form action="/submit-form" method="POST">
    <input type="text" name="username" placeholder="Ім'я" required><br><br>
    <input type="email" name="email" placeholder="Email" required><br><br>
    <button type="submit">Надіслати</button>
  </form>

  <h2>Інші маршрути</h2>
  <ul>
    <li><a href="/headers">/headers</a> - кастомні заголовки</li>
    <li><a href="/old-page">/old-page</a> - переадресація</li>
    <li><a href="/download">/download</a> - завантажити файл</li>
    <li><a href="/search?name=test&category=book">/search</a> - GET параметри</li>
  </ul>

  <script>
    // Тестування переадресації
    fetch('/old-page').then(() => console.log('Redirected'));
  </script>
</body>
</html>`;
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(html);
    return;
  }

  // 404 для невідомих маршрутів
  res.writeHead(404, { 'Content-Type': 'text/plain' });
  res.end('Page not found');
});

// Запуск сервера
const PORT = 3000;
server.listen(PORT, () => {
  console.log(`Сервер запущено на http://localhost:${PORT}`);
});