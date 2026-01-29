const express = require('express');
const path = require('path');
const app = express();
const port = process.env.PORT || 3000;

// --- a) Конвеєр обробки запиту та middleware ---
// Глобальний middleware (реєструється у конвеєрі) — виконується для кожного запиту
app.use((req, res, next) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.url}`);
  // додаємо власне поле до req для наступних middleware/ручок
  req.requestTime = Date.now();
  next(); // передаємо далі в конвеєр
});

// Підключаємо парсери (middleware для body)
app.use(express.json()); // для application/json  (пункт m)
app.use(express.urlencoded({ extended: true })); // для форм x-www-form-urlencoded (пункт j)

// --- e) Статичні файли в Express ---
// Папка "public" — для доступу до css/js/зображень
app.use('/static', express.static(path.join(__dirname, 'public')));

// --- b) Надсилання відповіді ---
app.get('/simple', (req, res) => {
  // res.send — автоматично встановлює Content-Type
  res.send('Проста відповідь: Hello from Express!');
});

// --- c) Функція sendFile ---
app.get('/file', (req, res) => {
  // Надсилаємо статичний HTML-файл
  const filePath = path.join(__dirname, 'public', 'sample.html');
  res.sendFile(filePath, (err) => {
    if (err) {
      console.error('Помилка надсилання файлу:', err);
      res.status(500).send('Помилка сервера при надсиланні файлу');
    }
  });
});

// --- d) Надсилання статусних кодів ---
app.get('/not-found', (req, res) => {
  // Встановлюємо статус і повертаємо повідомлення
  res.status(404).send('Сторінку не знайдено (404)');
});

// --- f) Маршрутизація в Express та g) Символи підстановок ---
// Простий маршрут з параметрами підстановки
app.get('/animals/:type', (req, res) => {
  // Наприклад /animals/cat або /animals/dog
  const { type } = req.params;
  res.send(`Ви запросили тварину: ${type}`);
});

app.get('/files/*', (req, res) => {
  const filePath = req.params[0]; // буде шлях після /files/
  res.send(`Запрошений шлях: ${filePath}`);
});

// --- h) Переадресація ---
app.get('/old-page', (req, res) => {
  // Постійна переадресація на /new-page
  res.redirect(301, '/new-page');
});
app.get('/new-page', (req, res) => res.send('Ви були переадресовані на нову сторінку'));

// --- i) Передача даних у додаток. Параметри рядка запиту ---

app.get('/search', (req, res) => {
  const { q, page = 1 } = req.query; // req.query — об'єкт параметрів рядка запиту
  res.send(`Пошук: q=${q || '(порожнє)'}, сторінка=${page}`);
});

// --- j) POST-запити та відправлення форм ---
// Форми HTML (GET/POST) можна покласти в public/form.html. Тут обробник POST:
app.post('/submit-form', (req, res) => {
  // Якщо форма була відправлена як application/x-www-form-urlencoded — вона буде в req.body
  const body = req.body;
  res.send(`Дані отримано: ${JSON.stringify(body)}`);
});

// --- k) Параметри маршруту (приклад з кількома параметрами) ---
app.get('/users/:userId/books/:bookId', (req, res) => {
  const { userId, bookId } = req.params;
  res.send(`Користувач ${userId} — книга ${bookId}`);
});

// --- l) Об'єкт Router ---
const adminRouter = express.Router();

// Middleware що застосовується лише до adminRouter
adminRouter.use((req, res, next) => {
  console.log('Admin area access');
  // наприклад перевірка авторизації (тут просто заглушка)
  next();
});
adminRouter.get('/', (req, res) => res.send('Admin: головна'));
adminRouter.get('/users', (req, res) => res.send('Admin: список користувачів'));
app.use('/admin', adminRouter); // всі шляхи /admin/* будуть оброблятись adminRouter

// --- m) Робота з данними у форматі JSON ---
app.post('/api/data', (req, res) => {
  // Приклад прийому JSON і відповіді JSON
  const payload = req.body; // express.json() має бути підключено
  if (!payload) return res.status(400).json({ error: 'Немає тіла запиту' });
  // повертаємо об'єкт з додатковим полем serverTime
  res.json({ received: payload, serverTime: new Date().toISOString() });
});

// --- Завдання: маршрут /greeting ---
app.get('/greeting', (req, res) => {
  const greetings = [
    { lang: 'Українська', text: 'Привіт' },
    { lang: 'English', text: 'Hello' },
    { lang: 'Русский', text: 'Привет' },
    { lang: 'Español', text: '¡Hola!' },
    { lang: 'Français', text: 'Bonjour' },
    { lang: 'Deutsch', text: 'Guten Tag' },
    { lang: 'Italiano', text: 'Ciao' },
    { lang: 'Polski', text: 'Cześć' },
    { lang: '中文', text: '你好' },
    { lang: '日本語', text: 'こんにちは' }
  ];


  function pickRandom(arr, n) {
    const copy = arr.slice();
    const result = [];
    n = Math.min(n, copy.length);
    for (let i = 0; i < n; i++) {
      const idx = Math.floor(Math.random() * copy.length);
      result.push(copy.splice(idx, 1)[0]);
    }
    return result;
  }

  const chosen = pickRandom(greetings, 3);

  const html = `<!doctype html>
  <html>
    <head>
      <meta charset="utf-8">
      <title>Greeting</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <link rel="stylesheet" href="/static/styles.css">
    </head>
    <body>
      <main>
        <h1>Вітання різними мовами</h1>
        <p>Випадкові привітання:</p>
        <ul>
          ${chosen.map(g => `<li><strong>${g.text}</strong> — <em>${g.lang}</em></li>`).join('\n')}
        </ul>
        <p>Час відповіді сервера: ${new Date(req.requestTime).toLocaleString()}</p>
        <p><a href="/">На головну</a></p>
      </main>
    </body>
  </html>`;

  res.send(html);
});
// --- Головна сторінка з посиланнями на приклади ---
app.get('/', (req, res) => {
  res.send(`
    <h2>Express приклади</h2>
    <ul>
      <li><a href="/simple">/simple</a></li>
      <li><a href="/file">/file (sendFile)</a></li>
      <li><a href="/not-found">/not-found (404)</a></li>
      <li><a href="/animals/cat">/animals/cat (params)</a></li>
      <li><a href="/files/path/to/my.txt">/files/* (wildcard)</a></li>
      <li><a href="/old-page">/old-page (redirect)</a></li>
      <li><a href="/search?q=express&page=2">/search?q=express&page=2</a></li>
      <li><a href="/greeting">/greeting (завдання)</a></li>
      <li><a href="/admin">/admin (Router)</a></li>
    </ul>
    
  `);
});

// --- Обробник помилок (останній middleware у конвеєрі) ---
app.use((err, req, res, next) => {
  console.error('Global error handler:', err);
  res.status(500).send('Внутрішня помилка сервера');
});

app.listen(port, () => console.log(`Server started on http://localhost:${port}`));

// не забудь http://localhost:3000/static/example.html